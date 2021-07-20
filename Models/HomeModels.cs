using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Net;
using foldinfoCore.App_Code;

namespace foldinfoCore.Models
{
    public class HomeClass
    {
        public sItemsModels GetSearchModels(otherData otherData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.countreportform;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = int.Parse(otherData.values.TrimEnd()) / 10;
            DataTable mainRows = new DataTable();
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchreportform @startId,@endId;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sItemsModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postdates", $"提出日期：{dr["postdate"].ToString().TrimEnd()}" }, { "postGroups", $"提出單位：{dr["post_group"].ToString().TrimEnd()}/{dr["postname"].ToString().TrimEnd()}" }, { "fails", $"不良率：{(float.Parse(dr["failure"].ToString().TrimEnd()) * 100).ToString("F2").TrimEnd()}%" }, { "homepage1s", $"客戶/廠商：{dr["homepage1"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "objs", $"品異來源：{dr["obj"].ToString().TrimEnd()}" }, { "worknumbers", $"來源單號：{dr["worknumber"].ToString().TrimEnd()}" }, { "repliers", $"處理人：{dr["replier"].ToString().TrimEnd()}" }, { "issuesorts", $"原因分類：{dr["issuesort"].ToString().TrimEnd()}_{dr["causeclass"].ToString().TrimEnd()}" }, { "belongs", $"責任單位：{dr["belong"].ToString().TrimEnd()} {dr["belonger"].ToString().TrimEnd()}" }, { "stages", $"處理狀態：{dr["stage"].ToString().TrimEnd()}" }, { "colors", colorProcess(dr["sign2"].ToString().TrimEnd(), dr["stage"].ToString().TrimEnd()) }, { "status", signProcess(dr["signing"].ToString().TrimEnd(), dr["sign2"].ToString().TrimEnd(), dr["stage"].ToString().TrimEnd()) }, { "itemPassed", addPassPermission(dr["signing"].ToString().TrimEnd(), dr["sign2"].ToString().TrimEnd(), otherData.userid.TrimEnd()) }, { "itemPlused", checkPassitem(dr["pn"].ToString().TrimEnd()) }, { "itemDelete", unsendPermission(otherData.userid.TrimEnd(), dr["postname"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd()) } });
            }
            return new sItemsModels() { showItem = itemCount != int.Parse(otherData.values.TrimEnd()) + mainRows.Rows.Count, itemCount = itemCount, items = items, status = "istrue" };
        }

        public sOptonModels GetFilterModels(userData userData, string cuurip)
        {
            database database = new database();
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            string[] tileArray = new string[] { "品異來源", "機種", "M/B", "生產樓層", "責任單位", "原因分類", "處理狀態" };
            string[] fieldArray = new string[] { "obj", "homepage_momo", "mb", "floor", "belong", "issuesort", "stage" };
            foreach (var item in fieldArray.Select((value, i) => new { i, value }))
            {
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@value", item.value));
                List<Dictionary<string, object>> optionitems = new List<Dictionary<string, object>>();
                optionitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", "" } });
                foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.filreportmodule @value;", dbparamlist).Rows)
                {
                    optionitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["value"].ToString().TrimEnd() } });
                }
                items.Add(new Dictionary<string, object>() { { "index", item.i }, { "tile", tileArray[item.i] }, { "filtValue", "" }, { "showMenu", false }, { "optionitems", optionitems.ToArray() } });
            }
            return new sOptonModels() { items = items };
        }

        public itemsModels GetScrollModels(sDesoData sDesoData, string cuurip)
        {
            string sqlCode = "";
            foreach (var item in sDesoData.items)
            {
                sqlCode += checkSqlCode(sqlCode, filterSqlCode(int.Parse(item["index"].ToString().TrimEnd()), item["filtValue"].ToString().TrimEnd()));
            }
            string firdate = string.IsNullOrWhiteSpace(sDesoData.firdate) ? "" : sDesoData.firdate.TrimEnd().Replace('-', '/'), secdate = string.IsNullOrWhiteSpace(sDesoData.secdate) ? "" : sDesoData.secdate.TrimEnd().Replace('-', '/');
            if (firdate != "" || secdate != "")
            {
                sqlCode += checkSqlCode(sqlCode, filterSqlDate(firdate, secdate));
            }
            if (sDesoData.record.TrimEnd() != "")
            {
                sqlCode += checkSqlCode(sqlCode, filterSqlRecord(sDesoData.record.TrimEnd(), sDesoData.newid.TrimEnd()));
            }
            List<dbparam> dbparamlist = new List<dbparam>();
            if (sqlCode != "")
            {
                dbparamlist.Add(new dbparam("@sqlCode", sqlCode));
            }
            int total = 0;
            database database = new database();
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", sqlCode == "" ? "exec web.countreportform;" : "exec web.countfiltreportform @sqlCode;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = int.Parse(sDesoData.value.TrimEnd()) / 10;
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", sqlCode == "" ? "exec web.searchreportform @startId,@endId;" : "exec web.sfiltreportform @startId,@endId,@sqlCode;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postdates", $"提出日期：{dr["postdate"].ToString().TrimEnd()}" }, { "postGroups", $"提出單位：{dr["post_group"].ToString().TrimEnd()}/{dr["postname"].ToString().TrimEnd()}" }, { "fails", $"不良率：{(float.Parse(dr["failure"].ToString().TrimEnd()) * 100).ToString("F2").TrimEnd()}%" }, { "homepage1s", $"客戶/廠商：{dr["homepage1"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "objs", $"品異來源：{dr["obj"].ToString().TrimEnd()}" }, { "worknumbers", $"來源單號：{dr["worknumber"].ToString().TrimEnd()}" }, { "repliers", $"處理人：{dr["replier"].ToString().TrimEnd()}" }, { "issuesorts", $"原因分類：{dr["issuesort"].ToString().TrimEnd()}_{dr["causeclass"].ToString().TrimEnd()}" }, { "belongs", $"責任單位：{dr["belong"].ToString().TrimEnd()} {dr["belonger"].ToString().TrimEnd()}" }, { "stages", $"處理狀態：{dr["stage"].ToString().TrimEnd()}" }, { "colors", colorProcess(dr["sign2"].ToString().TrimEnd(), dr["stage"].ToString().TrimEnd()) }, { "status", signProcess(dr["signing"].ToString().TrimEnd(), dr["sign2"].ToString().TrimEnd(), dr["stage"].ToString().TrimEnd()) }, { "itemPassed", addPassPermission(dr["signing"].ToString().TrimEnd(), dr["sign2"].ToString().TrimEnd(), sDesoData.newid.TrimEnd()) }, { "itemPlused", checkPassitem(dr["pn"].ToString().TrimEnd()) }, { "itemDelete", unsendPermission(sDesoData.newid.TrimEnd(), dr["postname"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd()) } });
                total++;
            }
            return new itemsModels() { showItem = itemCount != int.Parse(sDesoData.value.TrimEnd()) + total, items = items };
        }

        public sOptonModels GetSRecordModels(userData userData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@page", "home"));
            dbparamlist.Add(new dbparam("@together", "homeall"));
            dbparamlist.Add(new dbparam("@inoper", userData.userid.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchrecordlog @page,@together,@inoper;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "cordIcon", dr["icon"].ToString().TrimEnd() }, { "cordValue", dr["value"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public sItemsModels GetSFiltDateModels(sFidtData sFidtData, string cuurip, string userAgent)
        {
            string sqlCode = "";
            string firdate = string.IsNullOrWhiteSpace(sFidtData.firdate) ? "" : sFidtData.firdate.TrimEnd().Replace('-', '/'), secdate = string.IsNullOrWhiteSpace(sFidtData.secdate) ? "" : sFidtData.secdate.TrimEnd().Replace('-', '/');
            if (firdate != "" || secdate != "")
            {
                sqlCode += checkSqlCode(sqlCode, filterSqlDate(firdate, secdate));
            }
            if (sFidtData.record.TrimEnd() != "")
            {
                sqlCode += checkSqlCode(sqlCode, filterSqlRecord(sFidtData.record.TrimEnd(), sFidtData.newid.TrimEnd()));
            }
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@sqlCode", sqlCode));
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.countfiltreportform @sqlCode;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = 0, total = 0;
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.sfiltreportform @startId,@endId,@sqlCode;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postdates", $"提出日期：{dr["postdate"].ToString().TrimEnd()}" }, { "postGroups", $"提出單位：{dr["post_group"].ToString().TrimEnd()}/{dr["postname"].ToString().TrimEnd()}" }, { "fails", $"不良率：{(float.Parse(dr["failure"].ToString().TrimEnd()) * 100).ToString("F2").TrimEnd()}%" }, { "homepage1s", $"客戶/廠商：{dr["homepage1"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "objs", $"品異來源：{dr["obj"].ToString().TrimEnd()}" }, { "worknumbers", $"來源單號：{dr["worknumber"].ToString().TrimEnd()}" }, { "repliers", $"處理人：{dr["replier"].ToString().TrimEnd()}" }, { "issuesorts", $"原因分類：{dr["issuesort"].ToString().TrimEnd()}_{dr["causeclass"].ToString().TrimEnd()}" }, { "belongs", $"責任單位：{dr["belong"].ToString().TrimEnd()} {dr["belonger"].ToString().TrimEnd()}" }, { "stages", $"處理狀態：{dr["stage"].ToString().TrimEnd()}" }, { "colors", colorProcess(dr["sign2"].ToString().TrimEnd(), dr["stage"].ToString().TrimEnd()) }, { "status", signProcess(dr["signing"].ToString().TrimEnd(), dr["sign2"].ToString().TrimEnd(), dr["stage"].ToString().TrimEnd()) }, { "itemPassed", addPassPermission(dr["signing"].ToString().TrimEnd(), dr["sign2"].ToString().TrimEnd(), sFidtData.newid.TrimEnd()) }, { "itemPlused", checkPassitem(dr["pn"].ToString().TrimEnd()) }, { "itemDelete", unsendPermission(sFidtData.newid.TrimEnd(), dr["postname"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd()) } });
                total++;
            }
            switch (checkRecord(sFidtData.record.TrimEnd()))
            {
                case true:
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@page", "home"));
                    dbparamlist.Add(new dbparam("@value", sFidtData.record.TrimEnd()));
                    dbparamlist.Add(new dbparam("@externip", cuurip));
                    dbparamlist.Add(new dbparam("@hostname", Dns.GetHostEntry(cuurip).HostName.IndexOf('.') == -1 ? Dns.GetHostEntry(cuurip).HostName : Dns.GetHostEntry(cuurip).HostName.Split('.')[0]));
                    dbparamlist.Add(new dbparam("@browser", new information().browser(userAgent)));
                    dbparamlist.Add(new dbparam("@inoper", sFidtData.newid.TrimEnd()));
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
                case "today":
                case "closed":
                case "pending":
                case "myself":
                    return false;
            }
            return true;
        }

        public sItemsModels GetSFilterModels(sDeftData sDeftData, string cuurip)
        {
            string sqlCode = "";
            foreach (var item in sDeftData.items)
            {
                if (item["index"].ToString().TrimEnd() != sDeftData.index.ToString().TrimEnd())
                {
                    sqlCode += checkSqlCode(sqlCode, filterSqlCode(int.Parse(item["index"].ToString().TrimEnd()), item["filtValue"].ToString().TrimEnd()));
                }
            }
            if (sDeftData.value.TrimEnd() != "")
            {
                sqlCode += checkSqlCode(sqlCode, filterSqlCode(sDeftData.index, sDeftData.value.TrimEnd()));
            }
            string firdate = string.IsNullOrWhiteSpace(sDeftData.firdate) ? "" : sDeftData.firdate.TrimEnd().Replace('-', '/'), secdate = string.IsNullOrWhiteSpace(sDeftData.secdate) ? "" : sDeftData.secdate.TrimEnd().Replace('-', '/');
            if (firdate != "" || secdate != "")
            {
                sqlCode += checkSqlCode(sqlCode, filterSqlDate(firdate, secdate));
            }
            if (sDeftData.record.TrimEnd() != "")
            {
                sqlCode += checkSqlCode(sqlCode, filterSqlRecord(sDeftData.record.TrimEnd(), sDeftData.newid.TrimEnd()));
            }
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@sqlCode", sqlCode));
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.countfiltreportform @sqlCode;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = 0, total = 0;
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.sfiltreportform @startId,@endId,@sqlCode;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postdates", $"提出日期：{dr["postdate"].ToString().TrimEnd()}" }, { "postGroups", $"提出單位：{dr["post_group"].ToString().TrimEnd()}/{dr["postname"].ToString().TrimEnd()}" }, { "fails", $"不良率：{(float.Parse(dr["failure"].ToString().TrimEnd()) * 100).ToString("F2").TrimEnd()}%" }, { "homepage1s", $"客戶/廠商：{dr["homepage1"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "objs", $"品異來源：{dr["obj"].ToString().TrimEnd()}" }, { "worknumbers", $"來源單號：{dr["worknumber"].ToString().TrimEnd()}" }, { "repliers", $"處理人：{dr["replier"].ToString().TrimEnd()}" }, { "issuesorts", $"原因分類：{dr["issuesort"].ToString().TrimEnd()}_{dr["causeclass"].ToString().TrimEnd()}" }, { "belongs", $"責任單位：{dr["belong"].ToString().TrimEnd()} {dr["belonger"].ToString().TrimEnd()}" }, { "stages", $"處理狀態：{dr["stage"].ToString().TrimEnd()}" }, { "colors", colorProcess(dr["sign2"].ToString().TrimEnd(), dr["stage"].ToString().TrimEnd()) }, { "status", signProcess(dr["signing"].ToString().TrimEnd(), dr["sign2"].ToString().TrimEnd(), dr["stage"].ToString().TrimEnd()) }, { "itemPassed", addPassPermission(dr["signing"].ToString().TrimEnd(), dr["sign2"].ToString().TrimEnd(), sDeftData.newid.TrimEnd()) }, { "itemPlused", checkPassitem(dr["pn"].ToString().TrimEnd()) }, { "itemDelete", unsendPermission(sDeftData.newid.TrimEnd(), dr["postname"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd()) } });
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
                case 2:
                    return $"mb = '{value}'";
                case 3:
                    return $"floor = '{value}'";
                case 4:
                    return $"belong = '{value}'";
                case 5:
                    return $"issuesort = '{value}'";
            }
            return $"stage = '{value}'";
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
                result += checkFilterCode(result, item, new string[] { "and" }, $"( lower(number) like '%{item.ToLower()}%' or lower(version) like '%{item.ToLower()}%' or lower(post_group) like '%{item.ToLower()}%' or lower(postname) like '%{item.ToLower()}%' or lower(pnumber) like '%{item.ToLower()}%' or lower(worknumber) like '%{item.ToLower()}%' or lower(pn) like '%{item.ToLower()}%' or lower(subject) like '%{item.ToLower()}%' or lower(belonger) like '%{item.ToLower()}%' or lower(causeclass) like '%{item.ToLower()}%' or lower(replier) like '%{item.ToLower()}%' )");
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

        public string colorProcess(string signup, string stage)
        {
            switch (signup)
            {
                case "":
                    return "rgba(255,0,0,0.8)";
            }
            switch (stage)
            {
                case "結案":
                    return "rgba(169,169,169,0.8)";
            }
            return "#00B050";
        }

        public string signProcess(string signing, string signup, string stage)
        {
            switch (signing)
            {
                case "0":
                    return "品異建立中";
            }
            switch (signup)
            {
                case "":
                    return "品異審核中";
            }
            string status = stage == "" ? "建立" : stage;
            return $"品異已{status}";
        }

        public bool editPermission(string newid, string signing, string sign2, string stage)
        {
            switch (signing) { case "0": return true; }
            switch (stage) { case "對策發行(簽核中)": return false; }
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", newid));
            return sign2 == "" || new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchusername @newid;", dbparamlist).Rows[0]["username"].ToString().TrimEnd() == "何凱宏";
        }

        public bool unsendPermission(string newid, string postname, string signing)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", newid));
            switch (signing)
            {
                case "0":
                    return database.checkSelectSql("mssql", "flyfnstring", "exec web.searchusername @newid;", dbparamlist).Rows[0]["username"].ToString().TrimEnd() == postname;
            }
            return database.checkSelectSql("mssql", "flyfnstring", "exec web.searchusername @newid;", dbparamlist).Rows[0]["username"].ToString().TrimEnd() == "何凱宏";
        }

        public bool addPassPermission(string signing, string signup, string newid)
        {
            if (signing == "0" || signup == "") return false;
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", newid));
            return new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchusername @newid;", dbparamlist).Rows[0]["username"].ToString().TrimEnd() == "何凱宏";
        }

        public bool checkPassitem(string pn)
        {
            if (string.IsNullOrWhiteSpace(pn)) return false;
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@pn", pn));
            return new database().checkSelectSql("mssql", "flystkstring", "exec dbo.checknopassitem @pn;", dbparamlist).Rows.Count > 0;
        }

        public statusModels GetClearModels(dFormData dFormData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            if (new database().checkActiveSql("mssql", "flyfnstring", "exec web.deletereportform @id;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            return new statusModels() { status = "istrue" };
        }

        public statusModels GetAddModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchreportdeta @id;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "istrue" };
            }
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@number", mainRows.Rows[0]["pn"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@reason", $"5CREPORT NUMBER:{mainRows.Rows[0]["pn"].ToString().TrimEnd()}"));
            if (database.checkActiveSql("mssql", "flystkstring", "exec dbo.insertnopassitem @number,@reason;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            return new statusModels() { status = "istrue" };
        }

        public statusModels GetRemoveModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchreportdeta @id;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "istrue" };
            }
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@number", mainRows.Rows[0]["pn"].ToString().TrimEnd()));
            if (database.checkActiveSql("mssql", "flystkstring", "exec dbo.deletenopassitem @number;", dbparamlist) != "istrue")
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
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchreportdeta @id;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sRowsModels() { status = "nodata" };
            }
            string[] floorArray = new string[] { "NA", "1F", "2F", "3F", "4F", "5F", "6F" };
            List<Dictionary<string, object>> flooritems = new List<Dictionary<string, object>>();
            foreach (var floor in floorArray)
            {
                flooritems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", floor } });
            }
            dbparamlist.Clear();
            string momoCode = "", mbCode = "";
            switch (mainRows.Rows[0]["worknumber"].ToString().TrimEnd())
            {
                case "":
                    dbparamlist.Add(new dbparam("@value", ""));
                    momoCode = "select distinct 機種別 as value from dbo.islma where 機種別 != @value order by 機種別 asc;"; mbCode = "select distinct MB別 as value from dbo.islma where MB別 != @value order by MB別 asc;";
                    break;
                default:
                    dbparamlist.Add(new dbparam("@value", mainRows.Rows[0]["worknumber"].ToString().TrimEnd()));
                    momoCode = "exec dbo.searchmodelform @value;"; mbCode = "exec dbo.searchmbform @value;";
                    break;
            }
            List<Dictionary<string, object>> momoitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flycsastring", momoCode, dbparamlist).Rows)
            {
                momoitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            List<Dictionary<string, object>> mbitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flycsastring", mbCode, dbparamlist).Rows)
            {
                mbitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            string[] objArray = new string[] { "NA", "製造", "IQC", "DOA", "RMA", "銷退", "SMT", "DIP", "板測", "板測，系測", "加工", "組裝", "組裝，包裝", "PreTest", "系測", "包裝", "週邊", "QA校驗", "IPQC", "OQC", "其他", "客驗", "客訴" };
            List<Dictionary<string, object>> objitems = new List<Dictionary<string, object>>();
            foreach (var obj in objArray)
            {
                objitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", obj } });
            }
            dbparamlist.Clear();
            List<Dictionary<string, object>> groupitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.searchallgroupform;", dbparamlist).Rows)
            {
                groupitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["department"].ToString().TrimEnd() } });
            }
            string[] issueArray = new string[] { "NA", "材料", "設計", "製程", "缺料", "流程", "業務" };
            List<Dictionary<string, object>> issueitems = new List<Dictionary<string, object>>();
            foreach (var issue in issueArray)
            {
                issueitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", issue } });
            }
            List<Dictionary<string, object>> causeitems = new List<Dictionary<string, object>>();
            if (mainRows.Rows[0]["issuesort"].ToString().TrimEnd() != "")
            {
                var causeArray = new List<Dictionary<string, string[]>>();
                causeArray.Add(new Dictionary<string, string[]>() { { "NA", new string[] { "NA" } }, { "材料", new string[] { "尺寸不符", "包裝不良", "外觀不良", "外觀異常", "色差", "來料不良", "品保覆判OK", "客供料", "規格不符", "圖面錯誤" } }, { "設計", new string[] { "BOM錯誤", "Gerber錯誤", "Limitation", "材料規格不符", "系統相容性", "組裝異常", "設計不良", "測試異常", "新產品", "圖面錯誤" } }, { "製程", new string[] { "BIOS/EC燒錄異常", "BOM燒錯", "DMI燒錄異常", "FN內容錯誤", "SFIS異常", "SOP疏漏", "未依SOP作業", "未執行FN", "未執行客需SOP", "作業疏失", "治工具異常", "品保覆測OK", "重工不良", "重測/重組OK", "組裝異常", "測試異常", "新產品", "零件上錯件", "管控疏失", "設備異常" } }, { "缺料", new string[] { "客供料正常", "急單", "採購作業疏失", "設計變更", "發料疏失", "進料異常", "廠商延遲交貨" } }, { "流程", new string[] { "FN未連結工單", "FN連結錯誤", "工單內容填寫錯誤", "作業疏失", "客驗客訴", "訂單規則變更", "排程異常", "排程變更", "增減料錯誤", "銷退驗退", "聯絡單重工" } }, { "業務", new string[] { "工單內容填寫錯誤", "作業疏失", "客供OS異常", "訂單規格變更", "規格單勾錯" } } });
                foreach (var cause in causeArray[0][mainRows.Rows[0]["issuesort"].ToString().TrimEnd()])
                {
                    causeitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", cause } });
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
            string[] belongArray = new string[] { "", "CS", "DCC", "MIS", "PCC", "PM", "PE", "QC", "RD", "生管", "其他", "倉管", "採購", "設備廠商", "新產品", "業務", "資材", "製造", "製造_包裝", "製造_板卡", "製造_組裝", "製造_測試", "廠商" };
            List<Dictionary<string, object>> belongitems = new List<Dictionary<string, object>>();
            foreach (var belong in belongArray)
            {
                belongitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", belong } });
            }
            string[] stageArray = new string[] { "", "不處理", "原因確認", "現況掌握", "對策發行", "暫時對策", "結案" };
            List<Dictionary<string, object>> stageitems = new List<Dictionary<string, object>>();
            foreach (var stage in stageArray)
            {
                stageitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", stage } });
            }
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@original", mainRows.Rows[0]["worknumber"].ToString().TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "postdate", mainRows.Rows[0]["postdate"].ToString().TrimEnd() }, { "postGroup", mainRows.Rows[0]["post_group"].ToString().TrimEnd() }, { "postName", mainRows.Rows[0]["postname"].ToString().TrimEnd() }, { "showFloorMenu", false }, { "flooritems", flooritems.ToArray() }, { "floor", mainRows.Rows[0]["floor"].ToString().TrimEnd() }, { "workno", mainRows.Rows[0]["worknumber"].ToString().TrimEnd() }, { "showXps", int.Parse(database.checkSelectSql("mssql", "flycsastring", "exec dbo.countwkpaperform @original;", dbparamlist).Rows[0]["itemCount"].ToString().TrimEnd()) > 0 }, { "homepage1", mainRows.Rows[0]["homepage1"].ToString().TrimEnd() }, { "pnumber", mainRows.Rows[0]["pnumber"].ToString().TrimEnd() }, { "showMomoMenu", false }, { "momoitems", momoitems.ToArray() }, { "homepageMomo", mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd() }, { "showMbMenu", false }, { "mbitems", mbitems.ToArray() }, { "mb", mainRows.Rows[0]["mb"].ToString().TrimEnd() }, { "showObjMenu", false }, { "objitems", objitems.ToArray() }, { "obj", mainRows.Rows[0]["obj"].ToString().TrimEnd() }, { "pn", mainRows.Rows[0]["pn"].ToString().TrimEnd() }, { "amount", mainRows.Rows[0]["amount"].ToString().TrimEnd() }, { "invest", mainRows.Rows[0]["invest"].ToString().TrimEnd() }, { "fail", mainRows.Rows[0]["fail"].ToString().TrimEnd() }, { "subject", mainRows.Rows[0]["subject"].ToString().TrimEnd() }, { "containment", mainRows.Rows[0]["containment"].ToString().TrimEnd() }, { "cause", mainRows.Rows[0]["cause"].ToString().TrimEnd() }, { "showRegroupMenu", false }, { "regroupitems", groupitems.ToArray() }, { "reGroup", "" }, { "showReplierMenu", false }, { "replieritems", new List<Dictionary<string, object>>().ToArray() }, { "replier", mainRows.Rows[0]["replier"].ToString().TrimEnd() }, { "showIssueMenu", false }, { "issueitems", issueitems.ToArray() }, { "issuesort", mainRows.Rows[0]["issuesort"].ToString().TrimEnd() }, { "showCauseMenu", false }, { "causeitems", causeitems.ToArray() }, { "causeclass", mainRows.Rows[0]["causeclass"].ToString().TrimEnd() }, { "directPt", mainRows.Rows[0]["direct_pt"].ToString().TrimEnd() }, { "indirectPt", mainRows.Rows[0]["indirect_pt"].ToString().TrimEnd() }, { "correctiveaction1", mainRows.Rows[0]["correctiveaction1"].ToString().TrimEnd() }, { "correctiveaction2", mainRows.Rows[0]["correctiveaction2"].ToString().TrimEnd() }, { "showFile", showFile }, { "showImage", showImage }, { "showVideo", showVideo }, { "showAudio", showAudio }, { "src", src }, { "path", database.connectionString("folderHttps") }, { "original", original }, { "encryption", encryption }, { "extension", extension }, { "date", date }, { "closure", mainRows.Rows[0]["closure"].ToString().TrimEnd() }, { "body", mainRows.Rows[0]["body"].ToString().TrimEnd() }, { "notice", mainRows.Rows[0]["notice"].ToString().TrimEnd() == "yes" }, { "nonstatistical", mainRows.Rows[0]["nonstatistical"].ToString().TrimEnd() == "yes" }, { "showBelongMenu", false }, { "belongitems", belongitems.ToArray() }, { "belong", mainRows.Rows[0]["belong"].ToString().TrimEnd() }, { "belonger", mainRows.Rows[0]["belonger"].ToString().TrimEnd() }, { "showStageMenu", false }, { "stageitems", stageitems.ToArray() }, { "stage", mainRows.Rows[0]["stage"].ToString().TrimEnd() }, { "releasedate", mainRows.Rows[0]["releasedate"].ToString().TrimEnd() == "" ? "尚未結案" : mainRows.Rows[0]["releasedate"].ToString().TrimEnd().Replace("/", "-") }, { "formDelete", unsendPermission(dFormData.newid.TrimEnd(), mainRows.Rows[0]["postname"].ToString().TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd()) }, { "formEdit", editPermission(dFormData.newid.TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd(), mainRows.Rows[0]["sign2"].ToString().TrimEnd(), mainRows.Rows[0]["stage"].ToString().TrimEnd()) }, { "formWork", false }, { "formQuality", qualityPermission(dFormData.newid.TrimEnd(), mainRows.Rows[0]["replier"].ToString().TrimEnd(), mainRows.Rows[0]["stage"].ToString().TrimEnd()) }, { "formSend", sendPermission(dFormData.newid.TrimEnd(), mainRows.Rows[0]["postname"].ToString().TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd()) }, { "formModify", false } });
            return new sRowsModels() { formId = mainRows.Rows[0]["id"].ToString().TrimEnd(), tile = $"{mainRows.Rows[0]["number"].ToString().TrimEnd()}-{mainRows.Rows[0]["version"].ToString().TrimEnd()}", items = items, status = "istrue" };
        }

        public bool sendPermission(string newid, string postname, string signing)
        {
            switch (signing)
            {
                case "0":
                    List<dbparam> dbparamlist = new List<dbparam>();
                    dbparamlist.Add(new dbparam("@newid", newid));
                    return new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchusername @newid;", dbparamlist).Rows[0]["username"].ToString().TrimEnd() == postname;
            }
            return false;
        }

        public bool qualityPermission(string newid, string replier, string stage)
        {
            switch (stage) { case "對策發行(簽核中)": return false; }
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", newid));
            string username = new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchusername @newid;", dbparamlist).Rows[0]["username"].ToString().TrimEnd();
            return username == "何凱宏" || username == replier;
        }

        public sOptonModels GetSFileModels(dFormData dFormData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchrefiledeta @id;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "photoId", dr["iid"].ToString().TrimEnd() }, { "photoImage", dr["flImages"].ToString().TrimEnd() == "1" }, { "photoVideo", dr["flVideos"].ToString().TrimEnd() == "1" }, { "photoAudio", dr["flAudios"].ToString().TrimEnd() == "1" }, { "photoSrc", dr["flImages"].ToString().TrimEnd() == "1" && dr["flShowed"].ToString().TrimEnd() == "0" ? $"{dr["originals"].ToString().TrimEnd()}({dr["encryptions"].ToString().TrimEnd()}){dr["extensions"].ToString().TrimEnd()}" : $"{dr["original"].ToString().TrimEnd()}({dr["encryption"].ToString().TrimEnd()}){dr["extension"].ToString().TrimEnd()}" }, { "photoPath", dr["flImages"].ToString().TrimEnd() == "1" && dr["flShowed"].ToString().TrimEnd() == "0" ? dr["imagePaths"].ToString().TrimEnd() : dr["imagePath"].ToString().TrimEnd() }, { "filePath", dr["imagePath"].ToString().TrimEnd() }, { "photoOriginal", dr["original"].ToString().TrimEnd() }, { "photoEncryption", dr["encryption"].ToString().TrimEnd() }, { "photoExtension", dr["extension"].ToString().TrimEnd() }, { "photoDate", dr["indate"].ToString().TrimEnd() }, { "photoInsert", false }, { "showDelete", dr["inoper"].ToString().TrimEnd() == dFormData.newid.TrimEnd() }, { "photoDelete", false } });
            }
            return new sOptonModels() { items = items };
        }

        public itemModels GetCloseModels(sRowsData sRowsData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", sRowsData.formId.TrimEnd()));
            switch (database.checkSelectSql("mssql", "flyfnstring", "exec web.searchsinglereportform @formId;", dbparamlist).Rows.Count)
            {
                case 0:
                    return new itemModels() { status = "nodata" };
            }
            dbparamlist.Add(new dbparam("@value", sRowsData.value.TrimEnd().Replace("-", "/")));
            if (database.checkActiveSql("mssql", "flyfnstring", "exec web.modifyreportdate @formId,@value;", dbparamlist) != "istrue")
            {
                return new itemModels() { status = "error" };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "stage", "結案" }, { "date", new datetime().sqldate("mssql", "flyfnstring") } });
            return new itemModels() { items = items, status = "istrue" };
        }

        public statusModels GetInsertModels(iFormsData iFormsData, string cuurip)
        {
            string checkItems = checkItemValue(iFormsData.items), stage = "";
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            database database = new database();
            foreach (var item in iFormsData.items)
            {
                string sqlCode = "";
                stage = checkStage(item["containment"].ToString().TrimEnd(), item["cause"].ToString().TrimEnd(), item["correctiveaction1"].ToString().TrimEnd(), item["issuesort"].ToString().TrimEnd(), item["causeclass"].ToString().TrimEnd(), item["indirectPt"].ToString().TrimEnd(), item["correctiveaction2"].ToString().TrimEnd());
                List<dbparam> dbparamlist = new List<dbparam>();
                switch (bool.Parse(item["formEdit"].ToString().TrimEnd()))
                {
                    case true:
                        dbparamlist.Add(new dbparam("@floor", item["floor"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@homepage1", item["homepage1"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@pnumber", item["pnumber"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@mb", item["mb"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@workno", item["workno"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@pn", item["pn"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@amount", item["amount"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@invest", item["invest"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@fail", item["fail"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@failure", Math.Round(float.Parse(item["fail"].ToString().TrimEnd()) / float.Parse(item["invest"].ToString().TrimEnd()), 2, MidpointRounding.AwayFromZero)));
                        dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@containment", item["containment"].ToString().TrimEnd()));
                        sqlCode = "floor = @floor,homepage1 = @homepage1,pnumber = @pnumber,homepage_momo = @homepageMomo,mb = @mb,obj = @obj,worknumber = @workno,pn = @pn,amount = @amount,invest = @invest,fail = @fail,failure = @failure,subject = @subject,containment = @containment";
                        break;
                }
                switch (bool.Parse(item["formQuality"].ToString().TrimEnd()))
                {
                    case true:
                        dbparamlist.Add(new dbparam("@cause", item["cause"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@replier", item["replier"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@issuesort", item["issuesort"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@homepage3", item["src"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@notice", bool.Parse(item["notice"].ToString().TrimEnd()) ? "yes" : "no"));
                        dbparamlist.Add(new dbparam("@nonstatistical", bool.Parse(item["nonstatistical"].ToString().TrimEnd()) ? "yes" : "no"));
                        dbparamlist.Add(new dbparam("@causeclass", item["causeclass"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@directPt", item["directPt"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@indirectPt", item["indirectPt"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@correctiveaction1", item["correctiveaction1"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@correctiveaction2", item["correctiveaction2"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@closure", item["closure"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                        //dbparamlist.Add(new dbparam("@belong", item["belong"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@belong", checkBelong(item["belonger"].ToString().TrimEnd(), item["belong"].ToString().TrimEnd(), item["issuesort"].ToString().TrimEnd(), item["causeclass"].ToString().TrimEnd())));
                        dbparamlist.Add(new dbparam("@belonger", item["belonger"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@stage", stage));
                        if (sqlCode != "")
                        {
                            sqlCode += ",";
                        }
                        sqlCode += "cause = @cause,replier = @replier,issuesort = @issuesort,homepage3 = @homepage3,notice = @notice,nonstatistical = @nonstatistical,causeclass = @causeclass,direct_pt = @directPt,indirect_pt = @indirectPt,correctiveaction1 = @correctiveaction1,correctiveaction2 = @correctiveaction2,closure = @closure,body = @body,belong = @belong,belonger = @belonger,stage = @stage";
                        break;
                }
                if (sqlCode != "")
                {
                    datetime datetime = new datetime();
                    sqlCode += ",modate = @modate, motime = @motime, mooper = @mooper";
                    dbparamlist.Add(new dbparam("@modate", datetime.sqldate("mssql", "flyfnstring")));
                    dbparamlist.Add(new dbparam("@motime", datetime.sqltime("mssql", "flyfnstring")));
                    dbparamlist.Add(new dbparam("@mooper", iFormsData.newid.TrimEnd()));
                    dbparamlist.Add(new dbparam("@id", iFormsData.formId.TrimEnd()));
                    if (database.checkActiveSql("mssql", "flyfnstring", $"update dbo.[5C_Report] set {sqlCode} where id = @id;", dbparamlist) != "istrue")
                    {
                        return new statusModels() { status = "error" };
                    }
                }
            }
            switch (stage)
            {
                case "":
                    DataTable mainRows = new DataTable();
                    List<dbparam> dbparamlist = new List<dbparam>();
                    dbparamlist.Add(new dbparam("@id", iFormsData.formId.TrimEnd()));
                    mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchreportdeta @id;", dbparamlist);
                    stage = checkStage(mainRows.Rows[0]["containment"].ToString().TrimEnd(), mainRows.Rows[0]["cause"].ToString().TrimEnd(), mainRows.Rows[0]["correctiveaction1"].ToString().TrimEnd(), mainRows.Rows[0]["issuesort"].ToString().TrimEnd(), mainRows.Rows[0]["causeclass"].ToString().TrimEnd(), mainRows.Rows[0]["indirect_pt"].ToString().TrimEnd(), mainRows.Rows[0]["correctiveaction2"].ToString().TrimEnd());
                    break;
            }
            foreach (var item in iFormsData.qaitems)
            {
                bool insert = bool.Parse(item["photoInsert"].ToString().TrimEnd()), delete = bool.Parse(item["photoDelete"].ToString().TrimEnd());
                switch (insert)
                {
                    case true:
                        switch (delete)
                        {
                            case false:
                                List<dbparam> dbparamlist = new List<dbparam>();
                                dbparamlist.Add(new dbparam("@formId", iFormsData.formId.TrimEnd()));
                                dbparamlist.Add(new dbparam("@inoper", iFormsData.newid.TrimEnd()));
                                dbparamlist.Add(new dbparam("@uploadPath", ""));
                                dbparamlist.Add(new dbparam("@imagePath", item["photoPath"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@original", item["photoOriginal"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@encryption", item["photoEncryption"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@extension", item["photoExtension"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(item["photoExtension"].ToString().TrimEnd())));
                                dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(database.connectionString("folderFiles"), $"{item["photoOriginal"].ToString().TrimEnd()}({item["photoEncryption"].ToString().TrimEnd()}){item["photoExtension"].ToString().TrimEnd()}")));
                                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertrefileform @formId,@inoper,@uploadPath,@imagePath,@original,@encryption,@extension,@type,@capacity;", dbparamlist) != "istrue")
                                {
                                    return new statusModels() { status = "error" };
                                }
                                break;
                        }
                        break;
                    default:
                        switch (delete)
                        {
                            case true:
                                List<dbparam> dbparamlist = new List<dbparam>();
                                dbparamlist.Add(new dbparam("@iid", item["photoId"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@formId", iFormsData.formId.TrimEnd()));
                                dbparamlist.Add(new dbparam("@inoper", iFormsData.newid.TrimEnd()));
                                if (database.checkActiveSql("mssql", "flyfnstring", "delete from web.refileform where iid = @iid and id = @formId and inoper = @inoper;", dbparamlist) != "istrue")
                                {
                                    return new statusModels() { status = "error" };
                                }
                                break;
                        }
                        break;
                }
            }
            return new statusModels() { status = stage == "對策發行" ? "isask" : "istrue" };
        }

        public statusModels GetSendModels(iFormsData iFormsData, string cuurip)
        {
            string checkItems = checkItemValue(iFormsData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", iFormsData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchreportdeta @id;", dbparamlist);
            foreach (var item in iFormsData.items)
            {
                string sqlCode = "";
                dbparamlist.Clear();
                switch (bool.Parse(item["formEdit"].ToString().TrimEnd()))
                {
                    case true:
                        dbparamlist.Add(new dbparam("@floor", item["floor"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@homepage1", item["homepage1"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@pnumber", item["pnumber"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@mb", item["mb"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@workno", item["workno"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@pn", item["pn"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@amount", item["amount"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@invest", item["invest"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@fail", item["fail"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@failure", Math.Round(float.Parse(item["fail"].ToString().TrimEnd()) / float.Parse(item["invest"].ToString().TrimEnd()), 2, MidpointRounding.AwayFromZero)));
                        dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@containment", item["containment"].ToString().TrimEnd()));
                        sqlCode = "floor = @floor,homepage1 = @homepage1,pnumber = @pnumber,homepage_momo = @homepageMomo,mb = @mb,obj = @obj,worknumber = @workno,pn = @pn,amount = @amount,invest = @invest,fail = @fail,failure = @failure,subject = @subject,containment = @containment";
                        break;
                }
                switch (bool.Parse(item["formQuality"].ToString().TrimEnd()))
                {
                    case true:
                        dbparamlist.Add(new dbparam("@cause", item["cause"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@replier", item["replier"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@issuesort", item["issuesort"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@homepage3", item["src"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@causeclass", item["causeclass"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@directPt", item["directPt"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@indirectPt", item["indirectPt"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@correctiveaction1", item["correctiveaction1"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@correctiveaction2", item["correctiveaction2"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@closure", item["closure"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                        //dbparamlist.Add(new dbparam("@belong", item["belong"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@belong", checkBelong(item["belonger"].ToString().TrimEnd(), item["belong"].ToString().TrimEnd(), item["issuesort"].ToString().TrimEnd(), item["causeclass"].ToString().TrimEnd())));
                        dbparamlist.Add(new dbparam("@belonger", item["belonger"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@stage", checkStage(item["containment"].ToString().TrimEnd(), item["cause"].ToString().TrimEnd(), item["correctiveaction1"].ToString().TrimEnd(), item["issuesort"].ToString().TrimEnd(), item["causeclass"].ToString().TrimEnd(), item["indirectPt"].ToString().TrimEnd(), item["correctiveaction2"].ToString().TrimEnd())));
                        if (sqlCode != "")
                            sqlCode += ",";
                        sqlCode += "cause = @cause,replier = @replier,issuesort = @issuesort,homepage3 = @homepage3,causeclass = @causeclass,direct_pt = @directPt,indirect_pt = @indirectPt,correctiveaction1 = @correctiveaction1,correctiveaction2 = @correctiveaction2,closure = @closure,body = @body,belong = @belong,belonger = @belonger,stage = @stage";
                        break;
                }
                noticeReplier(mainRows.Rows[0]["sign2"].ToString().TrimEnd(), mainRows.Rows[0]["replier"].ToString().TrimEnd(), item["replier"].ToString().TrimEnd(), iFormsData.formId.TrimEnd(), iFormsData.tile.TrimEnd(), iFormsData.newid.TrimEnd());
                if (sqlCode != "")
                {
                    datetime datetime = new datetime();
                    sqlCode += ",modate = @modate, motime = @motime, mooper = @mooper";
                    dbparamlist.Add(new dbparam("@modate", datetime.sqldate("mssql", "flyfnstring")));
                    dbparamlist.Add(new dbparam("@motime", datetime.sqltime("mssql", "flyfnstring")));
                    dbparamlist.Add(new dbparam("@mooper", iFormsData.newid.TrimEnd()));
                    dbparamlist.Add(new dbparam("@id", iFormsData.formId.TrimEnd()));
                    if (database.checkActiveSql("mssql", "flyfnstring", $"update dbo.[5C_Report] set {sqlCode} where id = @id;", dbparamlist) != "istrue")
                        return new statusModels() { status = "error" };
                }
            }
            foreach (var item in iFormsData.qaitems)
            {
                bool insert = bool.Parse(item["photoInsert"].ToString().TrimEnd()), delete = bool.Parse(item["photoDelete"].ToString().TrimEnd());
                switch (insert)
                {
                    case true:
                        switch (delete)
                        {
                            case false:
                                dbparamlist.Clear();
                                dbparamlist.Add(new dbparam("@formId", iFormsData.formId.TrimEnd()));
                                dbparamlist.Add(new dbparam("@inoper", iFormsData.newid.TrimEnd()));
                                dbparamlist.Add(new dbparam("@uploadPath", ""));
                                dbparamlist.Add(new dbparam("@imagePath", item["photoPath"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@original", item["photoOriginal"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@encryption", item["photoEncryption"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@extension", item["photoExtension"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(item["photoExtension"].ToString().TrimEnd())));
                                dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(database.connectionString("folderFiles"), $"{item["photoOriginal"].ToString().TrimEnd()}({item["photoEncryption"].ToString().TrimEnd()}){item["photoExtension"].ToString().TrimEnd()}")));
                                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertrefileform @formId,@inoper,@uploadPath,@imagePath,@original,@encryption,@extension,@type,@capacity;", dbparamlist) != "istrue")
                                    return new statusModels() { status = "error" };
                                break;
                        }
                        break;
                    default:
                        switch (delete)
                        {
                            case true:
                                dbparamlist.Clear();
                                dbparamlist.Add(new dbparam("@iid", item["photoId"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@formId", iFormsData.formId.TrimEnd()));
                                dbparamlist.Add(new dbparam("@inoper", iFormsData.newid.TrimEnd()));
                                if (database.checkActiveSql("mssql", "flyfnstring", "delete from web.refileform where iid = @iid and id = @formId and inoper = @inoper;", dbparamlist) != "istrue")
                                    return new statusModels() { status = "error" };
                                break;
                        }
                        break;
                }
            }
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@signing", "1"));
            dbparamlist.Add(new dbparam("@id", iFormsData.formId.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "update dbo.[5C_Report] set signing = @signing where id = @id;", dbparamlist) != "istrue")
                return new statusModels() { status = "error" };
            dbparamlist.Clear();
            DataTable supeRows = new DataTable();
            dbparamlist.Add(new dbparam("@inoper", iFormsData.newid.TrimEnd()));
            supeRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksupeber @inoper;", dbparamlist);
            dbparamlist.Add(new dbparam("@formId", iFormsData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@newid", supeRows.Rows[0]["superid"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@value", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」建立品異單需簽核:{iFormsData.tile.TrimEnd()}"));
            dbparamlist.Add(new dbparam("@link", $"/signlistR#{iFormsData.formId.TrimEnd()}"));
            database.checkActiveSql("mssql", "flyfnstring", "exec web.insertnoticeform @formId,@newid,@inoper,@value,@link;", dbparamlist);
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@mAddrName", $"郭晉全,{supeRows.Rows[0]["supername"].ToString().TrimEnd()},{supeRows.Rows[0]["username"].ToString().TrimEnd()},${iFormsData.items[0]["replier"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
            dbparamlist.Add(new dbparam("@mSubject", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」建立品異單需簽核:{iFormsData.tile.TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;text-align:center;'><div style='padding: 12px; border:2px solid white;'><div><h2 style='color:red;'>5C REPORT SYSTEM NEWS</h2></div><div> <hr /></div><div><h3 style='color: red;'>建立品異單需簽核</h3></div><div style='font-size: 16px;'>{new datetime().sqldate("mssql", "flyfnstring")} {new datetime().sqltime("mssql", "flyfnstring")}</div><div><h4>請相關主管進行簽核或退簽此問題．</h4></div><div><h4>http://221.222.222.181:7250/signlistR#{iFormsData.formId.TrimEnd()} => 請複製此連結</h4></div></div></div>"));
            //dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;margin: 0 auto;'><div style='padding: 12px; border:2px solid white;'><div><h2 style='color:red;'>5C REPORT SYSTEM NEWS</h2></div><div> <hr /></div><div><h3 style='color: red;'>建立品異單需簽核</h3></div><div style='font-size: 16px;'>{new datetime().sqldate("mssql", "flyfnstring")} {new datetime().sqltime("mssql", "flyfnstring")}</div><div><h4>請相關主管進行簽核或退簽此問題．</h4></div><div><a style='background-color:red; color:white; padding:12px;' href='http://221.222.222.181:7250/signlistR#{iFormsData.formId.TrimEnd()}'>前往簽核</a></div></div></div>"));
            database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist);
            return new statusModels() { status = "istrue" };
        }

        public void noticeReplier(string signup, string beforeReplier, string afterReplier, string id, string tile, string inoper)
        {
            if (beforeReplier != afterReplier || signup != "")
            {
                database database = new database();

                DataTable mainRows = new DataTable();
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@inoper", inoper));
                mainRows = database.checkSelectSql("mssql", "flyfnstring", "select username from web.supeber where userid = @inoper;", dbparamlist);
                dbparamlist.Clear();
                DataTable supeRows = new DataTable();
                dbparamlist.Add(new dbparam("@inoper", afterReplier));
                supeRows = database.checkSelectSql("mssql", "flyfnstring", "select supername, username from web.supeber where username = @inoper;", dbparamlist);
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@mAddrName", $"郭晉全,{supeRows.Rows[0]["supername"].ToString().TrimEnd()},{supeRows.Rows[0]["username"].ToString().TrimEnd()}"));
                dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
                dbparamlist.Add(new dbparam("@mSubject", $"「{mainRows.Rows[0]["username"].ToString().TrimEnd()} 變更品異單處理者:{tile}"));
                dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;text-align:center;'><div style='padding: 12px; border:2px solid white;'><div><h2 style='color:red;'>5C REPORT SYSTEM NEWS</h2></div><div> <hr /></div><div><h3 style='color: red;'>變更品異單處理者</h3></div><div style='font-size: 16px;'>{new datetime().sqldate("mssql", "flyfnstring")} {new datetime().sqltime("mssql", "flyfnstring")}</div><div><h4>請相關處理者進行了解此問題．</h4></div><div><h4>http://221.222.222.181:7250/signlistR#{id} => 請複製此連結</h4></div></div></div>"));
                database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist);
            }
        }

        public statusModels GetStageModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@stage", "對策發行(簽核中)"));
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "update dbo.[5C_Report] set stage = @stage where id = @id;", dbparamlist) != "istrue")
                return new statusModels() { status = "error" };
            dbparamlist.Clear();
            List<string> mailist = new List<string>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "select username from web.resignform;", dbparamlist).Rows)
            {
                mailist.Add(dr["username"].ToString().TrimEnd());
            }
            dbparamlist.Clear();
            DataTable mainRows = new DataTable();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchreportdeta @id;", dbparamlist);
            DataTable supeRows = new DataTable();
            dbparamlist.Add(new dbparam("@inoper", mainRows.Rows[0]["postname"].ToString().TrimEnd()));
            supeRows = database.checkSelectSql("mssql", "flyfnstring", "select supername, username from web.supeber where username = @inoper;", dbparamlist);
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@mAddrName", $"郭晉全,{string.Join(',', mailist)},{supeRows.Rows[0]["supername"].ToString().TrimEnd()},{supeRows.Rows[0]["username"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
            dbparamlist.Add(new dbparam("@mSubject", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」對策發行需簽核"));
            dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;text-align:center;'><div style='padding: 12px; border:2px solid white;'><div><h2 style='color:red;'>5C REPORT SYSTEM NEWS</h2></div><div> <hr /></div><div><h3 style='color: red;'>建立品異單需簽核</h3></div><div style='font-size: 16px;'>{new datetime().sqldate("mssql", "flyfnstring")} {new datetime().sqltime("mssql", "flyfnstring")}</div><div><h4>請相關主管進行簽核或退簽此問題．</h4></div><div><h4>http://221.222.222.181:7250/signlistR#{dFormData.formId.TrimEnd()} => 請複製此連結</h4></div></div></div>"));
            return new statusModels() { status = "istrue" };
        }

        public string checkStage(string containment, string cause, string correctiveaction1, string issuesort, string causeclass, string indirectPt, string correctiveaction2)
        {
            if (containment != "" && cause != "" && issuesort != "" && causeclass != "" && indirectPt != "" && correctiveaction1 != "" && correctiveaction2 != "") return "對策發行";
            switch (correctiveaction1) { case "": return "暫時對策"; }
            switch (cause) { case "": return "原因確認"; }
            return "現況掌握";
        }

        public string checkBelong(string belonger, string belong, string issuesort, string causeclass)
        {
            switch (belonger)
            {
                case "張原裕":
                    return "生產 3/4F";
                case "黃忠嗣":
                case "周彩梅":
                    return "生產 6F";
            }
            switch (belong)
            {
                case "資材":
                    switch (issuesort)
                    {
                        case "缺料":
                            switch (causeclass)
                            {
                                case "廠商延遲交貨":
                                    return "資材（廠商）";
                                default:
                                    return "資材";
                            }
                    }
                    break;
            }
            return belong;
        }

        public string checkItemValue(List<Dictionary<string, object>> items)
        {
            foreach (var item in items)
            {
                switch (item["formEdit"])
                {
                    case true:
                        switch (item["floor"].ToString().TrimEnd())
                        {
                            case "":
                                return "生產樓層尚未選擇";
                        }
                        switch (item["homepage1"].ToString().TrimEnd())
                        {
                            case "":
                                return "客戶/廠商尚未填寫";
                        }
                        switch (item["pnumber"].ToString().TrimEnd())
                        {
                            case "":
                                return "產品規格單/總數量尚未填寫";
                        }
                        switch (item["homepageMomo"].ToString().TrimEnd())
                        {
                            case "":
                                return "機種尚未選擇";
                        }
                        switch (item["mb"].ToString().TrimEnd())
                        {
                            case "":
                                return "M/B尚未選擇";
                        }
                        switch (item["obj"].ToString().TrimEnd())
                        {
                            case "":
                                return "品異來源尚未選擇";
                        }
                        switch (item["workno"].ToString().TrimEnd())
                        {
                            case "":
                                return "來源單號/工單尚未填寫";
                        }
                        switch (item["pn"].ToString().TrimEnd())
                        {
                            case "":
                                return "不良料號尚未填寫";
                        }
                        switch (item["amount"].ToString().TrimEnd())
                        {
                            case "":
                                return "生產/檢驗數量尚未填寫";
                        }
                        switch (item["fail"].ToString().TrimEnd())
                        {
                            case "":
                                return "不良數量尚未填寫";
                        }
                        switch (item["subject"].ToString().TrimEnd())
                        {
                            case "":
                                return "異常內容尚未填寫";
                        }
                        switch (item["directPt"].ToString().TrimEnd())
                        {
                            case "":
                                return "直接損耗工時尚未填寫";
                        }
                        switch (item["reGroup"].ToString().TrimEnd())
                        {
                            case "":
                                return "處理部門尚未填寫";
                        }
                        switch (item["replier"].ToString().TrimEnd())
                        {
                            case "":
                                return "處理者尚未填寫";
                        }
                        switch (item["src"].ToString().TrimEnd())
                        {
                            case "":
                                return "檔案尚未上傳";
                        }
                        break;
                }
            }
            return "";
        }
    }
}