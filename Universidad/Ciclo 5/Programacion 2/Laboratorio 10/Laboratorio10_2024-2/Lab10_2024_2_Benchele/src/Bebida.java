
import java.util.Scanner;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Lenovo
 */
public class Bebida extends Producto{
    private char tipoBebida;

    /**
     * @return the tipoBebida
     */
    public char getTipoBebida() {
        return tipoBebida;
    }

    /**
     * @param tipoBebida the tipoBebida to set
     */
    public void setTipoBebida(char tipoBebida) {
        this.tipoBebida = tipoBebida;
    }
    
    @Override
    public void cargar(Scanner archivo) {
        super.cargar(archivo);
        tipoBebida = archivo.next().charAt(0);
    }

    @Override
    public void imprimir() {
        super.imprimir();
        System.out.println("Tipo: " + (tipoBebida == 'C' ? "Café" : tipoBebida == 'H' ? "Chocolate" : "Infusión"));
        System.out.println("---------------------------------------------------------------------------------");
    }
    
    @Override
    public void imprimir(Alumno alumno, Pais pais){
        super.imprimir(alumno, pais); 
        System.out.println("Tipo: " + (tipoBebida == 'C' ? "Café" : tipoBebida == 'H' ? "Chocolate" : "Infusión"));
        System.out.println("----------------------------------------------------------------------------------------------------");
    }
    
}
