import java.util.LinkedList;
import java.util.Queue;

// Exercicio 5.4

// quando há múltiplos consumidores, alguns threads ficam em starvation porque quando adiciona um item à fila
// apenas 1 thread é notificada(pela função notify()), a forma correta de se implementar é utilizando a função notifyAll()

public class Fila {
    private Queue<Integer> fila = new LinkedList<>();
    
    public synchronized void adicionar(int item) {
        fila.add(item);
        notifyAll(); // previamente notify()
    }
    
    public synchronized int remover() throws InterruptedException {
        while (fila.isEmpty()) {
           wait();
        }
        return fila.poll();
    }
}
