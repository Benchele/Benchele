import java.io.IOException;

/*
    Codigo: 20232242
    Nombre: Benjhamin Ruiz
*/

public class Principal {
    public static void main(String[] args) throws IOException {
        AutoridadTransporte atu = new AutoridadTransporte("datos.txt");
        atu.cargarDatos();
        atu.procesarCapturas();
        atu.imprimirInfracciones();
    }
}
