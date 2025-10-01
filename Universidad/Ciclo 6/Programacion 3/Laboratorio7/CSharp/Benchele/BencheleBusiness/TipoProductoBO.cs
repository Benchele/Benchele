using BencheleModel;
using BenchelePersistance.DAO;
using BenchelePersistance.DAOImpl;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BencheleBusiness
{
    public class TipoProductoBO
    {
        private TipoProductoDAO tipoProductoDAO;

        public TipoProductoBO()
        {
            this.tipoProductoDAO = new TipoProductoDAOImpl();
        }

        public IList<TiposProductosDTO> ConsultarTiposDeProductos(string nombre)
        {
            return this.tipoProductoDAO.ConsultarTiposDeProductos(nombre);
        }

        public TiposProductosDTO ObtenerPorId(int tipoProductoId)
        {
            return this.tipoProductoDAO.ObtenerPorId(tipoProductoId);
        }
    }
}
