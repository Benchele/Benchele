using Lab01.Pregunta01;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab01.Pregunta02
{
    public abstract class SeguroDecorador : ICotizable //Abstracta
    {
        protected ICotizable seguro;

        public SeguroDecorador(ICotizable seguro)
        {
            this.seguro = seguro;
        }

        public virtual double CalcularCosto()
        {
            return this.seguro.CalcularCosto();
        }
        public virtual Vehiculo Vehiculo()
        {
            return this.seguro.Vehiculo();
        }
        public virtual string Descripcion()
        {
            return this.seguro.Descripcion();
        }

        public override string ToString()
        {
            return $"Precio: {this.CalcularCosto():F2}, Descripción: {this.Descripcion()}";
        }


    }
}
