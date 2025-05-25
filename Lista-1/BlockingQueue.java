import java.util.LinkedList;
import java.util.Queue;

// Exercicio 4.1

public class BlockingQueue<T> {
    private final Queue<T> queue = new LinkedList<>();
    private final int maxSize = 3;

    public synchronized void put(T item) throws InterruptedException {
        if(queue.size() == maxSize) // bloqueia se cheio
            wait();
        queue.add(item);
        notifyAll();
    }
    
    public synchronized T take() throws InterruptedException {
        if(queue.isEmpty()) // bloqueia se vazio
            wait();
        T item = queue.poll();
        notifyAll();
        return item;
    }

    public static void main(String[] args) {
        BlockingQueue<Integer> fila = new BlockingQueue<>();

        Thread produtor = new Thread(() -> {
            for(int i = 0; i < 10; i++) {
                try {
                    fila.put(i);
                }
                catch(InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        Thread consumidor = new Thread(() -> {
            for(int i = 0; i < 10; i++) {
                try {
                    int item = fila.take();
                    System.err.println("Consumido: " + item);
                }
                catch(InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        produtor.start();
        consumidor.start();

        try {
            produtor.join();
            consumidor.join();
        }
        catch(InterruptedException e) {
            e.printStackTrace();
        }

    }
}
