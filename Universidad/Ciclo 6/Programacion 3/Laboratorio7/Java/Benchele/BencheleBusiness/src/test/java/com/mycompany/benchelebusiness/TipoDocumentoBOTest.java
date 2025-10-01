/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit5TestClass.java to edit this template
 */
package com.mycompany.benchelebusiness;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 *
 * @author Lenovo
 */
public class TipoDocumentoBOTest {
    
    private TipoDocumentoBO tipoDocumentoBO;
    
    public TipoDocumentoBOTest() {
        this.tipoDocumentoBO = new TipoDocumentoBO();
    }
    
    @Test
    public void testInsertar() {
        System.out.println("insertar");                
        Integer resultado = this.tipoDocumentoBO.insertar(1, "Orden de compra");
        assertTrue(resultado != 0);
                
        resultado = this.tipoDocumentoBO.insertar(2, "Guía de remisión");
        assertTrue(resultado != 0);
        
        resultado = this.tipoDocumentoBO.eliminar(1);
        assertTrue(resultado != 0);

        resultado = this.tipoDocumentoBO.eliminar(2);
        assertTrue(resultado != 0);
    }    
    
}
