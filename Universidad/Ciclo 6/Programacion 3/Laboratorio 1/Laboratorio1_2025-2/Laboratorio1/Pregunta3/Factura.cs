using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pregunta3
{
    internal class Factura : Comprobante
    {
        private string ruc;
        private string razonSocial;

        public string Ruc
        {
            get { return ruc; }
            set { ruc = value; }
        }
        public string RazonSocial
        {
            get { return razonSocial; }
            set { razonSocial = value; }
        }

        public Factura() : base()
        {
            ruc = null;
            razonSocial = null;
        }
        public Factura(string ruc, string razonSocial) : base()
        {
            this.ruc = ruc;
            this.razonSocial = razonSocial;
        }
        public override string ToString()
        {

            string reporte = "FACTURA\n";
            reporte += "CLIENTE:\n\tRUC: " + Ruc + "\n";
            reporte += "\tRazon social: " + RazonSocial + "\n";
            reporte += base.ToString();
            return reporte;
        }
    }
}

//Fin: 5:30 pm