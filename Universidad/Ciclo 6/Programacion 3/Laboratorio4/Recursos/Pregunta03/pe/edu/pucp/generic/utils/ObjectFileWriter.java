package pe.edu.pucp.generic.utils;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.text.SimpleDateFormat;

import pe.edu.pucp.gamesoft.model.Videojuego;

public class ObjectFileWriter{
	/**
	@param ruta: de la carpeta donde se almacenará el archivo. La carpeta debe existir.
    @param nombreArchivo: nombre del archivo con extension .txt
    @param listaVideojuegos Lista de videojuegos a guardar en ArrayList<Videojuego>.
    */
	
	public void guardarVideojuegosEnArchivoTXT(String ruta, String nombreArchivo, ArrayList<Videojuego> listaVideojuegos) {
		String filePath = ruta;
        if (!ruta.endsWith("/") && !ruta.endsWith("\\")) {
            filePath += System.getProperty("file.separator");
        }
        filePath += nombreArchivo;
		
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            for (Videojuego vj : listaVideojuegos) {
                writer.write("ID: " + vj.getIdVideojuego());
                writer.newLine();
                writer.write("Título: " + vj.getTitulo());
                writer.newLine();
                writer.write("Fecha de lanzamiento: " + (vj.getFechaLanzamiento() != null ? sdf.format(vj.getFechaLanzamiento()) : "N/A"));
                writer.newLine();
                writer.write("Clasificación: " + (vj.getClasificacion() != null ? vj.getClasificacion().toString() : "N/A"));
                writer.newLine();
                writer.write("Precio: " + vj.getPrecio());
                writer.newLine();
                writer.write("¿Es multijugador?: " + vj.isEsMultijugador());
                writer.newLine();
                writer.write("Número máximo de jugadores: " + vj.getNumeroMaxJugadores());
                writer.newLine();
                writer.write("--------------------------");
                writer.newLine();
            }
            System.out.println("✅ Archivo guardado en: " + filePath);
        } catch (IOException e) {
            System.err.println("❌ Error al guardar el archivo: " + e.getMessage());
        }
	}
}