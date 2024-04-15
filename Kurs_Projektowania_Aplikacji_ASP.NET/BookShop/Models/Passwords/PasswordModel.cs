using System.ComponentModel.DataAnnotations;

namespace BookShop.Models
{
    public class PasswordModel
    {
        [Key]
        public Guid UserId { get; set; }
        public string PasswordShortcut { get; set; }
        public string Salt { get; set; }
        public int HashRounds { get; set; }
        public DateTime Date { get; set; }
    }
}
