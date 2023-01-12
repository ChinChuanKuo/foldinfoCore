using Microsoft.AspNetCore.Mvc;
using FOLDINFOCore.Models;

namespace FOLDINFOCore.Controllers
{
    public class SignlistRController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH SIGNUP 品異單";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistRClass().GetSearchModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sFileData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistRClass().GetSFileModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sendData([FromBody] iFormData iFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistRClass().GetSSendModels(iFormData, clientip));
        }

        [HttpPost]
        public JsonResult backData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignlistRClass().GetSBackModels(dFormData, clientip));
        }
    }
}