/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.bencheletest;

import com.mycompany.bencheledbmanager.DBManager;
import java.sql.Connection;
import static org.junit.jupiter.api.Assertions.*;

/**
 *
 * @author Lenovo
 */
public class DBManagerTest {
    @org.junit.jupiter.api.Test
    public void testGetInstance() {
        System.out.println("getInstance");                
        DBManager dBManager = DBManager.getInstance();
        assertNotNull(dBManager);
    }
    
    @org.junit.jupiter.api.Test
    public void testGetConnection() {
        System.out.println("getConnection");                
        DBManager dBManager = DBManager.getInstance();
        Connection conexion = dBManager.getConnection();
        assertNotNull(conexion);
    }
}
