/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lab10_2024_1_benchele;

import java.util.Scanner;

/**
 *
 * @author Lenovo
 */
public class Cliente {
    private int dni;
    private String nombre;
    private double totalGastado;

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
     * @return the totalGastado
     */
    public double getTotalGastado() {
        return totalGastado;
    }

    /**
     * @param totalGastado the totalGastado to set
     */
    public void setTotalGastado(double totalGastado) {
        this.totalGastado = totalGastado;
    }
    
    //Cliente
        
    /*
    20449598   Velasquez_Huayanay_Edgard_Henry
    72832218   Vega_Garcia_Janet_Rebeca
    DNI        NOMBRE DEL CLIENTE
    */
    public boolean leer(Scanner arch){
        dni = arch.nextInt();
        if(dni == 0)return false;
        nombre = arch.next();
        return true;
    }
    
    public void imprimir(){
        System.out.printf("DNI: %10d   NOMBRE: %-60s", dni, nombre);
    }
}
