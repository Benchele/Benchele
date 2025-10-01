package com.mycompany.dao;

import java.util.ArrayList;
import com.mycompany.benchelemodel.AlmacenesDTO;

public interface AlmacenDAO {
    
    public Integer insertar(AlmacenesDTO almacen);
    
    public AlmacenesDTO obtenerPorId(Integer almacenId);
    
    public ArrayList<AlmacenesDTO> listarTodos();
    
    public Integer modificar(AlmacenesDTO almacen);
    
    public Integer eliminar(AlmacenesDTO almacen);
    
    public ArrayList<AlmacenesDTO> listarTodosPorProcedure();
}
