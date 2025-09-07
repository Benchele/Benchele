using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab01.Pregunta01
{
    public class SeguroBasico : ICotizable
    {
        protected Vehiculo vehiculo;

        public SeguroBasico(Vehiculo vehiculo)
        {
            this.vehiculo = vehiculo;
        }



        public virtual double CalcularCosto()
        {

            double costo = 500;
            if(vehiculo.Antiguedad > 10) //Si tiene mas de 10 años de antiguedades
            {
                costo += 200;
            }
            else
            {
                if(vehiculo.Antiguedad > 5) //Si tiene mas de 5 años de antiguedades
                {   
                    costo += 100;
                }
            }

            if(vehiculo.Marca == Marca.Audi || vehiculo.Marca == Marca.BMW || vehiculo.Marca == Marca.Mercedez) //Si es una marca premium (Audi, BMW, Mercedez) 
            {
                costo += 100;
            }
            return costo;
        }
        public virtual Vehiculo Vehiculo()
        {
            return vehiculo;
        }
        public virtual string Descripcion()
        {
            string descp = "Seguro básico vehicular";
            return descp;
        }

        public override string ToString()
        {
            return $"Precio: {this.CalcularCosto():F2}, Descripción: {this.Descripcion()}";
        }


    }
}
