using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pregunta3
{
    public class Principal
    {
        static void Main(string[] args)
        {
            Comprobante comprobante = new Comprobante();
            comprobante.agregarDetalle("Polo azul", 2, 56.99);
            comprobante.agregarDetalle("Blue Jean", 1, 99.45);
            Console.WriteLine(comprobante);
            Console.WriteLine();
            comprobante = new Factura("10236786549", "Asociación Programación 3");
            comprobante.agregarDetalle("Polo azul", 2, 56.99);
            comprobante.agregarDetalle("Blue Jean", 1, 99.45);
            Console.WriteLine(comprobante);
        }

    }
}
