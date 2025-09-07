/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author alulab14
 */
public class RegistroInfraccion {
    private String codigoInfraccion;
    private double monto;
    private int puntos;
    private Captura captura;
    private Vehiculo vehiculo;

    /**
     * @return the codigoInfraccion
     */
    
    public RegistroInfraccion(){
        captura = new Captura();
        vehiculo = new Vehiculo();
    }
    public String getCodigoInfraccion() {
        return codigoInfraccion;
    }

    /**
     * @param codigoInfraccion the codigoInfraccion to set
     */
    public void setCodigoInfraccion(String codigoInfraccion) {
        this.codigoInfraccion = codigoInfraccion;
    }

    /**
     * @return the monto
     */
    public double getMonto() {
        return monto;
    }

    /**
     * @param monto the monto to set
     */
    public void setMonto(double monto) {
        this.monto = monto;
    }

    /**
     * @return the puntos
     */
    public int getPuntos() {
        return puntos;
    }

    /**
     * @param puntos the puntos to set
     */
    public void setPuntos(int puntos) {
        this.puntos = puntos;
    }
    
    public String toString(){
        return "hola";
    }
    
    public void completarAtributos(Captura cap, Vehiculo vehiculo, int tipo){
        this.captura = cap;
        this.vehiculo = vehiculo;
        if(tipo == 2){
            codigoInfraccion = "M20";
            monto = 963.00;
            puntos = 50;
        }else{
            codigoInfraccion = "G29";
            monto = 428.00;
            puntos = 50;
        }
    }
    
    //Parte 3
    public void imprimirInfra(){
        System.out.printf("Codigo de la infraccion: %s\nMonto de la licencia: S/. %.2f\nPuntos de licencia: %d\n", codigoInfraccion, monto, puntos);
        
        System.out.println("----------------------------------------------------------------------------");
        System.out.println("DESTINATARIO DE LA INFRACCION: ");
        System.out.println("----------------------------------------------------------------------------");
        vehiculo.getPropietario().imprimir();
        
        System.out.println("----------------------------------------------------------------------------");
        System.out.println("DATOS DEL VEHICULO: ");
        System.out.println("----------------------------------------------------------------------------");
        vehiculo.imprimir();
        
        System.out.println("----------------------------------------------------------------------------");
        System.out.println("DATOS CAPTURA ELECTRONICA: ");
        System.out.println("----------------------------------------------------------------------------");
        String placa = vehiculo.getPlaca();
        String carr = captura.getCarril().getTipo();
        
        //Aqui podría imprimir dentro de captura pero mejor lo hice así
        System.out.printf("Placa: %s\nVelocidad: %.2f km/h\nCarril: %s\nUbicacion: Lat %10.6f, Lon %10.6f\nRegion: %s\nProvincia: %s\nKilometro: %d\nFecha: %s\nHora: %s\nCodigo Camara: %s\n", 
                          placa, captura.getVelocidad(), carr, captura.getLatitud(), captura.getLongitud(), captura.getRegion(), captura.getProvincia(), captura.getKm(), captura.getFecha(), captura.getHora(), captura.getCodigoCamara());
        
    }
}
