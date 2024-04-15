using System.ComponentModel.DataAnnotations;

namespace BookShop.Models
{
    public class AddToCartModel
    {
        public Guid BookId { get; set; }
        public string Title { get; set; }
        public string Author { get; set; }
        public int Amount { get; set; }
        public int Sites { get; set; }
        public string Description { get; set; }
        public string PhotoPath { get; set; }

        [Required(ErrorMessage = "Podaj liczbę egzemplarzy")]
        [Range(0, int.MaxValue, ErrorMessage = "Nieprawidłowa liczba egzemplarzy")]
        public int ChosenAmount { get; set; }
        public double Price { get; set; }
    }
}
