using Microsoft.AspNetCore.Mvc;
using FOLDINFOCore.Models;

namespace FOLDINFOCore.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH 品異單List";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetSearchModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult filterData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetFilterModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult scrollData([FromBody] sDesoData sDesoData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetScrollModels(sDesoData, clientip));
        }

        [HttpPost]
        public JsonResult sRecordData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetSRecordModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult sFiltDateData([FromBody] sFidtData sFidtData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new HomeClass().GetSFiltDateModels(sFidtData, clientip, userAgent));
        }

        [HttpPost]
        public JsonResult sFilterData([FromBody] sDeftData sDeftData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetSFilterModels(sDeftData, clientip));
        }

        [HttpPost]
        public JsonResult clearData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetClearModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult addData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetAddModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult removeData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetRemoveModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sItemData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetSItemModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sFileData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetSFileModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult closeData([FromBody] sRowsData sRowsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetCloseModels(sRowsData, clientip));
        }

        [HttpPost]
        public JsonResult insertData([FromBody] iFormsData iFormsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetInsertModels(iFormsData, clientip));
        }

        [HttpPost]
        public JsonResult sendData([FromBody] iFormsData iFormsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetSendModels(iFormsData, clientip));
        }

        [HttpPost]
        public JsonResult stageData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new HomeClass().GetStageModels(dFormData, clientip));

        }
    }
}