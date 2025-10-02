package pe.edu.pucp.gamesoft.model;
import java.util.Date;
public class Videojuego{
	private static int correlativo = 1;
	private int idVideojuego;
	private String titulo;
	private Date fechaLanzamiento;
	private Clasificacion clasificacion;
	private double precio;
	private boolean esMultijugador;
	private int numeroMaxJugadores;
	
	public Videojuego(){}
	public Videojuego(int idVideojuego, String titulo, Date fechaLanzamiento, Clasificacion clasificacion, double precio, boolean esMultijugador, int numeroMaxJugadores){
		this.idVideojuego = idVideojuego;
		this.titulo = titulo;
		this.fechaLanzamiento = fechaLanzamiento;
		this.clasificacion = clasificacion;
		this.precio = precio;
		this.esMultijugador = esMultijugador;
		this.numeroMaxJugadores = numeroMaxJugadores;
	}
	public Videojuego(String titulo, Date fechaLanzamiento,Clasificacion clasificacion, double precio, boolean esMultijugador, int numeroMaxJugadores){
		this.idVideojuego = correlativo;
		this.titulo = titulo;
		this.fechaLanzamiento = fechaLanzamiento;
		this.clasificacion = clasificacion;
		this.precio = precio;
		this.esMultijugador = esMultijugador;
		this.numeroMaxJugadores = numeroMaxJugadores;
		correlativo++;
	}
	
	public int getIdVideojuego(){
		return idVideojuego;
	}
	public void setIdVideojuego(int idVideojuego){
		this.idVideojuego = idVideojuego;
	}
	
	public String getTitulo(){
		return titulo;
	}
	public void setTitulo(String titulo){
		this.titulo = titulo;
	}
	
	public Date getFechaLanzamiento(){
		return fechaLanzamiento;
	}
	public void setFechaLanzamiento(Date fechaLanzamiento){
		this.fechaLanzamiento = fechaLanzamiento;
	}
	
	public Clasificacion getClasificacion(){
		return clasificacion;
	}
	public void setClasificacion(Clasificacion clasificacion){
		this.clasificacion = clasificacion;
	}
	
	public double getPrecio(){
		return precio;
	}
	public void setPrecio(double precio){
		this.precio = precio;
	}
	
	public boolean isEsMultijugador(){
		return esMultijugador;
	}
	public void setIsMultijugador(boolean esMultijugador){
		this.esMultijugador = esMultijugador;
	}
	
	public int getNumeroMaxJugadores(){
		return numeroMaxJugadores;
	}
	public void setNumeroMaxJugadores(int numeroMaxJugadores){
		this.numeroMaxJugadores = numeroMaxJugadores;
	}
}