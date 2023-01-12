using Microsoft.AspNetCore.Mvc;

namespace FOLDINFOCore.Controllers
{
    public class OauthController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH BTS";
            return View();
        }
    }
}
