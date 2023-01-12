using System;
using System.Collections.Generic;
using System.Data;
using System.Text.Json;
using FOLDINFOCore.App_Code;

namespace FOLDINFOCore.Models
{
    public class CreatePClass
    {
        public sItemModels GetSearchModels(userData userData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            List<Dictionary<string, object>> groupitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.searchallgroupform;", dbparamlist).Rows)
            {
                groupitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["department"].ToString().TrimEnd() } });
            }
            List<Dictionary<string, object>> mtstitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flycsastring", "exec dbo.searchallinventform;", dbparamlist).Rows)
            {
                mtstitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["mb"].ToString().TrimEnd() } });
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "showGroupMenu", false }, { "groupitems", groupitems.ToArray() }, { "postGroup", "" }, { "showNameMenu", false }, { "nameitems", new List<Dictionary<string, object>>().ToArray() }, { "postName", "" }, { "subject", "" }, { "homepageMomo", "" }, { "mbitems", new List<Dictionary<string, object>>().ToArray() }, { "showMtstMenu", false }, { "mtstitems", mtstitems.ToArray() }, { "mtst", "" }, { "showMbstMenu", false }, { "mbstitems", new List<Dictionary<string, object>>().ToArray() }, { "mbst", "" }, { "pageitems", new List<Dictionary<string, object>>().ToArray() }, { "custom", "" }, { "showCustom", false }, { "customitems", new List<Dictionary<string, object>>().ToArray() }, { "showDrop", false }, { "showFile", false }, { "showImage", false }, { "showVideo", false }, { "showAudio", false }, { "src", "" }, { "path", "" }, { "original", "" }, { "encryption", "" }, { "extension", "" }, { "date", "" }, { "showPdfDrop", false }, { "showPdfFile", false }, { "showPdfImage", false }, { "showPdfVideo", false }, { "showPdfAudio", false }, { "pdfSrc", "" }, { "pdfPath", "" }, { "pdfOriginal", "" }, { "pdfEncryption", "" }, { "pdfExtension", "" }, { "pdfDate", "" }, { "showTotal", false }, { "first", "1" }, { "final", "0" }, { "body", "" } });
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
            DataTable finalRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            string formId = new sha256().new256("mssql", "flyfnstring"), number = $"N{DateTime.Now.ToString("yyyyMM")}", endnumber = "001";
            dbparamlist.Add(new dbparam("@number", number));
            finalRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchfinalproductform @number;", dbparamlist);
            if (finalRows.Rows.Count > 0)
            {
                endnumber = (int.Parse(finalRows.Rows[0]["endnumber"].ToString().TrimEnd()) + 1).ToString().TrimEnd().PadLeft(3, '0');
            }
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
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", formId));
                dbparamlist.Add(new dbparam("@postGroup", item["postGroup"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@postName", item["postName"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@number", number + endnumber));
                dbparamlist.Add(new dbparam("@version", "A"));
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", mb));
                dbparamlist.Add(new dbparam("@homepage1", homepage1));
                dbparamlist.Add(new dbparam("@homepage2", item["pdfSrc"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepage3", item["src"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertproductform @formId,@postGroup,@postName,@number,@version,@subject,@homepageMomo,@mb,@homepage1,@homepage2,@homepage3,@body;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            return new statusModels() { status = "istrue" };
        }

        public string checkItemValue(List<Dictionary<string, object>> items)
        {
            foreach (var item in items)
            {
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
                }*/
                switch (item["body"].ToString().TrimEnd())
                {
                    case "":
                        return "備註尚未填寫";
                }
            }
            return "";
        }
    }
}