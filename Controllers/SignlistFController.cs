using foldinfoCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace foldinfoCore.Controllers
{
    public class SignlistFController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH SIGNUP 工廠內部通告";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistFClass().GetSearchModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sFileData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistFClass().GetSFileModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sGrotoData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistFClass().GetSGrotoModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sendData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistFClass().GetSSendModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult backData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistFClass().GetSBackModels(dFormData, clientip));
        }
    }
}