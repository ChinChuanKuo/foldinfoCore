using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text.Json;
using foldinfoCore.App_Code;

namespace foldinfoCore.Models
{
    public class CreateIClass
    {
        public sItemModels GetSearchModels(userData userData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            string[] typeArray = new string[] { "作業指導書", "作業規格書", "IQC檢驗SIP", "OQC檢驗SIP", "IPQC檢驗SIP", "QA校驗SIP" };
            List<Dictionary<string, object>> typeitems = new List<Dictionary<string, object>>();
            foreach (string value in typeArray)
            {
                typeitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", value } });
            }
            List<Dictionary<string, object>> groupitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.searchallgroupform;", dbparamlist).Rows)
            {
                groupitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["department"].ToString().TrimEnd() } });
            }
            string[] objArray = new string[] { "", "DIP", "DOA", "IPQC", "IQC", "NA", "OQC", "PreTest", "QA校驗", "RMA", "SMT", "加工", "包裝", "系測", "其它", "板測", "板測,系測", "客訴", "客驗", "組裝", "組裝,包裝", "週邊", "製程", "銷退" };
            List<Dictionary<string, object>> objitems = new List<Dictionary<string, object>>();
            foreach (var obj in objArray)
            {
                objitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", obj } });
            }
            List<Dictionary<string, object>> mtstitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flycsastring", "exec dbo.searchallinventform;", dbparamlist).Rows)
            {
                mtstitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["mb"].ToString().TrimEnd() } });
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "showTypeMenu", false }, { "typeitems", typeitems.ToArray() }, { "type_", "" }, { "showGroupMenu", false }, { "groupitems", groupitems }, { "postGroup", "" }, { "showNameMenu", false }, { "nameitems", new List<Dictionary<string, object>>().ToArray() }, { "postName", "" }, { "subject", "" }, { "showObjMenu", false }, { "objitems", objitems.ToArray() }, { "obj", "" }, { "homepageMomo", "" }, { "mbitems", new List<Dictionary<string, object>>().ToArray() }, { "showMtstMenu", false }, { "mtstitems", mtstitems.ToArray() }, { "mtst", "" }, { "showMbstMenu", false }, { "mbstitems", new List<Dictionary<string, object>>().ToArray() }, { "mbst", "" }, { "pageitems", new List<Dictionary<string, object>>().ToArray() }, { "custom", "" }, { "showCustom", false }, { "customitems", new List<Dictionary<string, object>>().ToArray() }, { "showDrop", false }, { "showFile", false }, { "showImage", false }, { "showVideo", false }, { "showAudio", false }, { "src", "" }, { "path", "" }, { "original", "" }, { "encryption", "" }, { "extension", "" }, { "date", "" }, { "showPdfDrop", false }, { "showPdfFile", false }, { "showPdfImage", false }, { "showPdfVideo", false }, { "showPdfAudio", false }, { "pdfSrc", "" }, { "pdfPath", "" }, { "pdfOriginal", "" }, { "pdfEncryption", "" }, { "pdfExtension", "" }, { "pdfDate", "" }, { "showTotal", false }, { "first", "1" }, { "final", "0" }, { "body", "" }, { "releaseDate", "" }, { "limit", false }, { "endDate", "" } });
            return new sItemModels() { items = items, status = "istrue" };
        }

        public sOptonModels GetSGroupModels(otherData otherData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@group", otherData.values.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchgroupform @group;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["username"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public sOptonModels GetSModelModels(otherData otherData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@model", otherData.values.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flycsastring", "exec dbo.searchinventform @model;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["品號"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public sOptonModels GetSCustomModels(otherData otherData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@length", otherData.values.Length));
            dbparamlist.Add(new dbparam("@value", otherData.values.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flycsastring", "exec dbo.searchcustomidform @length,@value;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public statusModels GetCCustomModels(otherData otherData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@value", otherData.values.TrimEnd()));
            mainRows = new database().checkSelectSql("mssql", "flycsastring", "exec dbo.checkcustomidform @value;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            return new statusModels() { status = "istrue" };
        }

        public statusModels GetInsertModels(iItemsData iItemsData, string cuurip)
        {
            string checkItems = checkItemValue(iItemsData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            database database = new database();
            string formId = new sha256().new256("mssql", "flyfnstring"), number = "";
            foreach (var item in iItemsData.items)
            {
                string mb = "", homepage1 = "";
                foreach (var mbitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["mbitems"].ToString().TrimEnd()))
                {
                    switch (mb.IndexOf(mbitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            mb += $"{mbitem["mbValue"].ToString().TrimEnd()},";
                            break;
                    }
                }
                foreach (var pageitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["pageitems"].ToString().TrimEnd()))
                {
                    switch (homepage1.IndexOf(pageitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            homepage1 += $"{pageitem["mbValue"].ToString().TrimEnd()},";
                            break;
                    }
                }
                bool showFile = bool.Parse(item["showFile"].ToString().TrimEnd()),
                showPdfFile = bool.Parse(item["showPdfFile"].ToString().TrimEnd());
                number = checkTypeData(checkTypeValue(item["type_"].ToString().TrimEnd()));
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@formId", formId));
                dbparamlist.Add(new dbparam("@postGroup", item["postGroup"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@postName", item["postName"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@number", number));
                dbparamlist.Add(new dbparam("@version", "A"));
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", mb));
                dbparamlist.Add(new dbparam("@homepage1", homepage1));
                dbparamlist.Add(new dbparam("@homepage2", showPdfFile ? $"{item["pdfOriginal"].ToString().TrimEnd()}({item["pdfEncryption"].ToString().TrimEnd()}){item["pdfExtension"].ToString().TrimEnd()}" : ""));
                dbparamlist.Add(new dbparam("@homepage3", showFile ? $"{item["original"].ToString().TrimEnd()}({item["encryption"].ToString().TrimEnd()}){item["extension"].ToString().TrimEnd()}" : ""));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@releaseDate", item["releaseDate"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@endDate", item["endDate"].ToString().TrimEnd()));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertisofileform @formId,@postGroup,@postName,@number,@version,@subject,@obj,@homepageMomo,@mb,@homepage1,@homepage2,@homepage3,@body,@releaseDate,@endDate;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            return new statusModels() { status = "istrue" };
        }

        public statusModels GetSendModels(iItemsData iItemsData, string cuurip)
        {
            string checkItems = checkItemValue(iItemsData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            string formId = new sha256().new256("mssql", "flyfnstring"), number = "";
            foreach (var item in iItemsData.items)
            {
                string mb = "", homepage1 = "";
                foreach (var mbitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["mbitems"].ToString().TrimEnd()))
                {
                    switch (mb.IndexOf(mbitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            mb += $"{mbitem["mbValue"].ToString().TrimEnd()},";
                            break;
                    }
                }
                foreach (var pageitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["pageitems"].ToString().TrimEnd()))
                {
                    switch (homepage1.IndexOf(pageitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            homepage1 += $"{pageitem["mbValue"].ToString().TrimEnd()},";
                            break;
                    }
                }
                bool showFile = bool.Parse(item["showFile"].ToString().TrimEnd()),
                showPdfFile = bool.Parse(item["showPdfFile"].ToString().TrimEnd());
                number = checkTypeData(checkTypeValue(item["type_"].ToString().TrimEnd()));
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", formId));
                dbparamlist.Add(new dbparam("@postGroup", item["postGroup"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@postName", item["postName"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@number", number));
                dbparamlist.Add(new dbparam("@version", "A"));
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", mb));
                dbparamlist.Add(new dbparam("@homepage1", homepage1));
                dbparamlist.Add(new dbparam("@homepage2", showPdfFile ? $"{item["pdfOriginal"].ToString().TrimEnd()}({item["pdfEncryption"].ToString().TrimEnd()}){item["pdfExtension"].ToString().TrimEnd()}" : ""));
                dbparamlist.Add(new dbparam("@homepage3", showFile ? $"{item["original"].ToString().TrimEnd()}({item["encryption"].ToString().TrimEnd()}){item["extension"].ToString().TrimEnd()}" : ""));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@releaseDate", item["releaseDate"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@endDate", item["endDate"].ToString().TrimEnd()));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertisofileform @formId,@postGroup,@postName,@number,@version,@subject,@obj,@homepageMomo,@mb,@homepage1,@homepage2,@homepage3,@body,@releaseDate,@endDate;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            dbparamlist.Clear();
            DataTable supeRows = new DataTable();
            dbparamlist.Add(new dbparam("@inoper", iItemsData.newid.TrimEnd()));
            supeRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksupeber @inoper;", dbparamlist);
            dbparamlist.Add(new dbparam("@formId", formId));
            dbparamlist.Add(new dbparam("@newid", supeRows.Rows[0]["superid"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@value", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」建立ISO檔案需簽核:{number}"));
            dbparamlist.Add(new dbparam("@link", $"/signlistF#{formId}"));
            database.checkActiveSql("mssql", "flyfnstring", "exec web.insertnoticeform @formId,@newid,@inoper,@value,@link;", dbparamlist);
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@mAddrName", $"郭晉全,{supeRows.Rows[0]["supername"].ToString().TrimEnd()},{supeRows.Rows[0]["username"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
            dbparamlist.Add(new dbparam("@mSubject", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」建立ISO檔案需簽核:{number}"));
            dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;text-align:center;'><div style='padding: 12px; border:2px solid white;'><div><h3 style='color: red;'>FN SYSTEM NEWS</h3></div><div> <hr /></div><div><h3 style='color: red;'>建立ISO檔案管理需簽核</h3></div><div style='font-size: 16px;'>{new datetime().sqldate("mssql", "flyfnstring")} {new datetime().sqltime("mssql", "flyfnstring")}</div><div><h4>請相關主管進行簽核或退簽此問題．</h4></div><div><a style='background-color:red; color:white; padding:12px;' href='http://221.222.222.181:7250/signlistR#{formId}'>前往簽核</a></div></div></div>"));
            database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist);
            return new statusModels() { status = "istrue" };
        }

        public string checkTypeValue(string value)
        {
            switch (value)
            {
                case "作業指導書":
                    return "I9-P-06";
                case "作業規格書":
                    return "I9-P-07";
                case "IQC檢驗SIP":
                    return "I9-Q-01";
                case "OQC檢驗SIP":
                    return "I9-Q-02";
                case "IPQC檢驗SIP":
                    return "I9-Q-12";
            }
            return "I9-Q-07";
        }

        public string checkTypeData(string value)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@type", value));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.checkisofiletypeform @type;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return $"{value}000";
            }
            return $"{value}{randomSerial(mainRows.Rows[0]["value"].ToString().TrimEnd().ToCharArray().Select(x => x.ToString()).ToArray(), new string[] { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" })}";
        }

        public string randomSerial(string[] array, string[] order)
        {
            bool istrue = true;
            int total = array.Length - 1;
            string final = order[order.Length - 1].TrimEnd();
            while (total >= 0)
            {
                string aValue = array[total].ToString().TrimEnd();
                array[total] = istrue ? order[Array.IndexOf(order, aValue) + 1].TrimEnd() : array[total].TrimEnd();
                istrue = aValue == final;
                total--;
            }
            return String.Join("", array);
        }

        public string checkItemValue(List<Dictionary<string, object>> items)
        {
            foreach (var item in items)
            {
                switch (item["type_"].ToString().TrimEnd())
                {
                    case "":
                        return "三階文件類型尚未選擇";
                }
                switch (item["postGroup"].ToString().TrimEnd())
                {
                    case "":
                        return "提出部門尚未選擇";
                }
                switch (item["postName"].ToString().TrimEnd())
                {
                    case "":
                        return "提出者尚未選擇";
                }
                switch (item["subject"].ToString().TrimEnd())
                {
                    case "":
                        return "文件名稱尚未填寫";
                }
                switch (item["obj"].ToString().TrimEnd())
                {
                    case "":
                        return "製程別尚未選擇";
                }
                switch (item["homepageMomo"].ToString().TrimEnd())
                {
                    case "":
                        return "機種尚未填寫";
                }
                switch (JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["mbitems"].ToString().TrimEnd()).Count)
                {
                    case 0:
                        return "板類尚未填寫";
                }
                switch (JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["pageitems"].ToString().TrimEnd()).Count)
                {
                    case 0:
                        return "客戶尚未填寫";
                }
                /*switch (bool.Parse(item["showFile"].ToString().TrimEnd()))
                {
                    case false:
                        return "請上傳檔案";
                }
                switch (bool.Parse(item["showPdfFile"].ToString().TrimEnd()))
                {
                    case false:
                        return "請上傳PDF或點擊轉檔";
                }*/
                switch (item["body"].ToString().TrimEnd())
                {
                    case "":
                        return "說明尚未填寫";
                }
                /*switch (item["releaseDate"].ToString().TrimEnd())
                {
                    case "":
                        return "發行日期尚未填寫";
                }
                if (bool.Parse(item["limit"].ToString().TrimEnd()) && item["endDate"].ToString().TrimEnd() == "")
                {
                    return "版本期限-到期日尚未填寫";
                }*/
            }
            return "";
        }
    }
}