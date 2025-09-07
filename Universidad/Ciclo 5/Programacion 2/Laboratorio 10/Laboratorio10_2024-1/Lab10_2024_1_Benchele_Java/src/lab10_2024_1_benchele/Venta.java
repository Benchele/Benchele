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
public class Venta {
    private int dni;
    private int calificacion;
    private int fecha;

    /**
     * @return the dni
     */
    public int getDni() {
        return dni;
    }

    /**
     * @param dni the dni to set
     */
    public void setDni(int dni) {
        this.dni = dni;
    }

    /**
     * @return the calificacion
     */
    public int getCalificacion() {
        return calificacion;
    }

    /**
     * @param calificacion the calificacion to set
     */
    public void setCalificacion(int calificacion) {
        this.calificacion = calificacion;
    }

    /**
     * @return the fecha
     */
    public int getFecha() {
        return fecha;
    }

    /**
     * @param fecha the fecha to set
     */
    public void setFecha(int fecha) {
        this.fecha = fecha;
    }
    /*
        CRY6839         34460612   15   10   2023   93
        WPU8819         42302422   9   2   2024   15
        CODLIB          DNICOMPRA FECHA CALIFICACION(0-100)
        */
    public void leer(Scanner arch){
        dni = arch.nextInt();
        int dd, mm, aa;
        dd = arch.nextInt();
        mm = arch.nextInt();
        aa = arch.nextInt();
        fecha = aa*10000 + mm*100 + dd;
        calificacion = arch.nextInt();
    }
    
    public void imprimir(ArrayList<Cliente> clientes){
        for (Cliente cliente : clientes) {
            if(dni == cliente.getDni()){
                cliente.imprimir();
            }
        }
        System.out.printf("CALIFICACION: %10d \n", calificacion);
    }
}
