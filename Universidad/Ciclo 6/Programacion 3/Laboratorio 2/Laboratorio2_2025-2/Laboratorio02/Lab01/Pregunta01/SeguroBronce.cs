using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab01.Pregunta01
{
    public class SeguroBronce : SeguroBasico
    {
        public SeguroBronce(Vehiculo vehiculo) : base(vehiculo)
        {
            //Llama al constructor del padre
        }

        public override double CalcularCosto()
        {
            double costo = base.CalcularCosto() + 100;
            if (base.vehiculo.Marca == Marca.Toyota) costo += 100;
            //if (base.Vehiculo().Marca == Marca.Toyota) costo += 100; //Se puede usar el atributo tanto como el metodo que devuelve vehiculo
            return costo;
        }

        public override string Descripcion()
        {
            return base.Descripcion() + " + cobertura contra robos";
        }
    }
}
