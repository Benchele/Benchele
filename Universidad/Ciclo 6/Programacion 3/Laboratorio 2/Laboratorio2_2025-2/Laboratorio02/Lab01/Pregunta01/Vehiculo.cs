using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab01.Pregunta01
{
    public class Vehiculo
    {
        private Marca marca;
        private int antiguedad;

        //Propiedades del vehículo
        public Marca Marca { 
            get { return marca; } set { marca = value; }  
        }

        public int Antiguedad {
            get { return antiguedad; } set { antiguedad = value; }
        }
    }
}
