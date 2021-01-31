package main;

import java.awt.event.MouseEvent;

import javax.swing.*;
import javax.swing.event.MouseInputListener;
import javax.swing.text.FlowView;

/**
 * Hello world!
 *
 */
public class App {
    public static void main(String[] args) {
        JFrame myWindow = new JFrame("Пробное окно");
        myWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        myWindow.setSize(400, 300);
        myWindow.setVisible(true);
        final JSlider slider = new JSlider();
        slider.setMinimum(0);
        slider.setMaximum(100);
        slider.setMajorTickSpacing(20);
        slider.setMinorTickSpacing(5);
        slider.setPaintTicks(true);
        slider.setPaintLabels(true);
        Box box = Box.createVerticalBox();
        box.add(slider);
        final MyThread thread_left = new MyThread(slider, -1, false);
        final MyThread thread_right = new MyThread(slider, 1, false);
        MyButton butt_left = new MyButton("Start 1", thread_left, thread_right, Side.LEFT);
        MyButton butt_right = new MyButton("Start 2", thread_left, thread_right, Side.RIGHT);
        box.add(butt_left);
        box.add(butt_right);

        myWindow.setContentPane(box);
    }
}
