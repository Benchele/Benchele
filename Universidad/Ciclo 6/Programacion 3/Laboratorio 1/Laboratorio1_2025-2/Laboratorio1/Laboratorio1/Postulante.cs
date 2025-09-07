using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Pregunta1
{


    public class Postulante
    {
        private string paterno;
        private string materno;
        private string nombre;
        private string dni;

        public string Paterno { get { return paterno; } set { paterno = value; } }
        public string Materno { get { return materno; } set { materno = value; } }
        public string Nombre { get { return nombre; } set { nombre = value; } }
        public string Dni { get { return dni; } set { dni = value; } }

        public Postulante()
        {
            this.paterno = null;
            this.materno = null;
            this.nombre = null;
            this.dni = null;
        }

        public Postulante(string paterno, string materno, string nombre, string dni)
        {
            this.Paterno = paterno;
            this.Materno = materno;
            this.Nombre = nombre;
            this.Dni = dni;
        }

        public Postulante(Postulante postulante)
        {
            this.Paterno = postulante.Paterno;
            this.Materno = postulante.Materno;
            this.Nombre = postulante.Nombre;
            this.Dni = postulante.Dni;
        }

        public override string ToString()
        {
            return this.paterno + " " + this.materno + ", " + this.nombre + " (" + this.dni + ") ";
        }
    }

}