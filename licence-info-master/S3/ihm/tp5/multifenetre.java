/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package multifenetres;

import fr.ups.l2.ihm.Fenetre1;
import fr.ups.l2.ihm.Fenetre2;

/**
 *
 * @author martinie
 */
public class MultiFenetres {

    static Fenetre1 fenetre1 = new Fenetre1();
    static Fenetre2 fenetre2 = new Fenetre2();
    
   /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Fenetre1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Fenetre1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Fenetre1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Fenetre1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                fenetre1.setVisible(true);
            }
        });
    }
    
    public static void ouvrirFenetre1(){
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                fenetre1.setVisible(true);
                
            }
        });
    }
    
    public static void ouvrirFenetre2(){
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                fenetre2.setVisible(true);
            }
        });
    }
    
    public static void fermerFenetre1(){
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                fenetre1.setVisible(false);
                
            }
        });
    }
    
    public static void fermerFenetre2(){
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                fenetre2.setVisible(false);
            }
        });
    }
    
}
