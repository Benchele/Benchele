/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author alulab14
 */
public class CarrilRapido extends Carril{

    @Override
    public String getTipo() {
        return "Rapido";
    }

    @Override
    public double velocidadMaxima(int km) {
       if(km < 100)return 120;
       else if(km < 200)return 160;
       else if(km < 300)return 140;
       return 0;
    }

    @Override
    public boolean velocidadPermitida(int km, double vel) {
       if(vel < velocidadMaxima(km) && vel > velocidadMinima(km))return true;
       return false;
    }

    @Override
    public boolean vehiculoPermitido(String categoria) {
        if(categoria.equals("Coupe") || categoria.equals("SUV")
                || categoria.equals("Camioneta")||categoria.equals("Sedan"))return true;
        return false;
    }
    
    public double velocidadMinima(int km){
       if(km < 100)return 80;
       else if(km < 200)return 100;
       else if(km < 300)return 90;
       return 0;
    }
    
}
