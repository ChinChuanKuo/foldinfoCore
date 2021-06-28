using Microsoft.AspNetCore.Mvc;

namespace foldinfoCore.Controllers
{
    public class ModifyRController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH MODIFY 品異單";
            return View();
        }
    }
}