using foldinfoCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace foldinfoCore.Controllers
{
    public class SignlistController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH 簽核列表";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistClass().GetSearchModels(userData, clientip));
        }
    }
}