namespace BookShop.Models
{
    public class CartItemViewModel
    {
        public Guid Id { get; set; }
        public Guid BookId { get; set; }
        public string PhotoPath { get; set; }
        public string Title { get; set; }
        public string Author { get; set; }
        public int Amount { get; set; }
        public double Price { get; set; }
    }
}
