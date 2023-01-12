using System.Collections.Generic;
using System.Data;
using FOLDINFOCore.App_Code;

namespace FOLDINFOCore.Models
{
    public class MailistFClass
    {
        public sArrayModels GetSearchModels(userData userData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@inoper", userData.userid.TrimEnd()));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchinmailmentform @inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sArrayModels() { status = "nodata" };
            }
            List<string> items = new List<string>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(dr["department"].ToString().TrimEnd());
            }
            return new sArrayModels() { items = items.ToArray(), status = "istrue" };
        }

        public sRowsModels GetSItemModels(otherData otherData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@department", otherData.values.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", otherData.userid.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchinmailuserform @department,@inoper;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "newid", dr["newid"].ToString().TrimEnd() }, { "username", dr["username"].ToString().TrimEnd() }, { "notice", dr["notice"].ToString().TrimEnd() == "1" }, { "formModify", false } });
            }
            return new sRowsModels() { formId = otherData.values.TrimEnd(), tile = otherData.values.TrimEnd(), items = items, status = "istrue" };
        }

        public statusModels GetInsertModels(iFormData iFormData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", iFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", iFormData.newid.TrimEnd()));
            switch (database.checkSelectSql("mssql", "flyfnstring", "exec web.searchinmailform @formId,@inoper;", dbparamlist).Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            foreach (var item in iFormData.items)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@newid", item["newid"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@notice", bool.Parse(item["notice"].ToString().TrimEnd()) ? "1" : "0"));
                dbparamlist.Add(new dbparam("@inoper", iFormData.newid.TrimEnd()));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.updateinmailform @newid,@notice,@inoper;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            return new statusModels() { status = "istrue" };
        }
    }
}