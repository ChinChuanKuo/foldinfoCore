using Microsoft.AspNetCore.Mvc;

namespace foldinfoCore.Controllers
{
    public class BookmarksController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}