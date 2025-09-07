
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
public class Helado extends Producto {
    private final ArrayList<String> toppings;
    public Helado(){
        toppings = new ArrayList<>();
    }
    
    @Override
    public void cargar(Scanner archivo) {
        super.cargar(archivo);
        int cantidad;
        cantidad = archivo.nextInt();
        String topp;
        for (int i = 0; i < cantidad; i++) {
            topp = archivo.next();
            toppings.add(topp);
        }
    }

    @Override
    public void imprimir() {
        super.imprimir();
        System.out.println("Toppings: " + toppings);
        System.out.println("---------------------------------------------------------------------------------");
    }
    
    @Override
    public void imprimir(Alumno alumno, Pais pais){
        super.imprimir(alumno, pais);
        System.out.println("Toppings: " + toppings);
        System.out.println("----------------------------------------------------------------------------------------------------");
    }
}
