using System.Collections.Generic;
using System.Data;
using foldinfoCore.App_Code;

namespace foldinfoCore.Models
{
    public class PermissClass
    {
        public bool searchForm(string newid)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", newid));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchmissform @newid;", dbparamlist);
            if (mainRows.Rows.Count == 0 || mainRows.Rows[0]["issearch"].ToString().TrimEnd() == "0")
            {
                return false;
            }
            return true;
        }

        public bool insertForm(string newid)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", newid));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.insertmissform @newid;", dbparamlist);
            if (mainRows.Rows.Count == 0 || mainRows.Rows[0]["isinsert"].ToString().TrimEnd() == "0")
            {
                return false;
            }
            return true;
        }

        public bool modifyForm(string newid)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", newid));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.modifymissform @newid;", dbparamlist);
            if (mainRows.Rows.Count == 0 || mainRows.Rows[0]["ismodify"].ToString().TrimEnd() == "0")
            {
                return false;
            }
            return true;
        }

        public bool deleteForm(string newid)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", newid));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.deletemissform @newid;", dbparamlist);
            if (mainRows.Rows.Count == 0 || mainRows.Rows[0]["isdelete"].ToString().TrimEnd() == "0")
            {
                return false;
            }
            return true;
        }

        public bool adjustForm(string newid)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", newid));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.adjustmissform @newid;", dbparamlist);
            if (mainRows.Rows.Count == 0 || mainRows.Rows[0]["isadjust"].ToString().TrimEnd() == "0")
            {
                return false;
            }
            return true;
        }
    }
}