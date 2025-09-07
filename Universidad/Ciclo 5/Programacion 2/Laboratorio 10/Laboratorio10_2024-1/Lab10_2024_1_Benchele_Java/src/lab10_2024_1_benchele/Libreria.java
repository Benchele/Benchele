/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lab10_2024_1_benchele;

import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author Lenovo
 */
public class Libreria {
    private String nombre;
    private String direccion;
    private final ArrayList<Libro> libros;
    private final ArrayList<Cliente> clientes;
    private int cantidadVendida;
    private double totalVendido;
    
    public Libreria(){
        libros = new ArrayList<>();
        clientes = new ArrayList<>();
        cantidadVendida = 0;
        totalVendido = 0.0;
    }

    /**
     * @return the nombre
     */
    public String getNombre() {
        return nombre;
    }

    /**
     * @param nombre the nombre to set
     */
    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    /**
     * @return the direccion
     */
    public String getDireccion() {
        return direccion;
    }

    /**
     * @param direccion the direccion to set
     */
    public void setDireccion(String direccion) {
        this.direccion = direccion;
    }

    /**
     * @return the cantidadVendida
     */
    public int getCantidadVendida() {
        return cantidadVendida;
    }

    /**
     * @param cantidadVendida the cantidadVendida to set
     */
    public void setCantidadVendida(int cantidadVendida) {
        this.cantidadVendida = cantidadVendida;
    }

    /**
     * @return the totalVendido
     */
    public double getTotalVendido() {
        return totalVendido;
    }

    /**
     * @param totalVendido the totalVendido to set
     */
    public void setTotalVendido(double totalVendido) {
        this.totalVendido = totalVendido;
    }
    
    /*
        IIM5175   Diamantes_y_pedernales   Jose_Maria_Arguedas   69.02
        YDK7687   El_otonio_del_patriarca   Gabriel_Garcia_Marquez   368.04
    */
    public void leerLibros(Scanner arch){
        //Libros
        //CODIGO TITULO AUTOR PRECIO
        Libro libro;
        nombre = arch.next();
        direccion = arch.next();
        while (true) {
            libro = new Libro();
            if(!libro.leer(arch))break;
            libros.add(libro);
            cantidadVendida++; 
        }
        
    }

    public void leerClientes(Scanner arch){
        Cliente cliente;
        while (true) {
            cliente = new Cliente();
            if(!cliente.leer(arch))break;
            clientes.add(cliente);
        }
    }

    public void leerVentas(Scanner arch){
        /*
        CRY6839   34460612   15   10   2023   93
        WPU8819   42302422   9   2   2024   15
        CODLIB DNICOMPRA FECHA CALIFICACION(0-100)
        */
        String codlib;
        while (arch.hasNext()) {
            codlib = arch.next();
            for (Libro libro : libros) {
                if(codlib.compareTo(libro.getCodigo()) == 0){
                    libro.llenarVentas(arch);
                    break;
                }
            }
        }
    }
    
    public void imprimir(){
        for (Libro libro : libros) {
            libro.imprimir();
        }
        for (Cliente cliente : clientes) {
            cliente.imprimir();
        }
    }
    
    public void calcularRanking(){
        for (Libro libro : libros) {
            libro.actualizar();
            totalVendido += libro.getTotalVendido(); 
        }
    }
    
    public void imprimirReporte(){
        System.out.printf("%s \n", nombre);
        System.out.printf("%s \n", direccion);
        System.out.println("RESULTADO DE LAS VENTAS REALIZADAS");
        System.out.println();
        System.out.printf("TOTAL VENDIDO: %.2f   CANTIDAD TOTAL DE LIBROS VENDIDOS: %d \n", totalVendido, cantidadVendida);
        System.out.println();
        
        int i = 1;
        for (Libro libro : libros) {
            System.out.printf("LIBRO NO: %d \n", i++);
            libro.imprimir(clientes);
            System.out.println();
        }
    }
}
