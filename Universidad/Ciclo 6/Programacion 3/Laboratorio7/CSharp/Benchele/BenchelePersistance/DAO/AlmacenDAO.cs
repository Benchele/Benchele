using BencheleModel;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BenchelePersistance.DAO
{
    public interface AlmacenDAO
    {
        int Insertar(AlmacenesDTO almacen);

        AlmacenesDTO ObtenerPorId(int almacenId);

        IList<AlmacenesDTO> ListarTodos();

        int Modificar(AlmacenesDTO almacen);

        int Eliminar(AlmacenesDTO almacen);

        //Nuevo hecho por mi

        IList<AlmacenesDTO> ListarTodosPorProcedure();
        IList<AlmacenesDTO> ListarPorCriterio(string criterio);
    }
}
