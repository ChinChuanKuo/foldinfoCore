using FOLDINFOCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace FOLDINFOCore.Controllers
{
    public class SignlistIController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH SIGNUP ISO三階文件";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistIClass().GetSearchModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sendData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistIClass().GetSSendModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult backData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistIClass().GetSBackModels(dFormData, clientip));
        }
    }
}