using System.Collections.Generic;
using System.Data;
using System.Net;
using foldinfoCore.App_Code;

namespace foldinfoCore.Models
{
    public class LoginClass
    {
        public userModels GetUserModels(userData userData, string cuurip)
        {
            switch (string.IsNullOrWhiteSpace(userData.userid))
            {
                case true:
                    return new userModels() { status = "errorUserid" };
            }
            database database = new database();
            DataTable userRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@userid", userData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@status", "1"));
            userRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksiteber @userid,@status;", dbparamlist);
            switch (userRows.Rows.Count)
            {
                case 0:
                    return new userModels() { status = "nodata" };
            }
            switch (userRows.Rows[0]["isused"].ToString().TrimEnd())
            {
                case "1":
                    return new userModels() { newid = userRows.Rows[0]["newid"].ToString().TrimEnd(), status = "istrue" };
            }
            return new userModels() { status = "islock" };
        }

        public loginModels GetLoginModels(loginData loginData, string cuurip, string userAgent)
        {
            switch (string.IsNullOrWhiteSpace(loginData.userid))
            {
                case true:
                    return new loginModels() { status = "errorUserid" };
            }
            switch (string.IsNullOrWhiteSpace(loginData.password))
            {
                case true:
                    return new loginModels() { status = "errorPassword" };
            }
            DataTable userRows = new DataTable();
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@userid", loginData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@password", new sha256().encry256(loginData.password.TrimEnd())));
            dbparamlist.Add(new dbparam("@status", "1"));
            userRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.loginsiteber @userid,@password,@status;", dbparamlist);
            switch (userRows.Rows.Count)
            {
                case 0:
                    return new loginModels() { status = "nodata" };
            }
            datetime datetime = new datetime();
            string newid = userRows.Rows[0]["newid"].ToString().TrimEnd(), name = userRows.Rows[0]["username"].ToString().TrimEnd(), longitude = string.IsNullOrWhiteSpace(loginData.longitude) ? "0.0" : loginData.longitude, latitude = string.IsNullOrWhiteSpace(loginData.latitude) ? "0.0" : loginData.latitude, cuname = Dns.GetHostEntry(cuurip).HostName.IndexOf('.') == -1 ? Dns.GetHostEntry(cuurip).HostName : Dns.GetHostEntry(cuurip).HostName.Split('.')[0], date = datetime.sqldate("mssql", "flyfnstring"), time = datetime.sqltime("mssql", "flyfnstring");
            switch (userRows.Rows[0]["isused"].ToString().TrimEnd())
            {
                case "1":
                    information information = new information();
                    userRows.Clear();
                    dbparamlist.Add(new dbparam("@externip", cuurip));
                    userRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksitelog @userid,@password,@externip,@status;", dbparamlist);
                    switch (userRows.Rows.Count)
                    {
                        case 0:
                            dbparamlist.Clear();
                            dbparamlist.Add(new dbparam("@newid", newid));
                            dbparamlist.Add(new dbparam("@externip", cuurip));
                            dbparamlist.Add(new dbparam("@longitude", longitude));
                            dbparamlist.Add(new dbparam("@latitude", latitude));
                            dbparamlist.Add(new dbparam("@hostname", cuname));
                            dbparamlist.Add(new dbparam("@browser", information.browser(userAgent)));
                            dbparamlist.Add(new dbparam("@os", information.osystem(userAgent)));
                            dbparamlist.Add(new dbparam("@indate", date));
                            dbparamlist.Add(new dbparam("@intime", time));
                            dbparamlist.Add(new dbparam("@islogin", "1"));
                            if (database.checkActiveSql("mssql", "flyfnstring", "insert into web.sitelog (newid,externip,longitude,latitude,hostname,browser,os,indate,intime,islogin) values (@newid,@externip,@longitude,@latitude,@hostname,@browser,@os,@indate,@intime,@islogin);", dbparamlist) != "istrue")
                            {
                                return new loginModels() { status = "error" };
                            }
                            return new loginModels() { newid = newid, name = name.Substring(0, 1), allname = name, status = "istrue" };
                    }
                    if (userRows.Rows[0]["isused"].ToString().TrimEnd() == "1" && userRows.Rows[0]["islogin"].ToString().TrimEnd() == "1")
                    {
                        dbparamlist.Clear();
                        dbparamlist.Add(new dbparam("@longitude", longitude));
                        dbparamlist.Add(new dbparam("@latitude", latitude));
                        dbparamlist.Add(new dbparam("@browser", information.browser(userAgent)));
                        dbparamlist.Add(new dbparam("@os", information.osystem(userAgent)));
                        dbparamlist.Add(new dbparam("@indate", date));
                        dbparamlist.Add(new dbparam("@intime", time));
                        dbparamlist.Add(new dbparam("@newid", newid));
                        dbparamlist.Add(new dbparam("@externip", cuurip));
                        dbparamlist.Add(new dbparam("@islogin", "1"));
                        if (database.checkActiveSql("mssql", "flyfnstring", "update web.sitelog set longitude = @longitude,latitude = @latitude,browser = @browser,os = @os,indate = @indate,intime = @intime where newid = @newid and externip = @externip and islogin = @islogin;", dbparamlist) != "istrue")
                        {
                            return new loginModels() { status = "error" };
                        }
                        return new loginModels() { newid = newid, name = name.Substring(0, 1), allname = name, status = "istrue" };
                    }
                    break;
            }
            return new loginModels() { status = "islock" };
        }
    }
}
