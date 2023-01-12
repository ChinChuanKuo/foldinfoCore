using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using FOLDINFOCore.App_Code;

namespace FOLDINFOCore.Models
{
    public class SignlistIClass
    {
        public sRowsModels GetSearchModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchsignlistIdeta @formId,@inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sRowsModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> mbitems = new List<Dictionary<string, object>>();
            foreach (var item in mainRows.Rows[0]["mb"].ToString().TrimEnd().Split(',').Select((value, i) => new { i, value }))
            {
                mbitems.Add(new Dictionary<string, object>() { { "mbId", item.i }, { "mbValue", item.value } });
            }
            List<Dictionary<string, object>> pageitems = new List<Dictionary<string, object>>();
            foreach (var item in mainRows.Rows[0]["homepage1"].ToString().TrimEnd().Split(',').Select((value, i) => new { i, value }))
            {
                pageitems.Add(new Dictionary<string, object>() { { "mbId", item.i }, { "mbValue", item.value } });
            }
            bool showFile = false, showImage = false, showVideo = false, showAudio = false;
            string src = "", original = "", encryption = "", extension = "", date = "";
            switch (File.Exists($"{database.connectionString("folderFiles")}{mainRows.Rows[0]["homepage3"].ToString().TrimEnd()}"))
            {
                case true:
                    int finalPoint = mainRows.Rows[0]["homepage3"].ToString().TrimEnd().LastIndexOf(".");
                    string beforeExtension = mainRows.Rows[0]["homepage3"].ToString().TrimEnd().Substring(finalPoint, mainRows.Rows[0]["homepage3"].ToString().TrimEnd().Length - finalPoint);
                    DataTable fileRows = new DataTable();
                    dbparamlist.Add(new dbparam("@value", beforeExtension.Replace(".", "").Trim().ToLower()));
                    dbparamlist.Add(new dbparam("@needed", "1"));
                    fileRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.uploadfileform @value,@needed;", dbparamlist);
                    if (fileRows.Rows.Count > 0)
                    {
                        showFile = true;
                        showImage = fileRows.Rows[0]["flImages"].ToString().TrimEnd() == "1";
                        showVideo = fileRows.Rows[0]["flVideos"].ToString().TrimEnd() == "1";
                        showAudio = fileRows.Rows[0]["flAudios"].ToString().TrimEnd() == "1";
                        int leftPoint = mainRows.Rows[0]["homepage3"].ToString().TrimEnd().LastIndexOf("("), rightPoint = mainRows.Rows[0]["homepage3"].ToString().TrimEnd().LastIndexOf(")");
                        original = mainRows.Rows[0]["homepage3"].ToString().TrimEnd().Substring(0, leftPoint);
                        encryption = mainRows.Rows[0]["homepage3"].ToString().TrimEnd().Substring(leftPoint, rightPoint - leftPoint);
                        extension = beforeExtension;
                        src = fileRows.Rows[0]["flImages"].ToString().TrimEnd() == "1" && fileRows.Rows[0]["flShowed"].ToString().TrimEnd() == "0" ? $"{fileRows.Rows[0]["original"].ToString().TrimEnd()}({fileRows.Rows[0]["encryption"].ToString().TrimEnd()}){fileRows.Rows[0]["extension"].ToString().TrimEnd()}" : $"{original}({encryption}){extension}";
                    }
                    break;
            }
            bool showPdfFile = false, showPdfImage = false, showPdfVideo = false, showPdfAudio = false;
            string pdfSrc = "", pdfOriginal = "", pdfEncryption = "", pdfExtension = "", pdfDate = "";
            switch (File.Exists($"{database.connectionString("folderFiles")}{mainRows.Rows[0]["homepage2"].ToString().TrimEnd()}"))
            {
                case true:
                    int finalPoint = mainRows.Rows[0]["homepage2"].ToString().TrimEnd().LastIndexOf(".");
                    string beforeExtension = mainRows.Rows[0]["homepage2"].ToString().TrimEnd().Substring(finalPoint, mainRows.Rows[0]["homepage2"].ToString().TrimEnd().Length - finalPoint);
                    DataTable fileRows = new DataTable();
                    dbparamlist.Add(new dbparam("@value", beforeExtension.Replace(".", "").Trim().ToLower()));
                    dbparamlist.Add(new dbparam("@needed", "1"));
                    fileRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.uploadfileform @value,@needed;", dbparamlist);
                    if (fileRows.Rows.Count > 0)
                    {
                        showPdfFile = true;
                        showPdfImage = fileRows.Rows[0]["flImages"].ToString().TrimEnd() == "1";
                        showPdfVideo = fileRows.Rows[0]["flVideos"].ToString().TrimEnd() == "1";
                        showPdfAudio = fileRows.Rows[0]["flAudios"].ToString().TrimEnd() == "1";
                        int leftPoint = mainRows.Rows[0]["homepage2"].ToString().TrimEnd().LastIndexOf("("), rightPoint = mainRows.Rows[0]["homepage2"].ToString().TrimEnd().LastIndexOf(")");
                        pdfOriginal = mainRows.Rows[0]["homepage2"].ToString().TrimEnd().Substring(0, leftPoint);
                        pdfEncryption = mainRows.Rows[0]["homepage2"].ToString().TrimEnd().Substring(leftPoint, rightPoint - leftPoint);
                        pdfExtension = beforeExtension;
                        pdfSrc = fileRows.Rows[0]["flImages"].ToString().TrimEnd() == "1" && fileRows.Rows[0]["flShowed"].ToString().TrimEnd() == "0" ? $"{fileRows.Rows[0]["original"].ToString().TrimEnd()}({fileRows.Rows[0]["encryption"].ToString().TrimEnd()}){fileRows.Rows[0]["extension"].ToString().TrimEnd()}" : $"{pdfOriginal}({pdfEncryption}){pdfExtension}";
                    }
                    break;
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "postdate", mainRows.Rows[0]["postdate"].ToString().TrimEnd() }, { "postinfo", $"{mainRows.Rows[0]["post_group"].ToString().TrimEnd()}-{mainRows.Rows[0]["postname"].ToString().TrimEnd()}" }, { "subject", mainRows.Rows[0]["subject"].ToString().TrimEnd() }, { "obj", mainRows.Rows[0]["obj"].ToString().TrimEnd() }, { "homepageMomo", mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd() }, { "mbitems", mbitems }, { "pageitems", pageitems }, { "showFile", showFile }, { "showImage", showImage }, { "showVideo", showVideo }, { "showAudio", showAudio }, { "src", src }, { "path", database.connectionString("folderHttps") }, { "original", original }, { "encryption", encryption }, { "extension", extension }, { "date", date }, { "showPdfFile", showPdfFile }, { "showPdfImage", showPdfImage }, { "showPdfVideo", showPdfVideo }, { "showPdfAudio", showPdfAudio }, { "pdfSrc", pdfSrc }, { "pdfPath", database.connectionString("folderHttps") }, { "pdfOriginal", pdfOriginal }, { "pdfEncryption", pdfEncryption }, { "pdfExtension", pdfExtension }, { "pdfDate", pdfDate }, { "body", mainRows.Rows[0]["body"].ToString().TrimEnd() }, { "releaseDate", mainRows.Rows[0]["releasedate"].ToString().TrimEnd() }, { "limit", false }, { "endDate", mainRows.Rows[0]["end_date"].ToString().TrimEnd() } });
            return new sRowsModels() { formId = mainRows.Rows[0]["id"].ToString().TrimEnd(), tile = $"{mainRows.Rows[0]["number"].ToString().TrimEnd()}_{mainRows.Rows[0]["version"].ToString().TrimEnd()}", items = items, status = "istrue" };
        }

        public statusModels GetSSendModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchisofiledeta @formId;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            if (new database().checkActiveSql("mssql", "flyfnstring", "exec web.sendsignlistIdeta @formId,@inoper;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            dbparamlist.Clear();
            DataTable supeRows = new DataTable();
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            supeRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksupeber @inoper;", dbparamlist);
            dbparamlist.Clear();
            List<string> mailist = new List<string>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.sendismailform;", dbparamlist).Rows)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
                dbparamlist.Add(new dbparam("@newid", dr["newid"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@value", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」將此ISO三階文件審核:{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}"));
                dbparamlist.Add(new dbparam("@link", $"/modifyI#{dFormData.formId.TrimEnd()}"));
                database.checkActiveSql("mssql", "flyfnstring", "exec web.insertnoticeform @formId,@newid,@inoper,@value,@link;", dbparamlist);
                mailist.Add(dr["username"].ToString().TrimEnd());
            }
            string[] titleArray = new string[] { "提出日期", "提出資訊", "生產樓層" };
            string[] dataArray = new string[] { "123", "345", "567" };
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@mAddrName", $"郭晉全,{string.Join(',', mailist)}"));
            dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
            dbparamlist.Add(new dbparam("@mSubject", $"「ISO檔案 審核通知」:{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mBody", $"<div style='text-align:center;'><table border='0' cellpadding='0' cellspacing='0'><tr><td colspan='3'><h3 style='margin-bottom:12px;'>5C REPORT SYSTEM NEWS</h3></td><tr/><tr><td colspan='3'><h3 style='margin-bottom:12px;'>【Characterize】問題描述</h3></td><tr/>{new SignlistRClass().reviewTableRow(titleArray, dataArray, 3)}</tr><tr><th colspan='3' style='width:150px;height:50px;'><p style='font-size:12px;'>http://221.222.222.181:7250/modifyR#{dFormData.formId.TrimEnd()} => 請複製此連結</p></th></tr></table></div>"));
            System.Console.WriteLine(database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist));
            return new statusModels() { status = "istrue" };
        }

        public statusModels GetSBackModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchisofiledeta @formId;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            if (new database().checkActiveSql("mssql", "flyfnstring", "exec web.backsignlistIdeta @formId,@inoper;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            dbparamlist.Clear();
            DataTable supeRows = new DataTable();
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            supeRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksupeber @inoper;", dbparamlist);
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@newid", supeRows.Rows[0]["userid"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@value", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」將此ISO三階文件退審:{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@link", $"/modifyI#{dFormData.formId.TrimEnd()}"));
            database.checkActiveSql("mssql", "flyfnstring", "exec web.insertnoticeform @formId,@newid,@inoper,@value,@link;", dbparamlist);
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@mAddrName", $"郭晉全,{supeRows.Rows[0]["supername"].ToString().TrimEnd()},{supeRows.Rows[0]["username"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
            dbparamlist.Add(new dbparam("@mSubject", $"「{supeRows.Rows[0]["supername"].ToString().TrimEnd()}」將此ISO三階文件退審:{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;text-align:center;'><div style='padding: 12px; border:2px solid white;'><div><h5 style='color: red;'>ISO SYSTEM NEWS</h5></div><div> <hr /></div><div><h5 style='color: red;'>已退審完成資料</h5></div><div style='font-size: 16px;'>{new datetime().sqldate("mssql", "flyfnstring")} {new datetime().sqltime("mssql", "flyfnstring")}</div><div><h5>請提出者編修資料後再送出．</h5></div><div><a style='background-color:red; color:white; padding:12px;' href='http://221.222.222.181:7250/modifyI#{dFormData.formId.TrimEnd()}'>前往查看</a></div></div></div>"));
            database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist);
            return new statusModels() { status = "istrue" };
        }
    }
}