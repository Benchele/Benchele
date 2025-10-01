using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.Common;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BencheleDBManager
{
    public class DBManager
    {
        protected DbConnection conexion;
        protected string baseDeDatos;
        protected string nombreDeHost;
        protected string puerto;
        protected string usuario;
        protected string contraseña;
        protected static DBManager dbManager;

        private DBManager()
        {
            //constructor protegido para evitar que se creen instancias.
            //Solo se podrá crear una instancia y esta debe hacerse usando el 
            //método getInstance()
        }

        public static DBManager Instance
        {
            get
            {
                if (dbManager == null)
                {
                    DBManager.CreateInstance();
                }
                return dbManager;
            }
        }

        private static void CreateInstance()
        {
            if (DBManager.dbManager == null)
            {
                DBManager.dbManager = new DBManager();
                DBManager.dbManager.LeerArchivoDeConfiguracion();
            }
        }

        


        private void LeerArchivoDeConfiguracion()
        {
            this.baseDeDatos = ConfigurationManager.AppSettings["baseDeDatos"];
            this.nombreDeHost = ConfigurationManager.AppSettings["nombreDeHost"];
            this.puerto = ConfigurationManager.AppSettings["puerto"];
            this.usuario = ConfigurationManager.AppSettings["usuario"];
            this.contraseña = ConfigurationManager.AppSettings["contraseña"];
        }

        public DbConnection Connection
        {
            get
            {
                string cadenaDeConexion = this.ObtenerCadenaDeConexion();
                //System.Console.WriteLine(cadenaDeConexion);
                this.conexion = new MySqlConnection(cadenaDeConexion);
                return this.conexion;
            }
        }

        protected string ObtenerCadenaDeConexion()
        {
            MySqlConnectionStringBuilder csBuilder = new MySqlConnectionStringBuilder()
            {
                Server = $"{this.nombreDeHost},{this.puerto}",
                Database = this.baseDeDatos,
                UserID = this.usuario,
                Password = this.contraseña
            };

            return csBuilder.ConnectionString;
        }



        public DbCommand CrearComando()
        {
            return new MySqlCommand();
        }

        public string RetornarSQLParaUltimoAutoGenerado()
        {
            string sql = "select @@last_insert_id as id";
            return sql;
        }

        public static string Cifrar(string texto)
        {
            return Convert.ToBase64String(Encoding.Unicode.GetBytes(texto));
        }

        public static string Descifrar(string textoEncriptado)
        {
            return Encoding.Unicode.GetString(Convert.FromBase64String(textoEncriptado));
        }
    }
}
