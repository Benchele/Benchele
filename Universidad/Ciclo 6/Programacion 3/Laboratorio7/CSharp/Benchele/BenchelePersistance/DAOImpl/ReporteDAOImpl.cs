using BencheleModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BenchelePersistance.DAOImpl
{
    public class ReporteDAOImpl
    {
        //Simplemento ejemplos con no query

        //public void GenerarReporteStock(int año, int mes)
        //{
        //    object parametros = new ReporteStockParametrosBuilder()
        //        .ConAño(año)
        //        .ConMes(mes)
        //        .BuildReporteStockParametros();

        //    string sql = "{call SP_INV_GENERAR_REPORTE_STOCK (?, ?)}";
        //    bool conTransaccion = true;

        //    this.EjecutarProcedimientoAlmacenado(sql,
        //        this.IncluirValorDeParametrosParaGenerarReporteStock,
        //        parametros,
        //        conTransaccion);
        //}

        //private void IncluirValorDeParametrosParaGenerarReporteStock(object objetoParametros)
        //{
        //    ReporteStockParametros parametros = (ReporteStockParametros)objetoParametros;

        //    this.AgregarParametro("@año", parametros.Año);
        //    this.AgregarParametro("@mes", parametros.Mes);
        //}

        //public void InsertarDatosParaPrueba()
        //{
        //    string sql = "{call SP_INV_INSERTAR_DATOS_PRUEBA_REPORTE_STOCK ()}";
        //    bool conTransaccion = true;
        //    this.EjecutarProcedimientoAlmacenado(sql, conTransaccion);
        //}

        //public void EliminarDatosParaPrueba()
        //{
        //    string sql = "{call SP_INV_ELIMINAR_DATOS_PRUEBA_REPORTE_STOCK ()}";
        //    bool conTransaccion = true;
        //    this.EjecutarProcedimientoAlmacenado(sql, conTransaccion);
        //}

        //Listar por periodo
        //public IList<ReportesStocksDTO> ListarPorPeriodo(int año, int mes, int? almacenId, int? productoId)
        //{
        //    object parametros = new ReporteStockParametrosBuilder()
        //        .ConAño(año)
        //        .ConMes(mes)
        //        .ConAlmacenId(almacenId)
        //        .ConProductoId(productoId)
        //        .BuildReporteStockParametros();

        //    string sql = this.GenerarSQLParaListarPorPeriodo();

        //    return base.ListarTodos(sql,
        //        this.IncluirValorDeParametrosParaListarPorPeriodo,
        //        parametros)
        //        .Cast<ReportesStocksDTO>()
        //        .ToList();
        //}

        //private string GenerarSQLParaListarPorPeriodo()
        //{
        //    string sql = "SELECT ";
        //    sql += "r.ANHO, ";
        //    sql += "r.MES, ";
        //    sql += "r.ALMACEN_ID, ";
        //    sql += "r.PRODUCTO_ID, ";
        //    sql += "r.SALDO_INICIAL, ";
        //    sql += "r.ENTRADAS, ";
        //    sql += "r.SALIDAS, ";
        //    sql += "r.SALDO_FINAL ";
        //    sql += " FROM INV_REPORTES_STOCKS r";
        //    sql += " JOIN INV_PRODUCTOS p ON p.PRODUCTO_ID = r.PRODUCTO_ID ";
        //    sql += " JOIN INV_TIPOS_PRODUCTOS t on t.TIPO_PRODUCTO_ID = p.TIPO_PRODUCTO_ID ";
        //    sql += " JOIN INV_ALMACENES a on a.ALMACEN_ID = r.ALMACEN_ID ";
        //    sql += " WHERE r.ANHO = ?";
        //    return sql;
        //}

        //private void IncluirValorDeParametrosParaListarPorPeriodo(object objetoParametros)
        //{
        //    ReporteStockParametros parametros = (ReporteStockParametros)objetoParametros;
        //    this.AgregarParametro("@año", parametros.Año);
        //}
    }
}
