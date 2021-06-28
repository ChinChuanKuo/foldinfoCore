using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Net;
using System.Text.Json;
using foldinfoCore.App_Code;

namespace foldinfoCore.Models
{
    public class ProductClass
    {
        public sItemsModels GetSearchModels(otherData otherData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.countproductform;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = int.Parse(otherData.values.TrimEnd()) / 10;
            DataTable mainRows = new DataTable();
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchproductform @startId,@endId;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sItemsModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postdates", $"提出日期：{dr["postdate"].ToString().TrimEnd()}" }, { "postGroups", $"提出單位：{dr["post_group"].ToString().TrimEnd()}_{dr["postname"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}%" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "homepage1s", $"客戶：{dr["homepage1"].ToString().TrimEnd()}" }, { "bodys", $"備註：{dr["Body"].ToString().TrimEnd()}" } });
            }
            return new sItemsModels() { showItem = itemCount != int.Parse(otherData.values.TrimEnd()) + mainRows.Rows.Count, itemCount = itemCount, items = items, status = "istrue" };
        }

        public sOptonModels GetFilterModels(userData userData, string cuurip)
        {
            database database = new database();
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            string[] tileArray = new string[] { "機種", "M/B" };
            string[] fieldArray = new string[] { "homepage_momo", "mb" };
            foreach (var item in fieldArray.Select((value, i) => new { i, value }))
            {
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@value", item.value));
                List<Dictionary<string, object>> optionitems = new List<Dictionary<string, object>>();
                optionitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", "" } });
                foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.filproductmodule @value;", dbparamlist).Rows)
                {
                    optionitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["value"].ToString().TrimEnd() } });
                }
                items.Add(new Dictionary<string, object>() { { "index", item.i }, { "tile", tileArray[item.i] }, { "filtValue", "" }, { "showMenu", false }, { "optionitems", optionitems } });
            }
            return new sOptonModels() { items = items };
        }

        public itemsModels GetScrollModels(sScroData sScroData, string cuurip)
        {
            string sqlCode = "";
            foreach (var item in sScroData.items)
            {
                sqlCode += checkSqlCode(sqlCode, filterSqlCode(int.Parse(item["index"].ToString().TrimEnd()), item["filtValue"].ToString().TrimEnd()));
            }
            if (sScroData.record.TrimEnd() != "")
            {
                sqlCode += checkSqlCode(sqlCode, filterSqlRecord(sScroData.record.TrimEnd()));
            }
            List<dbparam> dbparamlist = new List<dbparam>();
            if (sqlCode != "")
            {
                dbparamlist.Add(new dbparam("@sqlCode", sqlCode));
            }
            int total = 0;
            database database = new database();
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", sqlCode == "" ? "exec web.countproductform;" : "exec web.countfiltproductform @sqlCode;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = int.Parse(sScroData.value.TrimEnd()) / 10;
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", sqlCode == "" ? "exec web.searchproductform @startId,@endId;" : "exec web.sfiltproductform @startId,@endId,@sqlCode;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postdates", $"提出日期：{dr["postdate"].ToString().TrimEnd()}" }, { "postGroups", $"提出單位：{dr["post_group"].ToString().TrimEnd()}_{dr["postname"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}%" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "homepage1s", $"客戶：{dr["homepage1"].ToString().TrimEnd()}" }, { "bodys", $"備註：{dr["Body"].ToString().TrimEnd()}" } });
                total++;
            }
            return new itemsModels() { showItem = itemCount != int.Parse(sScroData.value.TrimEnd()) + total, items = items };
        }

        public sOptonModels GetSRecordModels(userData userData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@page", "product"));
            dbparamlist.Add(new dbparam("@together", "productall"));
            dbparamlist.Add(new dbparam("@inoper", userData.userid.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchrecordlog @page,@together,@inoper;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "cordIcon", dr["icon"].ToString().TrimEnd() }, { "cordValue", dr["value"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public sItemsModels GetSFiltCordModels(otherData otherData, string cuurip, string userAgent)
        {
            string sqlCode = otherData.values.TrimEnd() != "" ? checkSqlCode("", filterSqlRecord(otherData.values.TrimEnd())) : "";
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@sqlCode", sqlCode));
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.countfiltproductform @sqlCode;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = 0, total = 0;
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.sfiltproductform @startId,@endId,@sqlCode;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postdates", $"提出日期：{dr["postdate"].ToString().TrimEnd()}" }, { "postGroups", $"提出單位：{dr["post_group"].ToString().TrimEnd()}_{dr["postname"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}%" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "homepage1s", $"客戶：{dr["homepage1"].ToString().TrimEnd()}" }, { "bodys", $"備註：{dr["Body"].ToString().TrimEnd()}" } });
                total++;
            }
            switch (checkRecord(otherData.values.TrimEnd()))
            {
                case true:
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@page", "product"));
                    dbparamlist.Add(new dbparam("@value", otherData.values.TrimEnd()));
                    dbparamlist.Add(new dbparam("@externip", cuurip));
                    dbparamlist.Add(new dbparam("@hostname", Dns.GetHostEntry(cuurip).HostName.IndexOf('.') == -1 ? Dns.GetHostEntry(cuurip).HostName : Dns.GetHostEntry(cuurip).HostName.Split('.')[0]));
                    dbparamlist.Add(new dbparam("@browser", new information().browser(userAgent)));
                    dbparamlist.Add(new dbparam("@inoper", otherData.userid.TrimEnd()));
                    database.checkActiveSql("mssql", "flyfnstring", "exec web.insertrecordform @page,@value,@externip,@hostname,@browser,@inoper;", dbparamlist);
                    break;
            }
            return new sItemsModels() { showItem = itemCount != total, itemCount = itemCount, items = items, status = "istrue" };
        }

        public bool checkRecord(string record)
        {
            switch (record)
            {
                case "":
                    return false;
            }
            return true;
        }

        public sItemsModels GetSFilterModels(sFiltData sFiltData, string cuurip)
        {
            string sqlCode = "";
            foreach (var item in sFiltData.items)
            {
                if (item["index"].ToString().TrimEnd() != sFiltData.index.ToString().TrimEnd())
                {
                    sqlCode += checkSqlCode(sqlCode, filterSqlCode(int.Parse(item["index"].ToString().TrimEnd()), item["filtValue"].ToString().TrimEnd()));
                }
            }
            if (sFiltData.value.TrimEnd() != "")
            {
                sqlCode += checkSqlCode(sqlCode, filterSqlCode(sFiltData.index, sFiltData.value.TrimEnd()));
            }
            if (sFiltData.record.TrimEnd() != "")
            {
                sqlCode += checkSqlCode(sqlCode, filterSqlRecord(sFiltData.record.TrimEnd()));
            }
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@sqlCode", sqlCode));
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.countfiltproductform @sqlCode;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = 0, total = 0;
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.sfiltproductform @startId,@endId,@sqlCode;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postdates", $"提出日期：{dr["postdate"].ToString().TrimEnd()}" }, { "postGroups", $"提出單位：{dr["post_group"].ToString().TrimEnd()}_{dr["postname"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}%" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "homepage1s", $"客戶：{dr["homepage1"].ToString().TrimEnd()}" }, { "bodys", $"備註：{dr["Body"].ToString().TrimEnd()}" } });
                total++;
            }
            return new sItemsModels() { showItem = itemCount != total, itemCount = itemCount, items = items, status = "istrue" };
        }

        public string filterSqlCode(int index, string value)
        {
            switch (index)
            {
                case 0:
                    return $"homepage_momo = '{value}'";
            }
            return $"mb = '{value}'";
        }

        public string checkSqlCode(string sqlCode, string filterCode)
        {
            switch (sqlCode)
            {
                case "":
                    return $"where {filterCode}";
            }
            return $" and {filterCode}";
        }

        public string filterSqlRecord(string value)
        {
            string result = "";
            foreach (string item in value.Split(' '))
            {
                result += checkFilterCode(result, item, new string[] { "and" }, $"( lower(number) like '%{item.ToLower()}%' or lower(version) like '%{item.ToLower()}%' or lower(post_group) like '%{item.ToLower()}%' or lower(postname) like '%{item.ToLower()}%' or lower(homepage_momo) like '%{item.ToLower()}%' or lower(mb) like '%{item.ToLower()}%' or lower(homepage1) like '%{item.ToLower()}%' )");
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

        public statusModels GetClearModels(dFormData dFormData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            if (new database().checkActiveSql("mssql", "flyfnstring", "delete from dbo.prodSide where id = @id;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            return new statusModels() { status = "istrue" };
        }

        public sRowsModels GetSItemModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchproductdeta @id;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sRowsModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> mbitems = new List<Dictionary<string, object>>();
            foreach (var item in mainRows.Rows[0]["mb"].ToString().TrimEnd().Split(',').Select((value, i) => new { i, value }))
            {
                if (item.value != "")
                {
                    mbitems.Add(new Dictionary<string, object>() { { "mbId", item.i }, { "mbValue", item.value } });
                }
            }
            List<Dictionary<string, object>> mtstitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flycsastring", "exec dbo.searchallinventform;", dbparamlist).Rows)
            {
                mtstitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["mb"].ToString().TrimEnd() } });
            }
            List<Dictionary<string, object>> pageitems = new List<Dictionary<string, object>>();
            foreach (var item in mainRows.Rows[0]["homepage1"].ToString().TrimEnd().Split(',').Select((value, i) => new { i, value }))
            {
                if (item.value != "")
                {
                    pageitems.Add(new Dictionary<string, object>() { { "mbId", item.i }, { "mbValue", item.value } });
                }
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
                        int leftPoint = mainRows.Rows[0]["homepage3"].ToString().TrimEnd().LastIndexOf("(") + 1, rightPoint = mainRows.Rows[0]["homepage3"].ToString().TrimEnd().LastIndexOf(")");
                        original = mainRows.Rows[0]["homepage3"].ToString().TrimEnd().Substring(0, leftPoint - 1);
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
                        int leftPoint = mainRows.Rows[0]["homepage2"].ToString().TrimEnd().LastIndexOf("(") + 1, rightPoint = mainRows.Rows[0]["homepage2"].ToString().TrimEnd().LastIndexOf(")");
                        pdfOriginal = mainRows.Rows[0]["homepage2"].ToString().TrimEnd().Substring(0, leftPoint - 1);
                        pdfEncryption = mainRows.Rows[0]["homepage2"].ToString().TrimEnd().Substring(leftPoint, rightPoint - leftPoint);
                        pdfExtension = beforeExtension;
                        pdfSrc = fileRows.Rows[0]["flImages"].ToString().TrimEnd() == "1" && fileRows.Rows[0]["flShowed"].ToString().TrimEnd() == "0" ? $"{fileRows.Rows[0]["original"].ToString().TrimEnd()}({fileRows.Rows[0]["encryption"].ToString().TrimEnd()}){fileRows.Rows[0]["extension"].ToString().TrimEnd()}" : $"{pdfOriginal}({pdfEncryption}){pdfExtension}";
                    }
                    break;
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "postdate", mainRows.Rows[0]["postdate"].ToString().TrimEnd() }, { "postinfo", $"{mainRows.Rows[0]["post_group"].ToString().TrimEnd()}-{mainRows.Rows[0]["postname"].ToString().TrimEnd()}" }, { "subject", mainRows.Rows[0]["subject"].ToString().TrimEnd() }, { "homepageMomo", mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd() }, { "mbitems", mbitems }, { "showMtstMenu", false }, { "mtstitems", mtstitems }, { "mtst", "" }, { "showMbstMenu", false }, { "mbstitems", new List<Dictionary<string, object>>() }, { "mbst", "" }, { "pageitems", pageitems }, { "custom", "" }, { "showCustom", false }, { "customitems", new List<Dictionary<string, object>>() }, { "showDrop", false }, { "showFile", showFile }, { "showImage", showImage }, { "showVideo", showVideo }, { "showAudio", showAudio }, { "src", src }, { "path", database.connectionString("folderHttps") }, { "original", original }, { "encryption", encryption }, { "extension", extension }, { "date", date }, { "showPdfDrop", false }, { "showPdfFile", showPdfFile }, { "showPdfImage", showPdfImage }, { "showPdfVideo", showPdfVideo }, { "showPdfAudio", showPdfAudio }, { "pdfSrc", pdfSrc }, { "pdfPath", database.connectionString("folderHttps") }, { "pdfOriginal", pdfOriginal }, { "pdfEncryption", pdfEncryption }, { "pdfExtension", pdfExtension }, { "pdfDate", pdfDate }, { "showTotal", false }, { "first", "1" }, { "final", "0" }, { "body", mainRows.Rows[0]["Body"].ToString().TrimEnd() }, { "formModify", false } });
            return new sRowsModels() { formId = mainRows.Rows[0]["id"].ToString().TrimEnd(), tile = $"{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}", items = items, status = "istrue" };
        }

        public statusModels GetInsertModels(iFormData iFormData, string cuurip)
        {
            string checkItems = checkItemValue(iFormData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            database database = new database();
            foreach (var item in iFormData.items)
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
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", mb));
                dbparamlist.Add(new dbparam("@homepage1", homepage1));
                dbparamlist.Add(new dbparam("@homepage2", item["pdfSrc"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepage3", item["src"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@id", iFormData.formId.TrimEnd()));
                if (database.checkActiveSql("mssql", "flyfnstring", "update dbo.prodSide set subject = @subject,homepage_momo = @homepageMomo,mb = @mb,homepage1 = @homepage1,homepage2 = @homepage2,homepage3 = @homepage3,Body = @body where id = @id;", dbparamlist) != "istrue")
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