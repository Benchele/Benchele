using BencheleModel;
using BenchelePersistance.DAO;
using BenchelePersistance.DAOImpl.Util;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data.Common;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BenchelePersistance.DAOImpl
{
    public class AlmacenDAOImpl : DAOImplBase, AlmacenDAO
    {
        private AlmacenesDTO almacen;

        public AlmacenDAOImpl() : base("INV_ALMACENES")
        {
            this.retornarLlavePrimaria = true;
            this.almacen = null;
        }

        protected override void ConfigurarListaDeColumnas()
        {
            this.listaColumnas.Add(new Columna("ALMACEN_ID", true, true));
            this.listaColumnas.Add(new Columna("NOMBRE", false, false));
            this.listaColumnas.Add(new Columna("ALMACEN_CENTRAL", false, false));
        }

        protected override void IncluirValorDeParametrosParaInsercion()
        {
            AgregarParametro("@NOMBRE", this.almacen.Nombre);
            AgregarParametro("@ALMACEN_CENTRAL", (bool)this.almacen.AlmacenCentral ? 1 : 0);
        }

        protected override void IncluirValorDeParametrosParaModificacion()
        {
            AgregarParametro("@ALMACEN_ID", this.almacen.AlmacenId);
            AgregarParametro("@NOMBRE", this.almacen.Nombre);
            AgregarParametro("@ALMACEN_CENTRAL", (bool)this.almacen.AlmacenCentral ? 1 : 0);
        }

        protected override void IncluirValorDeParametrosParaEliminacion()
        {
            AgregarParametro("@ALMACEN_ID", this.almacen.AlmacenId);
        }

        protected override void IncluirValorDeParametrosParaObtenerPorId()
        {
            AgregarParametro("@ALMACEN_ID", this.almacen.AlmacenId);
        }

        protected override void InstanciarObjetoDelResultSet(DbDataReader lector)
        {
            this.almacen = new AlmacenesDTO();
            this.almacen.AlmacenId = this.lector.GetInt32(0);
            this.almacen.Nombre = this.lector.GetString(1);
            this.almacen.AlmacenCentral = this.lector.GetInt32(2) == 1;
        }

        protected override void LimpiarObjetoDelResultSet()
        {
            this.almacen = null;
        }

        protected override void AgregarObjetoALaLista(IList<Object> lista, DbDataReader lector)
        {
            this.InstanciarObjetoDelResultSet(lector);
            lista.Add(this.almacen);
        }

        public int Insertar(AlmacenesDTO almacen)
        {
            this.almacen = almacen;
            return base.Insertar();
        }

        public int Modificar(AlmacenesDTO almacen)
        {
            this.almacen = almacen;
            return base.Modificar();
        }

        public int Eliminar(AlmacenesDTO almacen)
        {
            this.almacen = almacen;
            return base.Eliminar();
        }

        public AlmacenesDTO ObtenerPorId(int almacenId)
        {
            this.almacen = new AlmacenesDTO();
            this.almacen.AlmacenId = almacenId;
            base.ObtenerPorId();
            return this.almacen;
        }

        public new IList<AlmacenesDTO> ListarTodos()
        {
            return base.ListarTodos()
               .Cast<AlmacenesDTO>()
               .ToList();
        }

        //Nuevo hecho por mi
        public IList<AlmacenesDTO> ListarTodosPorProcedure()
        {
            //string sql = "{CALL SP_LISTAR_ALMACENES ()}";
            string sql = "CALL SP_LISTAR_ALMACENES()";
            //En java si se podia poner llaves porque es mas flexible
            bool conTransaccion = false;

            return base.EjecutarProcedimientoAlmacenadoSELECT(sql, conTransaccion)
                .Cast<AlmacenesDTO>()
                .ToList();
        }

        // Ejemplo con parámetros
        public IList<AlmacenesDTO> ListarPorCriterio(string criterio)
        {
            string sql = "{CALL SP_LISTAR_ALMACENES_POR_CRITERIO (?)}";
            bool conTransaccion = false;

            return base.EjecutarProcedimientoAlmacenadoSELECT(sql,
                this.IncluirValorDeParametrosParaCriterio,
                criterio,
                conTransaccion)
                .Cast<AlmacenesDTO>()
                .ToList();
        }

        private void IncluirValorDeParametrosParaCriterio(object objetoParametros)
        {
            string criterio = (string)objetoParametros;
            this.AgregarParametro("@criterio", criterio);
        }
    }
}
