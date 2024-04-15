using BookShop.Data;
using BookShop.Models;
using BookShop.Models.Order;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Diagnostics;
using System.Security.Claims;

namespace BookShop.Controllers
{
    public class HomeController : Controller
    {
        private readonly AppDbContext appDbContext;

        public HomeController(AppDbContext appDbContext)
        {
            this.appDbContext = appDbContext;
        }

        public Guid getUserGuid() {
            string? userGuidString = User.Claims.FirstOrDefault(c => c.Type == ClaimTypes.NameIdentifier)?.Value;
            if (userGuidString == null)
                return Guid.Empty;
            return new Guid(userGuidString);
        }
        public async Task<IActionResult> Index()
        {
            var books = await appDbContext.BookTable.ToListAsync();
            return View(books);
        }

        [HttpGet]
        public async Task<IActionResult> Details(Guid id)
        {
            var book = await appDbContext.BookTable.FirstOrDefaultAsync(x => x.Id == id);

            if (book != null)
            {
                int amount = 0;
                Guid userGuid = getUserGuid();
                if (userGuid != Guid.Empty)
                {
                    var item = await appDbContext.CartTable.FirstOrDefaultAsync(x => x.UserId == userGuid && x.BookId == book.Id);
                    if (item != null)
                        amount = item.Amount;
                }

                var viewModel = new AddToCartModel()
                {
                    BookId = book.Id,
                    Title = book.Title,
                    Author = book.Author,
                    Amount = book.Amount,
                    Sites = book.Sites,
                    Description = book.Description,
                    PhotoPath = book.PhotoPath,
                    ChosenAmount = amount,
                    Price = book.Price
                };
                return await Task.Run(() => View("Details", viewModel));
            }
            return RedirectToAction("Index");
        }

        [HttpPost]
        public async Task<IActionResult> Details(AddToCartModel model)
        {
            if (!ModelState.IsValid)
                return View(model);

            var book = await appDbContext.BookTable.FirstOrDefaultAsync(x => x.Id == model.BookId);
            if (book != null)
            {
                Guid userGuid = getUserGuid();
                if (userGuid == Guid.Empty)
                    return RedirectToAction("Index");

                var item = await appDbContext.CartTable.FirstOrDefaultAsync(x => x.UserId == userGuid && x.BookId == book.Id);
                if (item != null)
                {
                    //w koszyku tego użytkownika już jest ta książka
                    if(model.ChosenAmount == 0)
                        appDbContext.CartTable.Remove(item);
                    else
                    {
                        item.Amount = model.ChosenAmount;
                        item.Date = DateTime.UtcNow;
                    }
                    await appDbContext.SaveChangesAsync();
                }
                else if(model.ChosenAmount != 0)
                {
                    var cartItem = new CartModel
                    {
                        Id = Guid.NewGuid(),
                        UserId = userGuid,
                        BookId = model.BookId,
                        Amount = model.ChosenAmount,
                        Date = DateTime.UtcNow
                    };

                    await appDbContext.CartTable.AddAsync(cartItem);
                    await appDbContext.SaveChangesAsync();
                }
                return RedirectToAction("Details", new { id = model.BookId });
            }
            return RedirectToAction("Index");
        }

        [Authorize]
        public async Task<IActionResult> SeeCart()
        {
            var items = await appDbContext.CartTable.ToListAsync();
            Guid userGuid = getUserGuid();
            if (userGuid == Guid.Empty)
                return RedirectToAction("Index");
            var filtered = items.FindAll(e => e.UserId == userGuid);

            var list = new List<CartItemViewModel>();
            foreach (var item in filtered)
            {
                var book = await appDbContext.BookTable.FirstOrDefaultAsync(x => x.Id == item.BookId);
                if(book != null)
                {
                    list.Add(new CartItemViewModel
                    {
                        Id = item.Id,
                        BookId = item.BookId,
                        PhotoPath = book.PhotoPath,
                        Title = book.Title,
                        Author = book.Author,
                        Amount = item.Amount,
                        Price = item.Amount * book.Price
                    });
                }
            }
            return View(list);
        }

        [Authorize]
        public async Task<IActionResult> DeleteFromCart(Guid Id)
        {
            var item = await appDbContext.CartTable.FirstOrDefaultAsync(x => x.Id == Id);
            if (item != null)
            {
                appDbContext.CartTable.Remove(item);
                await appDbContext.SaveChangesAsync();
            }
            return RedirectToAction("SeeCart");
        }

        [Authorize]
        [HttpGet]
        public IActionResult GetAddress()
        {
            AddressViewModel model = new AddressViewModel();
            return View(model);
        }

        [Authorize]
        [HttpPost]
        public async Task<IActionResult> GetAddress(AddressViewModel model)
        {
            if (!ModelState.IsValid)
                return View(model);

            var items = await appDbContext.CartTable.ToListAsync();
            Guid userGuid = getUserGuid();
            if (userGuid == Guid.Empty)
                return RedirectToAction("Index");
            var filtered = items.FindAll(e => e.UserId == userGuid);

            var problems = new List<CartItemViewModel>();
            foreach (var item in filtered)
            {
                var book = await appDbContext.BookTable.FirstOrDefaultAsync(x => x.Id == item.BookId);
                if (book != null && book.Amount < item.Amount)
                    problems.Add(new CartItemViewModel
                        {
                            PhotoPath = book.PhotoPath,
                            Title = book.Title,
                            Author = book.Author,
                        });
            }
            if(problems.Count > 0)
                return await Task.Run(() => View("Problem", problems));

            var orderModel = new OrderModel
            {
                OrderId = Guid.NewGuid(),
                UserId = userGuid,
                Date = DateTime.UtcNow,
                Country = model.Country,
                City = model.City,
                Street = model.Street,
                StreetNumber = model.StreetNumber
            };

            await appDbContext.OrderTable.AddAsync(orderModel);

            foreach (var item in filtered)
            {
                var book = await appDbContext.BookTable.FirstOrDefaultAsync(x => x.Id == item.BookId);
                if (book != null)
                {
                    OrderedBooksModel orderedBooksModel = new OrderedBooksModel
                    {
                        OrderedBookId = Guid.NewGuid(),
                        OrderId = orderModel.OrderId,
                        BookId = item.BookId,
                        Number = item.Amount,
                        Price = item.Amount * book.Price
                    };
                    await appDbContext.OrderedBooksTable.AddAsync(orderedBooksModel);
                    appDbContext.CartTable.Remove(item);
                    book.Amount -= item.Amount;
                }
            }

            await appDbContext.SaveChangesAsync();
            return RedirectToAction("List", "Order");
        }
    
        [HttpPost]
        public async Task<IActionResult> Search(string s)
        {
            if(s != null)
            {
                string searchWord = s.ToLower();
                var books = await appDbContext.BookTable.ToListAsync();
                var filtered = new List<BookModel>();
                foreach (var book in books)
                {
                    if (book.Title.ToLower().Contains(searchWord) || 
                        book.Author.ToLower().Contains(searchWord) || 
                        book.Description.ToLower().Contains(searchWord))
                        filtered.Add(book);
                }
                return await Task.Run(() => View("Index", filtered));
            }
            return RedirectToAction("Index");
        }
    }
}