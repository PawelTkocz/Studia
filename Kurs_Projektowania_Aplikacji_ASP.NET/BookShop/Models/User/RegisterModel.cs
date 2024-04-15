using System.ComponentModel.DataAnnotations;

namespace BookShop.Models
{
    public class RegisterModel
    {
        [Required(ErrorMessage = "Podaj imię")]
        public string FirstName { get; set; }

        [Required(ErrorMessage = "Podaj nazwisko")]
        public string LastName { get; set; }

        [Required(ErrorMessage = "Podaj email")]
        [EmailAddress(ErrorMessage = "Nieprawidłowy adres email")]
        public string Email { get; set; }

        [Required(ErrorMessage = "Podaj hasło")]
        public string Password { get; set; }

        [Required(ErrorMessage = "Powtórz hasło")]
        public string RepeatedPassword { get; set; }

        public bool EmailUsed { get; set; }
        public bool DifferentPasswords { get; set; }
        public bool PasswordTooShort { get; set; }
    }
}
