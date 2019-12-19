
package trafficlight;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class ControlPanel extends JPanel {

    private JButton Red;
    private JButton Yellow;
    private JButton Green;

    private TrafficLightPanel LightPanel;
    int click = 0;

    public ControlPanel() {

        setLayout(new BorderLayout());
        LightPanel = new TrafficLightPanel();

        Red = new JButton("R");
        Yellow = new JButton("Y");
        Green = new JButton("G");

        Red.addActionListener(new ControlPanel.ChangeListener(0));
        Yellow.addActionListener(new ControlPanel.ChangeListener(1));
        Green.addActionListener(new ControlPanel.ChangeListener(2));

        Red.setBounds(20, 190,30,30);
        Yellow.setBounds(60, 190,30,30);
        Green.setBounds(100, 190,30,30);

        add(Red);
        add(Yellow);
        add(Green);

        setPreferredSize(new Dimension(150,230));
        setBackground(Color.white);
        add(LightPanel, BorderLayout.CENTER);

    }

    private class ChangeListener implements ActionListener {
        int flag = 0;

        public ChangeListener(int f){
            this.flag = f;
        }



        public void actionPerformed(ActionEvent event) {
            LightPanel.change(flag);

        }
    }
}


