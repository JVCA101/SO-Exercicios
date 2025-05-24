// imports
import java.util.LinkedList;
import java.util.Queue;

public class BlockingQueue<T> {
    private final Queue<T> queue = new LinkedList<>();
    private final int maxSize = 3;

    public synchronized void put(T item) throws InterruptedException {
        // Complete aqui
    }
    
    public synchronized T take() throws InterruptedException {
        // Complete aqui
    }
}
