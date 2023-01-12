using Microsoft.AspNetCore.Mvc;
using FOLDINFOCore.Models;

namespace FOLDINFOCore.Controllers
{
    public class SendistFController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH SEND 工廠內部通告";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SendistFClass().GetSearchModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult sGroupData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SendistFClass().GetSGroupModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult insertData([FromBody] iItemsData iItemsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SendistFClass().GetInsertModels(iItemsData, clientip));
        }
    }
}