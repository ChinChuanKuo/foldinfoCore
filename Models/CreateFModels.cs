using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Net;
using System.Text.Json;
using foldinfoCore.App_Code;

namespace foldinfoCore.Models
{
    public class CreateFClass
    {
        public sItemModels GetSearchModels(userData userData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            List<Dictionary<string, object>> groupitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.searchallgroupform;", dbparamlist).Rows)
            {
                groupitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["department"].ToString().TrimEnd() } });
            }
            string[] caseArray = new string[] { "", "出貨內容修改", "包裝料件修改", "作業性變更", "訂單修改", "訂單備料", "異常處理變更", "組裝料件修改", "測試方式變更", "增加客戶需求" };
            List<Dictionary<string, object>> caseitems = new List<Dictionary<string, object>>();
            foreach (var value in caseArray)
            {
                caseitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", value } });
            }
            string[] objArray = new string[] { "", "DIP", "DOA", "IPQC", "IQC", "NA", "OQC", "PreTest", "QA校驗", "RMA", "SMT", "加工", "包裝", "系測", "其它", "板測", "板測,系測", "客訴", "客驗", "組裝", "組裝,包裝", "週邊", "製程", "銷退" };
            List<Dictionary<string, object>> objitems = new List<Dictionary<string, object>>();
            foreach (var value in objArray)
            {
                objitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", value } });
            }
            List<Dictionary<string, object>> typeitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.searchtypeform;", dbparamlist).Rows)
            {
                typeitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["type"].ToString().TrimEnd() } });
            }
            int i = 0;
            List<Dictionary<string, object>> mailitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.noticeinmailform;", dbparamlist).Rows)
            {
                mailitems.Add(new Dictionary<string, object>() { { "mbId", i }, { "mbValue", dr["username"].ToString().TrimEnd() } });
                i++;
            }
            List<Dictionary<string, object>> mtstitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flycsastring", "exec dbo.searchallinventform;", dbparamlist).Rows)
            {
                mtstitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["mb"].ToString().TrimEnd() } });
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "snno", "" }, { "showSnno", false }, { "snnoitems", new List<Dictionary<string, object>>().ToArray() }, { "showGroupMenu", false }, { "groupitems", groupitems.ToArray() }, { "postGroup", "" }, { "showNameMenu", false }, { "nameitems", new List<Dictionary<string, object>>().ToArray() }, { "postName", "" }, { "showCaseMenu", false }, { "caseitems", caseitems.ToArray() }, { "case", "" }, { "homepage1", "" }, { "pnumber", "" }, { "endDate", "" }, { "showObjMenu", false }, { "objitems", objitems.ToArray() }, { "obj", "" }, { "homepageMomo", "" }, { "mb", "" }, { "amount", "" }, { "subject", "" }, { "ecr", "" }, { "showXps", false }, { "ecn", "" }, { "en", "" }, { "showTypeMenu", false }, { "typeitems", typeitems.ToArray() }, { "type_", "" }, { "body", "" }, { "mailitems", mailitems.ToArray() }, { "showMagroupMenu", false }, { "magroupitems", groupitems.ToArray() }, { "maGroup", "" }, { "showManameMenu", false }, { "manameitems", new List<Dictionary<string, object>>().ToArray() }, { "maName", "" }, { "action1", "" }, { "workitems", new List<Dictionary<string, object>>().ToArray() }, { "work", "" }, { "showWork", false }, { "worknoitems", new List<Dictionary<string, object>>().ToArray() }, { "code", "" }, { "action2", "" }, { "mbitems", new List<Dictionary<string, object>>().ToArray() }, { "showMtstMenu", false }, { "mtstitems", mtstitems.ToArray() }, { "mtst", "" }, { "showMbstMenu", false }, { "mbstitems", new List<Dictionary<string, object>>().ToArray() }, { "mbst", "" }, { "oldno", "" }, { "newno", "" }, { "sopno", "" }, { "action3", "" }, { "sipno", "" }, { "action4", "" }, { "action5", "" } });
            return new sItemModels() { items = items, status = "istrue" };
        }

        public sArItemModels GetSSnnoModels(otherData otherData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@length", otherData.values.Length));
            dbparamlist.Add(new dbparam("@value", otherData.values.TrimEnd()));
            mainRows = new database().checkSelectSql("mssql", "epaperstring", "exec web.searchsnnodata @length,@value;", dbparamlist);
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            switch (mainRows.Rows[0]["status"].ToString().TrimEnd())
            {
                case "only":
                    List<Dictionary<string, object>> workitems = new List<Dictionary<string, object>>();
                    foreach (var item in mainRows.Rows[0]["workorderno"].ToString().TrimEnd().Split(',').Select((value, i) => new { i, value }))
                    {
                        if (item.value != "")
                        {
                            workitems.Add(new Dictionary<string, object>() { { "mbId", item.i }, { "mbValue", item.value } });
                        }
                    }
                    items.Add(new Dictionary<string, object>() { { "postGroup", mainRows.Rows[0]["userdepartment"].ToString().TrimEnd() }, { "postName", mainRows.Rows[0]["username"].ToString().TrimEnd() }, { "case", mainRows.Rows[0]["modifytype"].ToString().TrimEnd() }, { "homepage1", mainRows.Rows[0]["customername"].ToString().TrimEnd() }, { "pnumber", mainRows.Rows[0]["orderno"].ToString().TrimEnd() }, { "obj", mainRows.Rows[0]["station"].ToString().TrimEnd() }, { "homepageMomo", mainRows.Rows[0]["model"].ToString().TrimEnd() }, { "mb", mainRows.Rows[0]["motherboard"].ToString().TrimEnd() }, { "amount", mainRows.Rows[0]["count"].ToString().TrimEnd() }, { "subject", mainRows.Rows[0]["subject"].ToString().TrimEnd() }, { "body", mainRows.Rows[0]["description"].ToString().TrimEnd() }, { "workitems", workitems.ToArray() } });
                    return new sArItemModels() { array = items, status = "only" };
            }
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            return new sArItemModels() { items = items, status = "istrue" };
        }

        public sOptonModels GetSGroupModels(otherData otherData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@group", otherData.values.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchgroupform @group;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["username"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public sDataModels GetSTypeModels(otherData otherData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@type", otherData.values.TrimEnd()));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchcontentform @type;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sDataModels() { status = "nodata" };
            }
            return new sDataModels() { value = mainRows.Rows[0]["content"].ToString().TrimEnd(), status = "istrue" };
        }

        public sOptonModels GetSWorkModels(otherData otherData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@length", otherData.values.Length));
            dbparamlist.Add(new dbparam("@value", otherData.values.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flycsastring", "exec dbo.searchworkdeta @length,@value;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public statusModels GetCWorkModels(otherData otherData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@value", otherData.values.TrimEnd()));
            mainRows = new database().checkSelectSql("mssql", "flycsastring", "exec dbo.checkworkdeta @value;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            return new statusModels() { status = "istrue" };
        }

        public sRowsModels GetSXpsModels(otherData otherData, string cuurip)
        {
            database database = new database();
            switch (File.Exists($"{database.connectionString("ecrFiles")}{otherData.values.TrimEnd()}.pdf"))
            {
                case false:
                    return new sRowsModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "filePath", database.connectionString("ercHttps") }, { "fileSrc", $"{otherData.values.TrimEnd()}.pdf" } });
            return new sRowsModels() { formId = otherData.values.TrimEnd(), tile = otherData.values.TrimEnd(), items = items, status = "istrue" };
        }

        public sOptonModels GetSEcrnoModels(otherData otherData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            switch (otherData.values.TrimEnd())
            {
                case "":
                    mainRows = new database().checkSelectSql("mssql", "flycsastring", "exec dbo.searchallinventform;", dbparamlist);
                    break;
                default:
                    dbparamlist.Add(new dbparam("@ecrno", otherData.values.TrimEnd()));
                    mainRows = new database().checkSelectSql("mssql", "flyecrstring", "exec dbo.searchbeforecrdata @ecrno;", dbparamlist);
                    break;
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["mb"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public sOptonModels GetSModelModels(sRowsData sRowsData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@model", sRowsData.value.TrimEnd()));
            switch (sRowsData.formId.TrimEnd())
            {
                case "":
                    mainRows = new database().checkSelectSql("mssql", "flycsastring", "exec dbo.searchinventform @model;", dbparamlist);
                    break;
                default:
                    dbparamlist.Add(new dbparam("@ecrno", sRowsData.formId.TrimEnd()));
                    mainRows = new database().checkSelectSql("mssql", "flyecrstring", "exec dbo.searchallecrdata @ecrno,@model;", dbparamlist);
                    break;
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["品號"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public sDataModels GetCGrotoModels(userData userData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", userData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@isused", "1"));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "select department from web.siteber where newid = @newid and isused = @isused;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sDataModels() { status = "nodata" };
            }
            return new sDataModels() { value = mainRows.Rows[0]["department"].ToString().TrimEnd(), status = "istrue" };
        }

        public statusModels GetInsertModels(iSideData iSideData, string cuurip)
        {
            string checkItems = checkItemValue(iSideData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@inoper", iSideData.newid.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksupeber @inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            string number = $"FN{DateTime.Now.ToString("yyyyMM")}";
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@number", number));
            string endnumber = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchfinalinsideform @number;", dbparamlist).Rows[0]["endnumber"].ToString().TrimEnd(), formId = new sha256().new256("mssql", "flyfnstring"), othermail = "", workno = "", mblist = "";
            foreach (var item in iSideData.items)
            {
                foreach (var mailitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["mailitems"].ToString().TrimEnd()))
                {
                    switch (othermail.IndexOf(mailitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            othermail += $"{mailitem["mbValue"].ToString().TrimEnd()},";
                            break;
                    }
                }
                foreach (var workitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["workitems"].ToString().TrimEnd()))
                {
                    switch (workno.IndexOf(workitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            workno += $"{workitem["mbValue"].ToString().TrimEnd()}\n";
                            break;
                    }
                }
                foreach (var mbitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["mbitems"].ToString().TrimEnd()))
                {
                    switch (mblist.IndexOf(mbitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            mblist += $"{mbitem["mbValue"].ToString().TrimEnd()},";
                            break;
                    }
                }
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", formId));
                dbparamlist.Add(new dbparam("@postGroup", item["postGroup"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@postName", item["postName"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@number", number + endnumber));
                dbparamlist.Add(new dbparam("@version", "A"));
                dbparamlist.Add(new dbparam("@case", item["case"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepage1", item["homepage1"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@pnumber", item["pnumber"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@endDate", item["endDate"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", item["mb"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@amount", item["amount"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@othermail", othermail));
                dbparamlist.Add(new dbparam("@action1", item["action1"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@workno", workno));
                dbparamlist.Add(new dbparam("@action2", item["action2"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mblist", mblist));
                dbparamlist.Add(new dbparam("@oldno", item["oldno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@newno", item["newno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@sopno", item["sopno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@sipno", item["sipno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@action3", item["action3"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@action4", item["action4"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@action5", item["action5"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@ecrno", item["ecr"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@ecnno", item["ecn"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@enno", item["en"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@code", checkChangeCode(item["mbitems"].ToString().TrimEnd())));
                dbparamlist.Add(new dbparam("@snno", checkSnnoCode(item["snno"].ToString().TrimEnd())));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertinsideform @formId,@postGroup,@postName,@number,@version,@case,@homepage1,@pnumber,@endDate,@obj,@homepageMomo,@mb,@amount,@subject,@body,@othermail,@action1,@workno,@action2,@mblist,@oldno,@newno,@sopno,@sipno,@action3,@action4,@action5,@ecrno,@ecnno,@enno,@code;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            foreach (var item in iSideData.photoitems)
            {
                if (bool.Parse(item["photoInsert"].ToString().TrimEnd()) || !bool.Parse(item["photoDelete"].ToString().TrimEnd()))
                {
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@formId", formId));
                    dbparamlist.Add(new dbparam("@inoper", iSideData.newid.TrimEnd()));
                    dbparamlist.Add(new dbparam("@uploadPath", ""));
                    dbparamlist.Add(new dbparam("@imagePath", item["photoPath"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@original", item["photoOriginal"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@encryption", item["photoEncryption"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@extension", item["photoExtension"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(item["photoExtension"].ToString().TrimEnd())));
                    dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(database.connectionString("folderFiles"), $"{item["photoOriginal"].ToString().TrimEnd()}({item["photoEncryption"].ToString().TrimEnd()}){item["photoExtension"].ToString().TrimEnd()}")));
                    if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertinfileform @formId,@inoper,@uploadPath,@imagePath,@original,@encryption,@extension,@type,@capacity;", dbparamlist) != "istrue")
                    {
                        return new statusModels() { status = "error" };
                    }
                }
            }
            foreach (var item in iSideData.grotoitems)
            {
                if (bool.Parse(item["groupInsert"].ToString().TrimEnd()) || !bool.Parse(item["groupDelete"].ToString().TrimEnd()))
                {
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@formId", formId));
                    dbparamlist.Add(new dbparam("@inoper", iSideData.newid.TrimEnd()));
                    dbparamlist.Add(new dbparam("@name", item["grotoName"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@uploadPath", ""));
                    dbparamlist.Add(new dbparam("@imagePath", item["grotoPath"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@original", item["grotoOriginal"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@encryption", item["grotoEncryption"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@extension", item["grotoExtension"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(item["grotoExtension"].ToString().TrimEnd())));
                    dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(database.connectionString("folderFiles"), $"{item["grotoOriginal"].ToString().TrimEnd()}({item["grotoEncryption"].ToString().TrimEnd()}){item["grotoExtension"].ToString().TrimEnd()}")));
                    if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertinfileform @formId,@inoper,@name,@uploadPath,@imagePath,@original,@encryption,@extension,@type,@capacity;", dbparamlist) != "istrue")
                    {
                        return new statusModels() { status = "error" };
                    }
                }
            }
            string date = new datetime().sqldate("mssql", "flyfnstring"), time = new datetime().sqltime("mssql", "flyfnstring");
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@mAddrName", $"{othermail}{mainRows.Rows[0]["username"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
            dbparamlist.Add(new dbparam("@mSubject", $"「{mainRows.Rows[0]["username"].ToString().TrimEnd()}」建立工廠內部通告:{number}{endnumber}"));
            dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;text-align:center;'><div style='padding: 12px; border:2px solid white;'><div><h3 style='color: red;'>FN SYSTEM NEWS</h3></div><div> <hr /></div><div><h3 style='color: red;'>建立工廠內部通告需瞭解</h3></div><div style='font-size: 16px;'>{date} {time}</div><div><h4>請相關人員進行瞭解此問題．</h4></div><div><a style='background-color:red; color:white; padding:12px;' href='http://221.222.222.181:7250/modifyF#{formId}'>前往瞭解</a></div></div></div>"));
            database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist);
            return new statusModels() { status = "istrue" };
        }
        public string checkChangeCode(string items)
        {
            switch (JsonSerializer.Deserialize<List<Dictionary<string, object>>>(items).Count)
            {
                case 0:
                    return "";
            }
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@indate", new datetime().sqldate("mssql", "flyfnstring")));
            return new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchfinalcode @indate;", dbparamlist).Rows[0]["value"].ToString().TrimEnd();
        }

        public string checkSnnoCode(string snno)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@length", snno.Length));
            dbparamlist.Add(new dbparam("@value", snno.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "epaperstring", "exec web.searchsnnodata @length,@value;", dbparamlist);
            if (mainRows.Rows.Count > 0)
            {
                switch (mainRows.Rows[0]["status"].ToString().TrimEnd())
                {
                    case "only":
                        dbparamlist.Clear();
                        dbparamlist.Add(new dbparam("@snno", snno));
                        return database.checkSelectSql("mssql", "flyfnstring", "select snno from dbo.FN where snno = @snno;", dbparamlist).Rows.Count > 0 ? "" : snno;
                }
            }
            return "";
        }

        public statusModels GetSendModels(iSideData iSideData, string cuurip)
        {
            string checkItems = checkItemValue(iSideData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@inoper", iSideData.newid.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksupeber @inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            string number = $"FN{DateTime.Now.ToString("yyyyMM")}";
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@number", number));
            string endnumber = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchfinalinsideform @number;", dbparamlist).Rows[0]["endnumber"].ToString().TrimEnd(), formId = new sha256().new256("mssql", "flyfnstring"), othermail = "", workno = "", mblist = "";
            foreach (var item in iSideData.items)
            {
                foreach (var mailitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["mailitems"].ToString().TrimEnd()))
                {
                    switch (othermail.IndexOf(mailitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            othermail += $"{mailitem["mbValue"].ToString().TrimEnd()},";
                            break;
                    }
                }
                foreach (var workitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["workitems"].ToString().TrimEnd()))
                {
                    switch (workno.IndexOf(workitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            workno += $"{workitem["mbValue"].ToString().TrimEnd()}\n";
                            break;
                    }
                }
                foreach (var mbitem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["mbitems"].ToString().TrimEnd()))
                {
                    switch (mblist.IndexOf(mbitem["mbValue"].ToString().TrimEnd()))
                    {
                        case -1:
                            mblist += $"{mbitem["mbValue"].ToString().TrimEnd()},";
                            break;
                    }
                }
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", formId));
                dbparamlist.Add(new dbparam("@postGroup", item["postGroup"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@postName", item["postName"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@number", number + endnumber));
                dbparamlist.Add(new dbparam("@version", "A"));
                dbparamlist.Add(new dbparam("@case", item["case"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepage1", item["homepage1"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@pnumber", item["pnumber"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@endDate", item["endDate"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", item["mb"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@amount", item["amount"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@othermail", othermail));
                dbparamlist.Add(new dbparam("@action1", item["action1"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@workno", workno));
                dbparamlist.Add(new dbparam("@action2", item["action2"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mblist", mblist));
                dbparamlist.Add(new dbparam("@oldno", item["oldno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@newno", item["newno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@sopno", item["sopno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@sipno", item["sipno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@action3", item["action3"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@action4", item["action4"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@action5", item["action5"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@ecrno", item["ecr"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@ecnno", item["ecn"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@enno", item["en"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@code", checkChangeCode(item["mbitems"].ToString().TrimEnd())));
                dbparamlist.Add(new dbparam("@snno", checkSnnoCode(item["snno"].ToString().TrimEnd())));
                dbparamlist.Add(new dbparam("@signing", "1"));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertinsideform @formId,@postGroup,@postName,@number,@version,@case,@homepage1,@pnumber,@endDate,@obj,@homepageMomo,@mb,@amount,@subject,@body,@othermail,@action1,@workno,@action2,@mblist,@oldno,@newno,@sopno,@sipno,@action3,@action4,@action5,@ecrno,@ecnno,@enno,@code,@signing;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            foreach (var item in iSideData.photoitems)
            {
                if (bool.Parse(item["photoInsert"].ToString().TrimEnd()) || !bool.Parse(item["photoDelete"].ToString().TrimEnd()))
                {
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@formId", formId));
                    dbparamlist.Add(new dbparam("@inoper", iSideData.newid.TrimEnd()));
                    dbparamlist.Add(new dbparam("@uploadPath", ""));
                    dbparamlist.Add(new dbparam("@imagePath", item["photoPath"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@original", item["photoOriginal"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@encryption", item["photoEncryption"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@extension", item["photoExtension"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(item["photoExtension"].ToString().TrimEnd())));
                    dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(database.connectionString("folderFiles"), $"{item["photoOriginal"].ToString().TrimEnd()}({item["photoEncryption"].ToString().TrimEnd()}){item["photoExtension"].ToString().TrimEnd()}")));
                    if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertinfileform @formId,@inoper,@uploadPath,@imagePath,@original,@encryption,@extension,@type,@capacity;", dbparamlist) != "istrue")
                    {
                        return new statusModels() { status = "error" };
                    }
                }
            }
            foreach (var item in iSideData.grotoitems)
            {
                if (bool.Parse(item["groupInsert"].ToString().TrimEnd()) || !bool.Parse(item["groupDelete"].ToString().TrimEnd()))
                {
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@formId", formId));
                    dbparamlist.Add(new dbparam("@inoper", iSideData.newid.TrimEnd()));
                    dbparamlist.Add(new dbparam("@name", item["name"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@uploadPath", ""));
                    dbparamlist.Add(new dbparam("@imagePath", item["photoPath"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@original", item["photoOriginal"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@encryption", item["photoEncryption"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@extension", item["photoExtension"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(item["photoExtension"].ToString().TrimEnd())));
                    dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(database.connectionString("folderFiles"), $"{item["photoOriginal"].ToString().TrimEnd()}({item["photoEncryption"].ToString().TrimEnd()}){item["photoExtension"].ToString().TrimEnd()}")));
                    if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertinfileform @formId,@inoper,@name,@uploadPath,@imagePath,@original,@encryption,@extension,@type,@capacity;", dbparamlist) != "istrue")
                    {
                        return new statusModels() { status = "error" };
                    }
                }
            }
            string date = new datetime().sqldate("mssql", "flyfnstring"), time = new datetime().sqltime("mssql", "flyfnstring");
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@mAddrName", $"{othermail}{mainRows.Rows[0]["username"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
            dbparamlist.Add(new dbparam("@mSubject", $"「{mainRows.Rows[0]["username"].ToString().TrimEnd()}」建立工廠內部通告:{number}{endnumber}"));
            dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;text-align:center;'><div style='padding: 12px; border:2px solid white;'><div><h3 style='color: red;'>FN SYSTEM NEWS</h3></div><div> <hr /></div><div><h3 style='color: red;'>建立工廠內部通告需瞭解</h3></div><div style='font-size: 16px;'>{date} {time}</div><div><h4>請相關人員進行瞭解此問題．</h4></div><div><a style='background-color:red; color:white; padding:12px;' href='http://221.222.222.181:7250/modifyF#{formId}'>前往瞭解</a></div></div></div>"));
            database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist);
            dbparamlist.Clear();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.searchinsignlist;", dbparamlist).Rows)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", formId));
                dbparamlist.Add(new dbparam("@newid", dr["newid"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@inoper", iSideData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@value", $"「{mainRows.Rows[0]["username"].ToString().TrimEnd()}」建立工廠內部通告需簽核:{number}{endnumber}"));
                dbparamlist.Add(new dbparam("@link", $"/signlistF#{formId}"));
                database.checkActiveSql("mssql", "flyfnstring", "exec web.insertnoticeform @formId,@newid,@inoper,@value,@link;", dbparamlist);
            }
            return new statusModels() { status = "istrue" };
        }

        public string checkItemValue(List<Dictionary<string, object>> items)
        {
            foreach (var item in items)
            {
                switch (item["postGroup"].ToString().TrimEnd())
                {
                    case "":
                        return "提出部門尚未選擇";
                }
                switch (item["postName"].ToString().TrimEnd())
                {
                    case "":
                        return "提出者尚未選擇";
                }
                switch (item["case"].ToString().TrimEnd())
                {
                    case "":
                        return "變更內容尚未選擇";
                }
                switch (item["homepage1"].ToString().TrimEnd())
                {
                    case "":
                        return "客戶尚未填寫";
                }
                switch (item["pnumber"].ToString().TrimEnd())
                {
                    case "":
                        return "訂單號碼尚未填寫";
                }
                switch (item["endDate"].ToString().TrimEnd())
                {
                    case "":
                        return "文件有效期限尚未填寫";
                }
                switch (item["obj"].ToString().TrimEnd())
                {
                    case "":
                        return "影響站別尚未選擇";
                }
                switch (item["homepageMomo"].ToString().TrimEnd())
                {
                    case "":
                        return "機種尚未填寫";
                }
                switch (item["mb"].ToString().TrimEnd())
                {
                    case "":
                        return "M/B尚未填寫";
                }
                switch (item["amount"].ToString().TrimEnd())
                {
                    case "":
                        return "生產數量尚未填寫";
                }
                switch (item["subject"].ToString().TrimEnd())
                {
                    case "":
                        return "主旨尚未填寫";
                }
                switch (item["body"].ToString().TrimEnd())
                {
                    case "":
                        return "說明尚未填寫";
                }
                switch (JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["mailitems"].ToString().TrimEnd()).Count)
                {
                    case 0:
                        return "相關人員尚未填寫";
                }
            }
            return "";
        }

        public sDataModels GetDownloadModels(otherData otherData, string cuurip, string userAgent)
        {
            database database = new database();
            string file = $"{otherData.values.TrimEnd()}.pdf";
            switch (File.Exists($"{database.connectionString("ecrFiles")}{file}"))
            {
                case false:
                    return new sDataModels() { status = "nodata" };
            }
            datetime datetime = new datetime();
            string stdate = datetime.sqldate("mssql", "flyfnstring"), sttime = datetime.sqltime("mssql", "flyfnstring"), cuname = Dns.GetHostEntry(cuurip).HostName.IndexOf('.') == -1 ? Dns.GetHostEntry(cuurip).HostName : Dns.GetHostEntry(cuurip).HostName.Split('.')[0];
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", otherData.values.TrimEnd()));
            dbparamlist.Add(new dbparam("@files", otherData.values.TrimEnd()));
            dbparamlist.Add(new dbparam("@externip", cuurip));
            dbparamlist.Add(new dbparam("@hostname", cuname));
            dbparamlist.Add(new dbparam("@browser", new information().browser(userAgent)));
            dbparamlist.Add(new dbparam("@stdate", stdate));
            dbparamlist.Add(new dbparam("@sttime", sttime));
            dbparamlist.Add(new dbparam("@inoper", otherData.userid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertdownloadlog @formId,@files,@externip,@hostname,@browser,@stdate,@sttime,@inoper;", dbparamlist) != "istrue")
            {
                return new sDataModels() { status = "error" };
            }
            return new sDataModels() { value = $"{database.connectionString("ecrHttps")}{file}", status = "istrue" };
        }
    }
}