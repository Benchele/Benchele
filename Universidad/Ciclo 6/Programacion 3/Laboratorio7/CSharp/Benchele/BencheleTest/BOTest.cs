using BencheleBusiness;
using BencheleModel;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BencheleTest
{
    [TestClass]
    public class SoftInvBOTest
    {
        private AlmacenBO almacenBO;

        public SoftInvBOTest()
        {
            this.almacenBO = new AlmacenBO();
        }

        [TestMethod]
        public void TestInsertar()
        {
            Console.WriteLine("Insertar");
            int resultado = this.almacenBO.Insertar("Mi almacen central", true);
            Assert.IsTrue(resultado > 0);

            resultado = this.almacenBO.Insertar("Mi segundo almacen", false);
            Assert.IsTrue(resultado > 0);

            resultado = this.almacenBO.Insertar("Mi tercer almacen", false);
            Assert.IsTrue(resultado > 0);
        }

        [TestMethod]
        public void TestListarTodosConProcedure()
        {
            AlmacenBO bo = new AlmacenBO();
            IList<AlmacenesDTO> lista = bo.ListarTodosConProcedure();

            // Assert principal
            Assert.IsNotNull(lista, "La lista no debe ser null");

            // Impresión para verificar contenido en consola
            Console.WriteLine("---- LISTA DE ALMACENES ----");
            foreach (AlmacenesDTO almacen in lista)
            {
                string fila = string.Format(
                    "ID: {0,-3} | Nombre: {1,-20} | Central: {2}",
                    almacen.AlmacenId,
                    almacen.Nombre,
                    almacen.AlmacenCentral ?? false ? 1 : 0
                );
                Console.WriteLine(fila);
            }

            Assert.IsTrue(lista.Count > 0, "Debe existir al menos un almacén en la BD");
        }

    }
}
