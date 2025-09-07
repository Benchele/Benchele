
import java.util.ArrayList;
import java.util.Scanner;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Lenovo
 */
public class Menu {
    private final ArrayList<Producto> productos;
    
    public Menu(){
        productos = new ArrayList<>();
    }
    
    public void cargarProductos(Scanner arch){
        Producto producto;
        char tipo;
        while (arch.hasNext()) {
            tipo = arch.next().charAt(0);
            switch(tipo){
                case 'B':
                    producto = new Bebida();
                    break;
                case 'H':
                    producto = new Helado();
                    break;
                default:
                    producto = new Bebida();
                    break;
            }
            producto.cargar(arch);
            productos.add(producto);
        }
    }
    public void imprimirMenu(){
        System.out.println("============================= Menú del día ======================================");
        for (Producto producto : productos) {
            producto.imprimir();
        }
    }
    public void imprimirMenuPersonalizado(Alumno alumno, Pais pais){
        System.out.println("================ Menú en " + pais.getIdioma() + "("+ pais.getNombre() +") para, " + alumno.getCodigo() + ":" + alumno.getNombre() + " =========================");
        for (Producto producto : productos) {
            producto.imprimir(alumno, pais);
        }
    }
}
