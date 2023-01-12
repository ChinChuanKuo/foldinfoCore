using System.Collections.Generic;
using System.Data;
using FOLDINFOCore.App_Code;

namespace FOLDINFOCore.Models
{
    public class SignlistClass
    {
        public sItemModels GetSearchModels(userData userData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@inoper", userData.userid.TrimEnd()));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchsignlistform @inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sItemModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "id", dr["id"].ToString().TrimEnd() }, { "tile", $"{dr["number"].ToString().TrimEnd()}-{dr["version"].ToString().TrimEnd()}" }, { "subject", dr["subject"].ToString().TrimEnd() }, { "postdate", dr["postdate"].ToString().TrimEnd() }, { "postGroup", dr["postGroup"].ToString().TrimEnd() }, { "postName", dr["postName"].ToString().TrimEnd() } });
            }
            return new sItemModels() { items = items, status = "istrue" };
        }
    }
}