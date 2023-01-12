using System.Collections.Generic;
using System.Data;
using FOLDINFOCore.App_Code;

namespace FOLDINFOCore.Models
{
    public class SignupClass
    {
        public statusModels GetSignupUserModels(signupData signupData, string cuurip)
        {
            switch (string.IsNullOrWhiteSpace(signupData.userid))
            {
                case true:
                    return new statusModels() { status = "errorUserid" };
            }
            switch (string.IsNullOrWhiteSpace(signupData.password))
            {
                case true:
                    return new statusModels() { status = "errorPassword" };
            }
            switch (string.IsNullOrWhiteSpace(signupData.username))
            {
                case true:
                    return new statusModels() { status = "errorUsername" };
            }
            switch (string.IsNullOrWhiteSpace(signupData.birthday))
            {
                case true:
                    return new statusModels() { status = "errorBirthday" };
            }
            DataTable userRows = new DataTable();
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@userid", signupData.userid.TrimEnd()));
            userRows = database.checkSelectSql("mssql", "flyfnstring", "select newid,userid from web.siteber where userid = @userid;", dbparamlist);
            if (userRows.Rows.Count > 0)
            {
                return new statusModels() { status = "error" };
            }
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@userid", signupData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@password", new sha256().encry256(signupData.password.TrimEnd())));
            dbparamlist.Add(new dbparam("@username", signupData.username.TrimEnd()));
            dbparamlist.Add(new dbparam("@birthday", signupData.birthday.TrimEnd()));
            dbparamlist.Add(new dbparam("@permiss", "general"));
            if (database.checkActiveSql("mssql", "flyfnstring", "insert into web.siteber (userid,password,username,birthday,permiss) values (@userid,@password,@username,@birthday,@permiss);", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            return new statusModels() { status = "istrue" };
        }
    }
}