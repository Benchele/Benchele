using BencheleModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BenchelePersistance.DAO
{
    public interface TipoProductoDAO
    {
        IList<TiposProductosDTO> ConsultarTiposDeProductos(string nombre);

        TiposProductosDTO ObtenerPorId(int tipoProductoId);
    }
}
