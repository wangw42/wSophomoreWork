package trafficlight;

import javax.swing.JFrame;

public class TrafficLight extends JFrame {

    public static void main (String[] args) {
        JFrame frame = new JFrame("Traffic Light");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(150, 230);
        frame.add(new ControlPanel());
        frame.pack();
        frame.setVisible(true);
    }
}















