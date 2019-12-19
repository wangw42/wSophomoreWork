package DiningPhilosopherProblem;


public class Main {

    public static void main(String[] args) {
        int N = 5;

        Philosopher[] philosophers = new Philosopher[N];

        Object[] forks = new Object[N];
        for(int i = 0; i < N; i++){
            forks[i] = new Object();
        }

        for(int i = 0; i < N; i++){
            Object leftFork = forks[i];
            Object rightFork = forks[(i+1) % N];

            //---------------------deadlock here---------------------
            //philosophers[i] = new Philosopher(leftFork, rightFork);

            //last philosopher pick up right fork first
            if(i == N - 1){
                philosophers[i] = new Philosopher(rightFork, leftFork);
            }else{
                philosophers[i] = new Philosopher(leftFork,rightFork);
            }

            Thread t = new Thread(philosophers[i], "Philosopher " + (i + 1) );
            t.start();
        }
    }

}

//ref: https://www.baeldung.com/java-dining-philoshophers
