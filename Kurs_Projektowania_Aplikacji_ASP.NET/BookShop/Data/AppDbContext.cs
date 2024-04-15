using BookShop.Models;
using Microsoft.EntityFrameworkCore;

namespace BookShop.Data
{
    public class AppDbContext : DbContext
    {
        public AppDbContext(DbContextOptions options) : base(options)
        {
        }

        public DbSet<UserModel> UserTable { get; set; }
        public DbSet<PasswordModel> PasswordTable { get; set; }
        public DbSet<BookModel> BookTable { get; set; }
        public DbSet<OrderModel> OrderTable { get; set; }
        public DbSet<CartModel> CartTable { get; set; }
        public DbSet<OrderedBooksModel> OrderedBooksTable { get; set; }
    }
}
