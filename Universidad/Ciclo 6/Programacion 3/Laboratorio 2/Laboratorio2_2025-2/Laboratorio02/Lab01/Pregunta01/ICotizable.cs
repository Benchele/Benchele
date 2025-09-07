using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab01.Pregunta01
{
    public interface ICotizable
    {
        //Interfaz
        Vehiculo Vehiculo();

        string Descripcion();

        double CalcularCosto();
    }
}
