using Microsoft.AspNetCore.Mvc;
using foldinfoCore.Models;

namespace foldinfoCore.Controllers
{
    public class CreateIController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH CREATE ISO三階文件";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateIClass().GetSearchModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult sGroupData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateIClass().GetSGroupModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult sModelData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateIClass().GetSModelModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult sCustomData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateIClass().GetSCustomModels(otherData, clientip));
        }


        [HttpPost]
        public JsonResult cCustomData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateIClass().GetCCustomModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult insertData([FromBody] iItemsData iItemsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateIClass().GetInsertModels(iItemsData, clientip));
        }

        [HttpPost]
        public JsonResult sendData([FromBody] iItemsData iItemsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateIClass().GetSendModels(iItemsData, clientip));
        }
    }
}