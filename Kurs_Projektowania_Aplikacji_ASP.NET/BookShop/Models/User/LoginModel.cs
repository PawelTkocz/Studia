using System.ComponentModel.DataAnnotations;

namespace BookShop.Models
{
    public class LoginModel
    {
        [Required(ErrorMessage = "Podaj email")]
        [EmailAddress(ErrorMessage = "Nieprawidłowy adres email")]
        public string Email { get; set; }

        [Required(ErrorMessage = "Podaj hasło")]
        public string Password { get; set; }

        public bool TryAgain { get; set; }
    }
}
