using BookShop.Data;
using BookShop.Models;
using BookShop.Models.Order;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Security.Claims;

namespace BookShop.Controllers
{
    public class OrderController : Controller
    {
        private readonly AppDbContext appDbContext;

        public OrderController(AppDbContext appDbContext)
        {
            this.appDbContext = appDbContext;
        }
        public Guid getUserGuid()
        {
            string? userGuidString = User.Claims.FirstOrDefault(c => c.Type == ClaimTypes.NameIdentifier)?.Value;
            if (userGuidString == null)
                return Guid.Empty;
            return new Guid(userGuidString);
        }

        public async Task<double> orderPrice(Guid orderId)
        {
            double sum = 0;
            var items = await appDbContext.OrderedBooksTable.ToListAsync();
            var filtered = items.FindAll(e => e.OrderId == orderId);
            foreach (var item in filtered)
                sum += item.Price;
            return sum;
        }
        
        [Authorize]
        public async Task<IActionResult> List()
        {
            var items = await appDbContext.OrderTable.ToListAsync();
            Guid userGuid = getUserGuid();
            if (userGuid == Guid.Empty)
                return RedirectToAction("Index", "Home");
            var filtered = items.FindAll(e => e.UserId == userGuid);
            return View(filtered);
        }
        
        [Authorize]
        public async Task<IActionResult> Details(Guid Id)
        {
            var order = await appDbContext.OrderTable.FirstOrDefaultAsync(x => x.OrderId == Id);
            if (order != null)
            {
                var items = await appDbContext.OrderedBooksTable.ToListAsync();
                Guid userGuid = getUserGuid();
                if (userGuid == Guid.Empty)
                    return RedirectToAction("List");
                var filtered = items.FindAll(e => e.OrderId == Id);

                var list = new List<CartItemViewModel>();
                foreach (var item in filtered)
                {
                    var book = await appDbContext.BookTable.FirstOrDefaultAsync(x => x.Id == item.BookId);
                    if (book != null)
                    {
                        list.Add(new CartItemViewModel
                        {
                            BookId = item.BookId,
                            PhotoPath = book.PhotoPath,
                            Title = book.Title,
                            Author = book.Author,
                            Amount = item.Number,
                            Price = item.Price
                        });
                    }
                }

                OrderDetailsViewModel orderDetailsViewModel = new OrderDetailsViewModel
                {
                    Date = order.Date,
                    Country = order.Country,
                    City = order.City,
                    Street = order.Street,
                    StreetNumber = order.StreetNumber,
                    Items = list
                };
                return View(orderDetailsViewModel);
            }
            return RedirectToAction("List");
        }

        [Authorize(Roles = "Admin")]
        public async Task<IActionResult> ListAll()
        {
            var items = await appDbContext.OrderTable.ToListAsync();

            var list = new List<UsersOrdersViewModel>();
            foreach (var item in items)
            {
                var user = await appDbContext.UserTable.FirstOrDefaultAsync(x => x.Id == item.UserId);
                if(user != null)
                {
                    list.Add(new UsersOrdersViewModel
                    {
                        OrderId = item.OrderId,
                        UserId = item.UserId,
                        FirstName = user.FirstName,
                        LastName = user.LastName,
                        Email = user.Email,
                        Date = item.Date,
                        Country = item.Country,
                        City = item.City,
                        Street = item.Street,
                        StreetNumber = item.StreetNumber,
                        Price = await orderPrice(item.OrderId)
                    });
                }
            }
            return View(list);
        }

        [Authorize(Roles = "Admin")]
        public async Task<IActionResult> UserDetails(Guid Id)
        {
            var order = await appDbContext.OrderTable.FirstOrDefaultAsync(x => x.OrderId == Id);
            if (order != null)
            {
                var user = await appDbContext.UserTable.FirstOrDefaultAsync(x => x.Id == order.UserId);
                if(user != null)
                {
                    var items = await appDbContext.OrderedBooksTable.ToListAsync();
                    var filtered = items.FindAll(e => e.OrderId == Id);

                    var list = new List<CartItemViewModel>();
                    foreach (var item in filtered)
                    {
                        var book = await appDbContext.BookTable.FirstOrDefaultAsync(x => x.Id == item.BookId);
                        if (book != null)
                        {
                            list.Add(new CartItemViewModel
                            {
                                BookId = item.BookId,
                                PhotoPath = book.PhotoPath,
                                Title = book.Title,
                                Author = book.Author,
                                Amount = item.Number,
                                Price = item.Price
                            });
                        }
                    }

                    OrderDetailsViewModel orderDetailsViewModel = new OrderDetailsViewModel
                    {
                        Date = order.Date,
                        Country = order.Country,
                        City = order.City,
                        Street = order.Street,
                        StreetNumber = order.StreetNumber,
                        Items = list,
                        FirstName = user.FirstName,
                        LastName = user.LastName,
                        Email = user.Email
                    };
                    return View(orderDetailsViewModel);
                }
            }
            return RedirectToAction("List");
        }
    }
}
