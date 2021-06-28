using Microsoft.AspNetCore.Mvc;
using foldinfoCore.Models;

namespace foldinfoCore.Controllers
{
    public class MailistFController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH MAIL 工廠內部通告";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new MailistFClass().GetSearchModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult sItemData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new MailistFClass().GetSItemModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult insertData([FromBody] iFormData iFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new MailistFClass().GetInsertModels(iFormData, clientip));
        }
    }
}