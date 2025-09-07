import java.io.FileNotFoundException;

public class Principal {
    public static void main(String[] args) throws FileNotFoundException {
        //Paises de origen
            //TIPO NOMBRE MONEDA TIPOCAMBIO IDIOMA
        //Datos especificos estudaintes
            //TIPO CODIGO NOMBRE ESPECIALIDAD FACULTAD PAISORIG IDIOMAS
            //REGULAR            ESPECIALIDAD FACULTAD
            //INTERCAMBIO        PAISORIGEN   IDIOMAS SEMESTRES
        //Productos disponibles
            //TIPO  CODIGO TRADUCCIONNOMB PRECIO TRADUCCIONDESC STOCK
            //Bebida                                                    TIPOBEB
            //Helado                                                    CANTTOPPINGS  TOPPINGS

        Cafeteria cafeteria = new Cafeteria("datos.txt");
        cafeteria.cargarPaises();
        //cafeteria.imprimirPaises();
        
        cafeteria.cargarParticipantes();
        cafeteria.imprimirParticipantes();
        
        cafeteria.cargarMenu();
        cafeteria.imprimirMenuPredeterminado();
        cafeteria.imprimirMenusPersonalizados();
    }
}