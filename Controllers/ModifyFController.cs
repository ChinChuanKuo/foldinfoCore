using Microsoft.AspNetCore.Mvc;

namespace foldinfoCore.Controllers
{
    public class ModifyFController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH MODIFY 工廠內部通告";
            return View();
        }
    }
}