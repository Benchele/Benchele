import java.util.Scanner;

/**
 *
 * @author erichuiza
 */
public class Propietario extends Registro {
    private int dni;
    private String nombres;
    private String apellidos;
    private String direccion;
    
    public int getDni() {
        return dni;
    }
    public void setDni(int dni){
        this.dni = dni;
    }
    
    @Override
    public boolean cargarDatos(Scanner scanner) {
        // TODO: Implementar la lógica para cargar los datos del propietario desde el scanner
        if(!(scanner.hasNextInt()))return false;
        dni = scanner.nextInt();
        nombres = scanner.next();
        apellidos = scanner.next();
        direccion = scanner.next();
        return true;
    }

    @Override
    public String toString() {
        String resultado = "";
        resultado += String.format("║ DNI: %-45d ║\n", dni);
        resultado += String.format("║ Nombres: %-41s ║\n", nombres);
        resultado += String.format("║ Apellidos: %-39s ║\n", apellidos);
        resultado += String.format("║ Dirección: %-39s ║\n", direccion);
        return resultado;
    }
    
    @Override
    public void imprimir() {
        // TODO: Implementar la lógica para imprimir los datos del propietario
        System.out.printf("DNI: %10d \nNombre: %s\nApellidos: %s\nDireccion: %s\n", dni, nombres, apellidos, direccion);
        //System.out.println(toString()); //Asi se llama pero mejor use la mia xd
    }
}
