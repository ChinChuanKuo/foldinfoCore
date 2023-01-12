using System;
using System.Collections.Generic;
using System.Data;
using FOLDINFOCore.App_Code;

namespace FOLDINFOCore.Models
{
    public class ForgetClass
    {
        public statusModels GetForgetUserModels(otherData otherData, string cuurip)
        {
            switch (string.IsNullOrWhiteSpace(otherData.userid))
            {
                case true:
                    return new statusModels() { status = "nousers" };
            }
            switch (string.IsNullOrWhiteSpace(otherData.values))
            {
                case true:
                    return new statusModels() { status = "errorForget" };
            }
            DataTable userRows = new DataTable();
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", otherData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@birthday", otherData.values.TrimEnd()));
            dbparamlist.Add(new dbparam("@status", "1"));
            userRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.forgetsiteber @newid,@birthday,@status;", dbparamlist);
            switch (userRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            switch (userRows.Rows[0]["isused"].ToString().TrimEnd())
            {
                case "0":
                    return new statusModels() { status = "islock" };
            }
            Random random = new Random();
            datetime datetime = new datetime();
            string vecode = random.Next(100000, 999999).ToString().TrimEnd(), date = datetime.sqldate("mssql", "flyfnstring"), time = datetime.sqltime("mssql", "flyfnstring");
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@vedate", date));
            dbparamlist.Add(new dbparam("@vetime", time));
            dbparamlist.Add(new dbparam("@vecode", vecode));
            dbparamlist.Add(new dbparam("@modate", date));
            dbparamlist.Add(new dbparam("@motime", time));
            dbparamlist.Add(new dbparam("@newid", otherData.userid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "update web.siteber set vedate = @vedate,vetime = @vetime,vecode = @vecode,modate = @modate,motime = @motime where newid = @newid;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            return new statusModels() { status = "istrue" };
        }
    }
}