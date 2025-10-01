/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit5TestClass.java to edit this template
 */
package com.mycompany.bencheledbmanager;

import java.sql.Connection;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 *
 * @author Lenovo
 */
public class DBManagerTest {
    
    public DBManagerTest() {
    }

    /**
     * Test of getInstance method, of class DBManager.
     */
    @Test
    public void testGetInstance() {
        System.out.println("getInstance");
        DBManager expResult = null;
        DBManager result = DBManager.getInstance();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of getConnection method, of class DBManager.
     */
    @Test
    public void testGetConnection() {
        System.out.println("getConnection");
        DBManager instance = null;
        Connection expResult = null;
        Connection result = instance.getConnection();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }
    
}
