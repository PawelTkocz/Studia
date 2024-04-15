using System.Security.Cryptography;
using System.Text;

namespace BookShop.Models
{
    public class MakeHash
    {
        const int saltBytes = 32;
        public const int iterations = 1000;

        public static string getHash(string password, string salt)
        {
            string hash = password;
            for (int i = 0; i < iterations; i++)
            {
                hash = addSalt(hash, salt);
                hash = oneHashSHA256(hash);
            }
            return hash;
        }

        public static string addSalt(string password, string salt)
        {
            byte[] passwordBytes = Encoding.UTF8.GetBytes(password);
            byte[] saltBytes = Encoding.UTF8.GetBytes(salt);
            byte[] passwordAndSalt = new byte[passwordBytes.Length + saltBytes.Length];
            for (int i = 0; i < password.Length; i++)
                passwordAndSalt[i] = passwordBytes[i];
            for (int i = 0; i < salt.Length; i++)
                passwordAndSalt[password.Length + i] = saltBytes[i];
            return Encoding.Default.GetString(passwordAndSalt);
        }

        public static string getSalt()
        {
            string options = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789";
            Random rnd = new Random();
            byte[] bytes = new byte[saltBytes];
            for (int i = 0; i < saltBytes; i++)
                bytes[i] = Convert.ToByte(options[rnd.Next(options.Length)]);
            return Encoding.Default.GetString(bytes);
        }
        public static string oneHashSHA256(string text)
        {
            using (SHA256 sha256Hash = SHA256.Create())
            {
                byte[] bytes = sha256Hash.ComputeHash(Encoding.UTF8.GetBytes(text));
                StringBuilder builder = new StringBuilder();
                for (int i = 0; i < bytes.Length; i++)
                    builder.Append(bytes[i].ToString("x2"));
                return builder.ToString();
            }
        }
    }
}
