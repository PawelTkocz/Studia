using System.ComponentModel.DataAnnotations;

namespace BookShop.Models
{
    public class OrderModel
    {
        [Key]
        public Guid OrderId { get; set; }

        public Guid UserId { get; set; }

        public DateTime Date { get; set; }
        public string Country { get; set; }
        public string City { get; set; }
        public string Street { get; set; }
        public string StreetNumber { get; set; }
    }
}
