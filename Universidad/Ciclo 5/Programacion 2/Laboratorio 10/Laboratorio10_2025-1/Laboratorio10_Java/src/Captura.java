
import java.util.Scanner;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author alulab14
 */
public class Captura extends Registro{
    private String placa;
    private double velocidad;
    private Carril carril;
    private double latitud;
    private double longitud;
    private String region;
    private String provincia;
    private int km;
    private String fecha;
    private String hora;
    private String codigoCamara;

    
    public Captura(){
        
        //carril = new Carril();
    }
    /**
     * @return the placa
     */
    public String getPlaca() {
        return placa;
    }

    /**
     * @param placa the placa to set
     */
    public void setPlaca(String placa) {
        this.placa = placa;
    }

    /**
     * @return the velocidad
     */
    public double getVelocidad() {
        return velocidad;
    }

    /**
     * @param velocidad the velocidad to set
     */
    public void setVelocidad(double velocidad) {
        this.velocidad = velocidad;
    }

    /**
     * @return the latitud
     */
    public double getLatitud() {
        return latitud;
    }

    /**
     * @param latitud the latitud to set
     */
    public void setLatitud(double latitud) {
        this.latitud = latitud;
    }

    /**
     * @return the longitud
     */
    public double getLongitud() {
        return longitud;
    }

    /**
     * @param longitud the longitud to set
     */
    public void setLongitud(double longitud) {
        this.longitud = longitud;
    }

    /**
     * @return the region
     */
    public String getRegion() {
        return region;
    }

    /**
     * @param region the region to set
     */
    public void setRegion(String region) {
        this.region = region;
    }

    /**
     * @return the provincia
     */
    public String getProvincia() {
        return provincia;
    }

    /**
     * @param provincia the provincia to set
     */
    public void setProvincia(String provincia) {
        this.provincia = provincia;
    }

    /**
     * @return the km
     */
    public int getKm() {
        return km;
    }

    /**
     * @param km the km to set
     */
    public void setKm(int km) {
        this.km = km;
    }

    /**
     * @return the fecha
     */
    public String getFecha() {
        return fecha;
    }

    /**
     * @param fecha the fecha to set
     */
    public void setFecha(String fecha) {
        this.fecha = fecha;
    }

    /**
     * @return the hora
     */
    public String getHora() {
        return hora;
    }

    /**
     * @param hora the hora to set
     */
    public void setHora(String hora) {
        this.hora = hora;
    }

    /**
     * @return the codigoCamara
     */
    public String getCodigoCamara() {
        return codigoCamara;
    }

    /**
     * @param codigoCamara the codigoCamara to set
     */
    public void setCodigoCamara(String codigoCamara) {
        
    }

    @Override
    public boolean cargarDatos(Scanner scanner) {
        if(!scanner.hasNext())return false;
        placa = scanner.next();
        velocidad = scanner.nextDouble();
        int numCarril = scanner.nextInt();
        carril = getCarril(numCarril);
        latitud = scanner.nextDouble();
        longitud = scanner.nextDouble();
        region = scanner.next();
        provincia = scanner.next();
        km = scanner.nextInt();
        fecha = scanner.next();
        hora = scanner.next();
        codigoCamara = scanner.next();
        return true;
    }

    @Override
    public void imprimir() {
        System.out.printf("Placa: %s\n", placa);
    }
    
    public String toString(){
        return "hola";
    }
    
    public Carril getCarril(int numCarril){
        Carril aux;
        switch(numCarril){
            case 1:
                aux = new CarrilEmergencia();
                break;
            case 2:
                aux = new CarrilLento();
                break;
            case 3:
                aux = new CarrilEstandar();
                break;
            case 4:
                aux = new CarrilRapido();
                break;
            default:
                aux = new CarrilEstandar();
                break;
        }
        return aux;
    }
    
    public Carril getCarril(){
        return this.carril;
    }
    
    
    public boolean procesarCapturas(Vehiculo vehiculo, RegistroInfraccion regInfra){
        if(!carril.vehiculoPermitido(vehiculo.getCategoria())){
            //regInfra = new RegistroInfraccion();
            regInfra.completarAtributos(this, vehiculo, 1); //Si no cumple con el vehiculo permitido
            return true;
        }
        else{
            if(!(carril.velocidadPermitida(km, velocidad))){ //Si no cumple con la velocidad
                //regInfra = new RegistroInfraccion();
                regInfra.completarAtributos(this, vehiculo, 2);
                return true;
            };
        }
        return false;
    }
    
    
    
    
    
}
