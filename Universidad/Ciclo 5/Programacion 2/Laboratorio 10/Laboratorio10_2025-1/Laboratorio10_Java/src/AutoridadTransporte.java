
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author alulab14
 */
public class AutoridadTransporte {
    private final ArrayList<Propietario> propietarios;
    private final ArrayList<Vehiculo> vehiculos;
    private final ArrayList<Captura> capturas;
    private final ArrayList<RegistroInfraccion> regInfracciones;
    private Scanner archivo;
    
    public AutoridadTransporte(final String nombArch) throws FileNotFoundException{
        archivo = new Scanner(new File(nombArch));
        propietarios = new ArrayList<>();
        vehiculos = new ArrayList<>();
        capturas = new ArrayList<>();
        regInfracciones = new ArrayList<>();
    }
    
    public void cargarDatos(){
        //Cargar propietarios
        cargarPropietarios();
        //Cargar vehiculos
        cargarVehiculos();
        //Cargar capturas
        cargarCapturas();
    }
    public void procesarCapturas(){
        for (Captura captura : capturas) {
            procesarCapturaIndividual(captura);
        }
    }
    public void imprimirInfracciones(){
//        for (Propietario propietario : propietarios) {
//            propietario.imprimir();
//        }
//        for (Vehiculo vehiculo : vehiculos) {
//            vehiculo.imprimir();
//        }
//        for (Captura captura : capturas) {
//            captura.imprimir();
//        }
        System.out.printf("                      REGISTRO DE INFRACCION DE TRANSITO\n");
        
        for (RegistroInfraccion regInfraccione : regInfracciones) {
            System.out.println("============================================================================");
            regInfraccione.imprimirInfra();
        }
    }
    
    /////////Metodos
    private void cargarPropietarios(){
        Propietario prop;
        while(true){
            prop = new Propietario();
            if(!(prop.cargarDatos(archivo)))break;
            propietarios.add(prop);
        }
    }
    private void cargarVehiculos(){
        Vehiculo vehi;
        //Sacar el FIN anterior
        String aux = archivo.next();
        while(true){
            vehi = new Vehiculo();
            if(!(vehi.cargarDatos(archivo)))break;
            buscarPropietario(vehi); //Buscar y asignar el propietario al vehiculo
            vehiculos.add(vehi);
        }
    }
    private void cargarCapturas(){
        Captura cap;
        while(true){
            cap = new Captura();
            if(!(cap.cargarDatos(archivo)))break;
            capturas.add(cap);
        }
    }
    public void buscarPropietario(Vehiculo vehi){
        int dni = vehi.getPropietario().getDni();
        for (Propietario propietario : propietarios) {
            if(dni == propietario.getDni()){
                vehi.setPropietario(propietario);
                break;
            }
        }
    }
    //Parte 2
    private void procesarCapturaIndividual(Captura captura){
        RegistroInfraccion regInfra;
        for (Vehiculo vehiculo : vehiculos) {
            if(captura.getPlaca().compareTo(vehiculo.getPlaca()) == 0){
                regInfra = new RegistroInfraccion();
                if(captura.procesarCapturas(vehiculo, regInfra))regInfracciones.add(regInfra);
                break;
            }
        }
        
    }
}
