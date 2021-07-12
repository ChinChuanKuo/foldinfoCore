using Microsoft.AspNetCore.Mvc;
using foldinfoCore.Models;

namespace foldinfoCore.Controllers
{
    public class SendistRController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH SEND 品異單";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SendistRClass().GetSearchModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult addData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SendistRClass().GetAddModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult sGroupData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SendistRClass().GetSGroupModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult insertData([FromBody] iItemsData iItemsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SendistRClass().GetInsertModels(iItemsData, clientip));
        }
    }
}