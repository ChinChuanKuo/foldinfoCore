using Microsoft.AspNetCore.Mvc;
using foldinfoCore.Models;

namespace foldinfoCore.Controllers
{
    public class CreateFController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH CREATE 工廠內部通告";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateFClass().GetSearchModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult sSnnoData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateFClass().GetSSnnoModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult sGroupData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateFClass().GetSGroupModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult sTypeData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateFClass().GetSTypeModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult sWorknoData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateFClass().GetSWorkModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult cWorknoData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateFClass().GetCWorkModels(otherData, clientip));
        }

        [HttpPost]
        [System.Obsolete]
        public JsonResult sXpsData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateFClass().GetSXpsModels(otherData, clientip));
        }

        [HttpPost]
        [System.Obsolete]
        public JsonResult sEcrnoData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateFClass().GetSEcrnoModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult sModelData([FromBody] sRowsData sRowsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateFClass().GetSModelModels(sRowsData, clientip));
        }

        [HttpPost]
        public JsonResult cGrotoData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateFClass().GetCGrotoModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult insertData([FromBody] iSideData iSideData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateFClass().GetInsertModels(iSideData, clientip));
        }

        [HttpPost]
        public JsonResult sendData([FromBody] iSideData iSideData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CreateFClass().GetSendModels(iSideData, clientip));
        }

        [HttpPost]
        public JsonResult downloadData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new CreateFClass().GetDownloadModels(otherData, clientip, userAgent));
        }
    }
}