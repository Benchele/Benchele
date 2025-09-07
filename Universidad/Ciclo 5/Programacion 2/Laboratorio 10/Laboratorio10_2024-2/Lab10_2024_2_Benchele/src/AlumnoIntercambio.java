
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
public class AlumnoIntercambio extends Alumno {
    private String paisOrigen;
    private final ArrayList<String> idiomas;
    private int numeroDeSemestres;
    
    public AlumnoIntercambio(){
        super();
        idiomas = new ArrayList<>();
    }

    /**
     * @return the paisOrigen
     */
    public String getPaisOrigen() {
        return paisOrigen;
    }

    /**
     * @param paisOrigen the paisOrigen to set
     */
    public void setPaisOrigen(String paisOrigen) {
        this.paisOrigen = paisOrigen;
    }

    /**
     * @return the numeroDeSemestres
     */
    public int getNumeroDeSemestres() {
        return numeroDeSemestres;
    }

    /**
     * @param numeroDeSemestres the numeroDeSemestres to set
     */
    public void setNumeroDeSemestres(int numeroDeSemestres) {
        this.numeroDeSemestres = numeroDeSemestres;
    }

    @Override
    public double calcularPrecio(Producto producto, double tipoCambio) {
        return (producto.getPrecio() - (producto.getPrecio() * 0.05)) * tipoCambio;
    }
    
    @Override
    public void cargar(Scanner archivo) {
        super.cargar(archivo);
        paisOrigen = archivo.next();
        String idi;
        while (!archivo.hasNextInt()) {
            idi = archivo.next();
            idiomas.add(idi);
        }
        numeroDeSemestres = archivo.nextInt();
    }

    @Override
    public void imprimir() {
        super.imprimir();
        System.out.print(String.format("\t%-15s\t%-30s\t%-15s\t%-50s\t%-15s", "N/A", "N/A", paisOrigen, idiomas, "Semestres (" + numeroDeSemestres + ")"));
        System.out.println();
    }
}
