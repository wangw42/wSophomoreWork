package chatting;

import java.io.*;
import java.net.*;

public class Client {
    Socket socket = null;

    public Client(int port) {
        try {
            socket = new Socket("127.0.0.1", port);
            new ClientThread().start();
            System.out.println("Client->java Client");

            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            String msg1;
            while ((msg1 = br.readLine()) != null) {
                System.out.println(msg1);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    class ClientThread extends Thread {

        public void run() {
            try {
                BufferedReader re = new BufferedReader(new InputStreamReader(System.in));
                PrintWriter pw = new PrintWriter(socket.getOutputStream(), true);
                String msg2;
                while (true) {
                    msg2 = re.readLine();
                    pw.println(msg2);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }


        }
    }

    public static void main(String[] args) {
        new Client(8000);
    }

}