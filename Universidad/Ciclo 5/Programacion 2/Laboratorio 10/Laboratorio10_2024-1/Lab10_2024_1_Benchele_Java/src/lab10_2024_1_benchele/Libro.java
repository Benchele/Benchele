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
public class Libro {
    private String codigo;
    private String titulo;
    private String autor;
    private double precio;
    private final ArrayList<Venta> ventas;
    private int suma;
    private int ranking;
    private double totalVendido;
    
    public Libro(){
        ventas = new ArrayList<>();
        suma = 0;
        totalVendido = 0.0;
    }

    /**
     * @return the codigo
     */
    public String getCodigo() {
        return codigo;
    }

    /**
     * @param codigo the codigo to set
     */
    public void setCodigo(String codigo) {
        this.codigo = codigo;
    }

    /**
     * @return the titulo
     */
    public String getTitulo() {
        return titulo;
    }

    /**
     * @param titulo the titulo to set
     */
    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    /**
     * @return the auto
     */
    public String getAuto() {
        return autor;
    }

    /**
     * @param auto the auto to set
     */
    public void setAuto(String auto) {
        this.autor = auto;
    }

    /**
     * @return the precio
     */
    public double getPrecio() {
        return precio;
    }

    /**
     * @param precio the precio to set
     */
    public void setPrecio(double precio) {
        this.precio = precio;
    }

    /**
     * @return the suma
     */
    public int getSuma() {
        return suma;
    }

    /**
     * @param suma the suma to set
     */
    public void setSuma(int suma) {
        this.suma = suma;
    }

    /**
     * @return the ranking
     */
    public int getRanking() {
        return ranking;
    }

    /**
     * @param ranking the ranking to set
     */
    public void setRanking(int ranking) {
        this.ranking = ranking;
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
    
    public void imprimir(){
        System.out.printf("CODIGO: %10s   TITULO: %-60s  AUTOR: %-40s   PRECIO: %10.2f", codigo, titulo, autor, precio);
        System.out.println();
    }
    
    /*
        IIM5175   Diamantes_y_pedernales   Jose_Maria_Arguedas   69.02
        YDK7687   El_otonio_del_patriarca   Gabriel_Garcia_Marquez   368.04
        CODIGO    TITULO                    AUTOR                    PRECIO
    */
    public boolean leer(Scanner arch){
        codigo = arch.next();
        if(codigo.compareTo("FIN") == 0)return false;
        titulo = arch.next();
        autor = arch.next();
        precio = arch.nextDouble();
        return true;
    }
    /*
        CRY6839         34460612   15   10   2023   93
        WPU8819         42302422   9   2   2024   15
        CODLIB          DNICOMPRA FECHA CALIFICACION(0-100)
        */
    public void llenarVentas(Scanner arch){
        Venta venta;
        venta = new Venta();
        venta.leer(arch);
        ventas.add(venta);
    }
    
    public void actualizar (){
        for (Venta venta : ventas) {
            suma = venta.getCalificacion();
            totalVendido += precio;
        }
        
        int cantidadVenta = ventas.size(); 
        int promedio = 0;
        if(cantidadVenta == 0)ranking = 0;
        else{
            promedio = suma/ventas.size();

            if(promedio < 25)ranking = 1;
            else if(promedio < 50) ranking = 2;
            else if(promedio < 75) ranking = 3;
            else ranking = 4;
        }
    }
    
    public void imprimir(ArrayList<Cliente> clientes){
        int i = 1;
        System.out.printf("CODIGO: %10s   TITULO: %-60s  AUTOR: %-40s   PRECIO: %10.2f \n", codigo, titulo, autor, precio);
        System.out.printf("LIBROS VENDIDOS: %10d   RANKING: %8d \n", ventas.size(), ranking);
        System.out.println("VENTAS REALIZADAS: ");
        
        for (Venta venta : ventas) {
            System.out.printf("No. %d   ", i++);
            venta.imprimir(clientes);
        }
    }
    
}
