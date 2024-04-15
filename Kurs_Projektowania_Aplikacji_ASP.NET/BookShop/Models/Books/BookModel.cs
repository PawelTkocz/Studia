using System.ComponentModel.DataAnnotations;

namespace BookShop.Models
{
    public class BookModel
    {
        [Key]
        public Guid Id { get; set; }
        public string PhotoPath { get; set; }
        public string Title { get; set; }
        public string Author { get; set; }
        public int Amount { get; set; }
        public int Sites { get; set; }
        public string Description { get; set; }
        public double Price { get; set; }
    }
}
