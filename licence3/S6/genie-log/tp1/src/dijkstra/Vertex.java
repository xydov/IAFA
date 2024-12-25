package dijkstra;
 
public class Vertex implements Comparable{
    private int id;
    private float distance;
    private Vertex parent;
    
    public Vertex(){
        distance = Float.MAX_VALUE; // "infinity"
        parent = null;  
    }
    
    public Vertex(int id){
        this.id = id;
        distance = Float.MAX_VALUE; // "infinity"
        parent = null;  
    }
 
    public int getId() {
        return id;
    }
 
    public void setId(int id) {
        this.id = id;
    }
 
    public float getDistance() {
        return distance;
    }
    
    public void setDistance(float distance) {
        this.distance = distance;
    }
    
    public Vertex getParent() {
        return parent;
    }
    
    public void setParent(Vertex parent){
        this.parent = parent;
    }
    
    public int compareTo(Object o) {
        Vertex other = (Vertex) o;
        return Double.compare(this.distance, other.distance);
    }
}