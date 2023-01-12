using Microsoft.AspNetCore.Mvc;

namespace FOLDINFOCore.Controllers
{
    public class BookmarksController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}