using BookShop.Data;
using BookShop.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace BookShop.Controllers
{
    [Authorize(Roles = "Admin")]
    public class BookController : Controller
    {
        private readonly AppDbContext appDbContext;
        private readonly Microsoft.AspNetCore.Hosting.IHostingEnvironment environment;


        public BookController(Microsoft.AspNetCore.Hosting.IHostingEnvironment environment, AppDbContext appDbContext)
        {
            this.appDbContext = appDbContext;
            this.environment = environment;
        }

        public async Task<IActionResult> List()
        {
            var books = await appDbContext.BookTable.ToListAsync();
            return View(books);
        }

        [HttpGet]
        public IActionResult Add()
        {
            AddBookViewModel model = new AddBookViewModel();
            model.RepeatedBook = false;
            return View(model);
        }

        [HttpPost]
        public async Task<IActionResult> Add(AddBookViewModel model)
        {
            if (!ModelState.IsValid)
                return View(model);

            var book = await appDbContext.BookTable.FirstOrDefaultAsync(x => x.Title == model.Title && x.Author == model.Author);
            if (book != null)
            {
                model.RepeatedBook = true;
                return View(model);
            }

            var photoPath = model.Title + model.Author + ".png";
            var filePath = Path.Combine(environment.ContentRootPath, @"wwwroot/Images", photoPath);
            using var fileStream = new FileStream(filePath, FileMode.Create);
            await model.Photo.CopyToAsync(fileStream);
            fileStream.Close();

            var bookModel = new BookModel
            {
                Id = Guid.NewGuid(),
                PhotoPath = photoPath,
                Title = model.Title,
                Author = model.Author,
                Amount = (int)model.Amount,
                Sites = (int)model.Sites,
                Description = model.Description,
                Price = (double)model.Price
            };

            await appDbContext.BookTable.AddAsync(bookModel);
            await appDbContext.SaveChangesAsync();

            return RedirectToAction("List");
        }

        [HttpGet]
        public async Task<IActionResult> Edit(Guid id)
        {
            var book = await appDbContext.BookTable.FirstOrDefaultAsync(x => x.Id == id);

            if (book != null)
            {
                var viewModel = new EditBookViewModel()
                {
                    BookId = book.Id,
                    Title = book.Title,
                    Author = book.Author,
                    Amount = book.Amount,
                    Sites = book.Sites,
                    Description = book.Description,
                    Photo = null,
                    PhotoPath = book.PhotoPath,
                    Price = book.Price,
                    RepeatedBook = false
                };
                return await Task.Run(() => View("Edit", viewModel));
            }
            return RedirectToAction("List");
        }

        [HttpPost]
        public async Task<IActionResult> Edit(EditBookViewModel model)
        {
            if (!ModelState.IsValid)
                return View(model);

            var book = await appDbContext.BookTable.FindAsync(model.BookId);
            if (book != null)
            {
                if (model.Author != book.Author || model.Title != book.Title)
                {
                    var book2 = await appDbContext.BookTable.FirstOrDefaultAsync(x => x.Title == model.Title && x.Author == model.Author);
                    if (book2 != null)
                    {
                        model.RepeatedBook = true;
                        return View(model);
                    }
                }

                if (model.Photo != null)
                {
                    var filePath = Path.Combine(environment.ContentRootPath, @"wwwroot/Images", model.PhotoPath);
                    System.IO.File.Delete(filePath);
                    var photoPath = model.Title + model.Author + ".png";
                    filePath = Path.Combine(environment.ContentRootPath, @"wwwroot/Images", photoPath);
                    using var fileStream = new FileStream(filePath, FileMode.Create);
                    await model.Photo.CopyToAsync(fileStream);
                    fileStream.Close();
                    book.PhotoPath = photoPath;
                }

                book.Author = model.Author;
                book.Title = model.Title;
                book.Description = model.Description;
                book.Sites = model.Sites;
                book.Amount = model.Amount;
                book.Price = (double)model.Price;

                await appDbContext.SaveChangesAsync();
                return RedirectToAction("List");
            }
            return RedirectToAction("List");
        }

        [HttpGet]
        public async Task<IActionResult> Delete(Guid id)
        {
            var book = await appDbContext.BookTable.FirstOrDefaultAsync(x => x.Id == id);

            if (book != null)
            {
                var viewModel = new EditBookViewModel()
                {
                    BookId = book.Id,
                    Title = book.Title,
                    Author = book.Author,
                    Amount = book.Amount,
                    Sites = book.Sites,
                    Description = book.Description,
                    PhotoPath = book.PhotoPath,
                    Price = book.Price
                };
                return await Task.Run(() => View("Delete", viewModel));
            }
            return RedirectToAction("List");
        }

        [HttpPost]
        public async Task<IActionResult> Delete(EditBookViewModel model)
        {
            var book = await appDbContext.BookTable.FindAsync(model.BookId);
            if (book != null)
            {
                appDbContext.BookTable.Remove(book);
                await appDbContext.SaveChangesAsync();

                var filePath = Path.Combine(environment.ContentRootPath, @"wwwroot/Images", model.PhotoPath);
                System.IO.File.Delete(filePath);

                return RedirectToAction("List");
            }
            return RedirectToAction("List");
        }

        public async Task<IActionResult> Details(Guid id)
        {
            var book = await appDbContext.BookTable.FirstOrDefaultAsync(x => x.Id == id);

            if (book != null)
            {
                var viewModel = new BookModel()
                {
                    Title = book.Title,
                    Author = book.Author,
                    Amount = book.Amount,
                    Sites = book.Sites,
                    Description = book.Description,
                    PhotoPath = book.PhotoPath,
                    Price = book.Price
                };
                return await Task.Run(() => View("Details", viewModel));
            }
            return RedirectToAction("List");
        }
    }
}
