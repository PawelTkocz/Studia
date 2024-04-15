using System.ComponentModel.DataAnnotations;

namespace BookShop.Models
{
    public class CartModel
    {
        [Key]
        public Guid Id { get; set; }
        public Guid UserId { get; set; }
        public Guid BookId { get; set; }
        public int Amount { get; set; }
        public DateTime Date { get; set; } 
    }
}
