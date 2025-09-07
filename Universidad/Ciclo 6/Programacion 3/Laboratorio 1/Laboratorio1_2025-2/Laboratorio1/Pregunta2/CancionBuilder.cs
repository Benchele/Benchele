using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace Pregunta2
{
    public class CancionBuilder
    {
        private string titulo;

        private string otroTitulo;
        private BindingList<string> interpretes;
        private BindingList<string> compositores;
        private Genero? generoMusical;
        private string album;
        private int? opus;
        private int? subOpus;
        private string dedicatoria;

        public string Titulo { get { return titulo; } set { this.titulo = value; } }
        public string OtroTitulo { get { return otroTitulo; } set { this.otroTitulo = value; } }
        public Genero? GeneroMusical { get { return generoMusical; } set { this.generoMusical = value; } }
        public string Album { get { return album; } set { this.album = value; } }
        public int? Opus { get { return opus; } set { this.opus = value; } }
        public int? SubOpus { get { return subOpus; } set { this.subOpus = value; } }
        public string Dedicatoria { get { return dedicatoria; } set { this.dedicatoria = value; } }


        //public BindingList<string> Interpretes{
        //	get{return interpretes;}
        //	set{interpretes = value;}
        //}
        //public BindingList<string> Compositores{
        //	get{return compositores;}
        //	set{compositores = value;}
        //}

        public void agregarInterprete(string interprete)
        {
            this.interpretes.Add(interprete);
        }

        public void agregarCompositor(string compositor)
        {
            this.compositores.Add(compositor);
        }

        public CancionBuilder()
        {
            this.titulo = null;
            this.otroTitulo = null;
            this.interpretes = new BindingList<string>();
            this.compositores = new BindingList<string>();
            this.generoMusical = null;
            this.album = null;
            this.opus = null;
            this.subOpus = null;
            this.dedicatoria = null;
        }


        public CancionBuilder ConTitulo(string Titulo)
        {
            this.Titulo = Titulo;
            return this;
        }

        public CancionBuilder TambienConocidaComo(string OtroTitulo)
        {
            this.OtroTitulo = OtroTitulo;
            return this;
        }

        public CancionBuilder InterpretadoPor(string interprete)
        {
            this.agregarInterprete(interprete);
            return this;
        }

        public CancionBuilder CompuestoPor(string compositor)
        {
            this.agregarCompositor(compositor);
            return this;
        }

        public CancionBuilder DelGenero(Genero generoMusical)
        {
            this.GeneroMusical = generoMusical;
            return this;
        }

        public CancionBuilder EnElAlbum(string album)
        {
            this.album = album;
            return this;
        }

        public CancionBuilder IdentificadoConOpus(int opus)
        {
            this.Opus = opus;
            return this;
        }

        public CancionBuilder IdentificadoConSubOpus(int subOpus)
        {
            this.SubOpus = subOpus;
            return this;
        }

        public CancionBuilder DedicadoA(string dedicatoria)
        {
            this.dedicatoria = dedicatoria;
            return this;
        }

        public Cancion BuildCancion()
        {
            Cancion cancion = new Cancion();
            cancion.Titulo = this.Titulo;
            cancion.OtroTitulo = this.OtroTitulo;

                foreach (string interprete in interpretes)
            {
                cancion.agregarInterprete(interprete);
            }
            foreach (string compositor in compositores)
            {
                cancion.agregarCompositor(compositor);
            }
            cancion.GeneroMusical = this.GeneroMusical;
            cancion.Album = this.Album;
            cancion.Opus = this.Opus;
            cancion.SubOpus = this.SubOpus;
            cancion.Dedicatoria = this.Dedicatoria;


                return cancion;

        }
    }
}