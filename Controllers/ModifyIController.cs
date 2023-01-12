using Microsoft.AspNetCore.Mvc;

namespace FOLDINFOCore.Controllers
{
    public class ModifyIController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH MODIFY ISO三階文件";
            return View();
        }
    }
}