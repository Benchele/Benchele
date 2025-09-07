/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package lab10_2024_1_benchele;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 *
 * @author Lenovo
 */
public class Lab10_2024_1_Benchele {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws FileNotFoundException {
        // TODO code application logic here
        
        //Libros
        //CODIGO TITULO AUTOR PRECIO
        //Cliente
        //DNI NOMBRE DEL CLIENTE
        //Ventas
        //CODLIB DNICOMPRA FECHA CALIFICACION(0-100)

        File nombArch = new File("VentaDeLibros.txt");
        Scanner arch = new Scanner(nombArch);
        
        Libreria libreria = new Libreria();
        
        libreria.leerLibros(arch);
        libreria.leerClientes(arch);
        libreria.leerVentas(arch);
        libreria.calcularRanking();

        libreria.imprimirReporte();
    }
    
}
