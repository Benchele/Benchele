
package com.mycompany.dao;

import com.mycompany.benchelemodel.TiposDocumentosDTO;

public interface TipoDocumentoDAO {
    
    public Integer insertar(TiposDocumentosDTO tipoDocumento);
    
    public Integer eliminar(TiposDocumentosDTO tipoDocumento);
    
}
