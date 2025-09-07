using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pregunta1
{
    public class FichaEvaluacion
    {
        private Postulante candidato;
        private DateTime? fecha_hora;
        private int? evaluacion_expediente;
        private int? evaluacion_entrevista;
        private int? evaluacion_examen;
        private Estado estado_candidato;
        private static int? PUNTAJE_MINIMO = 75;


        public Postulante Candidato { get { return candidato; } set { candidato = value; } }
        public DateTime? Fecha_hora { get { return fecha_hora; } set { fecha_hora = value; } }
        public int? Evaluacion_expediente { get { return evaluacion_expediente; } set { evaluacion_expediente = value; } }
        public int? Evaluacion_entrevista { get { return evaluacion_entrevista; } set { evaluacion_entrevista = value; } }
        public int? Evaluacion_examen { get { return evaluacion_examen; } set { evaluacion_examen = value; } }
        public Estado Estado_candidato
        {
            get
            {
                int? puntaje_total = this.Evaluacion_expediente + this.Evaluacion_entrevista + this.Evaluacion_examen;
                if (puntaje_total > PUNTAJE_MINIMO)
                {
                    this.Estado_candidato = Estado.ADMITIDO;
                }
                else
                {
                    this.Estado_candidato = Estado.NO_ADMITIDO;
                }
                return estado_candidato;
            }
            set
            {
                estado_candidato = value;
            }
        }

        public FichaEvaluacion(Postulante candidato, DateTime? fecha_hora, int? evaluacion_expediente, int? evaluacion_entrevista, int? evaluacion_examen, Estado estado_candidato)
        {
            Postulante candidatoCopia = new Postulante(candidato); //Crear otro espacio de memoria
            this.Candidato = candidatoCopia;
            this.Fecha_hora = fecha_hora;
            this.Evaluacion_expediente = evaluacion_expediente;
            this.Evaluacion_entrevista = evaluacion_entrevista;
            this.Evaluacion_examen = evaluacion_examen;
            this.Estado_candidato = estado_candidato;
        }

        public FichaEvaluacion()
        {
            this.Candidato = null;
            this.Fecha_hora = null;
            this.Evaluacion_expediente = null;
            this.Evaluacion_entrevista = null;
            this.Evaluacion_examen = null;
            this.Estado_candidato = Estado.SIN_EVALUACIÓN;
        }

        public FichaEvaluacion(FichaEvaluacion ficha)
        {
            Postulante candidatoCopia = new Postulante(ficha.Candidato); //Crear otro espacio de memoria
            this.Candidato = candidatoCopia;
            this.Fecha_hora = ficha.fecha_hora;
            this.Evaluacion_expediente = ficha.evaluacion_expediente;
            this.Evaluacion_entrevista = ficha.evaluacion_entrevista;
            this.Evaluacion_examen = ficha.evaluacion_examen;
            this.Estado_candidato = ficha.estado_candidato;
        }

    }

}