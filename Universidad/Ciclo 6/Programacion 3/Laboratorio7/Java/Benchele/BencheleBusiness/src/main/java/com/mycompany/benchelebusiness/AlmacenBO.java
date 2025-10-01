/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.benchelebusiness;

import com.mycompany.benchelemodel.AlmacenesDTO;
import com.mycompany.dao.AlmacenDAO;
import com.mycompany.daoImpl.AlmacenDAOImpl;
import java.util.ArrayList;

/**
 *
 * @author Lenovo
 */
public class AlmacenBO {
    private AlmacenDAO almacenDAO;
    
    public AlmacenBO(){
        this.almacenDAO = new AlmacenDAOImpl();
    }
    
    public Integer insertar(String nombre, Boolean almacen_central){
        AlmacenesDTO almacenesDTO = new AlmacenesDTO();
        almacenesDTO.setNombre(nombre);
        almacenesDTO.setAlmacen_central(almacen_central);
        return this.almacenDAO.insertar(almacenesDTO);
    }
    
    public AlmacenesDTO obtenerPorId(Integer almacenId){
        AlmacenesDTO almacenesDTO = new AlmacenesDTO();
        almacenesDTO.setAlmacenId(almacenId);
        return this.almacenDAO.obtenerPorId(almacenId);
    }
    
    public ArrayList<AlmacenesDTO> listarTodos(){
        return this.almacenDAO.listarTodos();
    }
    
    public Integer modificar(Integer almacenId, String nombre, Boolean almacen_central){
        AlmacenesDTO almacenesDTO = new AlmacenesDTO();
        almacenesDTO.setAlmacenId(almacenId);
        almacenesDTO.setNombre(nombre);
        almacenesDTO.setAlmacen_central(almacen_central);
        return this.almacenDAO.modificar(almacenesDTO);
    }
    
    public Integer eliminar(Integer almacenId){
        AlmacenesDTO almacenesDTO = new AlmacenesDTO();
        almacenesDTO.setAlmacenId(almacenId);
        return this.almacenDAO.eliminar(almacenesDTO);
    }
    
    public ArrayList<AlmacenesDTO> listarTodosConProcedure(){
        return this.almacenDAO.listarTodosPorProcedure();
    }
}
