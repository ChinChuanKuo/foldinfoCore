using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Net;
using System.Text.Json;
using FOLDINFOCore.App_Code;

namespace FOLDINFOCore.Models
{
    public class IsoFileClass
    {
        public sItemsModels GetSearchModels(otherData otherData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.countisofileform;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = int.Parse(otherData.values.TrimEnd()) / 10;
            DataTable mainRows = new DataTable();
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchisofileform @startId,@endId;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sItemsModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postGroups", $"登入單位：{dr["post_group"].ToString().TrimEnd()}_{dr["postname"].ToString().TrimEnd()}" }, { "objs", $"製程別：{dr["obj"].ToString().TrimEnd()}%" }, { "issuedates", $"申請日期：{dr["issuedate"].ToString().TrimEnd()}" }, { "releasedates", $"發行日期：{dr["releasedate"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "homepage1s", $"客戶：{dr["homepage1"].ToString().TrimEnd()}" }, { "bodys", $"說明：{dr["body"].ToString().TrimEnd()}" }, { "itemDelete", deletePermission(otherData.userid.TrimEnd(), dr["postname"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd()) } });
            }
            return new sItemsModels() { showItem = itemCount != int.Parse(otherData.values.TrimEnd()) + mainRows.Rows.Count, itemCount = itemCount, items = items, status = "istrue" };
        }

        public sOptonModels GetFilterModels(userData userData, string cuurip)
        {
            database database = new database();
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            string[] tileArray = new string[] { "製程別", "機種", "M/B" };
            string[] fieldArray = new string[] { "obj", "homepage_momo", "mb" };
            foreach (var item in fieldArray.Select((value, i) => new { i, value }))
            {
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@value", item.value));
                List<Dictionary<string, object>> optionitems = new List<Dictionary<string, object>>();
                optionitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", "" } });
                foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.filisofilemodule @value;", dbparamlist).Rows)
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
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", sqlCode == "" ? "exec web.countisofileform;" : "exec web.countfiltisofileform @sqlCode;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = int.Parse(sScroData.value.TrimEnd()) / 10;
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", sqlCode == "" ? "exec web.searchisofileform @startId,@endId;" : "exec web.sfiltisofileform @startId,@endId,@sqlCode;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postGroups", $"登入單位：{dr["post_group"].ToString().TrimEnd()}_{dr["postname"].ToString().TrimEnd()}" }, { "objs", $"製程別：{dr["obj"].ToString().TrimEnd()}%" }, { "issuedates", $"申請日期：{dr["issuedate"].ToString().TrimEnd()}" }, { "releasedates", $"發行日期：{dr["releasedate"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "homepage1s", $"客戶：{dr["homepage1"].ToString().TrimEnd()}" }, { "bodys", $"說明：{dr["body"].ToString().TrimEnd()}" }, { "itemDelete", deletePermission(sScroData.newid.TrimEnd(), dr["postname"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd()) } });
                total++;
            }
            return new itemsModels() { showItem = itemCount != int.Parse(sScroData.value.TrimEnd()) + total, items = items };
        }

        public sOptonModels GetSRecordModels(userData userData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@page", "isofile"));
            dbparamlist.Add(new dbparam("@together", "isofileall"));
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
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.countfiltisofileform @sqlCode;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = 0, total = 0;
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.sfiltisofileform @startId,@endId,@sqlCode;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postGroups", $"登入單位：{dr["post_group"].ToString().TrimEnd()}_{dr["postname"].ToString().TrimEnd()}" }, { "objs", $"製程別：{dr["obj"].ToString().TrimEnd()}%" }, { "issuedates", $"申請日期：{dr["issuedate"].ToString().TrimEnd()}" }, { "releasedates", $"發行日期：{dr["releasedate"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "homepage1s", $"客戶：{dr["homepage1"].ToString().TrimEnd()}" }, { "bodys", $"說明：{dr["body"].ToString().TrimEnd()}" } });
                total++;
            }
            switch (checkRecord(otherData.values.TrimEnd()))
            {
                case true:
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@page", "isofile"));
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
            return record != "";
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
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.countfiltisofileform @sqlCode;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = 0, total = 0;
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.sfiltisofileform @startId,@endId,@sqlCode;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postGroups", $"登入單位：{dr["post_group"].ToString().TrimEnd()}_{dr["postname"].ToString().TrimEnd()}" }, { "objs", $"製程別：{dr["obj"].ToString().TrimEnd()}%" }, { "issuedates", $"申請日期：{dr["issuedate"].ToString().TrimEnd()}" }, { "releasedates", $"發行日期：{dr["releasedate"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "homepage1s", $"客戶：{dr["homepage1"].ToString().TrimEnd()}" }, { "bodys", $"說明：{dr["body"].ToString().TrimEnd()}" } });
                total++;
            }
            return new sItemsModels() { showItem = itemCount != total, itemCount = itemCount, items = items, status = "istrue" };
        }

        public string filterSqlCode(int index, string value)
        {
            switch (index)
            {
                case 0:
                    return $"obj = '{value}'";
                case 1:
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
                result += checkFilterCode(result, item, new string[] { "and" }, $"( lower(number) like '%{item.ToLower()}%' or lower(version) like '%{item.ToLower()}%' or lower(post_group) like '%{item.ToLower()}%' or lower(postname) like '%{item.ToLower()}%' or lower(subject) like '%{item.ToLower()}%' or lower(obj) like '%{item.ToLower()}%' or lower(homepage_momo) like '%{item.ToLower()}%' or lower(mb) like '%{item.ToLower()}%' or lower(homepage1) like '%{item.ToLower()}%' or lower(body) like '%{item.ToLower()}%' )");
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
            if (new database().checkActiveSql("mssql", "flyfnstring", "delete from dbo.isoFile where id = @id;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            return new statusModels() { status = "istrue" };
        }

        public sOptonModels GetSListModels(dFormData dFormData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchisofilelist @formId;", dbparamlist).Rows)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@newid", dr["inoper"].ToString().TrimEnd()));
                items.Add(new Dictionary<string, object>() { { "id", dr["id"].ToString().TrimEnd() }, { "content", dr["content"].ToString().TrimEnd() }, { "inoper", new database().checkSelectSql("mssql", "flyfnstring", "exec web.checksiteberform @newid;", dbparamlist).Rows[0]["username"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public sRowsModels GetPreviousModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.previousisofiledeta @id;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sRowsModels() { status = "nodata" };
            }
            string[] objArray = new string[] { "", "DIP", "DOA", "IPQC", "IQC", "NA", "OQC", "PreTest", "QA校驗", "RMA", "SMT", "加工", "包裝", "系測", "其它", "板測", "板測,系測", "客訴", "客驗", "組裝", "組裝,包裝", "週邊", "製程", "銷退" };
            List<Dictionary<string, object>> objitems = new List<Dictionary<string, object>>();
            foreach (var obj in objArray)
            {
                objitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", obj } });
            }
            List<Dictionary<string, object>> mbitems = new List<Dictionary<string, object>>();
            foreach (var item in mainRows.Rows[0]["mb"].ToString().TrimEnd().Split(',').Select((value, i) => new { i, value }))
            {
                if (item.value != "")
                {
                    mbitems.Add(new Dictionary<string, object>() { { "mbId", item.i }, { "mbValue", item.value } });
                }
            }
            dbparamlist.Clear();
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
                    dbparamlist.Clear();
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
                    dbparamlist.Clear();
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
            items.Add(new Dictionary<string, object>() { { "postdate", mainRows.Rows[0]["postdate"].ToString().TrimEnd() }, { "postinfo", $"{mainRows.Rows[0]["post_group"].ToString().TrimEnd()}-{mainRows.Rows[0]["postname"].ToString().TrimEnd()}" }, { "subject", mainRows.Rows[0]["subject"].ToString().TrimEnd() }, { "showObjMenu", false }, { "objitems", objitems.ToArray() }, { "obj", mainRows.Rows[0]["obj"].ToString().TrimEnd() }, { "homepageMomo", mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd() }, { "mbitems", mbitems.ToArray() }, { "showMtstMenu", false }, { "mtstitems", mtstitems.ToArray() }, { "mtst", "" }, { "showMbstMenu", false }, { "mbstitems", new List<Dictionary<string, object>>().ToArray() }, { "mbst", "" }, { "pageitems", pageitems.ToArray() }, { "custom", "" }, { "showCustom", false }, { "customitems", new List<Dictionary<string, object>>().ToArray() }, { "showDrop", false }, { "showFile", showFile }, { "showImage", showImage }, { "showVideo", showVideo }, { "showAudio", showAudio }, { "src", src }, { "path", database.connectionString("folderHttps") }, { "original", original }, { "encryption", encryption }, { "extension", extension }, { "date", date }, { "showPdfDrop", false }, { "showPdfFile", showPdfFile }, { "showPdfImage", showPdfImage }, { "showPdfVideo", showPdfVideo }, { "showPdfAudio", showPdfAudio }, { "pdfSrc", pdfSrc }, { "pdfPath", database.connectionString("folderHttps") }, { "pdfOriginal", pdfOriginal }, { "pdfEncryption", pdfEncryption }, { "pdfExtension", pdfExtension }, { "pdfDate", pdfDate }, { "showTotal", false }, { "first", "1" }, { "final", "0" }, { "body", mainRows.Rows[0]["body"].ToString().TrimEnd() }, { "releaseDate", mainRows.Rows[0]["releasedate"].ToString().TrimEnd().Replace("/", "-") }, { "limit", false }, { "endDate", mainRows.Rows[0]["end_date"].ToString().TrimEnd().Replace("/", "-") }, { "formInsert", insertPermission(mainRows.Rows[0]["id"].ToString().TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd(), mainRows.Rows[0]["sign1"].ToString().TrimEnd(), mainRows.Rows[0]["sign2"].ToString().TrimEnd(), mainRows.Rows[0]["releasedate"].ToString().TrimEnd()) }, { "formDelete", deletePermission(dFormData.newid.TrimEnd(), mainRows.Rows[0]["postname"].ToString().TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd()) }, { "formEdit", editPermission(dFormData.newid.TrimEnd(), mainRows.Rows[0]["postname"].ToString().TrimEnd(), mainRows.Rows[0]["releasedate"].ToString().TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd(), mainRows.Rows[0]["sign1"].ToString().TrimEnd(), mainRows.Rows[0]["sign2"].ToString().TrimEnd()) }, { "formSend", sendPermission(mainRows.Rows[0]["signing"].ToString().TrimEnd()) }, { "formModify", false } });
            return new sRowsModels() { formId = mainRows.Rows[0]["id"].ToString().TrimEnd(), tile = $"{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}", items = items, status = "istrue" };
        }

        public sRowsModels GetNextModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.nextisofiledeta @id;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sRowsModels() { status = "nodata" };
            }
            string[] objArray = new string[] { "", "DIP", "DOA", "IPQC", "IQC", "NA", "OQC", "PreTest", "QA校驗", "RMA", "SMT", "加工", "包裝", "系測", "其它", "板測", "板測,系測", "客訴", "客驗", "組裝", "組裝,包裝", "週邊", "製程", "銷退" };
            List<Dictionary<string, object>> objitems = new List<Dictionary<string, object>>();
            foreach (var obj in objArray)
            {
                objitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", obj } });
            }
            List<Dictionary<string, object>> mbitems = new List<Dictionary<string, object>>();
            foreach (var item in mainRows.Rows[0]["mb"].ToString().TrimEnd().Split(',').Select((value, i) => new { i, value }))
            {
                if (item.value != "")
                {
                    mbitems.Add(new Dictionary<string, object>() { { "mbId", item.i }, { "mbValue", item.value } });
                }
            }
            dbparamlist.Clear();
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
                    dbparamlist.Clear();
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
                    dbparamlist.Clear();
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
            items.Add(new Dictionary<string, object>() { { "postdate", mainRows.Rows[0]["postdate"].ToString().TrimEnd() }, { "postinfo", $"{mainRows.Rows[0]["post_group"].ToString().TrimEnd()}-{mainRows.Rows[0]["postname"].ToString().TrimEnd()}" }, { "subject", mainRows.Rows[0]["subject"].ToString().TrimEnd() }, { "showObjMenu", false }, { "objitems", objitems.ToArray() }, { "obj", mainRows.Rows[0]["obj"].ToString().TrimEnd() }, { "homepageMomo", mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd() }, { "mbitems", mbitems.ToArray() }, { "showMtstMenu", false }, { "mtstitems", mtstitems.ToArray() }, { "mtst", "" }, { "showMbstMenu", false }, { "mbstitems", new List<Dictionary<string, object>>().ToArray() }, { "mbst", "" }, { "pageitems", pageitems.ToArray() }, { "custom", "" }, { "showCustom", false }, { "customitems", new List<Dictionary<string, object>>().ToArray() }, { "showDrop", false }, { "showFile", showFile }, { "showImage", showImage }, { "showVideo", showVideo }, { "showAudio", showAudio }, { "src", src }, { "path", database.connectionString("folderHttps") }, { "original", original }, { "encryption", encryption }, { "extension", extension }, { "date", date }, { "showPdfDrop", false }, { "showPdfFile", showPdfFile }, { "showPdfImage", showPdfImage }, { "showPdfVideo", showPdfVideo }, { "showPdfAudio", showPdfAudio }, { "pdfSrc", pdfSrc }, { "pdfPath", database.connectionString("folderHttps") }, { "pdfOriginal", pdfOriginal }, { "pdfEncryption", pdfEncryption }, { "pdfExtension", pdfExtension }, { "pdfDate", pdfDate }, { "showTotal", false }, { "first", "1" }, { "final", "0" }, { "body", mainRows.Rows[0]["body"].ToString().TrimEnd() }, { "releaseDate", mainRows.Rows[0]["releasedate"].ToString().TrimEnd().Replace("/", "-") }, { "limit", false }, { "endDate", mainRows.Rows[0]["end_date"].ToString().TrimEnd().Replace("/", "-") }, { "formInsert", insertPermission(mainRows.Rows[0]["id"].ToString().TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd(), mainRows.Rows[0]["sign1"].ToString().TrimEnd(), mainRows.Rows[0]["sign2"].ToString().TrimEnd(), mainRows.Rows[0]["releasedate"].ToString().TrimEnd()) }, { "formDelete", deletePermission(dFormData.newid.TrimEnd(), mainRows.Rows[0]["postname"].ToString().TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd()) }, { "formEdit", editPermission(dFormData.newid.TrimEnd(), mainRows.Rows[0]["postname"].ToString().TrimEnd(), mainRows.Rows[0]["releasedate"].ToString().TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd(), mainRows.Rows[0]["sign1"].ToString().TrimEnd(), mainRows.Rows[0]["sign2"].ToString().TrimEnd()) }, { "formSend", sendPermission(mainRows.Rows[0]["signing"].ToString().TrimEnd()) }, { "formModify", false } });
            return new sRowsModels() { formId = mainRows.Rows[0]["id"].ToString().TrimEnd(), tile = $"{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}", items = items, status = "istrue" };
        }

        public sRowsModels GetSItemModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchisofiledeta @id;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sRowsModels() { status = "nodata" };
            }
            string[] objArray = new string[] { "", "DIP", "DOA", "IPQC", "IQC", "NA", "OQC", "PreTest", "QA校驗", "RMA", "SMT", "加工", "包裝", "系測", "其它", "板測", "板測,系測", "客訴", "客驗", "組裝", "組裝,包裝", "週邊", "製程", "銷退" };
            List<Dictionary<string, object>> objitems = new List<Dictionary<string, object>>();
            foreach (var obj in objArray)
            {
                objitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", obj } });
            }
            List<Dictionary<string, object>> mbitems = new List<Dictionary<string, object>>();
            foreach (var item in mainRows.Rows[0]["mb"].ToString().TrimEnd().Split(',').Select((value, i) => new { i, value }))
            {
                if (item.value != "")
                {
                    mbitems.Add(new Dictionary<string, object>() { { "mbId", item.i }, { "mbValue", item.value } });
                }
            }
            dbparamlist.Clear();
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
                    dbparamlist.Clear();
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
                    dbparamlist.Clear();
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
            items.Add(new Dictionary<string, object>() { { "postdate", mainRows.Rows[0]["postdate"].ToString().TrimEnd() }, { "postinfo", $"{mainRows.Rows[0]["post_group"].ToString().TrimEnd()}-{mainRows.Rows[0]["postname"].ToString().TrimEnd()}" }, { "subject", mainRows.Rows[0]["subject"].ToString().TrimEnd() }, { "showObjMenu", false }, { "objitems", objitems.ToArray() }, { "obj", mainRows.Rows[0]["obj"].ToString().TrimEnd() }, { "homepageMomo", mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd() }, { "mbitems", mbitems.ToArray() }, { "showMtstMenu", false }, { "mtstitems", mtstitems.ToArray() }, { "mtst", "" }, { "showMbstMenu", false }, { "mbstitems", new List<Dictionary<string, object>>().ToArray() }, { "mbst", "" }, { "pageitems", pageitems.ToArray() }, { "custom", "" }, { "showCustom", false }, { "customitems", new List<Dictionary<string, object>>().ToArray() }, { "showDrop", false }, { "showFile", showFile }, { "showImage", showImage }, { "showVideo", showVideo }, { "showAudio", showAudio }, { "src", src }, { "path", database.connectionString("folderHttps") }, { "original", original }, { "encryption", encryption }, { "extension", extension }, { "date", date }, { "showPdfDrop", false }, { "showPdfFile", showPdfFile }, { "showPdfImage", showPdfImage }, { "showPdfVideo", showPdfVideo }, { "showPdfAudio", showPdfAudio }, { "pdfSrc", pdfSrc }, { "pdfPath", database.connectionString("folderHttps") }, { "pdfOriginal", pdfOriginal }, { "pdfEncryption", pdfEncryption }, { "pdfExtension", pdfExtension }, { "pdfDate", pdfDate }, { "showTotal", false }, { "first", "1" }, { "final", "0" }, { "body", mainRows.Rows[0]["body"].ToString().TrimEnd() }, { "releaseDate", mainRows.Rows[0]["releasedate"].ToString().TrimEnd().Replace("/", "-") }, { "limit", false }, { "endDate", mainRows.Rows[0]["end_date"].ToString().TrimEnd().Replace("/", "-") }, { "formInsert", insertPermission(dFormData.formId.TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd(), mainRows.Rows[0]["sign1"].ToString().TrimEnd(), mainRows.Rows[0]["sign2"].ToString().TrimEnd(), mainRows.Rows[0]["releasedate"].ToString().TrimEnd()) }, { "formDelete", deletePermission(dFormData.newid.TrimEnd(), mainRows.Rows[0]["postname"].ToString().TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd()) }, { "formEdit", editPermission(dFormData.newid.TrimEnd(), mainRows.Rows[0]["postname"].ToString().TrimEnd(), mainRows.Rows[0]["releasedate"].ToString().TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd(), mainRows.Rows[0]["sign1"].ToString().TrimEnd(), mainRows.Rows[0]["sign2"].ToString().TrimEnd()) }, { "formSend", sendPermission(mainRows.Rows[0]["signing"].ToString().TrimEnd()) }, { "formModify", false } });
            return new sRowsModels() { formId = mainRows.Rows[0]["id"].ToString().TrimEnd(), tile = $"{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}", items = items, status = "istrue" };
        }

        public bool insertPermission(string id, string signing, string sign1, string sign2, string releasedate)
        {
            switch (releasedate)
            {
                case "":
                    return signing != "0" && sign1 != "" && sign2 != "";
            }
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", id));
            return new database().checkSelectSql("mssql", "flyfnstring", "exec web.nextisofiledeta @id;", dbparamlist).Rows.Count == 0;
        }

        public bool deletePermission(string newid, string postname, string signing)
        {
            switch (signing)
            {
                case "0":
                    database database = new database();
                    List<dbparam> dbparamlist = new List<dbparam>();
                    dbparamlist.Add(new dbparam("@newid", newid));
                    return database.checkSelectSql("mssql", "flyfnstring", "exec web.searchusername @newid;", dbparamlist).Rows[0]["username"].ToString().TrimEnd() == postname;
            }
            return false;
        }

        public bool editPermission(string newid, string postname, string releasedate, string signing, string sign1, string sign2)
        {
            switch (signing)
            {
                case "0":
                    database database = new database();
                    List<dbparam> dbparamlist = new List<dbparam>();
                    dbparamlist.Add(new dbparam("@newid", newid));
                    return database.checkSelectSql("mssql", "flyfnstring", "exec web.searchusername @newid;", dbparamlist).Rows[0]["username"].ToString().TrimEnd() == postname;
            }
            return releasedate == "" && sign1 != "" && sign2 != "";
        }

        public bool sendPermission(string signing)
        {
            return signing == "0";
        }

        public statusModels GetDeleteModels(dFormData dFormData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            if (new database().checkActiveSql("mssql", "flyfnstring", "exec web.deleteisofiledeta @formId,@inoper;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            return new statusModels() { status = "istrue" };
        }

        public statusModels GetOrderModels(iFormData iFormData, string cuurip)
        {
            string checkItems = checkItemValue(iFormData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", iFormData.formId.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "exec web.releaseisofileform @formId;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
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
                string[] usinfoArray = finalArray(item["postinfo"].ToString().TrimEnd(), "-");
                string[] nvionArray = finalArray(iFormData.tile.TrimEnd(), "-");
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", new sha256().new256("mssql", "flyfnstring")));
                dbparamlist.Add(new dbparam("@postGroup", usinfoArray[0]));
                dbparamlist.Add(new dbparam("@postName", usinfoArray[1]));
                dbparamlist.Add(new dbparam("@number", nvionArray[0]));
                dbparamlist.Add(new dbparam("@version", checkVersion(nvionArray[1], 1)));
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", mb));
                dbparamlist.Add(new dbparam("@homepage1", homepage1));
                dbparamlist.Add(new dbparam("@homepage2", ""));
                dbparamlist.Add(new dbparam("@homepage3", ""));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@releaseDate", ""));
                dbparamlist.Add(new dbparam("@endDate", ""));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertisofileform @formId,@postGroup,@postName,@number,@version,@subject,@obj,@homepageMomo,@mb,@homepage1,@homepage2,@homepage3,@body,@releaseDate,@endDate;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            return new statusModels() { status = "istrue" };
        }

        public string[] finalArray(string value, string split)
        {
            int lastIndex = value.LastIndexOf(split);
            return new string[] { value.Substring(0, lastIndex), value.Substring(lastIndex + 1, value.Length - lastIndex - 1) };
        }

        public string checkVersion(string value, int index)
        {
            string[] letterArray = new string[] { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
            return letterArray["0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ".IndexOf(value) + index];
        }

        public statusModels GetInsertModels(iFormData iFormData, string cuurip)
        {
            string checkItems = checkItemValue(iFormData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            insertLog(iFormData.formId.TrimEnd(), iFormData.items, iFormData.newid.TrimEnd());
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
                bool showFile = bool.Parse(item["showFile"].ToString().TrimEnd()),
                showPdfFile = bool.Parse(item["showPdfFile"].ToString().TrimEnd());
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", mb));
                dbparamlist.Add(new dbparam("@homepage1", homepage1));
                dbparamlist.Add(new dbparam("@homepage2", showPdfFile ? $"{item["pdfOriginal"].ToString().TrimEnd()}({item["pdfEncryption"].ToString().TrimEnd()}){item["pdfExtension"].ToString().TrimEnd()}" : ""));
                dbparamlist.Add(new dbparam("@homepage3", showFile ? $"{item["original"].ToString().TrimEnd()}({item["encryption"].ToString().TrimEnd()}){item["extension"].ToString().TrimEnd()}" : ""));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@releaseDate", item["releaseDate"].ToString().TrimEnd().Replace("-", "/")));
                dbparamlist.Add(new dbparam("@endDate", item["endDate"].ToString().TrimEnd().Replace("-", "/")));
                dbparamlist.Add(new dbparam("@id", iFormData.formId.TrimEnd()));
                if (database.checkActiveSql("mssql", "flyfnstring", "update dbo.isoFile set subject = @subject,obj = @obj,homepage_momo = @homepageMomo,mb = @mb,homepage1 = @homepage1,homepage2 = @homepage2,homepage3 = @homepage3,body = @body,releasedate = @releaseDate,end_date = @endDate where id = @id;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            return new statusModels() { status = "istrue" };
        }

        public statusModels GetSendModels(iFormData iFormData, string cuurip)
        {
            string checkItems = checkItemValue(iFormData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            insertLog(iFormData.formId.TrimEnd(), iFormData.items, iFormData.newid.TrimEnd());
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
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
                bool showFile = bool.Parse(item["showFile"].ToString().TrimEnd()),
                showPdfFile = bool.Parse(item["showPdfFile"].ToString().TrimEnd());
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", mb));
                dbparamlist.Add(new dbparam("@homepage1", homepage1));
                dbparamlist.Add(new dbparam("@homepage2", showPdfFile ? $"{item["pdfOriginal"].ToString().TrimEnd()}({item["pdfEncryption"].ToString().TrimEnd()}){item["pdfExtension"].ToString().TrimEnd()}" : ""));
                dbparamlist.Add(new dbparam("@homepage3", showFile ? $"{item["original"].ToString().TrimEnd()}({item["encryption"].ToString().TrimEnd()}){item["extension"].ToString().TrimEnd()}" : ""));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@releaseDate", item["releaseDate"].ToString().TrimEnd().Replace("-", "/")));
                dbparamlist.Add(new dbparam("@endDate", item["endDate"].ToString().TrimEnd().Replace("-", "/")));
                dbparamlist.Add(new dbparam("@id", iFormData.formId.TrimEnd()));
                if (database.checkActiveSql("mssql", "flyfnstring", "update dbo.isoFile set subject = @subject,obj = @obj,homepage_momo = @homepageMomo,mb = @mb,homepage1 = @homepage1,homepage2 = @homepage2,homepage3 = @homepage3,body = @body,releasedate = @releaseDate,end_date = @endDate where id = @id;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@signing", "1"));
            dbparamlist.Add(new dbparam("@id", iFormData.formId.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "update dbo.isoFile set signing = @signing where id = @id;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            dbparamlist.Clear();
            DataTable supeRows = new DataTable();
            dbparamlist.Add(new dbparam("@inoper", iFormData.newid.TrimEnd()));
            supeRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksupeber @inoper;", dbparamlist);
            dbparamlist.Add(new dbparam("@formId", iFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@newid", supeRows.Rows[0]["superid"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@value", "測試"));
            dbparamlist.Add(new dbparam("@link", ""));
            database.checkActiveSql("mssql", "flyfnstring", "exec web.insertnoticeform @formId,@newid,@inoper,@value,@link;", dbparamlist);
            dbparamlist.Clear();
            //dbparamlist.Add(new dbparam("@mAddrName", $"郭晉全,{supeRows.Rows[0]["supername"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mAddrName", $"郭晉全"));
            dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
            dbparamlist.Add(new dbparam("@mSubject", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」建立ISO檔案需簽核:{iFormData.tile.TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;text-align:center;'><div style='padding: 12px; border:2px solid white;'><div><h2 style='color:red;'>ISO SYSTEM NEWS</h2></div><div> <hr /></div><div><h3 style='color: red;'>建立ISO文件需簽核</h3></div><div style='font-size: 16px;'>{new datetime().sqldate("mssql", "flyfnstring")} {new datetime().sqltime("mssql", "flyfnstring")}</div><div><h4>請相關主管進行簽核或退簽此問題．</h4></div><div><h4>http://221.222.222.181:7250/signlistI#{iFormData.formId.TrimEnd()} => 請複製此連結</h4></div></div></div>"));
            database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist);
            return new statusModels() { status = "istrue" };
        }

        public string differentValue(string tile, string before, string after)
        {
            if (before != after) return $"{tile}: {before} -> {after} <br/>";
            return "";
        }

        public void insertLog(string id, List<Dictionary<string, object>> items, string newid)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", id));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchisofiledeta @id;", dbparamlist);
            if (mainRows.Rows[0]["sign1"].ToString().TrimEnd() != "" && mainRows.Rows[0]["sign2"].ToString().TrimEnd() != "")
            {
                string logStr = "";
                foreach (var item in items)
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
                    logStr += differentValue("文件名稱", mainRows.Rows[0]["subject"].ToString().TrimEnd(), item["subject"].ToString().TrimEnd());
                    logStr += differentValue("製程別", mainRows.Rows[0]["obj"].ToString().TrimEnd(), item["obj"].ToString().TrimEnd());
                    logStr += differentValue("機種", mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd(), item["homepageMomo"].ToString().TrimEnd());
                    logStr += differentValue("板類", mainRows.Rows[0]["mb"].ToString().TrimEnd(), mb);
                    logStr += differentValue("客戶", mainRows.Rows[0]["homepage1"].ToString().TrimEnd(), homepage1);
                    logStr += differentValue("說明", mainRows.Rows[0]["body"].ToString().TrimEnd(), item["body"].ToString().TrimEnd());
                    logStr += differentValue("到期日", mainRows.Rows[0]["end_date"].ToString().TrimEnd(), item["endDate"].ToString().TrimEnd());
                }
                if (logStr != "")
                {
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@id", id));
                    dbparamlist.Add(new dbparam("@value", logStr));
                    dbparamlist.Add(new dbparam("@inoper", newid));
                    new database().checkActiveSql("mssql", "flyfnstring", "exec web.insertisofilelog @id, @value, @inoper;", dbparamlist);
                }
            }
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
                switch (item["body"].ToString().TrimEnd())
                {
                    case "":
                        return "說明尚未填寫";
                }
                if (bool.Parse(item["limit"].ToString().TrimEnd()) && item["endDate"].ToString().TrimEnd() == "")
                {
                    return "版本期限-到期日尚未填寫";
                }
            }
            return "";
        }
    }
}