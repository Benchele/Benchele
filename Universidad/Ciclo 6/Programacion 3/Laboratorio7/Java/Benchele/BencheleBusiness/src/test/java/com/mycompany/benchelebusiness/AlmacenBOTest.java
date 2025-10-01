/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit5TestClass.java to edit this template
 */
package com.mycompany.benchelebusiness;

import com.mycompany.benchelemodel.AlmacenesDTO;
import java.util.ArrayList;
import java.util.Objects;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 *
 * @author Lenovo
 */
public class AlmacenBOTest {
    
    private AlmacenBO almacenBO;
    
    public AlmacenBOTest() {
        this.almacenBO = new AlmacenBO();
    }

//    @Test
//    public void testInsertar() {
//        System.out.println("insertar");
//        ArrayList<Integer> listaAlmacenId = new ArrayList<>();
//        insertarAlmacenes(listaAlmacenId);
//        eliminarTodo();
//    }
//    
//    private void insertarAlmacenes(ArrayList<Integer> listaAlmacenId) {        
//        Integer resultado = this.almacenBO.insertar("Almacén central", Boolean.TRUE);
//        assertTrue(resultado != 0);
//        listaAlmacenId.add(resultado);
//                
//        resultado = this.almacenBO.insertar("Almacén PUCP", Boolean.FALSE);
//        assertTrue(resultado != 0);
//        listaAlmacenId.add(resultado);
//                
//        resultado = this.almacenBO.insertar("Almacén Progra3", Boolean.FALSE);
//        assertTrue(resultado != 0);
//        listaAlmacenId.add(resultado);        
//    }
//    
//    @Test
//    public void testObtenerPorId() {
//        System.out.println("obtenerPorId");
//        ArrayList<Integer> listaAlmacenId = new ArrayList<>();
//        insertarAlmacenes(listaAlmacenId);
//        AlmacenesDTO almacen = this.almacenBO.obtenerPorId(listaAlmacenId.get(0));
//        assertEquals(almacen.getAlmacenId(), listaAlmacenId.get(0));
//        
//        almacen = this.almacenBO.obtenerPorId(listaAlmacenId.get(1));
//        assertEquals(almacen.getAlmacenId(), listaAlmacenId.get(1));
//        
//        almacen = this.almacenBO.obtenerPorId(listaAlmacenId.get(2));
//        assertEquals(almacen.getAlmacenId(), listaAlmacenId.get(2));
//        eliminarTodo();
//    }
//    
//    @Test
//    public void testListarTodos() {
//        System.out.println("listarTodos");
//        ArrayList<Integer> listaAlmacenId = new ArrayList<>();
//        insertarAlmacenes(listaAlmacenId);
//        
//        ArrayList<AlmacenesDTO> listaAlmacenes = this.almacenBO.listarTodos();
//        assertEquals(listaAlmacenId.size(), listaAlmacenes.size());
//        for (Integer i = 0; i < listaAlmacenId.size(); i++) {
//            assertEquals(listaAlmacenId.get(i), listaAlmacenes.get(i).getAlmacenId());
//            
//        }
//        for (AlmacenesDTO almacen : listaAlmacenes) {
////            System.out.println(
////                "ID: " + almacen.getAlmacenId() +
////                " | Nombre: " + almacen.getNombre() +
////                " | Central: " + (Objects.equals(almacen.getAlmacen_central(), Integer.valueOf(1)) ? "Sí" : "No")
////            );
//            String fila = String.format(
//                        //"ID: %-3s | Nombre: %-20s | Central: %b",
//                        "ID: %-3s | Nombre: %-20s | Central: %d",
//                        almacen.getAlmacenId(),
//                        almacen.getNombre(),
//                        //almacen.getAlmacen_central()
//                        (almacen.getAlmacen_central() ? 1 : 0)
//                    );
//            System.out.println(fila);
//        }
//        eliminarTodo();
//    }
//    
//    @Test
//    public void testModificar() {
//        System.out.println("modificar");
//        ArrayList<Integer> listaAlmacenId = new ArrayList<>();
//        insertarAlmacenes(listaAlmacenId);
//        
//        ArrayList<AlmacenesDTO> listaAlmacenes = this.almacenBO.listarTodos();
//        assertEquals(listaAlmacenId.size(), listaAlmacenes.size());
//        for (Integer i = 0; i < listaAlmacenId.size(); i++) {
//            listaAlmacenes.get(i).setNombre("NuevoNombre" + i.toString());
//            listaAlmacenes.get(i).setAlmacen_central(!listaAlmacenes.get(i).getAlmacen_central());
//            this.almacenBO.modificar(listaAlmacenes.get(i).getAlmacenId(), listaAlmacenes.get(i).getNombre(), listaAlmacenes.get(i).getAlmacen_central());
//        }
//        
//        ArrayList<AlmacenesDTO> listaAlmacenesModificados = this.almacenBO.listarTodos();
//        assertEquals( listaAlmacenes.size(), listaAlmacenesModificados.size());
//        for (Integer i = 0; i < listaAlmacenes.size(); i++) {
//            assertEquals(listaAlmacenes.get(i).getNombre(), listaAlmacenesModificados.get(i).getNombre());
//            assertEquals(listaAlmacenes.get(i).getAlmacen_central(), listaAlmacenesModificados.get(i).getAlmacen_central());
//        }
//        eliminarTodo();
//    }
//    
//    @Test
//    public void testEliminar() {
//        System.out.println("eliminar");
//        ArrayList<Integer> listaAlmacenId = new ArrayList<>();
//        insertarAlmacenes(listaAlmacenId);
//        eliminarTodo();
//    }
//    
//    private void eliminarTodo(){                
//        ArrayList<AlmacenesDTO> listaAlmacenes = this.almacenBO.listarTodos();
//        for (Integer i = 0; i < listaAlmacenes.size(); i++) {
//            Integer resultado = this.almacenBO.eliminar(listaAlmacenes.get(i).getAlmacenId());
//            assertNotEquals(0, resultado);
//            AlmacenesDTO almacen = this.almacenBO.obtenerPorId(listaAlmacenes.get(i).getAlmacenId());
//            assertNull(almacen);
//        }
//    }
//    
    @Test
    public void testListarTodosConProcedure() {
        AlmacenBO bo = new AlmacenBO();
        ArrayList<AlmacenesDTO> lista = bo.listarTodosConProcedure();

        // assert principal
        assertNotNull(lista, "La lista no debe ser null");

        // impresión para verificar contenido en consola
        System.out.println("---- LISTA DE ALMACENES ----");
        for (AlmacenesDTO almacen : lista) {
//            System.out.println(
//                "ID: " + almacen.getAlmacenId() +
//                " | Nombre: " + almacen.getNombre() +
//                " | Central: " + (Objects.equals(almacen.getAlmacen_central(), Integer.valueOf(1)) ? "Sí" : "No")
//            );
            String fila = String.format(
                        //"ID: %-3s | Nombre: %-20s | Central: %b",
                        "ID: %-3s | Nombre: %-20s | Central: %d",
                        almacen.getAlmacenId(),
                        almacen.getNombre(),
                        //almacen.getAlmacen_central()
                        (almacen.getAlmacen_central() ? 1 : 0)
                    );
            System.out.println(fila);
        }

        // si esperas al menos 1 registro:
        //assertTrue(lista.size() > 0, "Debe existir al menos un almacén en la BD");
        assertTrue(!lista.isEmpty(), "Debe existir al menos un almacén en la BD");
    }
    
    
}
