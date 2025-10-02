package pe.edu.pucp.gamesoft.main;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import pe.edu.pucp.gamesoft.model.Clasificacion;
import pe.edu.pucp.gamesoft.model.Videojuego;
import pe.edu.pucp.generic.utils.ObjectFileWriter;
import java.util.Date;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;


public class Principal {
    public static void main(String[] args){
        // Creamos una lista de videojuegos
        ArrayList<Videojuego> lista = new ArrayList<>();

        //Creamos un SimpleDateForma para manejo de fechas
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");

        //Creamos las fechas
        Date fechaLazv1 = null;
        Date fechaLazv2 = null;
        Date fechaLazv3 = null;
        try{
        fechaLazv1 = sdf.parse("2017-02-03");
        fechaLazv2 = sdf.parse("2017-03-28");
        fechaLazv3 = sdf.parse("2020-05-19");
        }catch(ParseException ex){
            System.out.println("ERROR: " + ex.getMessage());
        }

        // Creamos algunos objetos videojuego
        Videojuego v1 = new Videojuego("Zelda: Breath of the Wild", fechaLazv1,
       Clasificacion.Teen, 59.99, false, 1);
        Videojuego v2 = new Videojuego("Mario Kart 8 Deluxe", fechaLazv2, Clasificacion.Everyone, 49.99, true, 4);
        Videojuego v3 = new Videojuego("The Last of Us Part II", fechaLazv3, Clasificacion.Mature, 69.99, false, 1);

        // Agregamos a la lista
        lista.add(v1);
        lista.add(v2);
        lista.add(v3);
        // Creamos escritor y guardamos en archivo
        ObjectFileWriter writer = new ObjectFileWriter();
        writer.guardarVideojuegosEnArchivoTXT("T:\\", "videojuegos.txt", lista);
        guardarVideojuegosEnBD(lista);
        
    }
    public static void guardarVideojuegosEnBD(ArrayList<Videojuego> listaVideojuegos) {
            String URL = "jdbc:mysql://labs-2025-2-prog3.czq4skuyco6z.us-east-1.rds.amazonaws.com:3306/laboratorio4";
            String USER = "root";
            String PASSWORD = "prog31inf30";
            String sql = "INSERT INTO videojuego (titulo, fecha_lanzamiento, clasificacion, precio, es_multijugador, numero_max_jugadores) VALUES (?, ?, ?, ?, ?, ?)";
            try (Connection conn = DriverManager.getConnection(URL, USER, PASSWORD)) {
                PreparedStatement ps = conn.prepareStatement(sql);
                for (Videojuego vj : listaVideojuegos) {
                    ps.setString(1, vj.getTitulo());
                    // Convertimos de java.util.Date a java.sql.Date
                    if (vj.getFechaLanzamiento() != null) {
                        ps.setDate(2, new java.sql.Date(vj.getFechaLanzamiento().getTime()));
                    } else {
                        ps.setDate(2, null);
                    }
                    ps.setString(3, vj.getClasificacion().toString());
                    ps.setDouble(4, vj.getPrecio());
                    ps.setBoolean(5, vj.isEsMultijugador());
                    ps.setInt(6, vj.getNumeroMaxJugadores());
                    
                    ps.executeUpdate();
                }
                System.out.println("Videojuegos guardados en la BD correctamente.");
            } catch (SQLException e) {
            System.err.println("Error al guardar en BD: " + e.getMessage());
        }
    }
    
}