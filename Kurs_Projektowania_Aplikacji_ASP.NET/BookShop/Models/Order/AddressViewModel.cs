using System.ComponentModel.DataAnnotations;

namespace BookShop.Models.Order
{
    public class AddressViewModel
    {
        [Required(ErrorMessage = "Podaj kraj")]
        public string Country { get; set; }

        [Required(ErrorMessage = "Podaj miasto")]
        public string City { get; set; }

        [Required(ErrorMessage = "Podaj ulicę")]
        public string Street { get; set; }

        [Required(ErrorMessage = "Podaj numer domu")]
        public string StreetNumber { get; set; }
    }
}
