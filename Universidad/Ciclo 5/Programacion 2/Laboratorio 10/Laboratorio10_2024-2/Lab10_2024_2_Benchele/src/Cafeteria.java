import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Cafeteria {
    private final List<Pais> paises;
    private final Scanner archivo;
    //TODO: agregar miembros faltantes
    private final ArrayList<Alumno> participantes;
    private Menu menu;
    
    public Cafeteria() {
        paises = new ArrayList<>();
        archivo = new Scanner(System.in);
        //TODO: inicializar miembros faltantes
        participantes = new ArrayList<>();
        menu = new Menu();
    }
    
    public Cafeteria(final String nombreArchivo) throws FileNotFoundException {
        archivo = new Scanner(new File(nombreArchivo));
        paises = new ArrayList<>();
        //TODO: inicializar miembros faltantes
        participantes = new ArrayList<>();
        menu = new Menu();
    }
    
    public void cargarPaises() {
        while (archivo.hasNext()) {
            char tipo = archivo.next().charAt(0);
            if (!(tipo == 'I' || tipo == 'N')) break;
            
            Pais pais = new Pais();
            pais.cargar(archivo);
            paises.add(pais);
        }
    }
    
    public void cargarParticipantes() {
        //TODO: cargar participantes
        String type;
        char tipo;
        Alumno alumno;
        while (archivo.hasNext()) {
            type = archivo.next();
            tipo = type.charAt(0);
            if(!(tipo == 'I' || tipo == 'R'))break;
            if(tipo == 'I'){
                alumno = new AlumnoIntercambio();
            }
            else{
                alumno = new AlumnoRegular();
            }
            alumno.cargar(archivo);
            participantes.add(alumno);
        }
    }
    
    public void cargarMenu() {
        //TODO: cargar menu
        menu.cargarProductos(archivo);
    }
    
    public void imprimirPaises() {
        System.out.println("==================LISTADO DE PAISES===================");
        System.out.println("------------------------------------------------------");
        System.out.println(String.format("%-15s\t%-10s\t%-10s\t%-10s", "NOMBRE", "MONEDA", "TIPO-CAMBIO", "IDIOMA"));
        System.out.println("------------------------------------------------------");
        for (Pais pais : paises) {
            pais.imprimir();
        }
        System.out.println("======================================================");
        System.out.println();
    }
    
    public void imprimirParticipantes() {
        //TODO: cargar participantes
        System.out.println("====================================================================================LISTADO DE PARTICIPANTES=================================================================================");
        System.out.println("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
        System.out.println(String.format("%-10s\t%-35s\t%-15s\t%-30s\t%-15s\t%-50s\t%-15s", "CÓDIGO", "NOMBRE", "FACULTAD", "ESPECIALIDAD", "PAÍS", "IDIOMAS", "DURACIÓN"));
        System.out.println("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
        for (Alumno participante : participantes) {
            participante.imprimir();
        }
        System.out.println("=============================================================================================================================================================================================");
        System.out.println();
    }
    
    public void imprimirMenuPredeterminado() {
        //TODO: imprimir menu predeterminado
        menu.imprimirMenu();
        System.out.println();
    }
    
    public void imprimirMenusPersonalizados() {
        //TODO: imprimir menús personalizados
        Pais pais;
        for (Alumno participante : participantes) {
            pais = buscarPais(participante.getPaisOrigen());
            menu.imprimirMenuPersonalizado(participante, pais);
            System.out.println();
        }
    }
    
    private Pais buscarPais(String nombre) {
        for (Pais pais : paises) {
            if (pais.getNombre().equals(nombre)) {
                return pais;
            }
        }
        
        return paises.get(0);
    }
}