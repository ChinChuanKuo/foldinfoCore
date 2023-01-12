using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Net;
using System.Text.Json;
using FOLDINFOCore.App_Code;

namespace FOLDINFOCore.Models
{
    public class InsideClass
    {
        public sItemsModels GetSearchModels(otherData otherData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.countinsideform;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = int.Parse(otherData.values.TrimEnd()) / 10;
            DataTable mainRows = new DataTable();
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchinsideform @startId,@endId;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sItemsModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                List<Dictionary<string, object>> signitems = new List<Dictionary<string, object>> {
                    new Dictionary<string, object>() { { "key", "工程處" }, { "value", dr["sign1"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "資材處" }, { "value", dr["sign2"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "品保處" }, { "value", dr["sign3"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "生產處" }, { "value", dr["sign4"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "主管" }, { "value", dr["sign5"].ToString().TrimEnd() } },
                };
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", dr["number"].ToString().TrimEnd() }, { "indexs", indexProcess(dr["end_date"].ToString().TrimEnd()) }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postdates", $"發文日期：{dr["postdate"].ToString().TrimEnd()}" }, { "postGroups", $"發文單位：{dr["post_group"].ToString().TrimEnd()}_{dr["postname"].ToString().TrimEnd()}" }, { "homepage1s", $"客戶：{dr["homepage1"].ToString().TrimEnd()}" }, { "pnumbers", $"訂單號碼：{dr["pnumber"].ToString().TrimEnd()}" }, { "objs", $"影響站別：{dr["obj"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "changeCases", $"變更內容：{dr["changecase"].ToString().TrimEnd()}" }, { "worknumbers", $"生產工單：{dr["worknumber"].ToString().TrimEnd().Replace("\n", ",")}" }, { "endDates", $"限期至：{dr["end_date"].ToString().TrimEnd()}" }, { "postTP", $"發文單位：{dr["postTP"].ToString().TrimEnd()}_{dr["postTN"].ToString().TrimEnd()}" }, { "postTM", $"機種：{dr["postTM"].ToString().TrimEnd()}" }, { "postTB", $"M/B：{dr["postTB"].ToString().TrimEnd()}" }, { "postTS", dr["postTS"].ToString().TrimEnd() }, { "colors", colorProcess(dr["end_date"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd(), signitems) }, { "status", signProcess(dr["end_date"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd(), signitems) } });
            }
            return new sItemsModels() { showItem = itemCount != int.Parse(otherData.values.TrimEnd()) + mainRows.Rows.Count, itemCount = itemCount, items = items, status = "istrue" };
        }

        public sOptonModels GetFilterModels(userData userData, string cuurip)
        {
            database database = new database();
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            string[] tileArray = new string[] { "影響暫別", "機種", "MB Code", "SN編號" };
            string[] fieldArray = new string[] { "obj", "homepage_momo", "code", "snno" };
            foreach (var item in fieldArray.Select((value, i) => new { i, value }))
            {
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@value", item.value));
                List<Dictionary<string, object>> optionitems = new List<Dictionary<string, object>>();
                optionitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", "" } });
                foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.filinsidemodule @value;", dbparamlist).Rows)
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
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", sqlCode == "" ? "exec web.countinsideform;" : "exec web.countfiltinsideform @sqlCode;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = int.Parse(sScroData.value.TrimEnd()) / 10;
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", sqlCode == "" ? "exec web.searchinsideform @startId,@endId;" : "exec web.sfiltinsideform @startId,@endId,@sqlCode;", dbparamlist).Rows)
            {
                List<Dictionary<string, object>> signitems = new List<Dictionary<string, object>> {
                    new Dictionary<string, object>() { { "key", "工程處" }, { "value", dr["sign1"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "資材處" }, { "value", dr["sign2"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "品保處" }, { "value", dr["sign3"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "生產處" }, { "value", dr["sign4"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "主管" }, { "value", dr["sign5"].ToString().TrimEnd() } },
                };
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", dr["number"].ToString().TrimEnd() }, { "indexs", indexProcess(dr["end_date"].ToString().TrimEnd()) }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postdates", $"發文日期：{dr["postdate"].ToString().TrimEnd()}" }, { "postGroups", $"發文單位：{dr["post_group"].ToString().TrimEnd()}_{dr["postname"].ToString().TrimEnd()}" }, { "homepage1s", $"客戶：{dr["homepage1"].ToString().TrimEnd()}" }, { "pnumbers", $"訂單號碼：{dr["pnumber"].ToString().TrimEnd()}" }, { "objs", $"影響站別：{dr["obj"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "changeCases", $"變更內容：{dr["changecase"].ToString().TrimEnd()}" }, { "worknumbers", $"生產工單：{dr["worknumber"].ToString().TrimEnd().Replace("\n", ",")}" }, { "endDates", $"限期至：{dr["end_date"].ToString().TrimEnd()}" }, { "postTP", $"發文單位：{dr["postTP"].ToString().TrimEnd()}_{dr["postTN"].ToString().TrimEnd()}" }, { "postTM", $"機種：{dr["postTM"].ToString().TrimEnd()}" }, { "postTB", $"M/B：{dr["postTB"].ToString().TrimEnd()}" }, { "postTS", dr["postTS"].ToString().TrimEnd() }, { "colors", colorProcess(dr["end_date"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd(), signitems) }, { "status", signProcess(dr["end_date"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd(), signitems) } });
                total++;
            }
            return new itemsModels() { showItem = itemCount != int.Parse(sScroData.value.TrimEnd()) + total, items = items };
        }

        public sOptonModels GetSRecordModels(userData userData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@page", "inside"));
            dbparamlist.Add(new dbparam("@together", "insideall"));
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
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.countfiltinsideform @sqlCode;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = 0, total = 0;
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.sfiltinsideform @startId,@endId,@sqlCode;", dbparamlist).Rows)
            {
                List<Dictionary<string, object>> signitems = new List<Dictionary<string, object>> {
                    new Dictionary<string, object>() { { "key", "工程處" }, { "value", dr["sign1"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "資材處" }, { "value", dr["sign2"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "品保處" }, { "value", dr["sign3"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "生產處" }, { "value", dr["sign4"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "主管" }, { "value", dr["sign5"].ToString().TrimEnd() } },
                };
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", dr["number"].ToString().TrimEnd() }, { "indexs", indexProcess(dr["end_date"].ToString().TrimEnd()) }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postdates", $"發文日期：{dr["postdate"].ToString().TrimEnd()}" }, { "postGroups", $"發文單位：{dr["post_group"].ToString().TrimEnd()}_{dr["postname"].ToString().TrimEnd()}" }, { "homepage1s", $"客戶：{dr["homepage1"].ToString().TrimEnd()}" }, { "pnumbers", $"訂單號碼：{dr["pnumber"].ToString().TrimEnd()}" }, { "objs", $"影響站別：{dr["obj"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "changeCases", $"變更內容：{dr["changecase"].ToString().TrimEnd()}" }, { "worknumbers", $"生產工單：{dr["worknumber"].ToString().TrimEnd().Replace("\n", ",")}" }, { "endDates", $"限期至：{dr["end_date"].ToString().TrimEnd()}" }, { "postTP", $"發文單位：{dr["postTP"].ToString().TrimEnd()}_{dr["postTN"].ToString().TrimEnd()}" }, { "postTM", $"機種：{dr["postTM"].ToString().TrimEnd()}" }, { "postTB", $"M/B：{dr["postTB"].ToString().TrimEnd()}" }, { "postTS", dr["postTS"].ToString().TrimEnd() }, { "colors", colorProcess(dr["end_date"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd(), signitems) }, { "status", signProcess(dr["end_date"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd(), signitems) } });
                total++;
            }
            switch (checkRecord(otherData.values.TrimEnd()))
            {
                case true:
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@page", "inside"));
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
                case "today":
                case "release":
                case "norelease":
                case "noworknumber1":
                case "noworknumber2":
                case "nosigning":
                case "reject":
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
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.countfiltinsideform @sqlCode;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd()), index = 0, total = 0;
            dbparamlist.Add(new dbparam("@startId", index + 10 * index));
            dbparamlist.Add(new dbparam("@endId", index + 10 * (index + 1)));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.sfiltinsideform @startId,@endId,@sqlCode;", dbparamlist).Rows)
            {
                List<Dictionary<string, object>> signitems = new List<Dictionary<string, object>> {
                    new Dictionary<string, object>() { { "key", "工程處" }, { "value", dr["sign1"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "資材處" }, { "value", dr["sign2"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "品保處" }, { "value", dr["sign3"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "生產處" }, { "value", dr["sign4"].ToString().TrimEnd() } },
                    new Dictionary<string, object>() { { "key", "主管" }, { "value", dr["sign5"].ToString().TrimEnd() } },
                };
                items.Add(new Dictionary<string, object>() { { "ids", dr["id"].ToString().TrimEnd() }, { "numbers", dr["number"].ToString().TrimEnd() }, { "indexs", indexProcess(dr["end_date"].ToString().TrimEnd()) }, { "subjects", dr["subject"].ToString().TrimEnd() }, { "postdates", $"發文日期：{dr["postdate"].ToString().TrimEnd()}" }, { "postGroups", $"發文單位：{dr["post_group"].ToString().TrimEnd()}_{dr["postname"].ToString().TrimEnd()}" }, { "homepage1s", $"客戶：{dr["homepage1"].ToString().TrimEnd()}" }, { "pnumbers", $"訂單號碼：{dr["pnumber"].ToString().TrimEnd()}" }, { "objs", $"影響站別：{dr["obj"].ToString().TrimEnd()}" }, { "homepageMomos", $"機種：{dr["homepage_momo"].ToString().TrimEnd()}" }, { "mbs", $"M/B：{dr["mb"].ToString().TrimEnd()}" }, { "changeCases", $"變更內容：{dr["changecase"].ToString().TrimEnd()}" }, { "worknumbers", $"生產工單：{dr["worknumber"].ToString().TrimEnd().Replace("\n", ",")}" }, { "endDates", $"限期至：{dr["end_date"].ToString().TrimEnd()}" }, { "postTP", $"發文單位：{dr["postTP"].ToString().TrimEnd()}_{dr["postTN"].ToString().TrimEnd()}" }, { "postTM", $"機種：{dr["postTM"].ToString().TrimEnd()}" }, { "postTB", $"M/B：{dr["postTB"].ToString().TrimEnd()}" }, { "postTS", dr["postTS"].ToString().TrimEnd() }, { "colors", colorProcess(dr["end_date"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd(), signitems) }, { "status", signProcess(dr["end_date"].ToString().TrimEnd(), dr["signing"].ToString().TrimEnd(), signitems) } });
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
                    return $"code = '{value}'";
            }
            return $"snno = '{value}'";
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
            switch (value)
            {
                case "today":
                    return $"postdate = '{new datetime().sqldate("mssql", "flyfnstring")}'";
                case "release":
                    return "releasedate != ''";
                case "norelease":
                    return "releasedate = ''";
                case "noworknumber1":
                    return "issuedate = '' and worknumber = ''";
                case "noworknumber2":
                    return "issuedate != '' and worknumber = ''";
                case "nosigning":
                    return "issuedate = ''";
                case "reject":
                    return "reject = 'true'";
            }
            string result = "";
            foreach (string item in value.Split(' '))
            {
                result += checkFilterCode(result, item, new string[] { "and" }, $"( lower(f.number) like '%{item.ToLower()}%' or lower(f.subject) like '%{item.ToLower()}%' or lower(f.body) like '%{item.ToLower()}%' or lower(f.version) like '%{item.ToLower()}%' or lower(f.post_group) like '%{item.ToLower()}%' or lower(f.postname) like '%{item.ToLower()}%' or lower(f.changecase) like '%{item.ToLower()}%' or lower(f.obj) like '%{item.ToLower()}%' or lower(f.homepage_momo) like '%{item.ToLower()}%' or lower(f.mb) like '%{item.ToLower()}%' or lower(snno) like '%{item.ToLower()}%' or lower(code) like '%{item.ToLower()}%' or lower(f.worknumber) like '%{item.ToLower()}%' or lower(f.ecrno) like '%{item.ToLower()}%' or lower(f.ecnno) like '%{item.ToLower()}%' )");
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

        public string colorProcess(string endDate, string signing, List<Dictionary<string, object>> items)
        {
            switch (endDate)
            {
                case "":
                    return "rgba(255,0,255,0.8)";
            }
            switch (signing)
            {
                case "0":
                    return "rgba(255,0,0,0.8)";
            }
            foreach (var item in items)
            {
                switch (item["value"].ToString().TrimEnd())
                {
                    case "":
                        return "#E36C0A";
                }
            }
            return "rgba(169,169,169,0.8)";
        }

        public int indexProcess(string endDate)
        {
            switch (endDate)
            {
                case "":
                    return 0;
            }
            return 1;
        }

        public string signProcess(string endDate, string signing, List<Dictionary<string, object>> items)
        {
            switch (endDate)
            {
                case "":
                    return "等待認領中";
            }
            switch (signing)
            {
                case "0":
                    return "文件建立中";
            }
            foreach (var item in items)
            {
                switch (item["value"].ToString().TrimEnd())
                {
                    case "":
                        return $"等待{item["key"].ToString().TrimEnd()}簽核";
                }
            }
            return "文件已發行";
        }

        public statusModels GetClearModels(dFormData dFormData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            if (new database().checkActiveSql("mssql", "flyfnstring", "exec web.deleteinsideform @id;", dbparamlist) != "istrue")
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
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchinsidedata @id;", dbparamlist);
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
            dbparamlist.Add(new dbparam("@group", mainRows.Rows[0]["post_group"].ToString().TrimEnd()));
            List<Dictionary<string, object>> nameitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchgroupform @group;", dbparamlist).Rows)
            {
                nameitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["username"].ToString().TrimEnd() } });
            }
            string[] caseArray = new string[] { "", "出貨內容修改", "包裝料件修改", "作業性變更", "訂單修改", "訂單備料", "異常處理變更", "組裝料件修改", "測試方式變更", "增加客戶需求" };
            List<Dictionary<string, object>> caseitems = new List<Dictionary<string, object>>();
            foreach (var value in caseArray)
            {
                caseitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", value } });
            }
            string[] objArray = new string[] { "", "DIP", "DOA", "IPQC", "IQC", "NA", "OQC", "PreTest", "QA校驗", "RMA", "SMT", "加工", "包裝", "系測", "其它", "板測", "板測,系測", "客訴", "客驗", "組裝", "組裝,包裝", "週邊", "製程", "銷退" };
            List<Dictionary<string, object>> objitems = new List<Dictionary<string, object>>();
            foreach (var value in objArray)
            {
                objitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", value } });
            }
            string[] typeArray = new string[] { "空白", "完整" };
            List<Dictionary<string, object>> typeitems = new List<Dictionary<string, object>>();
            foreach (var value in typeArray)
            {
                typeitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", value } });
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
            foreach (var item in mainRows.Rows[0]["mblist"].ToString().TrimEnd().Split(',').Select((value, i) => new { i, value }))
            {
                if (item.value != "")
                {
                    mbitems.Add(new Dictionary<string, object>() { { "mbId", item.i }, { "mbValue", item.value } });
                }
            }
            dbparamlist.Clear();
            List<Dictionary<string, object>> mtstitems = new List<Dictionary<string, object>>();
            switch (mainRows.Rows[0]["ecrno"].ToString().TrimEnd())
            {
                case "":
                    foreach (DataRow dr in database.checkSelectSql("mssql", "flycsastring", "exec dbo.searchallinventform;", dbparamlist).Rows)
                    {
                        mtstitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["mb"].ToString().TrimEnd() } });
                    }
                    break;
                default:
                    dbparamlist.Add(new dbparam("@ecrno", mainRows.Rows[0]["ecrno"].ToString().TrimEnd()));
                    foreach (DataRow dr in database.checkSelectSql("mssql", "flyecrstring", "exec dbo.searchbeforecrdata @ecrno;", dbparamlist).Rows)
                    {
                        mtstitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["mb"].ToString().TrimEnd() } });
                    }
                    break;
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
            items.Add(new Dictionary<string, object>() { { "snno", mainRows.Rows[0]["snno"].ToString().TrimEnd() }, { "postdate", mainRows.Rows[0]["postdate"].ToString().TrimEnd() }, { "showGroupMenu", false }, { "groupitems", groupitems.ToArray() }, { "postGroup", mainRows.Rows[0]["post_group"].ToString().TrimEnd() }, { "showNameMenu", false }, { "nameitems", nameitems.ToArray() }, { "postName", mainRows.Rows[0]["postname"].ToString().TrimEnd() }, { "showCaseMenu", false }, { "caseitems", caseitems.ToArray() }, { "case", mainRows.Rows[0]["changecase"].ToString().TrimEnd() }, { "homepage1", mainRows.Rows[0]["homepage1"].ToString().TrimEnd() }, { "pnumber", mainRows.Rows[0]["pnumber"].ToString().TrimEnd() }, { "endDate", mainRows.Rows[0]["end_date"].ToString().TrimEnd().Replace("/", "-") }, { "showObjMenu", false }, { "objitems", objitems.ToArray() }, { "obj", mainRows.Rows[0]["obj"].ToString().TrimEnd() }, { "homepageMomo", mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd() }, { "mb", mainRows.Rows[0]["mb"].ToString().TrimEnd() }, { "amount", mainRows.Rows[0]["amount"].ToString().TrimEnd() }, { "subject", mainRows.Rows[0]["subject"].ToString().TrimEnd() }, { "ecr", mainRows.Rows[0]["ecrno"].ToString().TrimEnd() }, { "showXps", File.Exists($"{database.connectionString("ecrFiles")}{mainRows.Rows[0]["ecrno"].ToString().TrimEnd()}.pdf") }, { "ecn", mainRows.Rows[0]["ecnno"].ToString().TrimEnd() }, { "en", mainRows.Rows[0]["enno"].ToString().TrimEnd() }, { "showTypeMenu", false }, { "typeitems", typeitems.ToArray() }, { "type_", "" }, { "body", mainRows.Rows[0]["body"].ToString().TrimEnd() }, { "mailitems", mailitems.ToArray() }, { "showMagroupMenu", false }, { "magroupitems", groupitems.ToArray() }, { "magroup", "" }, { "showManameMenu", false }, { "manameitems", new List<Dictionary<string, object>>().ToArray() }, { "maname", "" }, { "action1", mainRows.Rows[0]["action1"].ToString().TrimEnd() }, { "workitems", workitems.ToArray() }, { "work", "" }, { "showWork", false }, { "worknoitems", new List<Dictionary<string, object>>().ToArray() }, { "code", "" }, { "action2", mainRows.Rows[0]["action2"].ToString().TrimEnd() }, { "mbitems", mbitems.ToArray() }, { "showMtstMenu", false }, { "mtstitems", mtstitems.ToArray() }, { "mtst", "" }, { "showMbstMenu", false }, { "mbstitems", new List<Dictionary<string, object>>().ToArray() }, { "mbst", "" }, { "oldno", mainRows.Rows[0]["oldpn"].ToString().TrimEnd() }, { "newno", mainRows.Rows[0]["newpn"].ToString().TrimEnd() }, { "sopno", mainRows.Rows[0]["sopdoc"].ToString().TrimEnd() }, { "action3", mainRows.Rows[0]["action3"].ToString().TrimEnd() }, { "sipno", mainRows.Rows[0]["sipdoc"].ToString().TrimEnd() }, { "action4", mainRows.Rows[0]["action4"].ToString().TrimEnd() }, { "action5", mainRows.Rows[0]["action5"].ToString().TrimEnd() }, { "formTrans", mainRows.Rows[0]["transform"].ToString().TrimEnd() != "1" }, { "formSend", checkFormSend(mainRows.Rows[0]["signing"].ToString().TrimEnd()) }, { "formModify", false } });
            return new sRowsModels() { formId = mainRows.Rows[0]["id"].ToString().TrimEnd(), tile = mainRows.Rows[0]["number"].ToString().TrimEnd(), items = items, status = "istrue" };
        }

        public bool checkFormSend(string signing)
        {
            switch (signing)
            {
                case "0":
                    return true;
            }
            return false;
        }

        public sOptonModels GetSFileModels(dFormData dFormData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", dFormData.formId.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchinfiledeta @id;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "photoId", dr["iid"].ToString().TrimEnd() }, { "photoImage", dr["flImages"].ToString().TrimEnd() == "1" }, { "photoVideo", dr["flVideos"].ToString().TrimEnd() == "1" }, { "photoAudio", dr["flAudios"].ToString().TrimEnd() == "1" }, { "photoSrc", dr["flImages"].ToString().TrimEnd() == "1" && dr["flShowed"].ToString().TrimEnd() == "0" ? $"{dr["originals"].ToString().TrimEnd()}({dr["encryptions"].ToString().TrimEnd()}){dr["extensions"].ToString().TrimEnd()}" : $"{dr["original"].ToString().TrimEnd()}({dr["encryption"].ToString().TrimEnd()}){dr["extension"].ToString().TrimEnd()}" }, { "photoPath", dr["flImages"].ToString().TrimEnd() == "1" && dr["flShowed"].ToString().TrimEnd() == "0" ? dr["imagePaths"].ToString().TrimEnd() : dr["imagePath"].ToString().TrimEnd() }, { "filePath", dr["imagePath"].ToString().TrimEnd() }, { "photoOriginal", dr["original"].ToString().TrimEnd() }, { "photoEncryption", dr["encryption"].ToString().TrimEnd() }, { "photoExtension", dr["extension"].ToString().TrimEnd() }, { "photoDate", dr["indate"].ToString().TrimEnd() }, { "photoInsert", false }, { "showDelete", dr["inoper"].ToString().TrimEnd() == dFormData.newid.TrimEnd() }, { "photoDelete", false } });
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
                items.Add(new Dictionary<string, object>() { { "grotoId", dr["iid"].ToString().TrimEnd() }, { "grotoImage", dr["flImages"].ToString().TrimEnd() == "1" }, { "grotoVideo", dr["flVideos"].ToString().TrimEnd() == "1" }, { "grotoAudio", dr["flAudios"].ToString().TrimEnd() == "1" }, { "grotoSrc", dr["flImages"].ToString().TrimEnd() == "1" && dr["flShowed"].ToString().TrimEnd() == "0" ? $"{dr["originals"].ToString().TrimEnd()}({dr["encryptions"].ToString().TrimEnd()}){dr["extensions"].ToString().TrimEnd()}" : $"{dr["original"].ToString().TrimEnd()}({dr["encryption"].ToString().TrimEnd()}){dr["extension"].ToString().TrimEnd()}" }, { "grotoPath", dr["flImages"].ToString().TrimEnd() == "1" && dr["flShowed"].ToString().TrimEnd() == "0" ? dr["imagePaths"].ToString().TrimEnd() : dr["imagePath"].ToString().TrimEnd() }, { "filePath", dr["imagePath"].ToString().TrimEnd() }, { "grotoOriginal", dr["original"].ToString().TrimEnd() }, { "grotoEncryption", dr["encryption"].ToString().TrimEnd() }, { "grotoExtension", dr["extension"].ToString().TrimEnd() }, { "grotoName", dr["name"].ToString().TrimEnd() }, { "grotoDate", dr["indate"].ToString().TrimEnd() }, { "grotoInsert", false }, { "showDelete", dr["inoper"].ToString().TrimEnd() == dFormData.newid.TrimEnd() }, { "grotoDelete", false } });
            }
            return new sOptonModels() { items = items };
        }

        public sOptonModels GetSActionModels(sRowsData sRowsData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", sRowsData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", sRowsData.newid.TrimEnd()));
            dbparamlist.Add(new dbparam("@length", sRowsData.value.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.searchactionlog @id,@inoper,@length;", dbparamlist).Rows)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@newid", dr["inoper"].ToString().TrimEnd()));
                items.Add(new Dictionary<string, object>() { { "actId", dr["formId"].ToString().TrimEnd() }, { "actName", database.checkSelectSql("mssql", "flyfnstring", "exec web.checksiteberform @newid;", dbparamlist).Rows[0]["username"].ToString().TrimEnd() }, { "actContent", dr["content"].ToString().TrimEnd() }, { "actDate", dr["indate"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public statusModels GetInsertModels(iSirmsData iSirmsData, string cuurip)
        {
            string checkItems = new CreateFClass().checkItemValue(iSirmsData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", iSirmsData.formId.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchinsidedata @id;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            dbparamlist.Clear();
            DataTable supeRows = new DataTable();
            dbparamlist.Add(new dbparam("@inoper", iSirmsData.newid.TrimEnd()));
            supeRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksupeber @inoper;", dbparamlist);
            switch (supeRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            string mailMessage = differentMainRow(iSirmsData.formId.TrimEnd(), new string[] { "發文部門", "發文者", "變更內容", "客戶", "訂單號碼", "文件有效期限", "影響站別", "機種", "M/B", "生產數量", "主旨", "資材處", "工程處", "舊料號", "新料號", "SOP文件編號", "品保處", "SIP文件編號", "生產處" }, iSirmsData.items), othermail = "", workno = "", mblist = "";
            foreach (var item in iSirmsData.items)
            {
                foreach (var mailitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["mailitems"].ToString().TrimEnd()))
                {
                    switch (othermail.IndexOf(mailitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            othermail += $"{mailitem["mbValue"].ToString().TrimEnd()},";
                            break;
                    }
                }
                foreach (var workitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["workitems"].ToString().TrimEnd()))
                {
                    switch (workno.IndexOf(workitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            workno += $"{workitem["mbValue"].ToString().TrimEnd()}\n";
                            break;
                    }
                }
                foreach (var mbitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["mbitems"].ToString().TrimEnd()))
                {
                    switch (mblist.IndexOf(mbitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            mblist += $"{mbitem["mbValue"].ToString().TrimEnd()},";
                            break;
                    }
                }
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@postGroup", item["postGroup"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@postName", item["postName"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@case", item["case"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepage1", item["homepage1"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@pnumber", item["pnumber"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@endDate", item["endDate"].ToString().TrimEnd().Replace('-', '/')));
                dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", item["mb"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@amount", int.Parse(item["amount"].ToString().TrimEnd())));
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@othermail", othermail));
                dbparamlist.Add(new dbparam("@action1", item["action1"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@workno", workno));
                dbparamlist.Add(new dbparam("@action2", item["action2"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mblist", mblist));
                dbparamlist.Add(new dbparam("@oldno", item["oldno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@newno", item["newno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@sopno", item["sopno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@sipno", item["sipno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@action3", item["action3"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@action4", item["action4"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@action5", item["action5"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@ecrno", item["ecr"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@ecnno", item["ecn"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@enno", item["en"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@id", iSirmsData.formId.TrimEnd()));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.modifyinsideform @postGroup,@postName,@case,@homepage1,@pnumber,@endDate,@obj,@homepageMomo,@mb,@amount,@subject,@body,@othermail,@action1,@workno,@action2,@mblist,@oldno,@newno,@sopno,@sipno,@action3,@action4,@action5,@ecrno,@ecnno,@enno,@id;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            mailMessage += differentFileRow(iSirmsData.formId.TrimEnd(), new string[] { "圖庫" }, iSirmsData.photoitems);
            List<string> deleteitems = new List<string>();
            foreach (var item in iSirmsData.photoitems)
            {
                bool insert = bool.Parse(item["photoInsert"].ToString().TrimEnd()), delete = bool.Parse(item["photoDelete"].ToString().TrimEnd());
                switch (insert)
                {
                    case true:
                        switch (delete)
                        {
                            case false:
                                dbparamlist.Clear();
                                dbparamlist.Add(new dbparam("@formId", iSirmsData.formId.TrimEnd()));
                                dbparamlist.Add(new dbparam("@inoper", iSirmsData.newid.TrimEnd()));
                                dbparamlist.Add(new dbparam("@uploadPath", ""));
                                dbparamlist.Add(new dbparam("@imagePath", item["photoPath"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@original", item["photoOriginal"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@encryption", item["photoEncryption"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@extension", item["photoExtension"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(item["photoExtension"].ToString().TrimEnd())));
                                dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(database.connectionString("folderFiles"), $"{item["photoOriginal"].ToString().TrimEnd()}({item["photoEncryption"].ToString().TrimEnd()}){item["photoExtension"].ToString().TrimEnd()}")));
                                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertinfileform @formId,@inoper,@uploadPath,@imagePath,@original,@encryption,@extension,@type,@capacity;", dbparamlist) != "istrue")
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
                                deleteitems.Add(item["photoId"].ToString().TrimEnd());
                                break;
                        }
                        break;
                }
            }
            if (deleteitems.Count > 0)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", iSirmsData.formId.TrimEnd()));
                dbparamlist.Add(new dbparam("@inoper", iSirmsData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@sqlcode", string.Join(',', deleteitems)));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.deleteinfileform @formId,@inoper,@sqlcode;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            mailMessage += differentGroupRow(iSirmsData.formId.TrimEnd(), iSirmsData.newid.TrimEnd(), new string[] { "部門圖庫" }, iSirmsData.grotoitems);
            deleteitems = new List<string>();
            foreach (var item in iSirmsData.grotoitems)
            {
                bool insert = bool.Parse(item["grotoInsert"].ToString().TrimEnd()), delete = bool.Parse(item["grotoDelete"].ToString().TrimEnd());
                switch (insert)
                {
                    case true:
                        switch (delete)
                        {
                            case false:
                                dbparamlist.Clear();
                                dbparamlist.Add(new dbparam("@formId", iSirmsData.formId.TrimEnd()));
                                dbparamlist.Add(new dbparam("@inoper", iSirmsData.newid.TrimEnd()));
                                dbparamlist.Add(new dbparam("@name", item["grotoName"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@uploadPath", ""));
                                dbparamlist.Add(new dbparam("@imagePath", item["grotoPath"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@original", item["grotoOriginal"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@encryption", item["grotoEncryption"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@extension", item["grotoExtension"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(item["grotoExtension"].ToString().TrimEnd())));
                                dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(database.connectionString("folderFiles"), $"{item["grotoOriginal"].ToString().TrimEnd()}({item["grotoEncryption"].ToString().TrimEnd()}){item["grotoExtension"].ToString().TrimEnd()}")));
                                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertingroupform @formId,@inoper,@name,@uploadPath,@imagePath,@original,@encryption,@extension,@type,@capacity;", dbparamlist) != "istrue")
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
                                deleteitems.Add(item["grotoId"].ToString().TrimEnd());
                                break;
                        }
                        break;
                }
            }
            if (deleteitems.Count > 0)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", iSirmsData.formId.TrimEnd()));
                dbparamlist.Add(new dbparam("@inoper", iSirmsData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@sqlcode", string.Join(',', deleteitems)));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.deleteingroupform @formId,@inoper,@sqlcode;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            //通知
            if (mailMessage != "")
            {
                List<Dictionary<string, object>> signitems = new List<Dictionary<string, object>>();
                signitems.Add(new Dictionary<string, object>() { { "key", "工程處" }, { "value", mainRows.Rows[0]["sign1"].ToString().TrimEnd() } });
                signitems.Add(new Dictionary<string, object>() { { "key", "資材處" }, { "value", mainRows.Rows[0]["sign2"].ToString().TrimEnd() } });
                signitems.Add(new Dictionary<string, object>() { { "key", "品保處" }, { "value", mainRows.Rows[0]["sign3"].ToString().TrimEnd() } });
                signitems.Add(new Dictionary<string, object>() { { "key", "生產處" }, { "value", mainRows.Rows[0]["sign4"].ToString().TrimEnd() } });
                signitems.Add(new Dictionary<string, object>() { { "key", "主管" }, { "value", mainRows.Rows[0]["sign5"].ToString().TrimEnd() } });
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", iSirmsData.formId.TrimEnd()));
                dbparamlist.Add(new dbparam("@inoper", iSirmsData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@content", mailMessage));
                dbparamlist.Add(new dbparam("@status", signProcess(mainRows.Rows[0]["end_date"].ToString().TrimEnd(), mainRows.Rows[0]["signing"].ToString().TrimEnd(), signitems)));
                database.checkActiveSql("mssql", "flyfnstring", "exec web.insertactionlog @formId,@inoper,@content,@status;", dbparamlist);
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@mAddrName", $"{othermail}{supeRows.Rows[0]["username"].ToString().TrimEnd()}"));
                dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
                dbparamlist.Add(new dbparam("@mSubject", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」建立工廠內部通告:{iSirmsData.tile.TrimEnd()}"));
                dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;text-align:center;'><div style='padding: 12px; border:2px solid white;'><div><h3 style='color: red;'>FN SYSTEM NEWS</h3></div><div> <hr /></div><div><h3 style='color: red;'>儲存工廠內部通告變更資訊</h3></div><div style='font-size: 16px;'>{new datetime().sqldate("mssql", "flyfnstring")} {new datetime().sqltime("mssql", "flyfnstring")}</div><div><h4>變更內容如下：</h4></div><div>{mailMessage}</div><div><a style='background-color:red; color:white; padding:12px;' href='http://221.222.222.181:7250/modifyF#{iSirmsData.formId.TrimEnd()}'>前往瞭解</a></div></div></div>"));
                database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist);
            }
            return new statusModels() { status = "istrue" };
        }

        public string differentMainRow(string formId, string[] titleArray, List<Dictionary<string, object>> items)
        {
            string message = "";
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", formId));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchinsidedata @id;", dbparamlist);
            foreach (var item in items.Select((key, i) => new { i, key }))
            {
                message += differentRow(titleArray[item.i], mainRows.Rows[0]["post_group"].ToString().TrimEnd(), item.key["postGroup"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 1], mainRows.Rows[0]["postname"].ToString().TrimEnd(), item.key["postName"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 2], mainRows.Rows[0]["changecase"].ToString().TrimEnd(), item.key["case"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 3], mainRows.Rows[0]["homepage1"].ToString().TrimEnd(), item.key["homepage1"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 4], mainRows.Rows[0]["pnumber"].ToString().TrimEnd(), item.key["pnumber"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 5], mainRows.Rows[0]["end_date"].ToString().TrimEnd(), item.key["endDate"].ToString().TrimEnd().Replace('-', '/'));
                message += differentRow(titleArray[item.i + 6], mainRows.Rows[0]["obj"].ToString().TrimEnd(), item.key["obj"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 7], mainRows.Rows[0]["homepage_momo"].ToString().TrimEnd(), item.key["homepageMomo"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 8], mainRows.Rows[0]["mb"].ToString().TrimEnd(), item.key["mb"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 9], mainRows.Rows[0]["amount"].ToString().TrimEnd(), item.key["amount"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 10], mainRows.Rows[0]["subject"].ToString().TrimEnd(), item.key["subject"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 11], mainRows.Rows[0]["action1"].ToString().TrimEnd(), item.key["action1"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 12], mainRows.Rows[0]["action2"].ToString().TrimEnd(), item.key["action2"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 13], mainRows.Rows[0]["oldpn"].ToString().TrimEnd(), item.key["oldno"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 14], mainRows.Rows[0]["newpn"].ToString().TrimEnd(), item.key["newno"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 15], mainRows.Rows[0]["sopdoc"].ToString().TrimEnd(), item.key["sopno"].ToString().TrimEnd());
                message += differentRow(titleArray[item.i + 16], mainRows.Rows[0]["action4"].ToString().TrimEnd(), item.key["action4"].ToString().TrimEnd());
            }
            return message;
        }

        public string differentFileRow(string formId, string[] titleArray, List<Dictionary<string, object>> items)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", formId));
            string itemcount = new database().checkSelectSql("mssql", "flyfnstring", "exec web.countinfileform @id;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd();
            return differentRow(titleArray[0], $"{itemcount}張", $"{items.Count}張");
        }

        public string differentGroupRow(string formId, string inoper, string[] titleArray, List<Dictionary<string, object>> items)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@id", formId));
            dbparamlist.Add(new dbparam("@inoper", inoper));
            string itemcount = new database().checkSelectSql("mssql", "flyfnstring", "exec web.countingroupform @id,@inoper;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd();
            return differentRow(titleArray[0], $"{itemcount}張", $"{items.Count}張");
        }

        public string differentMessage(string message)
        {
            switch (message)
            {
                case "":
                    return message;
            }
            return $"<br/> {message}";
        }

        public string differentRow(string title, string before, string after)
        {
            if (before == after)
            {
                return "";
            }
            return $"{title}：{before} --> {after}";
        }

        public statusModels GetSendModels(iSirmsData iSirmsData, string cuurip)
        {
            string checkItems = new CreateFClass().checkItemValue(iSirmsData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            database database = new database();
            DataTable supeRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@inoper", iSirmsData.newid.TrimEnd()));
            supeRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksupeber @inoper;", dbparamlist);
            switch (supeRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            string othermail = "", workno = "", mblist = "";
            foreach (var item in iSirmsData.items)
            {
                foreach (var mailitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["mailitems"].ToString().TrimEnd()))
                {
                    switch (othermail.IndexOf(mailitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            othermail += $"{mailitem["mbValue"].ToString().TrimEnd()},";
                            break;
                    }
                }
                foreach (var workitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["workitems"].ToString().TrimEnd()))
                {
                    switch (workno.IndexOf(workitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            workno += $"{workitem["mbValue"].ToString().TrimEnd()}\n";
                            break;
                    }
                }
                foreach (var mbitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["mbitems"].ToString().TrimEnd()))
                {
                    switch (mblist.IndexOf(mbitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            mblist += $"{mbitem["mbValue"].ToString().TrimEnd()},";
                            break;
                    }
                }
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@postGroup", item["postGroup"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@postName", item["postName"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@case", item["case"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepage1", item["homepage1"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@pnumber", item["pnumber"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@endDate", item["endDate"].ToString().TrimEnd().Replace('-', '/')));
                dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", item["mb"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@amount", item["amount"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@othermail", othermail));
                dbparamlist.Add(new dbparam("@action1", item["action1"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@workno", workno));
                dbparamlist.Add(new dbparam("@action2", item["action2"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mblist", mblist));
                dbparamlist.Add(new dbparam("@oldno", item["oldno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@newno", item["newno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@sopno", item["sopno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@sipno", item["sipno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@action3", item["action3"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@action4", item["action4"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@action5", item["action5"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@ecrno", item["ecr"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@ecnno", item["ecn"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@enno", item["en"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@id", iSirmsData.formId.TrimEnd()));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.modifyinsideform @postGroup,@postName,@case,@homepage1,@pnumber,@endDate,@obj,@homepageMomo,@mb,@amount,@subject,@body,@othermail,@action1,@workno,@action2,@mblist,@oldno,@newno,@sopno,@sipno,@action3,@action4,@action5,@ecrno,@ecnno,@enno,@id;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            dbparamlist.Add(new dbparam("@signing", "1"));
            dbparamlist.Add(new dbparam("@id", iSirmsData.formId.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "update dbo.FN set signing = @signing where id = @id;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            List<string> deleteitems = new List<string>();
            foreach (var item in iSirmsData.photoitems)
            {
                bool insert = bool.Parse(item["photoInsert"].ToString().TrimEnd()), delete = bool.Parse(item["photoDelete"].ToString().TrimEnd());
                switch (insert)
                {
                    case true:
                        switch (delete)
                        {
                            case false:
                                dbparamlist.Clear();
                                dbparamlist.Add(new dbparam("@formId", iSirmsData.formId.TrimEnd()));
                                dbparamlist.Add(new dbparam("@inoper", iSirmsData.newid.TrimEnd()));
                                dbparamlist.Add(new dbparam("@uploadPath", ""));
                                dbparamlist.Add(new dbparam("@imagePath", item["photoPath"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@original", item["photoOriginal"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@encryption", item["photoEncryption"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@extension", item["photoExtension"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(item["photoExtension"].ToString().TrimEnd())));
                                dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(database.connectionString("folderFiles"), $"{item["photoOriginal"].ToString().TrimEnd()}({item["photoEncryption"].ToString().TrimEnd()}){item["photoExtension"].ToString().TrimEnd()}")));
                                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertinfileform @formId,@inoper,@uploadPath,@imagePath,@original,@encryption,@extension,@type,@capacity;", dbparamlist) != "istrue")
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
                                deleteitems.Add(item["photoId"].ToString().TrimEnd());
                                break;
                        }
                        break;
                }
            }
            if (deleteitems.Count > 0)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", iSirmsData.formId.TrimEnd()));
                dbparamlist.Add(new dbparam("@inoper", iSirmsData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@sqlcode", string.Join(',', deleteitems)));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.deleteinfileform @formId,@inoper,@sqlcode;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            deleteitems = new List<string>();
            foreach (var item in iSirmsData.grotoitems)
            {
                bool insert = bool.Parse(item["grotoInsert"].ToString().TrimEnd()), delete = bool.Parse(item["grotoDelete"].ToString().TrimEnd());
                switch (insert)
                {
                    case true:
                        switch (delete)
                        {
                            case false:
                                dbparamlist.Clear();
                                dbparamlist.Add(new dbparam("@formId", iSirmsData.formId.TrimEnd()));
                                dbparamlist.Add(new dbparam("@inoper", iSirmsData.newid.TrimEnd()));
                                dbparamlist.Add(new dbparam("@name", item["grotoName"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@uploadPath", ""));
                                dbparamlist.Add(new dbparam("@imagePath", item["grotoPath"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@original", item["grotoOriginal"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@encryption", item["grotoEncryption"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@extension", item["grotoExtension"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(item["grotoExtension"].ToString().TrimEnd())));
                                dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(database.connectionString("folderFiles"), $"{item["grotoOriginal"].ToString().TrimEnd()}({item["grotoEncryption"].ToString().TrimEnd()}){item["grotoExtension"].ToString().TrimEnd()}")));
                                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertingroupform @formId,@inoper,@name,@uploadPath,@imagePath,@original,@encryption,@extension,@type,@capacity;", dbparamlist) != "istrue")
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
                                deleteitems.Add(item["grotoId"].ToString().TrimEnd());
                                break;
                        }
                        break;
                }
            }
            if (deleteitems.Count > 0)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", iSirmsData.formId.TrimEnd()));
                dbparamlist.Add(new dbparam("@inoper", iSirmsData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@sqlcode", string.Join(',', deleteitems)));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.deleteingroupform @formId,@inoper,@sqlcode;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@mAddrName", $"{othermail}{supeRows.Rows[0]["username"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
            dbparamlist.Add(new dbparam("@mSubject", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」建立工廠內部通告:{iSirmsData.tile.TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;margin: 0 auto;'><div style='padding: 12px; border:2px solid white;'><div><h3 style='color: red;'>FN SYSTEM NEWS</h3></div><div> <hr /></div><div><h3 style='color: red;'>建立工廠內部通告需瞭解</h3></div><div style='font-size: 16px;'>{new datetime().sqldate("mssql", "flyfnstring")} {new datetime().sqltime("mssql", "flyfnstring")}</div><div><h4>請相關人員進行瞭解此問題．</h4></div><div><a style='background-color:red; color:white; padding:12px;' href='http://221.222.222.181:7250/modifyF#{iSirmsData.formId.TrimEnd()}'>前往瞭解</a></div></div></div>"));
            //缺少簽核狀態變更
            dbparamlist.Clear();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.searchinsignlist;", dbparamlist).Rows)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", iSirmsData.formId.TrimEnd()));
                dbparamlist.Add(new dbparam("@newid", dr["newid"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@inoper", iSirmsData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@value", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」建立工廠內部通告需簽核:{iSirmsData.tile.TrimEnd()}"));
                dbparamlist.Add(new dbparam("@link", $"/signlistF#{iSirmsData.formId.TrimEnd()}"));
                database.checkActiveSql("mssql", "flyfnstring", "exec web.insertnoticeform @formId,@newid,@inoper,@value,@link;", dbparamlist);
            }
            return new statusModels() { status = "istrue" };
        }
    }
}