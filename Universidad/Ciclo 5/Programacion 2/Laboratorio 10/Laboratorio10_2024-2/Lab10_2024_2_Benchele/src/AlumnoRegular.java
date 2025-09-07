
import java.util.Scanner;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Lenovo
 */
public class AlumnoRegular extends Alumno {
    private String especialidad;
    private String facultad;

    /**
     * @return the especialidad
     */
    public String getEspecialidad() {
        return especialidad;
    }

    /**
     * @param especialidad the especialidad to set
     */
    public void setEspecialidad(String especialidad) {
        this.especialidad = especialidad;
    }

    /**
     * @return the facultad
     */
    public String getFacultad() {
        return facultad;
    }

    /**
     * @param facultad the facultad to set
     */
    public void setFacultad(String facultad) {
        this.facultad = facultad;
    }

    @Override
    public String getPaisOrigen() {
        return "Peru";
    }

    @Override
    public double calcularPrecio(Producto producto, double tipoCambio) {
        //return 0;
        return (producto.getPrecio() - (producto.getPrecio() * 0.03)) * tipoCambio;
    }
    
    @Override
    public void cargar(Scanner arch){
        super.cargar(arch);
        especialidad = arch.next();
        facultad = arch.next();
    }
    @Override
    public void imprimir(){
        super.imprimir();
        System.out.print(String.format("\t%-15s\t%-30s\t%-15s\t%-50s\t%-15s", facultad, especialidad, "N/A", "N/A", "N/A"));
        System.out.println();
    }
    
}
