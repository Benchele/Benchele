using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

namespace Pregunta1
{
    public class Admision
    {
        private BindingList<FichaEvaluacion> listaFichas;
        private int cantidad_admitidos;
        private int cantidad_postulantes;

        public Admision()
        {
            this.listaFichas = new BindingList<FichaEvaluacion>();
            this.cantidad_admitidos = 0;
            this.cantidad_postulantes = 0;

        }
        //public BindingList<FichaEvaluacion>ListaFichas{

        //	get{return listaFichas;}
        //	set{listaFichas = value;}

        //}

        //public int Cantidad_admitidos{
        //	get{return cantidad_admitidos;}
        //	set{cantidad_admitidos = value;}
        //}

        //public int Cantidad_postulantes{
        //	get{return cantidad_postulantes;}
        //	set{cantidad_postulantes = value;}
        //}

        public void agregarFichaDeEvaluacion(FichaEvaluacion ficha)
        {
            FichaEvaluacion fichaCopia = new FichaEvaluacion(ficha);
            this.listaFichas.Add(fichaCopia);
            this.cantidad_postulantes++;
            if (ficha.Estado_candidato == Estado.ADMITIDO)
            {
                this.cantidad_admitidos++;
            }



        }
        public override string ToString()
        {
            string reporte = "REPORTE DE ADMITIDOS: ";
            reporte += this.cantidad_postulantes + " postulantes, " + this.cantidad_admitidos + " admitidos";
            reporte += "\n\tLISTA DE ADMITIDOS\n";
            foreach (FichaEvaluacion ficha in listaFichas)
            {
                if (ficha.Estado_candidato == Estado.ADMITIDO)
                {
                    reporte += "\t\t" + ficha.Candidato + "\n";
                }

            }
            return reporte;
        }
    }
}
