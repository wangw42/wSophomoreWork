
public class Customer implements Runnable {

    private Info info;

    public Customer(Info info) {
        this.info = info;
    }

    @Override
    public void run() {
        while(info.time < 11){
            synchronized (info){
                if(info.flag){
                    try{
                        info.wait();
                    }catch (InterruptedException e){
                        e.printStackTrace();
                    }

                }else{
                    if(info.item % 2 == 1){
                        System.out.println("Get "+ info.item + "-> Item1 : " + info.message);
                    }else{
                        System.out.println("Get "+ info.item + "-> Item2 : " + info.message);
                    }
                    info.time++;
                    info.item++;
                    info.flag = true;
                    info.notify();
                }
            }
        }
    }

    /*
    @Override
    public void run() {
        while (info.i < 11){
            synchronized (info){
                if(info.flag){
                    try{
                        info.wait();
                    }catch (InterruptedException e){
                        e.printStackTrace();
                    }

                } else {
                    if(info.k % 2 == 1){
                        System.out.println("Get "+ info.i + "-> Item1 : " + info.message);
                    } else {
                        System.out.println("Get "+ info.i + "-> Item2 : " + info.message);
                    }
                    info.k++;
                    info.i++;
                    info.flag = true;
                    info.notify();
                }
            }
        }
    }

 */
}
