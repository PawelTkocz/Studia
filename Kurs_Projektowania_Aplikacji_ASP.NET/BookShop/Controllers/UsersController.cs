using BookShop.Data;
using BookShop.Models;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Security.Claims;

namespace BookShop.Controllers
{
    public class UsersController : Controller
    {
        private readonly AppDbContext appDbContext;

        public UsersController(AppDbContext appDbContext)
        {
            this.appDbContext = appDbContext;
        }

        [Authorize(Roles = "Admin")]
        public async Task<IActionResult> List()
        {
            var users = await appDbContext.UserTable.ToListAsync();
            return View(users);
        }

        [HttpGet]
        public IActionResult Register()
        {
            if (User.Identity != null && User.Identity.IsAuthenticated)
                return RedirectToAction("Index", "Home");

            var model = new RegisterModel
            {
                EmailUsed = false,
                DifferentPasswords = false,
                PasswordTooShort = false
            };
            return View(model);
        }

        [HttpPost]
        public async Task<IActionResult> Register(RegisterModel model)
        {
            if (!ModelState.IsValid)
                return View(model);

            var user = await appDbContext.UserTable.FirstOrDefaultAsync(x => x.Email == model.Email);
            if (user != null)
            {
                //użytkownik o podanym emailu już istnieje
                model.EmailUsed = true;
                return View(model);
            }
            if (model.Password != model.RepeatedPassword)
            {
                model.DifferentPasswords = true;
                return View(model);
            }
            if (model.Password.Length < 6)
            {
                model.PasswordTooShort = true;
                return View(model);
            }

            var userModel = new UserModel
            {
                Id = Guid.NewGuid(),
                FirstName = model.FirstName,
                LastName = model.LastName,
                Email = model.Email,
            };

            string salt = MakeHash.getSalt();
            string hash = MakeHash.getHash(model.Password, salt);

            var password = new PasswordModel
            {
                UserId = userModel.Id,
                PasswordShortcut = hash,
                Salt = salt,
                HashRounds = MakeHash.iterations,
                Date = DateTime.UtcNow
            };

            await appDbContext.UserTable.AddAsync(userModel);
            await appDbContext.PasswordTable.AddAsync(password);
            await appDbContext.SaveChangesAsync();

            List<Claim> claims = new List<Claim>{
                            new Claim(ClaimTypes.Name, userModel.FirstName + " " + userModel.LastName),
                            new Claim(ClaimTypes.NameIdentifier, userModel.Id.ToString())
                        };

            ClaimsIdentity identity = new ClaimsIdentity(claims, CookieAuthenticationDefaults.AuthenticationScheme);
            ClaimsPrincipal principal = new ClaimsPrincipal(identity);
            await this.HttpContext.SignInAsync(CookieAuthenticationDefaults.AuthenticationScheme, principal);

            return RedirectToAction("Index", "Home");
        }

        [HttpGet]
        public IActionResult Login()
        {
            if (User.Identity != null && User.Identity.IsAuthenticated)
                return RedirectToAction("Index", "Home");

            var model = new LoginModel
            {
                TryAgain = false
            };
            return View(model);
        }

        [HttpPost]
        public async Task<IActionResult> Login(LoginModel model)
        {
            if (!ModelState.IsValid)
                return View(model);

            var user = await appDbContext.UserTable.FirstOrDefaultAsync(x => x.Email == model.Email);

            if (user != null)
            {
                var password = await appDbContext.PasswordTable.FirstOrDefaultAsync(x => x.UserId == user.Id);
                if (password != null)
                {
                    string passwordHash = MakeHash.getHash(model.Password, password.Salt);
                    if (password.PasswordShortcut == passwordHash)
                    {
                        List<Claim> claims = new List<Claim>{
                            new Claim(ClaimTypes.Name, user.FirstName + " " + user.LastName),
                            new Claim(ClaimTypes.NameIdentifier, user.Id.ToString())
                        };
                        if (user.IsAdmin)
                            claims.Add(new Claim(ClaimTypes.Role, "Admin"));
                        ClaimsIdentity identity = new ClaimsIdentity(claims, CookieAuthenticationDefaults.AuthenticationScheme);
                        ClaimsPrincipal principal = new ClaimsPrincipal(identity);
                        await this.HttpContext.SignInAsync(CookieAuthenticationDefaults.AuthenticationScheme, principal);

                        return RedirectToAction("Index", "Home");
                    }
                }
            }
            model.TryAgain = true;
            return View(model);
        }

        [Authorize]
        public async Task<IActionResult> Logout()
        {
            await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
            return RedirectToAction("Index", "Home");
        }

        [Authorize(Roles = "Admin")]
        public async Task<IActionResult> MakeAdmin(Guid UserId)
        {
            var user = await appDbContext.UserTable.FirstOrDefaultAsync(x => x.Id == UserId);
            if (user != null)
            {
                user.IsAdmin = true;
                await appDbContext.SaveChangesAsync();
            }
            return RedirectToAction("List");
        }
    }
}
