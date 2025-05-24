import java.util.LinkedList;
import java.util.Queue;

// Exercicio 4.1

public class BlockingQueue<T> {
    private final Queue<T> queue = new LinkedList<>();
    private final int maxSize = 3;

    public synchronized void put(T item) throws InterruptedException {
        while(queue.size() == maxSize)
            wait();
        System.err.println("put");
        queue.add(item);
    }
    
    public synchronized T take() throws InterruptedException {
        while(queue.isEmpty())
            wait();
        System.err.println("take");
        T item = queue.poll();
        notifyAll();
        return item;
    }

    public static void main(String[] args) {
        BlockingQueue<Integer> fila = new BlockingQueue<>();

        System.err.println("Fila criada");

        try{
            for(int i = 0; i < 10; i++) {
                fila.put(i);
                Integer item = fila.take();
                System.err.println("Consumido: " + item);
            }
        }
        catch(InterruptedException e) {
            System.err.println("Erro em inserir item");
        }
        finally {}

    }
}
