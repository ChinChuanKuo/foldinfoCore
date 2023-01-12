using System.Net;
using System.Collections.Generic;

namespace FOLDINFOCore.App_Code
{
    public class computer
    {
        public string sqlclient(string dataname, string clientip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            switch (dataname)
            {
                case "mssql":
                    return Dns.GetHostEntry(clientip).HostName.IndexOf('.') == -1 ? Dns.GetHostEntry(clientip).HostName : Dns.GetHostEntry(clientip).HostName.Split('.')[0];
                //return database.selectMsSql( database.connectionString( sqlstring ), "select host_name();", dbparamlist ).Rows[0][0].ToString().TrimEnd();
                case "postgresql":
                    return null;
                default:
                    return null;
            }
        }
    }
}