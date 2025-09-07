using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab01.Pregunta01
{
    public class SeguroOro : SeguroPlata
    {
        public SeguroOro(Vehiculo vehiculo) : base(vehiculo)
        {
            //Llama al constructor del padre
        }

        public override double CalcularCosto()
        {
            return base.CalcularCosto() + 300;
        }

        public override string Descripcion()
        {
            return base.Descripcion() + " + cobertura contra desastres naturales";
        }
    }
}
