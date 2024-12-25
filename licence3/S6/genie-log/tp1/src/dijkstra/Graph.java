package dijkstra;
 
import java.util.ArrayList;
import java.util.Iterator;
import java.util.PriorityQueue;
 
public class Graph {
    private int vCount;
    private PriorityQueue<Edge>[] adj;
    private String type;
 
    public int getvCount() {
        return vCount;
    }
 
    public Graph(int vCount, String type) {
        this.vCount = vCount;
        // initialize adj
        adj = new PriorityQueue[vCount];
        for (int i = 0; i < vCount; i++) {
            adj[i] = new PriorityQueue<Edge>();
        }
        this.type = type;
    }
 
    public void addEdge(int i, int j, float weight) {
    	adj[i].add(new Edge(i, j, weight));
    	if (this.type == "u") {
    		adj[j].add(new Edge(j, i, weight));
//    		System.out.println("Undirected graph - added Edge from " + j + " to " + i);
		}
    }
 
    public void addEdge(Edge e) {
        adj[e.getStartPoint()].add(e);
    }
 
    public void removeEdge(int i, int j) {
        Iterator<Edge> it = adj[i].iterator();
        Edge other = new Edge(i, j, 0);
        while (it.hasNext()) {
            if (it.next().equals(other)) {
                it.remove();
                return;
            }
        }
    }
 
    public boolean hasEdge(Edge e) {
        return adj[e.getStartPoint()].contains(e);
    }
 
    public PriorityQueue<Edge> neighbours(int vertex) {
        return adj[vertex];
    }
 
    public void printGraph() {
        for (int i = 0; i < vCount; i++) {
            PriorityQueue<Edge> edges = neighbours(i);
            Iterator<Edge> it = edges.iterator();
            System.out.print(i + ": ");
            for (int j = 0; j < edges.size(); j++) {
                System.out.print(it.next() + " ");
            }
            System.out.println();
        }
    }
    
    public ArrayList<String> Dijkstra(int startVertex) { // Graph g, 
    	//    		Graph g = self;
    	
        // for storing distances after removing vertex from Queue
        float[] distances = new float[this.getvCount()];
        // for storing father id's after removing vertex from Queue
        int[] parents = new int[this.getvCount()];
        for (int i = 0; i < this.getvCount(); i++) {
            parents[i] = -1;
        }
 
        // set up vertex queue
        PriorityQueue<Vertex> Q = new PriorityQueue<Vertex>();
        for (int i = 0; i < this.getvCount(); i++) {
            if (i != startVertex) {
                Q.add(new Vertex(i));
            }
        }
 
        // add startVertex
        Vertex node = new Vertex(startVertex);
        node.setDistance(0);
        Q.add(node);
 
        // loop through all vertices
        while (!Q.isEmpty()) {
            // get vertex with shortest distance
            Vertex u = Q.remove();
            distances[u.getId()] = u.getDistance();
 
            // iterate through all neighbours
            Iterator<Edge> it = this.neighbours(u.getId()).iterator();
            while (it.hasNext()) {
                Edge e = it.next();
                Iterator<Vertex> it2 = Q.iterator();
                while (it2.hasNext()) {
                    Vertex v = it2.next();
                    // check if vertex was visited already
                    if (e.getEndPoint() != v.getId()) {
                        continue;
                    }
                    // check distance 
                    if (v.getDistance() > u.getDistance() + e.getWeight()) {
                        v.setDistance(u.getDistance() + e.getWeight());
                        v.setParent(u);
                        parents[v.getId()] = v.getParent().getId();
                    }
                }
            }
 
        }
        
        // return final shortest paths
        ArrayList<String> sol = new ArrayList<>(); 
        for (int i = 0; i < this.getvCount(); i++) {
        	String line = i + " " + distances[i] + " " + parents[i];
        	sol.add(line);
        }
        return sol;
 
    }
}