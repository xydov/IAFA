package dijkstra;
 
import java.util.ArrayList;
import java.util.Iterator;
import java.util.PriorityQueue;
 
public class TestGraphs {
 
    public static void main(String[] args) {
    	Reader n = new Reader("test");
    	n.openAndTest();
    	
    	
        Graph g = new Graph(6, "u");
//        
//        System.out.println("Graph:");
//        // add Edges
        g.addEdge(0, 1, 5.2f);
        g.addEdge(0, 3, 12.8f);
        g.addEdge(0, 2, 10.3f);
        g.addEdge(1, 3, 5.9f);
        g.addEdge(1, 4, 15.2f);
        g.addEdge(2, 1, 1.5f);
        g.addEdge(2, 3, 2.3f);
        g.addEdge(3, 4, 8.5f);
        g.addEdge(4, 2, 2.7f);
//        
//        // G2
//        g.addEdge(0, 1, 2.0f);
//        g.addEdge(0, 4, 3.0f);    
//        g.addEdge(1, 2, 5.0f);
//        g.addEdge(1, 4, 4.0f);
//        g.addEdge(1, 5, 2.0f);
//        g.addEdge(2, 5, 4.0f);
//        g.addEdge(2, 3, 2.0f);
//        g.addEdge(3, 4, 2.0f);
//        g.addEdge(3, 5, 5.0f);
//        g.addEdge(4, 5, 2.0f);
//        
//        
//        // print Graph
//        g.printGraph();
//        g.Dijkstra(0);
    }
}