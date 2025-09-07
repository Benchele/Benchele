/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author alulab14
 */
public class CarrilEmergencia extends Carril {

    @Override
    public String getTipo() {
        return "Emergencia";
    }

    @Override
    public double velocidadMaxima(int km) {
        return 80;
    }

    @Override
    public boolean velocidadPermitida(int km, double vel) {
        if(vel < velocidadMaxima(km))return true;
        return false;
    }

    @Override
    public boolean vehiculoPermitido(String categoria) {
        if(categoria.equals("Ambulancia") || categoria.equals("Grúa"))return true;
        return false;
    }
    
}
