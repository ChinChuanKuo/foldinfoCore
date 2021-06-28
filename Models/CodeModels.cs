using System;
using System.Collections.Generic;
using System.Data;
using foldinfoCore.App_Code;

namespace foldinfoCore.Models
{
    public class CodeClass
    {
        public statusModels GetCodeUserModels(otherData otherData, string cuurip)
        {
            switch (string.IsNullOrWhiteSpace(otherData.userid))
            {
                case true:
                    return new statusModels() { status = "nousers" };
            }
            switch (string.IsNullOrWhiteSpace(otherData.values))
            {
                case true:
                    return new statusModels() { status = "errorCode" };
            }
            DataTable userRows = new DataTable();
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", otherData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@vecode", otherData.values.TrimEnd()));
            dbparamlist.Add(new dbparam("@status", "1"));
            userRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.codesiteber @newid,@vecode,@status;", dbparamlist);
            switch (userRows.Rows.Count)
            {
                case 0:
                    return  new statusModels() { status = "nodata" };
            }
            switch (userRows.Rows[0]["isused"].ToString().TrimEnd())
            {
                case "0":
                    return new statusModels() { status = "islock" };
            }
            datetime datetime = new datetime();
            string date = datetime.sqldate("mssql", "flyfnstring"), time = datetime.sqltime("mssql", "flyfnstring");
            DateTime startdate = DateTime.Parse(date + " " + time);
            DateTime enddate = DateTime.Parse(userRows.Rows[0]["vedate"].ToString().TrimEnd() + " " + userRows.Rows[0]["vetime"].ToString().TrimEnd()).AddMinutes(10);
            if (enddate >= startdate)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@vedate", ""));
                dbparamlist.Add(new dbparam("@vetime", ""));
                dbparamlist.Add(new dbparam("@vecode", ""));
                dbparamlist.Add(new dbparam("@modate", date));
                dbparamlist.Add(new dbparam("@motime", time));
                dbparamlist.Add(new dbparam("@newid", otherData.userid.TrimEnd()));
                if (database.checkActiveSql("mssql", "flyfnstring", "update web.siteber set vedate = @vedate,vetime = @vetime,vecode = @vecode,modate = @modate,motime = @motime where newid = @newid;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
                return new statusModels() { status = "istrue" };
            }
            Random random = new Random();
            string vecode = random.Next(100000, 999999).ToString().TrimEnd();
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
            return new statusModels() { status = "resend" };
        }
    }
}