using Microsoft.AspNetCore.Mvc;
using FOLDINFOCore.Models;

namespace FOLDINFOCore.Controllers
{
    public class MailistIController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH MAIL ISO三階文件";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new MailistIClass().GetSearchModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult sItemData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new MailistIClass().GetSItemModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult insertData([FromBody] iFormData iFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new MailistIClass().GetInsertModels(iFormData, clientip));
        }
    }
}