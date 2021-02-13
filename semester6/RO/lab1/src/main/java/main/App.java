package main;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JSlider;


public class App {

    public static void main(String[] args) {
        
        final JSlider slider = new JSlider();
        slider.setMinimum(0);
        slider.setMaximum(100);
        slider.setMajorTickSpacing(20);
        slider.setMinorTickSpacing(5);
        slider.setPaintTicks(true);
        slider.setPaintLabels(true);

        MyThread left_thread = new MyThread(slider, Side.LEFT);
        MyThread right_thread = new MyThread(slider, Side.RIGHT);
        
        JButton start_button = new JButton("Start");
        start_button.addActionListener(e -> {
            left_thread.setDaemon(true);
            right_thread.setDaemon(true);
            left_thread.start();
            right_thread.start();
        });

        JSlider prior_left = new JSlider();
        prior_left.setMinimum(1);
        prior_left.setMaximum(10);
        prior_left.setValue(5);
        prior_left.addChangeListener(e -> {
            left_thread.setPriority(prior_left.getValue());
        });

        JSlider prior_right = new JSlider();
        prior_right.setMinimum(1);
        prior_right.setMaximum(10);
        prior_right.setValue(5);
        prior_right.addChangeListener(e -> {
            right_thread.setPriority(prior_right.getValue());
        });


        Box box = Box.createVerticalBox();
        box.add(slider);
        box.add(start_button);
        box.add(prior_left);
        box.add(prior_right);

        JFrame myWindow = new JFrame("Пробное окно");
        myWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        myWindow.setSize(400, 300);
        myWindow.setVisible(true);
        myWindow.setContentPane(box);
    }
}
