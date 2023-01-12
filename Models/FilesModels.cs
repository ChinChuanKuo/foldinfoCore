using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Net;
using FOLDINFOCore.App_Code;
using Spire.Doc;
using Spire.Pdf;
using Spire.Xls;
using Spire.Presentation;
using System.Text.RegularExpressions;

namespace FOLDINFOCore.Models
{
    public class FilesClass
    {
        public sSiteModels GetWebsiteModels(sRowsData sRowsData, string cuurip, string userAgent)
        {
            database database = new database();
            datetime datetime = new datetime();
            string stdate = datetime.sqldate("mssql", "flyfnstring"), sttime = datetime.sqltime("mssql", "flyfnstring"), original = "", encryption = new sha256().new256("mssql", "flyfnstring"), extension = ".jpg";
            new WebClient().DownloadFile(sRowsData.value.TrimEnd(), $"{database.connectionString("folderFiles")}{original}({encryption}){extension}");
            List<dbparam> dbparamlist = new List<dbparam>();
            string date = datetime.sqldate("mssql", "flyfnstring"), time = datetime.sqltime("mssql", "flyfnstring"), cuname = Dns.GetHostEntry(cuurip).HostName.IndexOf('.') == -1 ? Dns.GetHostEntry(cuurip).HostName : Dns.GetHostEntry(cuurip).HostName.Split('.')[0];
            dbparamlist.Add(new dbparam("@formId", sRowsData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@website", sRowsData.value.TrimEnd()));
            dbparamlist.Add(new dbparam("@externip", cuurip));
            dbparamlist.Add(new dbparam("@hostname", cuname));
            dbparamlist.Add(new dbparam("@browser", new information().browser(userAgent)));
            dbparamlist.Add(new dbparam("@stdate", stdate));
            dbparamlist.Add(new dbparam("@sttime", sttime));
            dbparamlist.Add(new dbparam("@eddate", date));
            dbparamlist.Add(new dbparam("@edtime", time));
            dbparamlist.Add(new dbparam("@indate", date));
            dbparamlist.Add(new dbparam("@intime", time));
            dbparamlist.Add(new dbparam("@inoper", sRowsData.newid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "insert into web.websitelog (formId,website,externip,hostname,browser,stdate,sttime,eddate,edtime,indate,intime,inoper) values (@formId,@website,@externip,@hostname,@browser,@stdate,@sttime,@eddate,@edtime,@indate,@intime,@inoper);", dbparamlist) != "istrue")
            {
                return new sSiteModels() { status = "error" };
            }
            switch (File.Exists($"{database.connectionString("folderFiles")}{original}({encryption}){extension}"))
            {
                case false:
                    return new sSiteModels() { status = "nodata" };
            }
            return new sSiteModels() { images = true, videos = false, audios = false, src = $"{original}({encryption}){extension}", imagePath = database.connectionString("folderHttps"), original = original, encryption = encryption, extension = extension, status = "istrue" };
        }

        public statusModels GetDownloadModels(sRowsData sRowsData, string cuurip, string userAgent)
        {
            database database = new database();
            datetime datetime = new datetime();
            string stdate = datetime.sqldate("mssql", "flyfnstring"), sttime = datetime.sqltime("mssql", "flyfnstring");
            switch (File.Exists(database.connectionString("folderFiles") + sRowsData.value.TrimEnd()))
            {
                case false:
                    return new statusModels() { status = "nodata" };
            }
            string date = datetime.sqldate("mssql", "flyfnstring"), time = datetime.sqltime("mssql", "flyfnstring"), cuname = Dns.GetHostEntry(cuurip).HostName.IndexOf('.') == -1 ? Dns.GetHostEntry(cuurip).HostName : Dns.GetHostEntry(cuurip).HostName.Split('.')[0];
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", sRowsData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@files", sRowsData.value.TrimEnd()));
            dbparamlist.Add(new dbparam("@externip", cuurip));
            dbparamlist.Add(new dbparam("@hostname", cuname));
            dbparamlist.Add(new dbparam("@browser", new information().browser(userAgent)));
            dbparamlist.Add(new dbparam("@stdate", stdate));
            dbparamlist.Add(new dbparam("@sttime", sttime));
            dbparamlist.Add(new dbparam("@eddate", date));
            dbparamlist.Add(new dbparam("@edtime", time));
            dbparamlist.Add(new dbparam("@indate", date));
            dbparamlist.Add(new dbparam("@intime", time));
            dbparamlist.Add(new dbparam("@inoper", sRowsData.newid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyfnstring", "insert into web.downloadlog (formId,files,externip,hostname,browser,stdate,sttime,eddate,edtime,indate,intime,inoper) values (@formId,@files,@externip,@hostname,@browser,@stdate,@sttime,@eddate,@edtime,@indate,@intime,@inoper);", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            return new statusModels() { status = "istrue" };
        }

        [System.Obsolete]
        public sSiteModels GetTransferModels(sFileData sFileData, string cuurip)
        {
            database database = new database();
            string foldPath = new database().connectionString("folderFiles"), encryption = new sha256().new256("mssql", "flyfnstring"), extension = "pdf";
            switch (File.Exists($"{foldPath}{sFileData.original.TrimEnd()}({sFileData.encryption.TrimEnd()}){sFileData.extension.TrimEnd()}"))
            {
                case false:
                    return new sSiteModels() { status = "nodata" };
            }
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@value", extension));
            dbparamlist.Add(new dbparam("@needed", "1"));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.uploadfileform @value,@needed;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sSiteModels() { status = "nodata" };
            }
            if (mainRows.Rows[0]["flImages"].ToString().TrimEnd() == "0" && mainRows.Rows[0]["flVideos"].ToString().TrimEnd() == "0" && mainRows.Rows[0]["flAudios"].ToString().TrimEnd() == "0")
            {
                return new sSiteModels() { status = "nodata" };
            }
            switch (transFileToPDF(sFileData.extension.TrimEnd(), $"{foldPath}{sFileData.original.TrimEnd()}({sFileData.encryption.TrimEnd()}){sFileData.extension.TrimEnd()}", $"{foldPath}{sFileData.original.TrimEnd()}({encryption}).{extension}"))
            {
                case false:
                    return new sSiteModels() { status = "nodata" };
            }
            return new sSiteModels() { images = mainRows.Rows[0]["flImages"].ToString().TrimEnd() == "1", videos = mainRows.Rows[0]["flVideos"].ToString().TrimEnd() == "1", audios = mainRows.Rows[0]["flAudios"].ToString().TrimEnd() == "1", src = mainRows.Rows[0]["flImages"].ToString().TrimEnd() == "1" && mainRows.Rows[0]["flShowed"].ToString().TrimEnd() == "0" ? $"{mainRows.Rows[0]["original"].ToString().TrimEnd()}({mainRows.Rows[0]["encryption"].ToString().TrimEnd()}){mainRows.Rows[0]["extension"].ToString().TrimEnd()}" : $"{sFileData.original.TrimEnd()}({encryption}).{extension}", imagePath = database.connectionString("folderHttps"), original = sFileData.original.TrimEnd(), encryption = encryption, extension = $".{extension}", date = new datetime().sqldate("mssql", "flyfnstring"), status = "istrue" };
        }

        [System.Obsolete]
        public bool transFileToPDF(string extension, string originalPath, string savePath)
        {
            switch (extension)
            {
                case ".xls":
                case ".xlsx":
                    return transExcelToPDF(originalPath, savePath);
                case ".doc":
                case ".docx":
                    return transWordToPDF(originalPath, savePath);
                case ".ppt":
                case ".pptx":
                    return transPowerPointToPDF(originalPath, savePath);
                case ".xps":
                    return transXpsToPDF(originalPath, savePath);
            }
            return false;
        }

        public bool transExcelToPDF(string originalPath, string savePath)
        {
            Workbook workbook = new Workbook();
            workbook.LoadFromFile(originalPath, ExcelVersion.Version2010);
            workbook.SaveToFile(savePath, Spire.Xls.FileFormat.PDF);
            return File.Exists(savePath);
        }

        public bool transWordToPDF(string originalPath, string savePath)
        {
            Document document = new Document();
            document.LoadFromFile(originalPath);
            document.SaveToFile(savePath, Spire.Doc.FileFormat.PDF);
            return File.Exists(savePath);
        }

        public bool transPowerPointToPDF(string originalPath, string savePath)
        {
            Presentation presentation = new Presentation();
            presentation.LoadFromFile(originalPath);
            presentation.SaveToFile(savePath, Spire.Presentation.FileFormat.PDF);
            return File.Exists(savePath);
        }

        [System.Obsolete]
        public bool transXpsToPDF(string originalPath, string savePath)
        {
            PdfDocument document = new PdfDocument();
            document.UseHighQualityImage = true;
            document.LoadFromFile(originalPath, Spire.Pdf.FileFormat.XPS);
            document.SaveToFile(savePath, Spire.Pdf.FileFormat.PDF);
            return File.Exists(savePath);
        }

        public sDataModels GetTotalModels(sFileData sFileData, string cuurip)
        {
            string filePath = $"{new database().connectionString("folderFiles")}{sFileData.original.TrimEnd()}({sFileData.encryption.TrimEnd()}){sFileData.extension.TrimEnd()}";
            switch (File.Exists(filePath))
            {
                case false:
                    return new sDataModels() { status = "nodata" };
            }
            int final = 0;
            using (FileStream fileStream = new FileStream(filePath, FileMode.Open, FileAccess.Read))
            {
                final = new Regex(@"/Type\s*/Page[^s]").Matches(new StreamReader(fileStream).ReadToEnd()).Count;
            }
            return new sDataModels() { value = final.ToString().TrimEnd(), status = "istrue" };
        }

        public sDataModels GetRemoveModels(rFileData rFileData, string cuurip)
        {
            string filePath = $"{new database().connectionString("folderFiles")}{rFileData.original.TrimEnd()}({rFileData.encryption.TrimEnd()}){rFileData.extension.TrimEnd()}";
            switch (File.Exists(filePath))
            {
                case false:
                    return new sDataModels() { status = "nodata" };
            }
            int final = 0;
            using (FileStream fileStream = new FileStream(filePath, FileMode.Open, FileAccess.Read))
            {
                final = new Regex(@"/Type\s*/Page[^s]").Matches(new StreamReader(fileStream).ReadToEnd()).Count;
            }
            PdfDocument document = new PdfDocument();
            document.LoadFromFile(filePath);
            int reFinal = final - int.Parse(rFileData.final.TrimEnd()) - 1, reFirst = int.Parse(rFileData.first.TrimEnd()) - 1, total = reFinal - reFirst;
            while (reFinal >= 0)
            {
                document.Pages.RemoveAt(reFinal);
                reFinal--;
            }
            while (reFirst >= 0)
            {
                document.Pages.RemoveAt(reFirst);
                reFirst--;
            }
            document.SaveToFile(filePath, Spire.Pdf.FileFormat.PDF);
            return new sDataModels() { value = total.ToString().TrimEnd(), status = "istrue" };
        }

        public bool transPdfToImage(string originalPath, string savePath, string name, string extension)
        {
            ImageFormat imageFormat = extension == "jpg" ? ImageFormat.Jpeg : ImageFormat.Png;
            PdfDocument doc = new PdfDocument();
            doc.LoadFromFile(originalPath);
            for (int i = 0; i < doc.Pages.Count; i++)
            {
                Image bmp = new Bitmap(doc.SaveAsImage(i));
                bmp.Save($"{savePath}{name}_{i}.{extension}", imageFormat);
            }
            return true;
        }

        public string GetFileType(string extension)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@value", extension.Replace(".", "").ToLower()));
            dbparamlist.Add(new dbparam("@needed", "1"));
            mainRows = new database().checkSelectSql("mssql", "flyfnstring", "exec web.searchfiletype @value,@needed;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return "OTHER";
            }
            return mainRows.Rows[0]["flTitle"].ToString().TrimEnd();
        }

        public long GetFileCapacity(string filePath, string filename)
        {
            return new System.IO.FileInfo(filePath + filename).Length;
        }
    }
}