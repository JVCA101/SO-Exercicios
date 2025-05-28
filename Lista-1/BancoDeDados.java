// Exercicio 5.7

public class BancoDeDados {
    private int leitores = 0;
    private int escritores = 0;
    
    public synchronized void iniciarLeitura() throws InterruptedException {
        while(escritores > 0)
            wait();
        leitores++;
    }
    
    public synchronized void terminarLeitura() {
        leitores--;
        if(leitores == 0)
            notifyAll();
    }
    
    public synchronized void iniciarEscrita() throws InterruptedException {
        escritores++;
        while(leitores > 0)
            wait();
    }
    
    public synchronized void terminarEscrita() {
        escritores--;
        notifyAll();
    }
}
