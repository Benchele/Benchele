
import java.util.Scanner;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Lenovo
 */
public abstract class Alumno extends Registro{
    private int codigo;
    private String nombre;

    /**
     * @return the codigo
     */
    public int getCodigo() {
        return codigo;
    }

    /**
     * @param codigo the codigo to set
     */
    public void setCodigo(int codigo) {
        this.codigo = codigo;
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
    
    @Override
    public void cargar(Scanner arch){
        codigo = arch.nextInt();
        nombre = arch.next();
    }
    @Override
    public void imprimir(){
        System.out.print(String.format("%-10s\t%-35s", codigo, nombre));
    }
    
    public abstract String getPaisOrigen();
    
    public abstract double calcularPrecio(Producto producto, double tipoCambio);
}
