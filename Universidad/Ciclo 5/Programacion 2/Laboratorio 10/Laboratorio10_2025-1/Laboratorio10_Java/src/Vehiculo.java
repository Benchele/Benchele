import java.util.Scanner;

/**
 *
 * @author erichuiza
 */
public class Vehiculo extends Registro {
    private String placa;
    private String marca;
    private String modelo;
    private int anhoFab;
    private String categoria;
    private Propietario propietario;
    public Vehiculo(){
        propietario = new Propietario();
    }
    public Propietario getPropietario() {
        return this.propietario;
    }
    
    public void setPropietario(final Propietario propietario) {
        this.propietario = propietario;
    }
    
    public String getPlaca() {
        return placa;
    }

    
    public String getCategoria() {
        return categoria;
    }
    
    @Override
    public boolean cargarDatos(Scanner scanner) {
        // TODO: Implementar la lógica para cargar los datos del vehículo desde el scanner
        placa = scanner.next();
        if(placa.compareTo("FIN") == 0)return false;
        marca = scanner.next();
        modelo = scanner.next();
        anhoFab = scanner.nextInt();
        categoria = scanner.next();
        int dni = scanner.nextInt();
        propietario.setDni(dni);
        
        return true;
    }

    @Override
    public String toString() {
        String resultado = "";
        resultado += String.format("║ Placa: %-43s ║\n", placa);
        resultado += String.format("║ Marca: %-43s ║\n", marca);
        resultado += String.format("║ Modelo: %-42s ║\n", modelo);
        resultado += String.format("║ Año de Fabricación: %-30d ║\n", anhoFab);
        resultado += String.format("║ Categoría: %-39s ║\n", categoria);
        return resultado;
    }
    
    @Override
    public void imprimir() {
        // TODO: Implementar la lógica para imprimir los datos del vehículo
        System.out.printf("Placa: %s\nMarca: %s\nModelo:%s\nAño de Fabricacion:%d\nCategoria:%s\n", placa, marca, modelo, anhoFab, categoria);
        //System.out.println(toString()); //Asi se llama pero mejor use la mia xd
    }
}
