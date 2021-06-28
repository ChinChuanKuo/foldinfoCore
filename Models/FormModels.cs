using System.Collections.Generic;
using System.Data;
using System.Threading;
using foldinfoCore.App_Code;

namespace foldinfoCore.Models
{
    public class FormClass
    {
        public statusModels GetCheckNewModels(userData userData, string cuurip)
        {
            switch (string.IsNullOrWhiteSpace(userData.userid))
            {
                case true:
                    return new statusModels() { status = "nodata" };
            }
            DataTable checkRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", userData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@status", "1"));
            checkRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.checkformnewid @newid,@status;", dbparamlist);
            switch (checkRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            switch (checkRows.Rows[0]["isused"].ToString().TrimEnd())
            {
                case "1":
                    return new statusModels() { status = "istrue" };
            }
            return new statusModels() { status = "islock" };
        }

        public loginModels GetLoginFormModels(userData userData, string cuurip, string userAgent)
        {
            switch (string.IsNullOrWhiteSpace(userData.userid))
            {
                case true:
                    return new loginModels() { status = "errorFormLogin" };
            }
            database database = new database();
            DataTable loginRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", userData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@externip", cuurip));
            dbparamlist.Add(new dbparam("@status", "1"));
            loginRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checkformlogin @newid,@externip,@status;", dbparamlist);
            switch (loginRows.Rows.Count)
            {
                case 0:
                    return new loginModels() { status = "nodata" };
            }
            if (loginRows.Rows[0]["isused"].ToString().TrimEnd() == "1" && loginRows.Rows[0]["islogin"].ToString().TrimEnd() == "1")
            {
                datetime datetime = new datetime();
                information information = new information();
                string date = datetime.sqldate("mssql", "flyfnstring"), time = datetime.sqltime("mssql", "flyfnstring");
                dbparamlist.Add(new dbparam("@cpu", ""));
                dbparamlist.Add(new dbparam("@os", information.osystem(userAgent)));
                dbparamlist.Add(new dbparam("@internip", ""));
                dbparamlist.Add(new dbparam("@indate", date));
                dbparamlist.Add(new dbparam("@intime", time));
                switch (database.checkActiveSql("mssql", "flyfnstring", "update web.sitelog set cpu = @cpu,os = @os,internip = @internip,indate = @indate,intime = @intime where newid = @newid and externip = @externip and islogin = @status;", dbparamlist))
                {
                    case "istrue":
                        return new loginModels() { newid = loginRows.Rows[0]["newid"].ToString().TrimEnd(), name = loginRows.Rows[0]["username"].ToString().TrimEnd().Substring(0, 1), allname = loginRows.Rows[0]["username"].ToString().TrimEnd(), status = "istrue" };
                }
                return new loginModels() { status = "error" };
            }
            return new loginModels() { status = "islock" };
        }

        public statusModels GetBadgeFormModels(otherData otherData, string cuurip)
        {
            bool isbreak = true;
            string badge = "0";
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", otherData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@status", "0"));
            while (isbreak)
            {
                Thread.Sleep(5000);
                badge = database.checkSelectSql("mssql", "flyfnstring", "exec web.countnoticeform @newid,@status;", dbparamlist).Rows[0]["counts"].ToString().TrimEnd();
                if (badge != otherData.values.TrimEnd())
                {
                    isbreak = false;
                }
            }
            return new statusModels() { status = badge };
        }

        public permissModels GetPermissModels(userData userData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", userData.userid.TrimEnd()));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchallmissform @newid;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new permissModels() { insert = false, update = false, delete = false, export = false };
            }
            return new permissModels() { insert = mainRows.Rows[0]["isinsert"].ToString().TrimEnd() == "1", update = mainRows.Rows[0]["ismodify"].ToString().TrimEnd() == "1", delete = mainRows.Rows[0]["isdelete"].ToString().TrimEnd() == "1", export = mainRows.Rows[0]["isexport"].ToString().TrimEnd() == "1" };
        }

        public itemsModels GetRecordModels(userData userData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", userData.userid.TrimEnd()));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchrecordform @newid;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new itemsModels() { showItem = false };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "link", dr["link"].ToString().TrimEnd() }, { "icon", dr["icon"].ToString().TrimEnd() }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            return new itemsModels() { showItem = true, items = items };
        }

        public itemsModels GetBadgeModels(userData userData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@inoper", userData.userid.TrimEnd()));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.updatenoticeform @inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new itemsModels() { showItem = false };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "link", dr["link"].ToString().TrimEnd() }, { "name", dr["username"].ToString().TrimEnd().Substring(0, 1) }, { "value", dr["value"].ToString().TrimEnd() }, { "datetime", $"{dr["indate"].ToString().TrimEnd()} {dr["intime"].ToString().TrimEnd()}" } });
            }
            return new itemsModels() { showItem = true, items = items };
        }
    }
}