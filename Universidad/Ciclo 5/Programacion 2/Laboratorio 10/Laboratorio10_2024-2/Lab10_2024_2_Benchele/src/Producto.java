
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
public class Producto extends Registro{
    private String codigo;
    private final ArrayList<Traduccion> nombres;
    private final ArrayList<Traduccion> descripciones;
    private double precio;
    private int stock;
    
    public Producto(){
        nombres = new ArrayList<>();
        descripciones = new ArrayList<>();
    }

    /**
     * @return the codigo
     */
    public String getCodigo() {
        return codigo;
    }

    /**
     * @param codigo the codigo to set
     */
    public void setCodigo(String codigo) {
        this.codigo = codigo;
    }

    /**
     * @return the precio
     */
    public double getPrecio() {
        return precio;
    }

    /**
     * @param precio the precio to set
     */
    public void setPrecio(double precio) {
        this.precio = precio;
    }

    /**
     * @return the stock
     */
    public int getStock() {
        return stock;
    }

    /**
     * @param stock the stock to set
     */
    public void setStock(int stock) {
        this.stock = stock;
    }

    @Override
    public void cargar(Scanner archivo) {
        codigo = archivo.next();
        Traduccion nombre;
        while (!archivo.hasNextDouble()) {
            nombre = new Traduccion();
            nombre.setIdioma(archivo.next());
            nombre.setTexto(archivo.next());
            nombres.add(nombre);
        }
        precio = archivo.nextDouble();
        Traduccion desc;
        while (!archivo.hasNextInt()) {
            desc = new Traduccion();
            desc.setIdioma(archivo.next());
            desc.setTexto(archivo.next());
            descripciones.add(desc);
        }
        stock = archivo.nextInt();
        
        
    }

    @Override
    public void imprimir() {
        System.out.println(codigo + ": " + obtenerNombre("ES"));
        System.out.println(obtenerDescripcion("ES"));
        System.out.println("Precio: S/ " + String.format("%.2f", precio));
        System.out.println("Disponile: " + (stock > 0 ? "Sí" : "No"));
    }
    
    public String obtenerNombre(String idioma){
        for (Traduccion nombre : nombres) {
            if(nombre.getIdioma().equals(idioma)){ //Si el idioma del nombre es igual lo retorna
                return nombre.getTexto();
            }
        }
        return nombres.get(0).getTexto(); //Si no, retorna el primer idioma
    }
    public String obtenerDescripcion(String idioma){
        for (Traduccion descripcion : descripciones) { //Si el idioma de la descripcion es igual lo retorna
            if(descripcion.getIdioma().equals(idioma)){
                return descripcion.getTexto();
            }
        }
        return descripciones.get(0).getTexto(); //Si no, retorna el primer idioma
    }
    public void imprimir(Alumno alumno, Pais pais){
        System.out.println(codigo + ": " + obtenerNombre(pais.getIdioma()));
        System.out.println(obtenerDescripcion(pais.getIdioma()));
        System.out.println("Precio: " + pais.getMoneda() + " " + String.format("%.2f", alumno.calcularPrecio(this, pais.getTipoCambio())));
        System.out.println("Disponile: " + (stock > 0 ? "Sí" : "No"));
    }
    
}
