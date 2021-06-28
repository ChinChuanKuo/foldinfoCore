using Microsoft.AspNetCore.Mvc;
using foldinfoCore.Models;

namespace foldinfoCore.Controllers
{
    public class ResendController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH RESEND PASSWORD";
            return View();
        }

        [HttpPost]
        public JsonResult resendUserData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ResendClass().GetResendUserModels(otherData, clientip));
        }
    }
}