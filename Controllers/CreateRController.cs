using Microsoft.AspNetCore.Mvc;
using foldinfoCore.Models;

namespace foldinfoCore.Controllers
{
    public class CreateRController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH CREATE 品異單";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateRClass().GetSearchModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult sGroupData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateRClass().GetSGroupModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult sWorknoData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateRClass().GetSWorknoModels(otherData, clientip));
        }

        [HttpPost]
        [System.Obsolete]
        public JsonResult sXpsData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateRClass().GetSXpsModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult sPnData([FromBody] sRowsData sRowsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateRClass().GetSPnModels(sRowsData, clientip));
        }

        [HttpPost]
        public JsonResult sIssusData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateRClass().GetSIssueModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult insertData([FromBody] iIconData iIconData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateRClass().GetInsertModels(iIconData, clientip));
        }

        [HttpPost]
        public JsonResult sendData([FromBody] iIconData iIconData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateRClass().GetSendModels(iIconData, clientip));
        }

        [HttpPost]
        public JsonResult downloadData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new CreateRClass().GetDownloadModels(otherData, clientip, userAgent));
        }
    }
}