/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.benchelebusiness;

import com.mycompany.benchelemodel.TiposDocumentosDTO;
import com.mycompany.dao.TipoDocumentoDAO;
import com.mycompany.daoImpl.TipoDocumentoDAOImpl;

/**
 *
 * @author Lenovo
 */
public class TipoDocumentoBO {
    private TipoDocumentoDAO tipoDocumentoDAO;
    
    public TipoDocumentoBO(){
        this.tipoDocumentoDAO = new TipoDocumentoDAOImpl();
    }
    
    public Integer insertar(Integer tipoDocumentoId, String nombre){
        TiposDocumentosDTO tipoDocumentoDTO = new TiposDocumentosDTO();
        tipoDocumentoDTO.setTipoDocumentoId(tipoDocumentoId);
        tipoDocumentoDTO.setNombre(nombre);
        return this.tipoDocumentoDAO.insertar(tipoDocumentoDTO);
    }
    
    public Integer eliminar(Integer tipoDocumentoId){
        TiposDocumentosDTO tipoDocumentoDTO = new TiposDocumentosDTO();
        tipoDocumentoDTO.setTipoDocumentoId(tipoDocumentoId);        
        return this.tipoDocumentoDAO.eliminar(tipoDocumentoDTO);
    }
}
