package com.mycompany.dao;

import java.util.ArrayList;
import com.mycompany.benchelemodel.ReportesStocksDTO;

public interface ReporteStockDAO {

    public ArrayList<ReportesStocksDTO> listarPorPeriodo(Integer año, Integer mes, Integer almacenId, Integer productoId);

    public void insertarDatosParaPrueba();

    public void eliminarDatosParaPrueba();

    public void generarReporteStock(Integer año, Integer mes);
}
