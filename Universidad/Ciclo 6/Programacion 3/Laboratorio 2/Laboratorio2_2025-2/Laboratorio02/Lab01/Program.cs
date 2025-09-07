using System;
using Lab01.Pregunta01;
using Lab01.Pregunta02;
namespace Lab01
{
    public class Program
    {
        public static void Main(string[] args)
        {
            //Nombre: Benjhamin Ruiz
            //Codigo: 20232242

            Vehiculo vehiculo = new Vehiculo
            {
                Antiguedad = 10,
                Marca = Marca.Toyota
            };


            Console.WriteLine("===== SEGUROS PREDEFINIDOS =====");
            ICotizable seguro = new SeguroBasico(vehiculo);
            Console.WriteLine(seguro);
            seguro = new SeguroBronce(vehiculo);
            Console.WriteLine(seguro);
            seguro = new SeguroPlata(vehiculo);
            Console.WriteLine(seguro);
            seguro = new SeguroOro(vehiculo);
            Console.WriteLine(seguro);
            /* Implementación utilizando el Patrón Decorador
            * para extender funcionalidades de manera flexible */
            Console.WriteLine("\n===== SEGUROS DECORADOS (Patrón Decorador) =====");
            seguro = new SeguroBasico(vehiculo);
            Console.WriteLine(seguro);
            seguro = new SeguroBasico(vehiculo)
                .ConCoberturaContraRobos();
            Console.WriteLine(seguro);
            seguro = new SeguroBasico(vehiculo)
            .ConCoberturaContraRobos()
            .ConAsistenciaVial();
            Console.WriteLine(seguro);
            seguro = new SeguroBasico(vehiculo)
            .ConCoberturaContraRobos()
            .ConAsistenciaVial()
            .ConCoberturaContraDesastresNaturales();
            Console.WriteLine(seguro);
        }
    }

}