using Microsoft.AspNetCore.Mvc;
using FOLDINFOCore.Models;

namespace FOLDINFOCore.Controllers
{
    public class CodeController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH CODING";
            return View();
        }

        [HttpPost]
        public JsonResult codeUserData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new CodeClass().GetCodeUserModels(otherData, clientip));
        }
    }
}
