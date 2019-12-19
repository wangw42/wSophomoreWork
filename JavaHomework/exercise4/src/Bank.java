import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Bank implements Runnable{
    private int a = 100;
    private int b = 0;
    private int c =0;
    Lock loc = new ReentrantLock();
    static boolean bool = true;


    public  void run(){

        for(int i = 1; i <= 20; i++){
            synchronized(this){
                notifyAll();
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                if(a < 2100){
                    a += 100;
                    if(Thread.currentThread().getName().equals("B")){
                        b += 100;
                        System.out.println("account B transfer $100 to account A, balance of account A: $" + a);
                    }else{
                        c += 100;
                        System.out.println("account C transfer $100 to account A, balance of account A: $" + a);
                    }

                    try {
                        wait();
                    } catch (InterruptedException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    }


                }else{
                    System.out.println("account B transfer $"+ b + " to account A in total");
                    System.out.println("account C transfer $"+ c + " to account A in total");
                    System.out.println("balance of account A: $" + a);
                    System.exit(0);
                }
            }
        }
    }

    public void bank(){
        Bank b = new Bank();
        System.out.println("balance of account A: $" + b.a);
        Thread t1 = new Thread(b,"B");
        Thread t2 = new Thread(b,"C");
        t1.start();
        t2.start();

    }
}
