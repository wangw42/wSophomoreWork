

public class SellTickets {

    public static void main(String[] args){
        Window window = new Window();
        window.window();
    }
}


class Window implements Runnable{

    int num = 20;

    @Override
    public void run(){
         while(true){
             synchronized (this){
                 if(num > 0) {
                     try {
                         Thread.sleep((int) Math.random() * 2000);
                     } catch (Exception e) {
                         e.printStackTrace();
                     }
                     System.out.println("Window " + Thread.currentThread().getName() + ": ticket " + (21-num));
                     num--;
                 }else {
                     System.out.println("Sold Out");
                     System.exit(0);
                 }

             }
         }
    }

    public void window(){
        Window window = new Window();
        Thread w1 = new Thread(window);
        w1.setName("1");
        Thread w2 = new Thread(window);
        w2.setName("2");
        Thread w3 = new Thread(window);
        w3.setName("3");

        w1.start();
        w2.start();
        w3.start();

    }

}
