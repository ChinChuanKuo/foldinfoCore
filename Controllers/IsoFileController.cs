using Microsoft.AspNetCore.Mvc;
using FOLDINFOCore.Models;

namespace FOLDINFOCore.Controllers
{
    public class IsoFileController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH ISO三階文件List";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetSearchModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult filterData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetFilterModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult scrollData([FromBody] sScroData sScroData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetScrollModels(sScroData, clientip));
        }

        [HttpPost]
        public JsonResult sRecordData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetSRecordModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult sFiltCordData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new IsoFileClass().GetSFiltCordModels(otherData, clientip, userAgent));
        }

        [HttpPost]
        public JsonResult sFilterData([FromBody] sFiltData sFiltData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetSFilterModels(sFiltData, clientip));
        }

        [HttpPost]
        public JsonResult clearData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetClearModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sListData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetSListModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult previousData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetPreviousModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult nextData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetNextModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sItemData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetSItemModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult deleteData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetDeleteModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult orderData([FromBody] iFormData iFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetOrderModels(iFormData, clientip));
        }

        [HttpPost]
        public JsonResult insertData([FromBody] iFormData iFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetInsertModels(iFormData, clientip));
        }

        [HttpPost]
        public JsonResult sendData([FromBody] iFormData iFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IsoFileClass().GetSendModels(iFormData, clientip));
        }
    }
}