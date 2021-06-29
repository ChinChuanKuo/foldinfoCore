using Microsoft.AspNetCore.Mvc;
using foldinfoCore.App_Code;
using NPOI.SS.UserModel;
using NPOI.XSSF.UserModel;
using System.Collections.Generic;
using System.IO;
using System.Data;
using foldinfoCore.Models;
using System;
using System.Net;
using System.Linq;

namespace foldinfoCore.Controllers
{
    public class ExcelController : Controller
    {
        [HttpGet]
        public ActionResult exampleData(string record, string firdate, string secdate, List<Dictionary<string, object>> items, string newid)
        {
            string filename = "", clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            XSSFWorkbook workbook = new XSSFWorkbook();
            XSSFSheet sheet = (XSSFSheet)workbook.CreateSheet("Information");
            sheet.SetColumnWidth(0, (int)((9.5 + 0.71) * 256));
            sheet.SetColumnWidth(1, (int)((10 + 0.71) * 256));
            sheet.SetColumnWidth(3, (int)((10 + 0.71) * 256));
            sheet.SetColumnWidth(4, (int)((13 + 0.71) * 256));
            sheet.SetColumnWidth(6, (int)((14 + 0.71) * 256));
            sheet.SetColumnWidth(10, (int)((12 + 0.71) * 256));
            sheet.SetColumnWidth(11, (int)((14 + 0.71) * 256));
            sheet.SetColumnWidth(15, (int)((40 + 0.71) * 256));
            sheet.SetColumnWidth(16, (int)((40 + 0.71) * 256));
            sheet.SetColumnWidth(17, (int)((40 + 0.71) * 256));
            sheet.SetColumnWidth(18, (int)((14 + 0.71) * 256));
            sheet.SetColumnWidth(19, (int)((14 + 0.71) * 256));
            sheet.SetColumnWidth(20, (int)((14 + 0.71) * 256));
            sheet.SetColumnWidth(21, (int)((14 + 0.71) * 256));
            sheet.SetColumnWidth(22, (int)((14 + 0.71) * 256));
            sheet.SetColumnWidth(23, (int)((14 + 0.71) * 256));
            sheet.SetColumnWidth(25, (int)((40 + 0.71) * 256));
            sheet.SetColumnWidth(26, (int)((40 + 0.71) * 256));
            sheet.SetColumnWidth(27, (int)((12 + 0.71) * 256));
            sheet.SetColumnWidth(28, (int)((12 + 0.71) * 256));
            sheet.SetColumnWidth(29, (int)((16 + 0.71) * 256));
            sheet.SetColumnWidth(30, (int)((16 + 0.71) * 256));
            XSSFRow row = (XSSFRow)sheet.CreateRow(0);
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", newid));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchusername @newid;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    row.CreateCell(0).SetCellValue("NOT YOUR INFORMATION ABOUT THIS FORM DATABASE");
                    filename = "沒資料呈現";
                    break;
                default:
                    string recordValue = string.IsNullOrWhiteSpace(record) ? "" : record.TrimEnd(), firDate = string.IsNullOrWhiteSpace(firdate) ? "" : firdate.TrimEnd().Replace('-', '/'), secDate = string.IsNullOrWhiteSpace(secdate) ? "" : secdate.TrimEnd().Replace('-', '/');
                    datetime datetime = new datetime();
                    string sqlCode = "", stdate = datetime.sqldate("mssql", "flyfnstring"), sttime = datetime.sqltime("mssql", "flyfnstring");
                    /*foreach (var item in items)
                    {
                        sqlCode += new HomeClass().checkSqlCode(sqlCode, new HomeClass().filterSqlCode(int.Parse(item["index"].ToString().TrimEnd()), item["value"].ToString().TrimEnd()));
                    }*/
                    if (firDate != "" || secDate != "")
                    {
                        sqlCode += new HomeClass().checkSqlCode(sqlCode, filterSqlDate(firDate, secDate));
                    }
                    if (recordValue != "")
                    {
                        sqlCode += new HomeClass().checkSqlCode(sqlCode, filterSqlRecord(recordValue, newid.TrimEnd()));
                    }
                    ICellStyle thinStyle = workbook.CreateCellStyle();
                    thinStyle.BorderTop = BorderStyle.Thin;
                    thinStyle.BorderRight = BorderStyle.Thin;
                    thinStyle.BorderBottom = BorderStyle.Thin;
                    thinStyle.BorderLeft = BorderStyle.Thin;
                    thinStyle.WrapText = true;
                    thinStyle.VerticalAlignment = NPOI.SS.UserModel.VerticalAlignment.Top;
                    string[] cellArray = new string[] { "提出日期", "提出部門", "提出者", "生產樓層", "文件編號", "客戶", "產品規格單", "機種", "M/B", "製程別", "生產工單", "不良料號", "投入數", "不良數量", "不良率", "異常內容", "緊急處置", "真因調查", "責任單位", "責任人員", "原因大分類", "原因小分類", "直接損耗工時", "間接損耗工時", "處理者", "短期對策", "長期對策", "處理狀態", "結案日期", "不列入統計資料", "列入注意事項" };
                    row = (XSSFRow)sheet.CreateRow(0);
                    foreach (var item in cellArray.Select((value, i) => new { i, value }))
                    {
                        row.CreateCell(item.i).SetCellValue(item.value);
                        row.GetCell(item.i).CellStyle = thinStyle;
                    }
                    int i = 1;
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@sqlCode", sqlCode));
                    foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.efiltreportform @sqlCode;", dbparamlist).Rows)
                    {
                        float fail = float.Parse(dr["fail"].ToString().TrimEnd()),
                        invest = float.Parse(dr["invest"].ToString().TrimEnd());
                        double badPersent = fail == 0 || invest == 0 ? 0.0 : Math.Round(fail / invest, 4, MidpointRounding.AwayFromZero), secPersent = badPersent * 10000.0;
                        row = (XSSFRow)sheet.CreateRow(i);
                        row.CreateCell(0).SetCellValue(dr["postdate"].ToString().TrimEnd());
                        row.GetCell(0).CellStyle = thinStyle;
                        row.CreateCell(1).SetCellValue(dr["post_group"].ToString().TrimEnd());
                        row.GetCell(1).CellStyle = thinStyle;
                        row.CreateCell(2).SetCellValue(dr["postname"].ToString().TrimEnd());
                        row.GetCell(2).CellStyle = thinStyle;
                        row.CreateCell(3).SetCellValue(dr["floor"].ToString().TrimEnd());
                        row.GetCell(3).CellStyle = thinStyle;
                        row.CreateCell(4).SetCellValue(dr["number"].ToString().TrimEnd());
                        row.GetCell(4).CellStyle = thinStyle;
                        row.CreateCell(5).SetCellValue(dr["homepage1"].ToString().TrimEnd());
                        row.GetCell(5).CellStyle = thinStyle;
                        row.CreateCell(6).SetCellValue(dr["pnumber"].ToString().TrimEnd());
                        row.GetCell(6).CellStyle = thinStyle;
                        row.CreateCell(7).SetCellValue(dr["homepage_momo"].ToString().TrimEnd());
                        row.GetCell(7).CellStyle = thinStyle;
                        row.CreateCell(8).SetCellValue(dr["mb"].ToString().TrimEnd());
                        row.GetCell(8).CellStyle = thinStyle;
                        row.CreateCell(9).SetCellValue(dr["obj"].ToString().TrimEnd());
                        row.GetCell(9).CellStyle = thinStyle;
                        row.CreateCell(10).SetCellValue(dr["worknumber"].ToString().TrimEnd());
                        row.GetCell(10).CellStyle = thinStyle;
                        row.CreateCell(11).SetCellValue(dr["pn"].ToString().TrimEnd());
                        row.GetCell(11).CellStyle = thinStyle;
                        row.CreateCell(12).SetCellValue(int.Parse(dr["invest"].ToString().TrimEnd()));
                        row.GetCell(12).CellStyle = thinStyle;
                        row.CreateCell(13).SetCellValue(int.Parse(dr["fail"].ToString().TrimEnd()));
                        row.GetCell(13).CellStyle = thinStyle;
                        row.CreateCell(14).SetCellValue($"{Math.Floor(secPersent) / 100}%");
                        row.GetCell(14).CellStyle = thinStyle;
                        row.CreateCell(15).SetCellValue(dr["subject"].ToString().TrimEnd());
                        row.GetCell(15).CellStyle = thinStyle;
                        row.CreateCell(16).SetCellValue(dr["containment"].ToString().TrimEnd());
                        row.GetCell(16).CellStyle = thinStyle;
                        row.CreateCell(17).SetCellValue(dr["cause"].ToString().TrimEnd());
                        row.GetCell(17).CellStyle = thinStyle;
                        row.CreateCell(18).SetCellValue(dr["belong"].ToString().TrimEnd());
                        row.GetCell(18).CellStyle = thinStyle;
                        row.CreateCell(19).SetCellValue(dr["belonger"].ToString().TrimEnd());
                        row.GetCell(19).CellStyle = thinStyle;
                        row.CreateCell(20).SetCellValue(dr["issuesort"].ToString().TrimEnd());
                        row.GetCell(20).CellStyle = thinStyle;
                        row.CreateCell(21).SetCellValue(dr["causeclass"].ToString().TrimEnd());
                        row.GetCell(21).CellStyle = thinStyle;
                        row.CreateCell(22).SetCellValue(dr["direct_pt"].ToString().TrimEnd());
                        row.GetCell(22).CellStyle = thinStyle;
                        row.CreateCell(23).SetCellValue(dr["indirect_pt"].ToString().TrimEnd());
                        row.GetCell(23).CellStyle = thinStyle;
                        row.CreateCell(24).SetCellValue(dr["replier"].ToString().TrimEnd());
                        row.GetCell(24).CellStyle = thinStyle;
                        row.CreateCell(25).SetCellValue(dr["correctiveaction1"].ToString().TrimEnd());
                        row.GetCell(25).CellStyle = thinStyle;
                        row.CreateCell(26).SetCellValue(dr["correctiveaction2"].ToString().TrimEnd());
                        row.GetCell(26).CellStyle = thinStyle;
                        row.CreateCell(27).SetCellValue(dr["stage"].ToString().TrimEnd());
                        row.GetCell(27).CellStyle = thinStyle;
                        row.CreateCell(28).SetCellValue(dr["releasedate"].ToString().TrimEnd());
                        row.GetCell(28).CellStyle = thinStyle;
                        row.CreateCell(29).SetCellValue(dr["nonstatistical"].ToString().TrimEnd());
                        row.GetCell(29).CellStyle = thinStyle;
                        row.CreateCell(30).SetCellValue(dr["notice"].ToString().TrimEnd());
                        row.GetCell(30).CellStyle = thinStyle;
                        i++;
                    }
                    dbparamlist.Clear();
                    string cuname = Dns.GetHostEntry(clientip).HostName.IndexOf('.') == -1 ? Dns.GetHostEntry(clientip).HostName : Dns.GetHostEntry(clientip).HostName.Split('.')[0];
                    dbparamlist.Add(new dbparam("@externip", clientip));
                    dbparamlist.Add(new dbparam("@hostname", cuname));
                    dbparamlist.Add(new dbparam("@stdate", stdate));
                    dbparamlist.Add(new dbparam("@sttime", sttime));
                    dbparamlist.Add(new dbparam("@inoper", newid));
                    database.checkActiveSql("mssql", "flyfnstring", "exec web.insertexamplelog @externip,@hostname,@stdate,@sttime,@inoper;", dbparamlist);
                    filename = $"{mainRows.Rows[0]["username"].ToString().TrimEnd()}匯入表單範本";
                    break;
            }
            MemoryStream ms = new MemoryStream();
            workbook.Write(ms);
            byte[] bytes = ms.ToArray();
            return File(bytes, "application/vnd.ms-excel", $"FLYTECH{filename}.xlsx");
        }

        public bool checkSqlDate(string firdate, string secdate)
        {
            if (firdate == "" || secdate == "")
            {
                return false;
            }
            DateTime firDate = Convert.ToDateTime(firdate), secDate = Convert.ToDateTime(secdate);
            switch (DateTime.Compare(firDate, secDate))
            {
                case -1:
                    return (secDate - firDate).Days > 90 == false;
                case 1:
                    return (firDate - secDate).Days > 90 == false;
            }
            return true;
        }

        public bool checkSqlRecord(string record)
        {
            switch (record)
            {
                case "today":
                case "closed":
                case "pending":
                case "myself":
                    return true;
            }
            return false;
        }

        public string filterSqlDate(string firdate, string secdate)
        {
            if (firdate == "" && secdate != "")
            {
                return $"postdate <= '{secdate}'";
            }
            else if (firdate != "" && secdate == "")
            {
                return $"postdate >= '{firdate}'";
            }
            else if (firdate != "" && secdate != "")
            {
                switch (DateTime.Compare(Convert.ToDateTime(firdate), Convert.ToDateTime(secdate)))
                {
                    case -1:
                        return $"postdate between '{firdate}' and '{secdate}'";
                    case 1:
                        return $"postdate between '{secdate}' and '{firdate}'";
                }
                return $"postdate = '{firdate}'";
            }
            return "";
        }

        public string filterSqlRecord(string value, string newid)
        {
            switch (value)
            {
                case "today":
                    return $"postdate = '{new datetime().sqldate("mssql", "flyfnstring")}'";
                case "closed":
                    return "stage = '結案'";
                case "pending":
                    return "stage != '結案'";
                case "myself":
                    List<dbparam> dbparamlist = new List<dbparam>();
                    dbparamlist.Add(new dbparam("@newid", newid));
                    return $"replier = '{new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchusername @newid;", dbparamlist).Rows[0]["username"].ToString().TrimEnd()}' and stage != '結案'";
            }
            string result = "";
            foreach (string item in value.Split(' '))
            {
                result += checkFilterCode(result, item, new string[] { "and" }, $"( number like '%{item}%' or version like '%{item}%' or post_group like '%{item}%' or postname like '%{item}%' or pnumber like '%{item}%' or worknumber like '%{item}%' or pn like '%{item}%' or subject like '%{item}%' or belonger like '%{item}%' or causeclass like '%{item}%' or replier like '%{item}%' )");
            }
            return result;
        }

        public string checkFilterCode(string value, string item, string[] split, string sqlCode)
        {
            switch (value)
            {
                case "":
                    return sqlCode;
            }
            switch (Array.IndexOf(split, item))
            {
                case 0:
                    return $" or {sqlCode}";
            }
            return $" and {sqlCode}";
        }
    }
}