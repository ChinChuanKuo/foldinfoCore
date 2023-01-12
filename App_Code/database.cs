using System;
using Npgsql;
using System.Data;
using MongoDB.Driver;
using System.Data.SqlClient;
using System.Collections.Generic;
using Microsoft.Extensions.Configuration;
using System.Runtime.InteropServices;

namespace FOLDINFOCore.App_Code
{
    public class database
    {
        public string connectionString(string sqlstring)
        {
            //C:/
            ///users/chinchuankuo/documents/
            var configurationBuilder = new ConfigurationBuilder().SetBasePath(connectionSystem()).AddJsonFile("connection.json");
            IConfiguration config = configurationBuilder.Build();
            return config["connectionStrings:" + sqlstring];
        }
        public string connectionSystem()
        {
            switch (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
            {
                case true:
                    return "";
            }
            switch (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
            {
                case true:
                    return "/users/chinchuankuo/documents/";
            }
            return "C:/";
        }
        public DataTable checkSelectSql(string dataname, string sqlstring, string sqlcode, List<dbparam> dbparamlist)
        {
            switch (dataname)
            {
                case "mssql":
                    return selectMsSql(connectionString(sqlstring), sqlcode, dbparamlist);
                case "postgresql":
                    ;
                    return selectPostgreSql(connectionString(sqlstring), sqlcode, dbparamlist);
                default:
                    return null;
            }
        }
        public DataTable selectMsSql(string sqlstring, string sqlcode, List<dbparam> dbparamlist)
        {
            //var configurationBuilder = new ConfigurationBuilder().SetBasePath(Directory.GetCurrentDirectory()).AddJsonFile("appsettings.json",optional:true);
            DataTable dt = new DataTable();
            using (SqlConnection conn = new SqlConnection(sqlstring))
            {
                conn.Open();
                SqlTransaction tran = conn.BeginTransaction();
                try
                {
                    using (SqlDataAdapter adpater = new SqlDataAdapter())
                    {
                        SqlCommand sqlcmd = new SqlCommand(sqlcode, conn, tran);
                        foreach (dbparam dbparam in dbparamlist)
                        {
                            sqlcmd.Parameters.AddWithValue(dbparam.key, dbparam.value);
                        }
                        sqlcmd.ExecuteNonQuery();
                        adpater.SelectCommand = sqlcmd;
                        adpater.Fill(dt);
                        tran.Commit();
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine("error:" + ex.ToString().TrimEnd());
                    Console.WriteLine(sqlcode);
                    tran.Rollback();
                }
            }
            return dt;
        }

        public DataTable selectPostgreSql(string sqlstring, string sqlcode, List<dbparam> dbparamlist)
        {
            DataTable dt = new DataTable();
            using (NpgsqlConnection conn = new NpgsqlConnection(sqlstring))
            {
                conn.Open();
                NpgsqlTransaction tran = conn.BeginTransaction();
                try
                {
                    using (NpgsqlDataAdapter adpater = new NpgsqlDataAdapter())
                    {
                        NpgsqlCommand sqlcmd = new NpgsqlCommand(sqlcode, conn, tran);
                        foreach (dbparam dbparam in dbparamlist)
                        {
                            sqlcmd.Parameters.AddWithValue(dbparam.key, dbparam.value);
                        }
                        sqlcmd.ExecuteNonQuery();
                        adpater.SelectCommand = sqlcmd;
                        adpater.Fill(dt);
                        tran.Commit();
                    }
                }
                catch (Exception ex)
                {
                    tran.Rollback();
                }
            }
            return dt;
        }

        public string checkActiveSql(string dataname, string sqlstring, string sqlcode, List<dbparam> dbparamlist)
        {
            switch (dataname)
            {
                case "mssql":
                    return activeMsSql(connectionString(sqlstring), sqlcode, dbparamlist);
                case "postgresql":
                    return activePostgreSql(connectionString(sqlstring), sqlcode, dbparamlist);
                default:
                    return null;
            }
        }

        public string activeMsSql(string sqlstring, string sqlcode, List<dbparam> dbparamlist)
        {
            //var configurationBuilder = new ConfigurationBuilder().SetBasePath(Directory.GetCurrentDirectory()).AddJsonFile("appsettings.json",optional:true);
            string strmsg = string.Empty;
            using (SqlConnection conn = new SqlConnection(sqlstring))
            {
                conn.Open();
                SqlTransaction tran = conn.BeginTransaction();
                try
                {
                    using (SqlDataAdapter adpater = new SqlDataAdapter())
                    {
                        SqlCommand sqlcmd = new SqlCommand(sqlcode, conn, tran);
                        foreach (dbparam dbparam in dbparamlist)
                        {
                            sqlcmd.Parameters.AddWithValue(dbparam.key, dbparam.value);
                        }
                        sqlcmd.ExecuteNonQuery();
                        tran.Commit();
                        strmsg = "istrue";
                    }
                }
                catch (Exception ex)
                {
                    tran.Rollback();
                    strmsg = ex.ToString().TrimEnd();
                    Console.WriteLine(sqlcode);
                    Console.WriteLine("error:" + ex.ToString().TrimEnd());
                }
            }
            return strmsg;
        }

        public string activePostgreSql(string sqlstring, string sqlcode, List<dbparam> dbparamlist)
        {
            string strmsg = string.Empty;
            using (NpgsqlConnection conn = new NpgsqlConnection(sqlstring))
            {
                conn.Open();
                NpgsqlTransaction tran = conn.BeginTransaction();
                try
                {
                    using (NpgsqlDataAdapter adpater = new NpgsqlDataAdapter())
                    {
                        NpgsqlCommand sqlcmd = new NpgsqlCommand(sqlcode, conn, tran);
                        foreach (dbparam dbparam in dbparamlist)
                        {
                            sqlcmd.Parameters.AddWithValue(dbparam.key, dbparam.value);
                        }
                        sqlcmd.ExecuteNonQuery();
                        tran.Commit();
                        strmsg = "istrue";
                    }
                }
                catch (Exception ex)
                {
                    tran.Rollback();
                    strmsg = ex.ToString().TrimEnd();
                }
            }
            return strmsg;
        }

        public IMongoDatabase getMongoData(string connectstring, string sqlstring)
        {
            var mongoClient = new MongoClient(connectionString(connectstring));
            return mongoClient.GetDatabase(connectionString(sqlstring));
        }
    }
}