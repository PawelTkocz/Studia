namespace BookShop.Models.Order
{
    public class OrderDetailsViewModel
    {
        public DateTime Date { get; set; }
        public string Country { get; set; }
        public string City { get; set; }
        public string Street { get; set; }
        public string StreetNumber { get; set; }
        public List<CartItemViewModel> Items { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public string Email { get; set; }
    }
}
