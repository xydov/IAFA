package dijkstra;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;


public class Reader {
	private String filepath;
	
	public Reader(String fp) {
		this.filepath = fp;
	}
	
	public void openAndTest() {
		Graph g;
		boolean testPassed = true;
		File f = new File(filepath);
		try (Scanner f_scanner = new Scanner(f)){
			String data = f_scanner.nextLine();
			String[] parts = data.split(" ");
			if(parts[0].equals("#") && parts[1].equals("Start")) {
				// ============== Start while loop for multi graph tests
				// get name of the graph
				String g_name = f_scanner.nextLine().split(" ")[1];
				// get number of nodes 
				data = f_scanner.nextLine();
				int n_vertices = Integer.parseInt(data);
				// create graph
				g = new Graph(n_vertices, "d");
				// read all graph lines
				data = f_scanner.nextLine();
				String[] p = data.split(" ");
				p = data.split(" ");
				while( ! p[0].equals("#")) { 
					g.addEdge(Integer.parseInt(p[0]), Integer.parseInt(p[1]), Float.parseFloat(p[2]));
					data = f_scanner.nextLine();
					p = data.split(" ");
				}
				// check if name is ok
				parts = data.split(" ");
				if (!parts[0].equals("#") || !parts[1].equals("results") || !parts[2].equals(g_name)) {
					System.err.println("Error reading results, file is not in the right format");
					return;
				}
				// get source
				ArrayList<String> gottenList = g.Dijkstra(f_scanner.nextInt());
				f_scanner.nextLine(); // flush | _
				// read all awaited solutions
				ArrayList<String> awaitedList = new ArrayList<>();
				data = f_scanner.nextLine();
				while (! data.equals("# End")) {// !p[0].equals("#") && !p[1].equals("End")) {
					awaitedList.add(data);
					data = f_scanner.nextLine(); 
				}
				// check against computed sol
				testPassed  = awaitedList.equals(gottenList) && test(awaitedList, gottenList, g_name);
				
			} else {
				System.err.println("[Err] - File is not in the right format");
				return;
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		if (testPassed) {
			System.out.println("[Tests Report] Everything passed.");
		} else {
			System.out.println("[Tests Report] - Some tests did not passed");
		}
	}
	
	private boolean test(ArrayList<String> awaitedList, ArrayList<String> gottenList, String gName) {
		boolean ok = true;
		if (awaitedList.size() != gottenList.size()) {
			System.err.println("[Err] - the gotten result array is not the same size than the awaited one");
		}
		System.out.println("[Test] - Unit Test on graph: " + gName);
		for (int i = 0; i < awaitedList.size(); i++) {
			String a = awaitedList.get(i);
			String g = gottenList.get(i);
			if (a.equals(g)) {
				System.out.println("[Test " + (i + 1) +"] - PASS");
			} else {
				System.out.println("[Test " + (i + 1) +"] - FAIL !");
				ok = false;
			}
		}
		return ok;
	}
}
