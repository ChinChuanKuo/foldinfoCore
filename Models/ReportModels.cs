using System.Collections.Generic;
using System.Data;
using foldinfoCore.App_Code;

namespace foldinfoCore.Models
{
    public class ReportClass
    {
        public sOptonModels GetSearchModels(userData userData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@isused", "1"));
            List<Dictionary<string, object>> groupitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "select distinct substring(department,4,len(department)-3) as department from web.siteber where isused = @isused;", dbparamlist).Rows)
            {
                groupitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["department"].ToString().TrimEnd() } });
            }
            string[] floorArray = new string[] { "NA", "1F", "2F", "3F", "4F", "5F", "6F", "外包" };
            List<Dictionary<string, object>> flooritems = new List<Dictionary<string, object>>();
            foreach (var floor in floorArray)
            {
                flooritems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", floor } });
            }
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@value", ""));
            List<Dictionary<string, object>> momoitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flycsastring", "select distinct 機種別 from dbo.islma where 機種別 != @value order by 機種別 asc;", dbparamlist).Rows)
            {
                momoitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["機種別"].ToString().TrimEnd() } });
            }
            List<Dictionary<string, object>> mbitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flycsastring", "select distinct MB別 from dbo.islma where MB別 != @value order by MB別 asc;", dbparamlist).Rows)
            {
                mbitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["MB別"].ToString().TrimEnd() } });
            }
            string[] objArray = new string[] { "NA", "製造", "IQC", "DOA", "RMA", "銷退", "SMT", "DIP", "板測", "板測，系測", "加工", "組裝", "組裝，包裝", "PreTest", "系測", "包裝", "週邊", "QA校驗", "IPQC", "OQC", "其他", "客驗", "客訴" };
            List<Dictionary<string, object>> objitems = new List<Dictionary<string, object>>();
            foreach (var obj in objArray)
            {
                objitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", obj } });
            }
            return new sOptonModels() { items = new List<Dictionary<string, object>>() { new Dictionary<string, object>() { { "number", "" }, { "version", "" }, { "postdate", "" }, { "postInfo", $"-" }, { "showFloorMenu", false }, { "flooritems", flooritems.ToArray() }, { "floor", "" }, { "homepage1", "" }, { "pnumber", "" }, { "showMomoMenu", false }, { "momoitems", momoitems.ToArray() }, { "homepageMomo", "" }, { "showMbMenu", false }, { "mbitems", mbitems.ToArray() }, { "mb", "" }, { "showObjMenu", false }, { "objitems", objitems.ToArray() }, { "obj", "" }, { "worknumber", "" }, { "pn", "" }, { "amount", "" }, { "fail", "" }, { "subject", "" }, { "containment", "" } } } };
        }
    }
}