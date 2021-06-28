using Microsoft.AspNetCore.Mvc;
using foldinfoCore.Models;

namespace foldinfoCore.Controllers
{
    public class LoginController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH LOGIN";
            return View();
        }

        [HttpPost]
        public JsonResult checkUserData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new LoginClass().GetUserModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult loginUserData([FromBody] loginData loginData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new LoginClass().GetLoginModels(loginData, clientip, userAgent));
        }
    }
}