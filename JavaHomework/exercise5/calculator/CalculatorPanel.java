package calculator;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class CalculatorPanel extends JPanel {
    private JButton display;

    private double result;
    private String preResult;
    private boolean start;

    protected void makebutton(String name, GridBagLayout gridbag, GridBagConstraints c, ActionListener listener){
        Button button = new Button(name);
        button.addActionListener(listener);
        gridbag.setConstraints(button, c);
        add(button);
    }

    public CalculatorPanel() {

        setLayout(new BorderLayout());

        result = 0;
        preResult = "=";
        start = true;

        ActionListener insert = new insertNumber();
        ActionListener command = new insertCommand();

        GridBagLayout gridbag = new GridBagLayout();
        GridBagConstraints c = new GridBagConstraints();

        setFont(new Font("SansSerif", Font.PLAIN, 14));
        setLayout(gridbag);

        c.fill = GridBagConstraints.BOTH;
        c.weightx = 1.0;

        c.gridx = 0;
        c.gridwidth = 5;
        display = new JButton("0");
        display.setEnabled(false);
        gridbag.setConstraints(display, c);
        add(display);

        c.gridwidth = 1;
        c.gridy = 1;
        c.gridx = 0;
        makebutton("MC", gridbag, c, command); c.gridx++;
        makebutton("MR", gridbag, c, command); c.gridx++;
        makebutton("MS", gridbag, c, command); c.gridx++;
        makebutton("M+", gridbag, c, command); c.gridx++;
        makebutton("M-", gridbag, c, command); c.gridx++;

        c.gridy = 2;
        c.gridx = 0;
        makebutton("<-", gridbag, c, command); c.gridx++;
        makebutton("CE", gridbag, c, command); c.gridx++;
        makebutton("C", gridbag, c, command); c.gridx++;
        makebutton("+-", gridbag, c, command); c.gridx++;
        makebutton("√", gridbag, c, command); c.gridx++;

        c.gridy = 3;
        c.gridx = 0;
        makebutton("7", gridbag, c, insert); c.gridx++;
        makebutton("8", gridbag, c, insert); c.gridx++;
        makebutton("9", gridbag, c, insert); c.gridx++;
        makebutton("/", gridbag, c, command); c.gridx++;
        makebutton("%", gridbag, c, command); c.gridx++;

        c.gridy = 4;
        c.gridx = 0;
        makebutton("4", gridbag, c, insert); c.gridx++;
        makebutton("5", gridbag, c, insert); c.gridx++;
        makebutton("6", gridbag, c, insert); c.gridx++;
        makebutton("*", gridbag, c, command); c.gridx++;
        makebutton("1/x", gridbag, c, command); c.gridx++;

        c.gridy = 5;
        c.gridx = 0;
        makebutton("1", gridbag, c, insert); c.gridx++;
        makebutton("2", gridbag, c, insert); c.gridx++;
        makebutton("3", gridbag, c, insert); c.gridx++;
        makebutton("-", gridbag, c, command); c.gridx++;
        c.gridheight = 2;
        makebutton("=", gridbag, c, command); c.gridx++;
        c.gridheight = 1;

        c.gridy = 6;
        c.gridx = 0;
        c.gridwidth = 2;
        makebutton("0", gridbag, c, insert); c.gridx+=2;
        c.gridwidth = 1;
        makebutton(".", gridbag, c, insert); c.gridx++;
        makebutton("+", gridbag, c, command); c.gridx++;

    }


    private class insertNumber implements ActionListener {
        public void actionPerformed(ActionEvent event) {

            String input = event.getActionCommand();
            if (start) {
                display.setText("");
                start = false;
            }
            display.setText(display.getText() + input);
        }
    }


    private class insertCommand implements ActionListener {
        public void actionPerformed(ActionEvent event) {

            String command = event.getActionCommand();

            if (start) {
                if (command.equals("-")) {
                    display.setText(command);
                    start = false;
                }
                else preResult = command;
            }
            else {
                calculate(Double.parseDouble(display.getText()));
                preResult = command;
                start = true;
            }
        }
    }



    public void calculate(double x) {
        if (preResult.equals("+")) result += x;
        else if (preResult.equals("-")) result -= x;
        else if (preResult.equals("*")) result *= x;
        else if (preResult.equals("/")) result /= x;
        else if (preResult.equals("=")) result = x;
        else if (preResult.equals("√")) result = Math.sqrt(x);
        else if (preResult.equals("+-")) result = -x;
        else if (preResult.equals("%")) result %= x;
        else if (preResult.equals("CE") || preResult.equals("MR") || preResult.equals("MC")
                || preResult.equals("MS") || preResult.equals("M+") || preResult.equals("M-")
                || preResult.equals("C") || preResult.equals("<-")) result = 0;
        display.setText("" + result);
    }
}
