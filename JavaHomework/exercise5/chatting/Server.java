package chatting;

import java.net.*;
import java.io.*;
import java.util.*;

public class Server {
    List<Socket> clients;
    ServerSocket server;

    public Server() {
        try {
            server = new ServerSocket(8000);
            clients = new ArrayList<Socket>();
            System.out.println("Server->java Server");
            System.out.println("Initializing Port...");
            System.out.println("Listening...");

            while (true) {
                Socket socket = server.accept();
                clients.add(socket);
                ServerThread t = new ServerThread(socket);
                t.start();
                System.out.println("Connet to client!");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    class ServerThread extends Thread {
        Socket sk;
        private BufferedReader br;
        private PrintWriter pw;
        public String msg;

        public ServerThread(Socket s) {
            sk = s;
        }

        public void run() {
            try {
                br = new BufferedReader(new InputStreamReader(sk.getInputStream()));

                while ((msg = br.readLine()) != null) {
                    msg = "Receive: " + msg;
                    send();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        public void send() {
            try {
                for (int i = clients.size() - 1; i >= 0; i--) {
                    pw = new PrintWriter(clients.get(i).getOutputStream(), true);
                    pw.println(msg);
                    pw.flush();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        new Server();
    }

}
