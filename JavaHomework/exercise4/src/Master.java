public class Master{
        public  void master(){
            Info info = new Info();

            Producer producer = new Producer(info);
            Customer customer = new Customer(info);

            Thread t1 = new Thread(producer);
            Thread t2 = new Thread(customer);

            t1.start();
            t2.start();
        }
}

class Info{
    boolean flag = true;
    String message = "";
    int item = 1;
    int time = 1;
}



/*

public class Master {

    public void master(){
        Info info = new Info();
        Producer producer = new Producer(info);
        Customer customer = new Customer(info);

        Thread proThread = new Thread(producer);
        Thread curThread = new Thread(customer);

        proThread.start();
        curThread.start();
    }
}

class Info{
    int i = 1;
    int k = 1;
    String message = "";
    boolean flag = true;
}
*/