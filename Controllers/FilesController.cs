using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using foldinfoCore.App_Code;
using foldinfoCore.Models;

namespace foldinfoCore.Controllers
{
    public class FilesController : Controller
    {
        [HttpPost]
        public async Task<JsonResult> uploadData()
        {
            if (Request.Form.Files.Count > 0)
            {
                string original = Request.Form.Files[0].FileName.Substring(0, Request.Form.Files[0].FileName.LastIndexOf('.')), encryption = new sha256().new256("mssql", "flyfnstring"), extension = Path.GetExtension(Request.Form.Files[0].FileName);
                database database = new database();
                DataTable mainRows = new DataTable();
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@value", extension.Replace(".", "").Trim().ToLower()));
                dbparamlist.Add(new dbparam("@needed", "1"));
                mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.uploadfileform @value,@needed;", dbparamlist);
                switch (mainRows.Rows.Count)
                {
                    case 0:
                        return Json(new sSiteModels() { status = "nodata" });
                }
                if (mainRows.Rows[0]["flImages"].ToString().TrimEnd() == "0" && mainRows.Rows[0]["flVideos"].ToString().TrimEnd() == "0" && mainRows.Rows[0]["flAudios"].ToString().TrimEnd() == "0")
                {
                    return Json(new sSiteModels() { status = "nodata" });
                }
                using (var fileStream = new FileStream($"{database.connectionString("folderFiles")}{original}({encryption}){extension}", FileMode.Create))
                {
                    await Request.Form.Files[0].CopyToAsync(fileStream);
                    return Json(new sSiteModels() { images = mainRows.Rows[0]["flImages"].ToString().TrimEnd() == "1", videos = mainRows.Rows[0]["flVideos"].ToString().TrimEnd() == "1", audios = mainRows.Rows[0]["flAudios"].ToString().TrimEnd() == "1", src = mainRows.Rows[0]["flImages"].ToString().TrimEnd() == "1" && mainRows.Rows[0]["flShowed"].ToString().TrimEnd() == "0" ? $"{mainRows.Rows[0]["original"].ToString().TrimEnd()}({mainRows.Rows[0]["encryption"].ToString().TrimEnd()}){mainRows.Rows[0]["extension"].ToString().TrimEnd()}" : $"{original}({encryption}){extension}", imagePath = database.connectionString("folderHttps"), original = original, encryption = encryption, extension = extension, date = new datetime().sqldate("mssql", "flyfnstring"), status = "istrue" });
                }
            }
            return Json(new sSiteModels() { status = "nodata" });
        }

        [HttpPost]
        public JsonResult websiteData([FromBody] sRowsData sRowsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new FilesClass().GetWebsiteModels(sRowsData, clientip, userAgent));
        }

        [HttpPost]
        public JsonResult downloadData([FromBody] sRowsData sRowsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new FilesClass().GetDownloadModels(sRowsData, clientip, userAgent));
        }

        [HttpPost]
        [System.Obsolete]
        public JsonResult transferData([FromBody] sFileData sFileData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new FilesClass().GetTransferModels(sFileData, clientip));
        }

        [HttpPost]
        public JsonResult totalData([FromBody] sFileData sFileData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new FilesClass().GetTotalModels(sFileData, clientip));
        }

        [HttpPost]
        public JsonResult removeData([FromBody] rFileData rFileData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new FilesClass().GetRemoveModels(rFileData, clientip));
        }

        [HttpPost]
        public JsonResult reviewData([FromBody] dFormData dFormData)
        {
            //string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchreportdeta @id;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return Json(new sDataModels() { status = "nodata" });
            }
            sha256 sha256 = new sha256();
            string folder = sha256.new256("mssql", "flyfnstring"), name = sha256.new256("mssql", "flyfnstring");
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            dbparamlist.Add(new dbparam("@folder", folder));
            dbparamlist.Add(new dbparam("@name", name));
            if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertreviewlog @id,@inoper,@folder,@name;", dbparamlist) != "istrue")
            {
                return Json(new sDataModels() { status = "error" });
            }
            string folderFile = $"{new database().connectionString("folderFiles")}\\html\\{folder}\\", htmlFile = $"{name}.html";
            Directory.CreateDirectory(folderFile);
            using (var fileStream = new FileStream($"{folderFile}{htmlFile}", FileMode.Create))
            {
                using (StreamWriter streamWriter = new StreamWriter(fileStream, Encoding.UTF8))
                {
                    streamWriter.WriteLine($"{ reviewHtmlHead()}<body><div style='margin:0 auto;' class='outside'><div class='together tile'><h1>編輯 品異單/5C Report</h1></div><div class='together subtile'><h3>【Characterize】問題描述</h3></div><div class='together subfield'><div class='datefield inlineDiv'><h4>提出日期</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["postdate"].ToString().TrimEnd())}</div></div><div class='departfield inlineDiv'><h4>提出部門 / 提出者</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["post_group"].ToString().TrimEnd())} / {reviewHtmlBody(mainRows.Rows[0]["postname"].ToString().TrimEnd())}</div></div><div class='floorfield inlineDiv'><h4>生產樓層</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["floor"].ToString().TrimEnd())}</div></div><div class='numfield inlineDiv'><h4>文件編號</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["number"].ToString().TrimEnd())}-{reviewHtmlBody(mainRows.Rows[0]["version"].ToString().TrimEnd())}</div></div></div><div class='together subfield'><div class='datefield inlineDiv'><h4>客戶 / 廠商</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["homepage1"].ToString().TrimEnd())}</div></div><div class='departfield inlineDiv'><div style='width:160px;' class='inlineDiv'><h4>產品規格單/總數量</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["pnumber"].ToString().TrimEnd())}</div></div><div class='inlineDiv'><h4>機種</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd())}</div></div></div><div class='floorfield inlineDiv'><h4>M/B</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["mb"].ToString().TrimEnd())}</div></div><div class='numfield inlineDiv'><h4>品異來源</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["obj"].ToString().TrimEnd())}</div></div></div><div class='together subfield'><div class='datefield inlineDiv'><h4>來源單號/工單</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["worknumber"].ToString().TrimEnd())}</div></div><div class='departfield inlineDiv'><div style='width:160px;' class='inlineDiv'><h4>不良料號</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["pn"].ToString().TrimEnd())}</div></div><div class='inlineDiv'><h4>生產/檢驗數量</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["amount"].ToString().TrimEnd())}</div></div></div><div class='floorfield inlineDiv'><h4>不良數量</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["fail"].ToString().TrimEnd())}</div></div><div class='numfield inlineDiv'><h4>不良率</h4><div class='subcontent'>100%</div></div></div><div class='together differfield'><div class='datefield inlineDiv'><h4>異常內容</h4></div><div class='inlineDiv'><div>{reviewHtmlBody(mainRows.Rows[0]["subject"].ToString().TrimEnd())}</div></div></div><div class='linefield'><hr /></div><div style='height:300px;padding:1px;' class='together'><div style='width:465px;float:left;' class='inlineDiv'><div class='together subtile'><h3>【Containment】緊急處置</h3></div><div style='height:116px;padding:1px 6px;'>{reviewHtmlBody(mainRows.Rows[0]["containment"].ToString().TrimEnd())}</div><div class='together subtile'><h3>【Cause】真因調查</h3></div><div style='height:116px;padding:1px 6px;'>{reviewHtmlBody(mainRows.Rows[0]["cause"].ToString().TrimEnd())}</div></div><div style='width:384px;' class='inlineDiv'><div class='together subtile'><h3>【Image】顯示圖</h3></div><div style='padding:0px 12px;'>image<!--image information--></div></div></div><div class='together subfield'><div class='datefield inlineDiv'><h4>處理人(中文全名)</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["replier"].ToString().TrimEnd())}</div></div><div class='departfield inlineDiv'><h4>原因分類</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["issuesort"].ToString().TrimEnd())} {reviewHtmlBody(mainRows.Rows[0]["causeclass"].ToString().TrimEnd())}</div></div><div class='floorfield inlineDiv'><h4>直接損耗工時</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["direct_pt"].ToString().TrimEnd())} mins</div></div><div class='numfield inlineDiv'><h4>間接損耗工時</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["indirect_pt"].ToString().TrimEnd())} mins</div></div></div><div class='linefield'><hr /></div><div class='together subtile'><h3>【Corrective Action】改善對策</h3></div><div style='height:134px;padding:1px 6px;' class='together'><h4>Short Term：</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["correctiveaction1"].ToString().TrimEnd())}</div></div><div style='height:134px;padding:1px 6px;' class='together'><h4>Long Term：</h4><div class='subcontent'>{reviewHtmlBody(mainRows.Rows[0]["correctiveaction2"].ToString().TrimEnd())}</div></div><div class='linefield'><hr /></div><div class='together subtile'><h3>【Closure】成效驗證</h3></div><div style='height:125px;padding:1px 12px;' class='together'><div style='width:453px;float:left;' class='inlineDiv'>{reviewHtmlBody(mainRows.Rows[0]["closure"].ToString().TrimEnd())}</div><div style='width:372px;' class='inlineDiv'>{reviewHtmlBody(mainRows.Rows[0]["body"].ToString().TrimEnd())}</div></div><div style='height:26px;padding:0px 12px;' class='together'><div style='width:277px;' class='inlineDiv'><div class='inlineDiv'>責任單位/人員：</div><div class='inlineDiv'>{reviewHtmlBody(mainRows.Rows[0]["belong"].ToString().TrimEnd())}/{reviewHtmlBody(mainRows.Rows[0]["belonger"].ToString().TrimEnd())} (中文全名)</div></div><div style='width:277px;' class='inlineDiv'><div class='inlineDiv'>處理狀態：</div><div class='inlineDiv'>{reviewHtmlBody(mainRows.Rows[0]["stage"].ToString().TrimEnd())}</div></div><div style='width:277px;' class='inlineDiv'><div class='inlineDiv'>結案日期：</div><div class='inlineDiv'>{reviewHtmlBody(mainRows.Rows[0]["releasedate"].ToString().TrimEnd())}</div></div></div></div></body>{reviewHtmlFoot()}");
                }
            }
            return Json(new sDataModels() { value = $"http://221.222.222.16:4500/folderFile/html/{folder}/{htmlFile}", status = "istrue" });
        }

        public string reviewHtmlHead()
        {
            return "<!DOCTYPE html><html><head><meta charset='utf-8' /><meta name='viewport' content='width=device-width, initial-scale=1.0' /><title>5C Report</title><style type='text/css'>div, h1, h2, h3, h4, h5, h6 {margin: 0px;padding: 0px;}.together {font-family: Microsoft JhengHei;}.outside { width: 872px;height: 1220px;border: 10px solid gray;}.tile {height: 45px;padding: 12px;text-align: center;text-decoration: underline;}.subtile {width:calc(100% - 1px);height: 29px;padding: 1px;font-weight: bolder;}.subfield {width:calc(100% - 24px);height: 45px;padding: 6px 12px;}.subcontent {padding-top:3px;}.inlineDiv {display: inline-block;}.datefield {width: 169px;}.departfield {width: 283px;}.floorfield {width: 148px;}.numfield {width: 224px;}.differfield {width:calc(100% - 24px);height: 26px;padding: 6px 12px;}.linefield {padding: 0px 12px;}</style></head>";
        }

        public string reviewHtmlBody(string value)
        {
            switch (value)
            {
                case "":
                    return "xxxx";
            }
            return value.TrimEnd();
        }

        public string reviewHtmlFoot()
        {
            return "</html>";
        }
    }
}
