/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author alulab14
 */
public class CarrilEstandar extends Carril{

    @Override
    public String getTipo() {
        return "Estandar";
    }

    @Override
    public double velocidadMaxima(int km) {
       if(km < 100)return 80;
       else if(km < 200)return 120;
       else if(km < 300)return 100;
       return 0;
    }

    @Override
    public boolean velocidadPermitida(int km, double vel) {
        if(vel < velocidadMaxima(km))return true;
        return false;
    }

    @Override
    public boolean vehiculoPermitido(String categoria) {
        if(categoria.equals("Motocicleta") || categoria.equals("Coupé")
                || categoria.equals("SUV")|| categoria.equals("Camioneta")
                || categoria.equals("Sedan")|| categoria.equals("Ambulancia"))return true;
        return false;
    }
    
}
