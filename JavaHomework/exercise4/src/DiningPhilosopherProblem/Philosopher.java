package DiningPhilosopherProblem;

public class Philosopher implements Runnable{

    private Object leftFork;
    private Object rightFork;

    public Philosopher(Object leftFork, Object rightFork){
        this.leftFork = leftFork;
        this.rightFork = rightFork;
    }

    private void Action(String action) throws InterruptedException{
        System.out.println(Thread.currentThread().getName() + " " + action);
        Thread.sleep((int)(Math.random()*1000));
    }

    @Override
    public void run() {
        try {
            while (true){
                Action(": Thinking.");
                synchronized (leftFork){
                    Action( ": Pick up left fork.");
                    synchronized (rightFork){
                        Action(": Pick up right fork, stop thinkng and start eating.");
                        Action(": Put down right fork.");
                    }
                    Action(": Put down left fork, stop eating and back to thinking.");
                }
            }
        }catch (InterruptedException e){
            e.printStackTrace();
            Thread.currentThread().interrupt();
            return;
        }
    }
}
