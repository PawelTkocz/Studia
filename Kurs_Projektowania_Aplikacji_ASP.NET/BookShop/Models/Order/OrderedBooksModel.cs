using System.ComponentModel.DataAnnotations;

namespace BookShop.Models
{
    public class OrderedBooksModel
    {
        [Key]
        public Guid OrderedBookId { get; set; }

        public Guid OrderId { get; set; }
        public Guid BookId { get; set; }
        public int Number { get; set; }
        public double Price { get; set; }
    }
}
