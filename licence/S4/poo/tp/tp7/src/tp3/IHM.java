package tp3;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.rmi.Naming;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.text.DateFormat;
import java.util.Date;
import java.util.Random;
import java.util.Vector;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

import tp3.serveur.Asteroide325;
import tp3.serveur.VueSujet;

public class IHM extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private static final int port=5099;	//port par defaut pour communiquer avec le serveur RMI
	
	private Image roiImg;
	private Image princeImg;
	enum State{INIT,PLAYING};
	private State state=State.INIT;
	private Remote server;
	private Thread connection=null;
	private boolean cnxError=false;
	
	private Vector<VueSujet> world=new Vector<VueSujet>();
	
	private class AsteroideJTextArea extends JTextArea {
		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;

		AsteroideJTextArea() {
			super("Connexion... ",10,10);
			setEditable(false);
		}
	}
	
	private class AsteroideJPanel extends JPanel {
		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;
		private JTextArea jta;
		AsteroideJPanel(JTextArea jta) {
			this.jta=jta;
		}
		
		public void paintComponent(Graphics g) {
			Rectangle rect=this.getBounds();
			
			if ((state==State.INIT) || (cnxError)) {
				//si on est entrain de se connecter ou qu'il y a une erreur
				Random r=new Random();
				g.drawImage(roiImg,r.nextInt(rect.width-280),r.nextInt(rect.height-220),null);
				g.drawImage(princeImg,r.nextInt(rect.width-220),r.nextInt(rect.height-220),null);
			
				Font of=g.getFont();
				g.setFont(new Font("Arial",Font.BOLD,20));
				if (!cnxError) g.drawString("Connexion en cours sur le serveur Asteroede 325...",20, rect.height-20);
				else g.drawString("Erreur de connexion !",20, rect.height-20);
				g.setFont(of);
				
				//verifie si la connexion a ete realisee - isAlive (Thread)==true si on est en cours de connexion
				if ((connection!=null) && (! connection.isAlive())) {
					if (!cnxError) jta.append("ok !"); else jta.append("erreur !");
					state=State.PLAYING;
					connection=null;
				}
			} else {
				//si on est connecte, on recupere le monde, et on l'affiche
				/*for(int i=0; i<100; i++)
					for (int j=0; j<100; j++)
						g.fillRect(i*rect.width/100,j*rect.height/100,1,1);*/
				
				try {
					world=((Asteroide325) server).getWorld();
					int ref,cx,cy;
					String dial;
					
					jta.setText("");
					for(VueSujet s:world) {
						ref=s.getRef();
						Random r=new Random(ref);
						g.setColor(new Color(r.nextInt(255), r.nextInt(255), r.nextInt(255), 200));
						cx=s.getX()*rect.width/100;
						cy=s.getY()*rect.height/100;
						g.fillOval(cx,cy,8,8);
						dial=(s.getPhrase()==null)?"":" : "+s.getPhrase();
						g.drawString("["+s.getRef()+"]"+"("+s.getArgent()+")",cx+10,cy);
						jta.append("["+s.getRef()+"]"+s.getNom()+"("+s.getArgent()+")"+dial+"\n");
					}
				} catch (RemoteException e) {
					//en cas de deconnexion ou erreur du serveur
					state=State.INIT;
					JOptionPane.showMessageDialog(this,"Erreur de connection !\nRaison : "+e.getMessage(),"Message",JOptionPane.ERROR_MESSAGE);
					cnxError=true;
				}
			}
			g.setColor(Color.BLACK);
			g.drawString(DateFormat.getTimeInstance().format(new Date()),rect.width-60,20);
		}
	}
	
	IHM() {
		Toolkit kit=Toolkit.getDefaultToolkit();
		roiImg=kit.getImage("roi.gif");
		princeImg=kit.getImage("petitprince.gif");
		setIconImage(roiImg);
		
		Dimension size=kit.getScreenSize();
		setSize(size.width/2, size.height/2);
		setLocation(size.width/4, size.height/4);
		//setResizable(false);
		
		setTitle("IHM - Asteroede 325 / UPS - TP L3 Java");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		Action exitAction=new AbstractAction("Quitter") {
			/**
			 * 
			 */
			private static final long serialVersionUID = 1L;

			public void actionPerformed(ActionEvent ae) {System.exit(0);}
		};
		
		Action aboutAction=new AbstractAction("A propos") {
			/**
			 * 
			 */
			private static final long serialVersionUID = 1L;

			public void actionPerformed(ActionEvent ae) {JOptionPane.showMessageDialog(null,"Asteroede 325\nUne serie de TP proposee par S. Leriche et J.-F Rolland\ninspiree de l'univers du Petit Prince de St Exupery\npour les TP de 'Concepts de programmation' L3/UPS\nContact : {nom}@irit.fr");}
		};
		
		//items et menus 	
		JMenuBar m=new JMenuBar();
		JMenu file=new JMenu("Fichier");
		file.add(aboutAction);
		file.add(exitAction);
		m.add(file);
		setJMenuBar(m);
				
		AsteroideJTextArea ajta=new AsteroideJTextArea();
		getContentPane().add(new AsteroideJPanel(ajta));
		setVisible(true);
		
		//nouvelle JFrame pour contenir la console, ainsi les etudiants peuvent la mettre e
		//la taille necessaire pour bien visualiser le deroulement de l'action
		JFrame jf=new JFrame();
		jf.setSize(size.width/4, size.height/4);
		jf.setLocation(size.width*3/5, size.height/10);
		jf.getContentPane().add(new JScrollPane(ajta));
		jf.setTitle("Asteroede325 - Console");
		jf.setIconImage(roiImg);
		jf.setVisible(true);
	}
	
	/**
	 * lance une connexion au serveur dans un thread separe
	 *
	 */
	private void connect() {
		connection=new Thread() {
			public void run() {try {server=Naming.lookup("rmi://localhost:"+port+"/Asteroide325");} catch (Exception e) {
					cnxError=true;
					JOptionPane.showMessageDialog(null,"Impossible de se connecter au serveur Asteroede:"+port+" !\n(le serveur ne doit pas etre actif...)\nRaison : "+e.getMessage(),"Message",JOptionPane.ERROR_MESSAGE);
				}
			}
		};
		connection.start();
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		IHM ihm=new IHM();
		ihm.connect();
		//boucle infine, interrompue par l'utilisateur (IHM)
		while(true) {
			try {Thread.sleep(1000);} catch (InterruptedException e) {}
			ihm.repaint(); 
		}
	}

}
