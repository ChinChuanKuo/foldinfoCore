using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using FOLDINFOCore.App_Code;

namespace FOLDINFOCore.Models
{
    public class SignlistFClass
    {
        public sRowsModels GetSearchModels(dFormData dFormData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchsignlistFdeta @formId,@inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sRowsModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> mailitems = new List<Dictionary<string, object>>();
            foreach (var item in mainRows.Rows[0]["othermail"].ToString().TrimEnd().Split(',').Select((value, i) => new { i, value }))
            {
                if (item.value != "")
                {
                    mailitems.Add(new Dictionary<string, object>() { { "mbId", item.i }, { "mbValue", item.value } });
                }
            }
            List<Dictionary<string, object>> mbitems = new List<Dictionary<string, object>>();
            if (mainRows.Rows[0]["mblist"].ToString().TrimEnd().Length > 0)
            {
                foreach (var item in mainRows.Rows[0]["mblist"].ToString().TrimEnd().Split(',').Select((value, i) => new { i, value }))
                {
                    if (item.value != "")
                    {
                        mbitems.Add(new Dictionary<string, object>() { { "mbId", item.i }, { "mbValue", item.value } });
                    }
                }
            }
            List<Dictionary<string, object>> workitems = new List<Dictionary<string, object>>();
            foreach (var item in mainRows.Rows[0]["worknumber"].ToString().TrimEnd().Split('\n').Select((value, i) => new { i, value }))
            {
                if (item.value != "")
                {
                    workitems.Add(new Dictionary<string, object>() { { "mbId", item.i }, { "mbValue", item.value } });
                }
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "postdate", mainRows.Rows[0]["postdate"].ToString().TrimEnd() }, { "postinfo", $"{mainRows.Rows[0]["post_group"].ToString().TrimEnd()}_{mainRows.Rows[0]["postname"].ToString().TrimEnd()}" }, { "case", mainRows.Rows[0]["changecase"].ToString().TrimEnd() }, { "homepage1", mainRows.Rows[0]["homepage1"].ToString().TrimEnd() }, { "pnumber", mainRows.Rows[0]["pnumber"].ToString().TrimEnd() }, { "endDate", mainRows.Rows[0]["end_date"].ToString().TrimEnd().Split(' ')[0].Replace("/", "-") }, { "obj", mainRows.Rows[0]["obj"].ToString().TrimEnd() }, { "homepageMomo", mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd() }, { "mb", mainRows.Rows[0]["mb"].ToString().TrimEnd() }, { "amount", mainRows.Rows[0]["amount"].ToString().TrimEnd() }, { "subject", mainRows.Rows[0]["subject"].ToString().TrimEnd() }, { "ecr", "" }, { "ecn", "" }, { "body", mainRows.Rows[0]["body"].ToString().TrimEnd() }, { "mailitems", mailitems }, { "action1", mainRows.Rows[0]["action1"].ToString().TrimEnd() }, { "workitems", workitems }, { "action2", mainRows.Rows[0]["action2"].ToString().TrimEnd() }, { "mbitems", mbitems }, { "oldno", mainRows.Rows[0]["oldpn"].ToString().TrimEnd() }, { "newno", mainRows.Rows[0]["newpn"].ToString().TrimEnd() }, { "sopno", mainRows.Rows[0]["sopdoc"].ToString().TrimEnd() }, { "action3", mainRows.Rows[0]["action3"].ToString().TrimEnd() }, { "sipno", mainRows.Rows[0]["sipdoc"].ToString().TrimEnd() }, { "action4", mainRows.Rows[0]["action4"].ToString().TrimEnd() }, { "action5", mainRows.Rows[0]["action5"].ToString().TrimEnd() } });
            return new sRowsModels() { formId = mainRows.Rows[0]["id"].ToString().TrimEnd(), tile = mainRows.Rows[0]["number"].ToString().TrimEnd(), items = items, status = "istrue" };
        }

        public sOptonModels GetSFileModels(dFormData dFormData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchinfiledeta @id;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "photoId", dr["iid"].ToString().TrimEnd() }, { "photoImage", dr["flImages"].ToString().TrimEnd() == "1" }, { "photoVideo", dr["flVideos"].ToString().TrimEnd() == "1" }, { "photoAudio", dr["flAudios"].ToString().TrimEnd() == "1" }, { "photoSrc", dr["flImages"].ToString().TrimEnd() == "1" && dr["flShowed"].ToString().TrimEnd() == "0" ? $"{dr["originals"].ToString().TrimEnd()}({dr["encryptions"].ToString().TrimEnd()}){dr["extensions"].ToString().TrimEnd()}" : $"{dr["original"].ToString().TrimEnd()}({dr["encryption"].ToString().TrimEnd()}){dr["extension"].ToString().TrimEnd()}" }, { "photoPath", dr["flImages"].ToString().TrimEnd() == "1" && dr["flShowed"].ToString().TrimEnd() == "0" ? dr["imagePaths"].ToString().TrimEnd() : dr["imagePath"].ToString().TrimEnd() }, { "filePath", dr["imagePath"].ToString().TrimEnd() }, { "photoOriginal", dr["original"].ToString().TrimEnd() }, { "photoEncryption", dr["encryption"].ToString().TrimEnd() }, { "photoExtension", dr["extension"].ToString().TrimEnd() }, { "photoDate", dr["indate"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public sOptonModels GetSGrotoModels(dFormData dFormData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchingroupdeta @id,@inoper;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "grotoId", dr["iid"].ToString().TrimEnd() }, { "grotoImage", dr["flImages"].ToString().TrimEnd() == "1" }, { "grotoVideo", dr["flVideos"].ToString().TrimEnd() == "1" }, { "grotoAudio", dr["flAudios"].ToString().TrimEnd() == "1" }, { "grotoSrc", dr["flImages"].ToString().TrimEnd() == "1" && dr["flShowed"].ToString().TrimEnd() == "0" ? $"{dr["originals"].ToString().TrimEnd()}({dr["encryptions"].ToString().TrimEnd()}){dr["extensions"].ToString().TrimEnd()}" : $"{dr["original"].ToString().TrimEnd()}({dr["encryption"].ToString().TrimEnd()}){dr["extension"].ToString().TrimEnd()}" }, { "grotoPath", dr["flImages"].ToString().TrimEnd() == "1" && dr["flShowed"].ToString().TrimEnd() == "0" ? dr["imagePaths"].ToString().TrimEnd() : dr["imagePath"].ToString().TrimEnd() }, { "filePath", dr["imagePath"].ToString().TrimEnd() }, { "grotoOriginal", dr["original"].ToString().TrimEnd() }, { "grotoEncryption", dr["encryption"].ToString().TrimEnd() }, { "grotoExtension", dr["extension"].ToString().TrimEnd() }, { "grotoName", dr["name"].ToString().TrimEnd() }, { "grotoDate", dr["indate"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public statusModels GetSSendModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchinsidedata @formId;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            System.Console.WriteLine(dFormData.newid.TrimEnd());
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "exec web.sendsignlistFdeta @formId,@inoper;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            string date = new datetime().sqldate("mssql", "flyfnstring"), time = new datetime().sqltime("mssql", "flyfnstring");
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@mAddrName", $"{mainRows.Rows[0]["postname"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
            dbparamlist.Add(new dbparam("@mSubject", $"「{mainRows.Rows[0]["postname"].ToString().TrimEnd()}」建立工廠內部通告:{mainRows.Rows[0]["number"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;text-align:center;'><div style='padding: 12px; border:2px solid white;'><div><h3 style='color: red;'>FN SYSTEM NEWS</h3></div><div> <hr /></div><div><h3 style='color: red;'>建立工廠內部通告需瞭解</h3></div><div style='font-size: 16px;'>{date} {time}</div><div><h4>請相關人員進行瞭解此問題．</h4></div><div><a style='background-color:red; color:white; padding:12px;' href='http://221.222.222.181:7250/modifyF#{dFormData.formId.TrimEnd()}'>前往瞭解</a></div></div></div>"));
            database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist);
            return new statusModels() { status = "istrue" };
        }

        public string reviewHtmlHead()
        {
            return "<!DOCTYPE html><html><head><meta charset='utf-8' /><meta name='viewport' content='width=device-width, initial-scale=1.0' /><title>5C Report</title><style type='text/css'>div, h1, h2, h5, h5, h5, h6 {margin: 0px;padding: 0px;}</style></head>";
        }

        public string reviewHtmlFoot()
        {
            return "</html>";
        }

        public statusModels GetSBackModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchinsidedata @formId;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "exec web.backsignlistFdeta @formId,@inoper;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            //退簽時通知其他需簽核人員
            return new statusModels() { status = "istrue" };
        }
    }
}