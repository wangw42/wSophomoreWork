public class Producer implements Runnable {

    private Info info;

    public Producer(Info info) {
        this.info = info;
    }

    @Override
    public void run() {
        while( info.time < 11){
            synchronized (info){
                if(!info.flag){
                    try {
                        info.wait();
                    }catch (InterruptedException e){
                        e.printStackTrace();
                    }
                }else{
                    int i;
                    if(info.item % 2 == 1){
                        info.message = "12345";
                        i = info.item%2;
                    }else{
                        info.message = "abcde";
                        i = info.item%2 +2;
                    }
                    System.out.println("Set "+ info.item + "-> Item" + i +" : "+ info.message);
                    info.flag = false;
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
                if(!info.flag){
                    try{
                        info.wait();
                    }catch (InterruptedException e){
                        e.printStackTrace();
                    }

                } else{

                    int i;
                    if(info.k % 2 == 1){
                        info.message = "12345";
                        i = info.k % 2;
                    } else {
                        info.message = "abcde";
                        i = info.k % 2 + 2;
                    }
                    System.out.println("Set "+ info.i + "-> Item" + i +" : "+ info.message);
                    info.flag = false;
                    info.notify();
                }
            }
        }
    }
    */

}
