using System;
using System.Collections.Generic;
using System.Data;
using foldinfoCore.App_Code;

namespace foldinfoCore.Models
{
    public class SignlistRClass
    {
        public sRowsModels GetSearchModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchsignlistRdeta @formId,@inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sRowsModels() { status = "nodata" };
            }
            dbparamlist.Clear();
            List<Dictionary<string, object>> groupitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.searchallgroupform;", dbparamlist).Rows)
            {
                groupitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["department"].ToString().TrimEnd() } });
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "postdate", mainRows.Rows[0]["postdate"].ToString().TrimEnd() }, { "postinfo", $"{mainRows.Rows[0]["post_group"].ToString().TrimEnd()}_{mainRows.Rows[0]["postname"].ToString().TrimEnd()}" }, { "floor", mainRows.Rows[0]["floor"].ToString().TrimEnd() }, { "workno", mainRows.Rows[0]["worknumber"].ToString().TrimEnd() }, { "homepage1", mainRows.Rows[0]["homepage1"].ToString().TrimEnd() }, { "pnumber", mainRows.Rows[0]["pnumber"].ToString().TrimEnd() }, { "homepageMomo", mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd() }, { "mb", mainRows.Rows[0]["mb"].ToString().TrimEnd() }, { "obj", mainRows.Rows[0]["obj"].ToString().TrimEnd() }, { "pn", mainRows.Rows[0]["pn"].ToString().TrimEnd() }, { "invest", mainRows.Rows[0]["invest"].ToString().TrimEnd() }, { "amount", mainRows.Rows[0]["amount"].ToString().TrimEnd() }, { "fail", mainRows.Rows[0]["fail"].ToString().TrimEnd() }, { "subject", mainRows.Rows[0]["subject"].ToString().TrimEnd() }, { "containment", mainRows.Rows[0]["containment"].ToString().TrimEnd() }, { "cause", mainRows.Rows[0]["cause"].ToString().TrimEnd() }, { "showRegroupMenu", false }, { "regroupitems", groupitems.ToArray() }, { "reGroup", "" }, { "showReplierMenu", false }, { "replieritems", new List<Dictionary<string, object>>().ToArray() }, { "replier", mainRows.Rows[0]["replier"].ToString().TrimEnd() }, { "issuesort", mainRows.Rows[0]["issuesort"].ToString().TrimEnd() }, { "causeclass", mainRows.Rows[0]["causeclass"].ToString().TrimEnd() }, { "directPt", mainRows.Rows[0]["direct_pt"].ToString().TrimEnd() }, { "indirectPt", mainRows.Rows[0]["indirect_pt"].ToString().TrimEnd() }, { "correctiveaction1", mainRows.Rows[0]["correctiveaction1"].ToString().TrimEnd() }, { "correctiveaction2", mainRows.Rows[0]["correctiveaction2"].ToString().TrimEnd() }, { "showFile", false }, { "showImage", false }, { "showVideo", false }, { "showAudio", false }, { "src", "" }, { "path", "" }, { "original", "" }, { "encryption", "" }, { "extension", "" }, { "date", "" }, { "closure", mainRows.Rows[0]["closure"].ToString().TrimEnd() }, { "body", mainRows.Rows[0]["body"].ToString().TrimEnd() }, { "notice", mainRows.Rows[0]["notice"].ToString().TrimEnd() }, { "nonstatistical", mainRows.Rows[0]["nonstatistical"].ToString().TrimEnd() }, { "belong", mainRows.Rows[0]["belong"].ToString().TrimEnd() }, { "belonger", mainRows.Rows[0]["belonger"].ToString().TrimEnd() }, { "stage", mainRows.Rows[0]["stage"].ToString().TrimEnd() }, { "releasedate", mainRows.Rows[0]["releasedate"].ToString().TrimEnd() }, { "formEdit", checkEdit(mainRows.Rows[0]["stage"].ToString().TrimEnd()) }, { "formModify", false } });
            return new sRowsModels() { formId = mainRows.Rows[0]["id"].ToString().TrimEnd(), tile = $"{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}", items = items, status = "istrue" };
        }

        public bool checkEdit(string stage)
        {
            return stage == "對策發行(簽核中)";
        }

        public sOptonModels GetSFileModels(dFormData dFormData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchrefiledeta @id;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "photoId", dr["iid"].ToString().TrimEnd() }, { "photoImage", dr["flImages"].ToString().TrimEnd() == "1" }, { "photoVideo", dr["flVideos"].ToString().TrimEnd() == "1" }, { "photoAudio", dr["flAudios"].ToString().TrimEnd() == "1" }, { "photoSrc", dr["flImages"].ToString().TrimEnd() == "1" && dr["flShowed"].ToString().TrimEnd() == "0" ? $"{dr["originals"].ToString().TrimEnd()}({dr["encryptions"].ToString().TrimEnd()}){dr["extensions"].ToString().TrimEnd()}" : $"{dr["original"].ToString().TrimEnd()}({dr["encryption"].ToString().TrimEnd()}){dr["extension"].ToString().TrimEnd()}" }, { "photoPath", dr["flImages"].ToString().TrimEnd() == "1" && dr["flShowed"].ToString().TrimEnd() == "0" ? dr["imagePaths"].ToString().TrimEnd() : dr["imagePath"].ToString().TrimEnd() }, { "filePath", dr["imagePath"].ToString().TrimEnd() }, { "photoOriginal", dr["original"].ToString().TrimEnd() }, { "photoEncryption", dr["encryption"].ToString().TrimEnd() }, { "photoExtension", dr["extension"].ToString().TrimEnd() }, { "photoDate", dr["indate"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public statusModels GetSSendModels(iFormData iFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", iFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchreportdeta @formId;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            dbparamlist.Add(new dbparam("@inoper", iFormData.newid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "exec web.sendsignlistRdeta @formId,@inoper;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            if (mainRows.Rows[0]["stage"].ToString().TrimEnd() != "對策發行(簽核中)")
            {
                dbparamlist.Clear();
                DataTable supeRows = new DataTable();
                dbparamlist.Add(new dbparam("@inoper", iFormData.newid.TrimEnd()));
                supeRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksupeber @inoper;", dbparamlist);
                dbparamlist.Clear();
                List<string> mailist = new List<string>();
                foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.sendremailform;", dbparamlist).Rows)
                {
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@inoper", iFormData.newid.TrimEnd()));
                    dbparamlist.Add(new dbparam("@formId", iFormData.formId.TrimEnd()));
                    dbparamlist.Add(new dbparam("@newid", dr["newid"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@value", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」將此品異單審核:{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}"));
                    dbparamlist.Add(new dbparam("@link", $"/modifyR#{iFormData.formId.TrimEnd()}"));
                    database.checkActiveSql("mssql", "flyfnstring", "exec web.insertnoticeform @formId,@newid,@inoper,@value,@link;", dbparamlist);
                    mailist.Add(dr["username"].ToString().TrimEnd());
                }
                string[] titleArray = new string[] { "提出日期", "提出資訊", "生產樓層", "工單", "客戶", "產品規格單", "機種", "M/B", "品異來源", "不良料號", "工單總數", "", "投入數", "不良數量", "不良率" };
                string[] dataArray = new string[] { mainRows.Rows[0]["postdate"].ToString().TrimEnd(), $"{mainRows.Rows[0]["post_group"].ToString().TrimEnd()}_{mainRows.Rows[0]["postname"].ToString().TrimEnd()}", mainRows.Rows[0]["floor"].ToString().TrimEnd(), mainRows.Rows[0]["worknumber"].ToString().TrimEnd(), mainRows.Rows[0]["homepage1"].ToString().TrimEnd(), mainRows.Rows[0]["pnumber"].ToString().TrimEnd(), mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd(), mainRows.Rows[0]["mb"].ToString().TrimEnd(), mainRows.Rows[0]["obj"].ToString().TrimEnd(), mainRows.Rows[0]["pn"].ToString().TrimEnd(), mainRows.Rows[0]["amount"].ToString().TrimEnd(), "", mainRows.Rows[0]["invest"].ToString().TrimEnd(), mainRows.Rows[0]["fail"].ToString().TrimEnd(), Math.Round(float.Parse(mainRows.Rows[0]["fail"].ToString().TrimEnd()) / float.Parse(mainRows.Rows[0]["invest"].ToString().TrimEnd()), 2, MidpointRounding.AwayFromZero).ToString().TrimEnd() };
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@mAddrName", $"郭晉全,{string.Join(',', mailist)},${supeRows.Rows[0]["supername"].ToString().TrimEnd()},${iFormData.items[0]["replier"].ToString().TrimEnd()}"));
                dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
                dbparamlist.Add(new dbparam("@mSubject", $"「品質異常單 審核通知」:{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}"));
                dbparamlist.Add(new dbparam("@mBody", $"<div style='text-align:center;'><table border='0' cellpadding='0' cellspacing='0'><tr><td colspan='3'><h3 style='margin-bottom:12px;'>5C REPORT SYSTEM NEWS</h3></td><tr/><tr><td colspan='3'><h3 style='margin-bottom:12px;'>【Characterize】問題描述</h3></td><tr/>{reviewTableRow(titleArray, dataArray, 3)}<th colspan='3' style='width:150px;height:50px;'><p style='font-size:12px;'>異常內容<br/>{mainRows.Rows[0]["subject"].ToString().TrimEnd()}</p></th></tr><tr><th colspan='3' style='width:150px;height:50px;'><p style='font-size:12px;'>http://221.222.222.181:7250/modifyR#{iFormData.formId.TrimEnd()} => 請複製此連結</p></th></tr></table></div>"));
                database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist);
            }
            return new statusModels() { status = "istrue" };
        }

        public string reviewTableRow(string[] titleArray, string[] dataArray, int betweenIndex)
        {
            int arrayLen = 0;
            string dataitem = "<tr>";
            while (arrayLen < titleArray.Length)
            {
                dataitem += $"<th style='width:150px;height:50px;'><p style='font-size:12px;'>{titleArray[arrayLen]}<br/>{dataArray[arrayLen]}</p></th>";
                if (arrayLen % betweenIndex == 2)
                {
                    dataitem += "</tr><tr>";
                }
                arrayLen++;
            }
            return dataitem;
        }

        public statusModels GetSBackModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchreportdeta @formId;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "exec web.backsignlistRdeta @formId,@inoper;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@reason", $"5cReport number：{dFormData.formId.TrimEnd()}"));
            database.checkSelectSql("mssql", "flystkstring", "exec dbo.deletenopassitem @reason;", dbparamlist);
            dbparamlist.Clear();
            DataTable supeRows = new DataTable();
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            supeRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksupeber @inoper;", dbparamlist);
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@newid", supeRows.Rows[0]["userid"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@value", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」將此品異單退審:{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@link", $"/modifyR#{dFormData.formId.TrimEnd()}"));
            database.checkActiveSql("mssql", "flyfnstring", "exec web.insertnoticeform @formId,@newid,@inoper,@value,@link;", dbparamlist);
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@mAddrName", $"郭晉全,{supeRows.Rows[0]["supername"].ToString().TrimEnd()},{supeRows.Rows[0]["username"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
            dbparamlist.Add(new dbparam("@mSubject", $"「品質異常單 退審通知」:{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mBody", $"<div style='text-align:center;'><table border='0' cellpadding='0' cellspacing='0'><tr><td colspan='3'><h3 style='margin-bottom:12px;'>5C REPORT SYSTEM NEWS</h3></td><tr/><tr><th colspan='3' style='width:150px;height:150px;'><p style='font-size:12px;'>請提出者編修資料後再送出．</p></th></tr><tr><th colspan='3' style='width:150px;height:150px;'><p style='font-size:12px;'>http://221.222.222.181:7250/modifyR#{dFormData.formId.TrimEnd()} => 請複製此連結</p></th></tr></table></div>"));
            database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist);
            return new statusModels() { status = "istrue" };
        }
    }
}