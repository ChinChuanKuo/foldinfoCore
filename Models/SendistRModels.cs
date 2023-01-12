using System.Collections.Generic;
using System.Data;
using FOLDINFOCore.App_Code;

namespace FOLDINFOCore.Models
{
    public class SendistRClass
    {
        public itemModels GetSearchModels(userData userData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@inoper", userData.userid.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchresignform @inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new itemModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                dbparamlist.Clear();
                List<Dictionary<string, object>> groupitems = new List<Dictionary<string, object>>();
                foreach (DataRow drs in database.checkSelectSql("mssql", "flyfnstring", "exec web.searchallgroupform;", dbparamlist).Rows)
                {
                    groupitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", drs["department"].ToString().TrimEnd() } });
                }
                dbparamlist.Add(new dbparam("@group", mainRows.Rows[0]["department"].ToString().TrimEnd()));
                List<Dictionary<string, object>> nameitems = new List<Dictionary<string, object>>();
                foreach (DataRow drs in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchgroupform @group;", dbparamlist).Rows)
                {
                    nameitems.Add(new Dictionary<string, object>() { { "padding", false }, { "key", drs["newid"].ToString().TrimEnd() }, { "value", drs["username"].ToString().TrimEnd() } });
                }
                items.Add(new Dictionary<string, object>() { { "iid", dr["iid"].ToString().TrimEnd() }, { "group", dr["department"].ToString().TrimEnd() }, { "showGroupMenu", false }, { "groupitems", groupitems.ToArray() }, { "id", dr["newid"].ToString().TrimEnd() }, { "name", dr["username"].ToString().TrimEnd() }, { "showNameMenu", false }, { "nameitems", nameitems.ToArray() }, { "itemInsert", false }, { "itemModify", false } });
            }
            return new itemModels() { items = items, status = "istrue" };
        }

        public sOptonModels GetAddModels(userData userData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow drs in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchallgroupform;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", drs["department"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public sOptonModels GetSGroupModels(otherData otherData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@group", otherData.values.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchgroupform @group;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "padding", false }, { "key", dr["newid"].ToString().TrimEnd() }, { "value", dr["username"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public statusModels GetInsertModels(iItemsData iItemsData, string cuurip)
        {
            database database = new database();
            foreach (var item in iItemsData.items)
            {
                switch (bool.Parse(item["itemInsert"].ToString().TrimEnd()))
                {
                    case true:
                        List<dbparam> dbparamlist = new List<dbparam>();
                        dbparamlist.Add(new dbparam("@iid", item["iid"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@inoper", iItemsData.newid.TrimEnd()));
                        dbparamlist.Add(new dbparam("@newid", item["id"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@username", item["name"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@department", item["group"].ToString().TrimEnd()));
                        if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertresignform @iid,@inoper,@newid,@username,@department;", dbparamlist) != "istrue")
                        {
                            return new statusModels() { status = "nodata" };
                        }
                        break;
                    default:
                        dbparamlist = new List<dbparam>();
                        dbparamlist.Add(new dbparam("@newid", item["id"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@username", item["name"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@department", item["group"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@iid", item["iid"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@inoper", iItemsData.newid.TrimEnd()));
                        if (database.checkActiveSql("mssql", "flyfnstring", "exec web.modifyresignform @newid,@username,@department,@iid,@inoper;", dbparamlist) != "istrue")
                        {
                            return new statusModels() { status = "nodata" };
                        }
                        break;
                }
            }
            return new statusModels() { status = "istrue" };
        }
    }
}