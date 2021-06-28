using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Net;
using foldinfoCore.App_Code;

namespace foldinfoCore.Models
{
    public class CreateRClass
    {
        public sItemModels GetSearchModels(userData userData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            string[] floorArray = new string[] { "NA", "1F", "2F", "3F", "4F", "5F", "6F" };
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
            string[] objArray = new string[] { "NA", "製造", "IQC", "DOA", "RMA", "銷退", "SMT", "DIP", "板測", "加工", "組裝", "PreTest", "PostTest", "系測", "包裝", "週邊", "QA校驗", "IPQC", "OQC", "其他", "客驗", "客訴" };
            List<Dictionary<string, object>> objitems = new List<Dictionary<string, object>>();
            foreach (var obj in objArray)
            {
                objitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", obj } });
            }
            dbparamlist.Clear();
            List<Dictionary<string, object>> groupitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyfnstring", "exec web.searchallgroupform;", dbparamlist).Rows)
            {
                groupitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["department"].ToString().TrimEnd() } });
            }
            string[] issueArray = new string[] { "NA", "材料", "設計", "製程", "缺料", "流程", "業務" };
            List<Dictionary<string, object>> issueitems = new List<Dictionary<string, object>>();
            foreach (var issue in issueArray)
            {
                issueitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", issue } });
            }
            string[] belongArray = new string[] { "", "CS", "DCC", "MIS", "PCC", "PM", "PE", "QC", "RD", "生管", "其他", "倉管", "採購", "設備廠商", "新產品", "業務", "資材", "製造", "製造_包裝", "製造_板卡", "製造_組裝", "製造_測試", "廠商" };
            List<Dictionary<string, object>> belongitems = new List<Dictionary<string, object>>();
            foreach (var belong in belongArray)
            {
                belongitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", belong } });
            }
            string[] stageArray = new string[] { "", "不處理", "原因確認", "現況掌握", "對策發行", "暫時對策", "結案" };
            List<Dictionary<string, object>> stageitems = new List<Dictionary<string, object>>();
            foreach (var stage in stageArray)
            {
                stageitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", stage } });
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "showFloorMenu", false }, { "flooritems", flooritems.ToArray() }, { "floor", "" }, { "workno", "" }, { "showXps", false }, { "homepage1", "" }, { "pnumber", "" }, { "showMomoMenu", false }, { "momoitems", momoitems.ToArray() }, { "homepageMomo", "" }, { "showMbMenu", false }, { "mbitems", mbitems.ToArray() }, { "mb", "" }, { "showObjMenu", false }, { "objitems", objitems.ToArray() }, { "obj", "" }, { "pn", "" }, { "showPnMenu", false }, { "pnitems", new List<Dictionary<string, object>>().ToArray() }, { "invest", "0" }, { "amount", "0" }, { "fail", "0" }, { "subject", "" }, { "containment", "" }, { "cause", "" }, { "showRegroupMenu", false }, { "regroupitems", groupitems.ToArray() }, { "reGroup", "" }, { "showReplierMenu", false }, { "replieritems", new List<Dictionary<string, object>>().ToArray() }, { "replier", "" }, { "showIssueMenu", false }, { "issueitems", issueitems.ToArray() }, { "issuesort", "" }, { "showCauseMenu", false }, { "causeitems", new List<Dictionary<string, object>>().ToArray() }, { "causeclass", "" }, { "directPt", "" }, { "indirectPt", "" }, { "correctiveaction1", "" }, { "correctiveaction2", "" }, { "showFile", false }, { "showImage", false }, { "showVideo", false }, { "showAudio", false }, { "src", "" }, { "path", "" }, { "original", "" }, { "encryption", "" }, { "extension", "" }, { "date", "" }, { "closure", "" }, { "body", "" }, { "notice", false }, { "nonstatistical", false }, { "showBelongMenu", false }, { "belongitems", belongitems.ToArray() }, { "belong", "" }, { "belonger", "" }, { "showStageMenu", false }, { "stageitems", stageitems.ToArray() }, { "stage", "" }, { "formWork", false } });
            return new sItemModels() { items = items, status = "istrue" };
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

        public sOptonModels GetSWorknoModels(otherData otherData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            string workno = otherData.values.TrimEnd().ToUpper();
            dbparamlist.Add(new dbparam("@value", workno));
            mainRows = database.checkSelectSql("mssql", "flycsastring", "exec dbo.checkworknoform @value;", dbparamlist);
            List<Dictionary<string, object>> momoitems = new List<Dictionary<string, object>>(), mbitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flycsastring", "exec dbo.searchmodelform @value;", dbparamlist).Rows)
            {
                momoitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            string mb = mainRows.Rows[0]["firmb"].ToString().TrimEnd() == "" || mainRows.Rows[0]["firmb"].ToString().TrimEnd() == "NA" ? mainRows.Rows[0]["secmb"].ToString().TrimEnd() : mainRows.Rows[0]["firmb"].ToString().TrimEnd();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flycsastring", "exec dbo.searchmbform @value;", dbparamlist).Rows)
            {
                mbitems.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "workno", workno.Length > 10 ? workno.Substring(0, 10) : workno }, { "showxps", int.Parse(database.checkSelectSql("mssql", "flycsastring", "exec dbo.countwkpaperform @value;", dbparamlist).Rows[0]["itemCount"].ToString().TrimEnd()) > 0 }, { "custname", mainRows.Rows[0]["custname"].ToString().TrimEnd() }, { "pnumber", mainRows.Rows[0]["pnumber"].ToString().TrimEnd() }, { "mbname", mainRows.Rows[0]["mbname"].ToString().TrimEnd() }, { "momoitems", momoitems }, { "mb", mb }, { "mbitems", mbitems }, { "amount", mainRows.Rows[0]["amount"].ToString().TrimEnd().Contains('.') ? mainRows.Rows[0]["amount"].ToString().TrimEnd().Substring(0, mainRows.Rows[0]["amount"].ToString().TrimEnd().IndexOf('.')) : mainRows.Rows[0]["amount"].ToString().TrimEnd() } });
            return new sOptonModels() { items = items };
        }

        [Obsolete]
        public sRowsModels GetSXpsModels(otherData otherData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@original", otherData.values.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchrexpsform @original;", dbparamlist);
            if (mainRows.Rows.Count > 0)
            {
                items.Add(new Dictionary<string, object>() { { "filePath", mainRows.Rows[0]["imagePath"].ToString().TrimEnd() }, { "fileSrc", $"{mainRows.Rows[0]["original"].ToString().TrimEnd()}({mainRows.Rows[0]["encryption"].ToString().TrimEnd()}){mainRows.Rows[0]["extension"].ToString().TrimEnd()}" } });
                return new sRowsModels() { formId = otherData.values.TrimEnd(), tile = otherData.values.TrimEnd(), items = items, status = "istrue" };
            }
            string savePath = $"{database.connectionString("dispatchFiles")}{otherData.values.TrimEnd().Substring(1, 4)}\\{otherData.values.TrimEnd()}\\", originalPath = $"{database.connectionString("dispatchFiles")}{otherData.values.TrimEnd().Substring(1, 4)}\\", httpPath = $"{database.connectionString("dispatchHttps")}{otherData.values.TrimEnd().Substring(1, 4)}/{otherData.values.TrimEnd()}/", encryption = new sha256().new256("mssql", "flyfnstring");
            Directory.CreateDirectory(savePath);
            switch (new FilesClass().transFileToPDF(".xps", $"{originalPath}{otherData.values.TrimEnd()}.xps", $"{savePath}{otherData.values.TrimEnd()}({encryption}).pdf"))
            {
                case false:
                    return new sRowsModels() { status = "error" };
            }
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@original", otherData.values.TrimEnd()));
            dbparamlist.Add(new dbparam("@uploadPath", originalPath));
            dbparamlist.Add(new dbparam("@imagePath", httpPath));
            dbparamlist.Add(new dbparam("@encryption", encryption));
            dbparamlist.Add(new dbparam("@extension", ".pdf"));
            dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(".pdf")));
            dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(savePath, $"{otherData.values.TrimEnd()}({encryption}).pdf")));
            dbparamlist.Add(new dbparam("@inoper", otherData.userid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertrexpsform @original,@uploadPath,@imagePath,@encryption,@extension,@type,@capacity,@inoper;", dbparamlist) != "istrue")
            {
                return new sRowsModels() { status = "error" };
            }
            items.Add(new Dictionary<string, object>() { { "filePath", httpPath }, { "fileSrc", $"{otherData.values.TrimEnd()}({encryption}).pdf" } });
            return new sRowsModels() { formId = otherData.values.TrimEnd(), tile = otherData.values.TrimEnd(), items = items, status = "istrue" };
        }

        public sOptonModels GetSPnModels(sRowsData sRowsData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@workno", sRowsData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@length", sRowsData.value.Length));
            dbparamlist.Add(new dbparam("@pn", sRowsData.value.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flycsastring", "exec dbo.searchpndeta @workno,@length,@pn;", dbparamlist).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", dr["品號"].ToString().TrimEnd() } });
            }

            return new sOptonModels() { items = items };
        }

        public sOptonModels GetSIssueModels(otherData otherData, string cuurip)
        {
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            var causeArray = new List<Dictionary<string, string[]>>();
            causeArray.Add(new Dictionary<string, string[]>() { { "NA", new string[] { "NA" } }, { "材料", new string[] { "尺寸不符", "包裝不良", "外觀不良", "外觀異常", "色差", "來料不良", "品保覆判OK", "客供料", "規格不符", "圖面錯誤" } }, { "設計", new string[] { "BOM錯誤", "Gerber錯誤", "Limitation", "材料規格不符", "系統相容性", "組裝異常", "設計不良", "測試異常", "新產品", "圖面錯誤" } }, { "製程", new string[] { "BIOS/EC燒錄異常", "BOM燒錯", "DMI燒錄異常", "FN內容錯誤", "SFIS異常", "SOP疏漏", "未依SOP作業", "未執行FN", "未執行客需SOP", "作業疏失", "治工具異常", "品保覆測OK", "重工不良", "重測/重組OK", "組裝異常", "測試異常", "新產品", "零件上錯件", "管控疏失", "設備異常" } }, { "缺料", new string[] { "客供料正常", "急單", "採購作業疏失", "設計變更", "發料疏失", "進料異常", "廠商延遲交貨" } }, { "流程", new string[] { "FN未連結工單", "FN連結錯誤", "工單內容填寫錯誤", "作業疏失", "客驗客訴", "訂單規則變更", "排程異常", "排程變更", "增減料錯誤", "銷退驗退", "聯絡單重工" } }, { "業務", new string[] { "工單內容填寫錯誤", "作業疏失", "客供OS異常", "訂單規格變更", "規格單勾錯" } } });
            foreach (var cause in causeArray[0][otherData.values.TrimEnd()])
            {
                items.Add(new Dictionary<string, object>() { { "optionPadding", false }, { "value", cause } });
            }
            return new sOptonModels() { items = items };
        }

        public statusModels GetInsertModels(iIconData iIconData, string cuurip)
        {
            string checkItems = checkItemValue(iIconData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            database database = new database();
            DataTable finalRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            string formId = new sha256().new256("mssql", "flyfnstring"), number = $"QM{DateTime.Now.ToString("yyyyMM")}", endnumber = "001";
            dbparamlist.Add(new dbparam("@number", number));
            finalRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchfinalreportform @number;", dbparamlist);
            if (finalRows.Rows.Count > 0)
            {
                endnumber = (int.Parse(finalRows.Rows[0]["endnumber"].ToString().TrimEnd()) + 1).ToString().TrimEnd().PadLeft(3, '0');
            }
            dbparamlist.Clear();
            DataTable userRows = new DataTable();
            dbparamlist.Add(new dbparam("@newid", iIconData.newid.TrimEnd()));
            userRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksiteberform @newid;", dbparamlist);
            string[] versionArray = new string[] { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
            foreach (var item in iIconData.items)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@workno", item["workno"].ToString().TrimEnd()));
                int count = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.searchcountversion @workno;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd());
                if (count > 0) { count -= 1; }
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", formId));
                dbparamlist.Add(new dbparam("@postGroup", userRows.Rows[0]["department"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@postName", userRows.Rows[0]["username"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@floor", item["floor"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@number", number + endnumber));
                dbparamlist.Add(new dbparam("@version", versionArray[count].TrimEnd()));
                dbparamlist.Add(new dbparam("@homepage1", item["homepage1"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@pnumber", item["pnumber"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", item["mb"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@workno", item["workno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@pn", item["pn"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@amount", item["amount"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@invest", item["invest"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@fail", item["fail"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@failure", Math.Round(float.Parse(item["fail"].ToString().TrimEnd()) / float.Parse(item["invest"].ToString().TrimEnd()), 2, MidpointRounding.AwayFromZero)));
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@containment", item["containment"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@cause", item["cause"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@replier", item["replier"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@issuesort", item["issuesort"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepage3", item["src"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@causeclass", item["causeclass"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@directPt", item["directPt"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@indirectPt", item["indirectPt"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@correctiveaction1", item["correctiveaction1"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@correctiveaction2", item["correctiveaction2"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@closure", item["closure"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@notice", ""));
                dbparamlist.Add(new dbparam("@nonstatistical", ""));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@belong", item["belong"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@belonger", item["belonger"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@stage", item["stage"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@signing", "0"));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertreportform @formId,@postGroup,@postName,@floor,@number,@version,@homepage1,@pnumber,@homepageMomo,@mb,@obj,@workno,@pn,@amount,@invest,@fail,@failure,@subject,@containment,@cause,@replier,@issuesort,@homepage3,@causeclass,@directPt,@indirectPt,@correctiveaction1,@correctiveaction2,@closure,@notice,@nonstatistical,@body,@belong,@belonger,@stage,@signing;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            foreach (var item in iIconData.qaitems)
            {
                if (bool.Parse(item["photoInsert"].ToString().TrimEnd()) || !bool.Parse(item["photoDelete"].ToString().TrimEnd()))
                {
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@formId", formId));
                    dbparamlist.Add(new dbparam("@inoper", iIconData.newid.TrimEnd()));
                    dbparamlist.Add(new dbparam("@uploadPath", ""));
                    dbparamlist.Add(new dbparam("@imagePath", item["photoPath"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@original", item["photoOriginal"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@encryption", item["photoEncryption"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@extension", item["photoExtension"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(item["photoExtension"].ToString().TrimEnd())));
                    dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(database.connectionString("folderFiles"), $"{item["photoOriginal"].ToString().TrimEnd()}({item["photoEncryption"].ToString().TrimEnd()}){item["photoExtension"].ToString().TrimEnd()}")));
                    if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertrefileform @formId,@inoper,@uploadPath,@imagePath,@original,@encryption,@extension,@type,@capacity;", dbparamlist) != "istrue")
                    {
                        return new statusModels() { status = "error" };
                    }
                }
            }
            return new statusModels() { status = "istrue" };
        }

        public statusModels GetSendModels(iIconData iIconData, string cuurip)
        {
            string checkItems = checkItemValue(iIconData.items);
            if (checkItems != "")
            {
                return new statusModels() { status = checkItems };
            }
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            DataTable finalRows = new DataTable();
            string formId = new sha256().new256("mssql", "flyfnstring"), number = $"QM{DateTime.Now.ToString("yyyyMM")}", endnumber = "001";
            dbparamlist.Add(new dbparam("@number", number));
            finalRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.searchfinalreportform @number;", dbparamlist);
            if (finalRows.Rows.Count > 0)
            {
                endnumber = (int.Parse(finalRows.Rows[0]["endnumber"].ToString().TrimEnd()) + 1).ToString().TrimEnd().PadLeft(3, '0');
            }
            int count = 0;
            dbparamlist.Clear();
            DataTable userRows = new DataTable();
            dbparamlist.Add(new dbparam("@newid", iIconData.newid.TrimEnd()));
            userRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksiteberform @newid;", dbparamlist);
            string[] versionArray = new string[] { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
            foreach (var item in iIconData.items)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@workno", item["workno"].ToString().TrimEnd()));
                count = int.Parse(database.checkSelectSql("mssql", "flyfnstring", "exec web.searchcountversion @workno;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd());
                if (count > 0) { count -= 1; }
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", formId));
                dbparamlist.Add(new dbparam("@postGroup", userRows.Rows[0]["department"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@postName", userRows.Rows[0]["username"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@floor", item["floor"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@number", number + endnumber));
                dbparamlist.Add(new dbparam("@version", versionArray[count].TrimEnd()));
                dbparamlist.Add(new dbparam("@homepage1", item["homepage1"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@pnumber", item["pnumber"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepageMomo", item["homepageMomo"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@mb", item["mb"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@obj", item["obj"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@workno", item["workno"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@pn", item["pn"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@amount", item["amount"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@invest", item["invest"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@fail", item["fail"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@failure", Math.Round(float.Parse(item["fail"].ToString().TrimEnd()) / float.Parse(item["invest"].ToString().TrimEnd()), 2, MidpointRounding.AwayFromZero)));
                dbparamlist.Add(new dbparam("@subject", item["subject"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@containment", item["containment"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@cause", item["cause"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@replier", item["replier"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@issuesort", item["issuesort"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@homepage3", item["src"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@causeclass", item["causeclass"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@directPt", item["directPt"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@indirectPt", item["indirectPt"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@correctiveaction1", item["correctiveaction1"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@correctiveaction2", item["correctiveaction2"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@closure", item["closure"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@notice", ""));
                dbparamlist.Add(new dbparam("@nonstatistical", ""));
                dbparamlist.Add(new dbparam("@body", item["body"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@belong", item["belong"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@belonger", item["belonger"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@stage", item["stage"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@signing", "1"));
                if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertreportform @formId,@postGroup,@postName,@floor,@number,@version,@homepage1,@pnumber,@homepageMomo,@mb,@obj,@workno,@pn,@amount,@invest,@fail,@failure,@subject,@containment,@cause,@replier,@issuesort,@homepage3,@causeclass,@directPt,@indirectPt,@correctiveaction1,@correctiveaction2,@closure,@notice,@nonstatistical,@body,@belong,@belonger,@stage,@signing;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            foreach (var item in iIconData.qaitems)
            {
                if (bool.Parse(item["photoInsert"].ToString().TrimEnd()) || !bool.Parse(item["photoDelete"].ToString().TrimEnd()))
                {
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@formId", formId));
                    dbparamlist.Add(new dbparam("@inoper", iIconData.newid.TrimEnd()));
                    dbparamlist.Add(new dbparam("@uploadPath", ""));
                    dbparamlist.Add(new dbparam("@imagePath", item["photoPath"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@original", item["photoOriginal"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@encryption", item["photoEncryption"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@extension", item["photoExtension"].ToString().TrimEnd()));
                    dbparamlist.Add(new dbparam("@type", new FilesClass().GetFileType(item["photoExtension"].ToString().TrimEnd())));
                    dbparamlist.Add(new dbparam("@capacity", new FilesClass().GetFileCapacity(database.connectionString("folderFiles"), $"{item["photoOriginal"].ToString().TrimEnd()}({item["photoEncryption"].ToString().TrimEnd()}){item["photoExtension"].ToString().TrimEnd()}")));
                    if (database.checkActiveSql("mssql", "flyfnstring", "exec web.insertrefileform @formId,@inoper,@uploadPath,@imagePath,@original,@encryption,@extension,@type,@capacity;", dbparamlist) != "istrue")
                    {
                        return new statusModels() { status = "error" };
                    }
                }
            }
            dbparamlist.Clear();
            DataTable supeRows = new DataTable();
            dbparamlist.Add(new dbparam("@inoper", iIconData.newid.TrimEnd()));
            supeRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.checksupeber @inoper;", dbparamlist);
            dbparamlist.Add(new dbparam("@formId", formId));
            dbparamlist.Add(new dbparam("@newid", supeRows.Rows[0]["superid"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@value", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」建立品異單需簽核:{number}{endnumber}-{versionArray[count].TrimEnd()}"));
            dbparamlist.Add(new dbparam("@link", $"/signlistR#{formId}"));
            database.checkActiveSql("mssql", "flyfnstring", "exec web.insertnoticeform @formId,@newid,@inoper,@value,@link;", dbparamlist);
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@mAddrName", $"郭晉全,{supeRows.Rows[0]["supername"].ToString().TrimEnd()},{supeRows.Rows[0]["username"].ToString().TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mAddrBCCName", "郭晉全"));
            dbparamlist.Add(new dbparam("@mSubject", $"「{supeRows.Rows[0]["username"].ToString().TrimEnd()}」建立品異單需簽核:{number}{endnumber}-{versionArray[count].TrimEnd()}"));
            dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;text-align:center;'><div style='padding: 12px; border:2px solid white;'><div><h3 style='color: red;'>5C REPORT SYSTEM NEWS</h3></div><div> <hr /></div><div><h3 style='color: red;'>建立品異單需簽核</h3></div><div style='font-size: 16px;'>{new datetime().sqldate("mssql", "flyfnstring")} {new datetime().sqltime("mssql", "flyfnstring")}</div><div><h4>請相關主管進行簽核或退簽此問題．</h4></div><div><h4>http://221.222.222.181:7250/signlistR#{formId} => 請複製此連結</h4></div></div></div>"));
            //dbparamlist.Add(new dbparam("@mBody", $"<div style='width: 300px;margin: 0 auto;'><div style='padding: 12px; border:2px solid white;'><div><h3 style='color: red;'>5C REPORT SYSTEM NEWS</h3></div><div> <hr /></div><div><h3 style='color: red;'>建立品異單需簽核</h3></div><div style='font-size: 16px;'>{new datetime().sqldate("mssql", "flyfnstring")} {new datetime().sqltime("mssql", "flyfnstring")}</div><div><h4>請相關主管進行簽核或退簽此問題．</h4></div><div><a style='background-color:red; color:white; padding:12px;' href='http://221.222.222.181:7250/signlistR#{formId}'>前往簽核</a></div></div></div>"));
            database.checkActiveSql("mssql", "mailstring", "insert into dbo.MailBox (mAddrName,mAddrBCCName,mSubject,mBody) values (@mAddrName,@mAddrBCCName,@mSubject,@mBody);", dbparamlist);
            return new statusModels() { status = "istrue" };
        }

        public string checkItemValue(List<Dictionary<string, object>> items)
        {
            foreach (var item in items)
            {
                switch (item["floor"].ToString().TrimEnd())
                {
                    case "":
                        return "生產樓層尚未選擇";
                }
                switch (item["workno"].ToString().TrimEnd())
                {
                    case "":
                        return "工單尚未填寫";
                }
                switch (item["homepage1"].ToString().TrimEnd())
                {
                    case "":
                        return "客戶/廠商尚未填寫";
                }
                switch (item["pnumber"].ToString().TrimEnd())
                {
                    case "":
                        return "產品規格單尚未填寫";
                }
                switch (item["homepageMomo"].ToString().TrimEnd())
                {
                    case "":
                        return "機種尚未選擇";
                }
                switch (item["mb"].ToString().TrimEnd())
                {
                    case "":
                        return "M/B尚未選擇";
                }
                switch (item["obj"].ToString().TrimEnd())
                {
                    case "":
                        return "品異來源尚未選擇";
                }
                switch (item["pn"].ToString().TrimEnd())
                {
                    case "":
                        return "不良料號尚未填寫";
                }
                switch (item["invest"].ToString().TrimEnd())
                {
                    case "":
                        return "工單總數尚未填寫";
                }
                switch (item["amount"].ToString().TrimEnd())
                {
                    case "":
                        return "投入數尚未填寫";
                }
                switch (item["fail"].ToString().TrimEnd())
                {
                    case "":
                        return "不良數量尚未填寫";
                }
                switch (item["subject"].ToString().TrimEnd())
                {
                    case "":
                        return "異常內容尚未填寫";
                }
                switch (item["directPt"].ToString().TrimEnd())
                {
                    case "":
                        return "直接損耗工時尚未填寫";
                }
                switch (item["reGroup"].ToString().TrimEnd())
                {
                    case "":
                        return "處理部門尚未填寫";
                }
                switch (item["replier"].ToString().TrimEnd())
                {
                    case "":
                        return "處理者尚未填寫";
                }
                switch (item["src"].ToString().TrimEnd())
                {
                    case "":
                        return "檔案尚未上傳";
                }
            }
            return "";
        }

        public sDataModels GetDownloadModels(otherData otherData, string cuurip, string userAgent)
        {
            database database = new database();
            string file = $"{otherData.values.TrimEnd().Substring(1, 4)}\\{otherData.values.TrimEnd()}.xps";
            switch (File.Exists($"{database.connectionString("dispatchFiles")}{file}"))
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
            return new sDataModels() { value = $"{database.connectionString("dispatchHttps")}{file}", status = "istrue" };
        }
    }
}