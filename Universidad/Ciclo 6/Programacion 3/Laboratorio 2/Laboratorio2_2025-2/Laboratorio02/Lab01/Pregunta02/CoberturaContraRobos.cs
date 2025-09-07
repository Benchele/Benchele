using Lab01.Pregunta01;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab01.Pregunta02
{
    public class CoberturaContraRobos : SeguroDecorador
    {
        public CoberturaContraRobos(ICotizable seguro) : base(seguro)
        {
            //Llama al constructor del padre
        }

        public override double CalcularCosto()
        {
            //double costo = base.seguro.CalcularCosto() + 100;
            //if(base.seguro.Vehiculo().Marca == Marca.Toyota)
            //{
            //    costo += 100;
            //}
            //return costo;

            double costo = 100.00;
            if (this.seguro.Vehiculo().Marca == Marca.Toyota)
            {
                costo += 100.00;
            }
            return this.seguro.CalcularCosto() + costo;
        }

        public override string Descripcion()
        {
            return this.seguro.Descripcion() + ", cobertura contra robos";
        }
    }
}
