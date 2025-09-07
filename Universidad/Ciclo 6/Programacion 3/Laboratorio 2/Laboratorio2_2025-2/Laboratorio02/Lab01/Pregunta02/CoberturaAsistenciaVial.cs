using Lab01.Pregunta01;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab01.Pregunta02
{
    class CoberturaAsistenciaVial : SeguroDecorador
    {
        public CoberturaAsistenciaVial(ICotizable seguro) : base(seguro)
        {
            //Llama al constructor del padre
        }
        public override double CalcularCosto()
        {
            return this.seguro.CalcularCosto() + 100.00;
        }

        public override string Descripcion()
        {
            return this.seguro.Descripcion() + ", asistencia vial";
        }
    }
}
