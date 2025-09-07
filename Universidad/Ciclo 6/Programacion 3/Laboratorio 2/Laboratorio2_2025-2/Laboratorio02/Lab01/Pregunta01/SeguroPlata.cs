using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab01.Pregunta01
{
    public class SeguroPlata : SeguroBronce
    {
        public SeguroPlata(Vehiculo vehiculo) : base(vehiculo)
        {
            //Llama al constructor del padre
        }

        public override double CalcularCosto()
        {
            return base.CalcularCosto() + 100;
        }

        public override string Descripcion()
        {
            return base.Descripcion() + " + asistencia vial";
        }
    }
}
