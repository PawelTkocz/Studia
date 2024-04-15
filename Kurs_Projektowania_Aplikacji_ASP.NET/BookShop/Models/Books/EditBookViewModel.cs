using System.ComponentModel.DataAnnotations;

namespace BookShop.Models
{
    public class EditBookViewModel
    {
        public Guid BookId { get; set; }
        public IFormFile? Photo { get; set; }
        public string PhotoPath { get; set; }

        [Required(ErrorMessage = "Podaj tytuł")]
        public string Title { get; set; }

        [Required(ErrorMessage = "Podaj autora")]
        public string Author { get; set; }

        [Required(ErrorMessage = "Podaj liczbę egzemplarzy")]
        [Range(0, int.MaxValue, ErrorMessage = "Nieprawidłowa liczba egzemplarzy")]
        public int Amount { get; set; }

        [Required(ErrorMessage = "Podaj liczbę stron")]
        [Range(1, int.MaxValue, ErrorMessage = "Nieprawidłowa liczba stron")]
        public int Sites { get; set; }

        [Required(ErrorMessage = "Podaj krótki opis")]
        public string Description { get; set; }

        [Required(ErrorMessage = "Podaj cenę")]
        [Range(0, int.MaxValue, ErrorMessage = "Nieprawidłowa cena")]
        public double? Price { get; set; }

        public bool RepeatedBook { get; set; }
    }
}
