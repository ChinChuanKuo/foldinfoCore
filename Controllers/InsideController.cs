using Microsoft.AspNetCore.Mvc;
using foldinfoCore.Models;

namespace foldinfoCore.Controllers
{
    public class InsideController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH 工廠內部通告List";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new InsideClass().GetSearchModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult filterData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new InsideClass().GetFilterModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult scrollData([FromBody] sScroData sScroData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new InsideClass().GetScrollModels(sScroData, clientip));
        }

        [HttpPost]
        public JsonResult sRecordData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new InsideClass().GetSRecordModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult sFiltCordData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new InsideClass().GetSFiltCordModels(otherData, clientip, userAgent));
        }

        [HttpPost]
        public JsonResult sFilterData([FromBody] sFiltData sFiltData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new InsideClass().GetSFilterModels(sFiltData, clientip));
        }

        [HttpPost]
        public JsonResult clearData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new InsideClass().GetClearModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sItemData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new InsideClass().GetSItemModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sFileData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new InsideClass().GetSFileModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sGrotoData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new InsideClass().GetSGrotoModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sActionData([FromBody] sRowsData sRowsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new InsideClass().GetSActionModels(sRowsData, clientip));
        }


        [HttpPost]
        public JsonResult insertData([FromBody] iSirmsData iSirmsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new InsideClass().GetInsertModels(iSirmsData, clientip));
        }

        [HttpPost]
        public JsonResult sendData([FromBody] iSirmsData iSirmsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new InsideClass().GetSendModels(iSirmsData, clientip));
        }
    }
}