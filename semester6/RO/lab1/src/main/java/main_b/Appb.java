package main_b;

import java.awt.event.MouseEvent;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

import javax.swing.*;
import javax.swing.event.MouseInputListener;
import javax.swing.text.FlowView;

public class Appb {
    static AtomicInteger semaphore = new AtomicInteger(0);
    static MyThread thread_left;
    static MyThread thread_right;
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
        StartButton start_left = new StartButton("Start 1", -1, semaphore, slider);
        StartButton start_right = new StartButton("Start 2", 1, semaphore, slider);
        EndButton end_left = new EndButton("End 1", -1, semaphore);
        EndButton end_right = new EndButton("End 2", 1, semaphore);
        box.add(start_left);
        box.add(start_right);
        box.add(end_left);
        box.add(end_right);
        myWindow.setContentPane(box);
    }
}
