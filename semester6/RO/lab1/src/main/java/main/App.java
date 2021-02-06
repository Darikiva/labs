package main;

import java.awt.event.MouseEvent;

import javax.swing.*;
import javax.swing.event.MouseInputAdapter;
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
        final MyThread thread_left = new MyThread(slider, Side.LEFT);
        final MyThread thread_right = new MyThread(slider, Side.RIGHT);
        thread_left.start();
        thread_right.start();
        MyButton butt_left = new MyButton("Prioritaze 1 thr", thread_left, thread_right, Side.LEFT);
        MyButton butt_right = new MyButton("Prioritaze 2 thr", thread_left, thread_right, Side.RIGHT);
        JButton end_left = new JButton("End left");
        end_left.addMouseListener(new MouseInputListener() {

            @Override
            public void mouseClicked(MouseEvent arg0) {
                // TODO Auto-generated method stub
                thread_left.setRunning(false);
            }

            @Override
            public void mouseEntered(MouseEvent arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void mouseExited(MouseEvent arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void mousePressed(MouseEvent arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void mouseReleased(MouseEvent arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void mouseDragged(MouseEvent arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void mouseMoved(MouseEvent arg0) {
                // TODO Auto-generated method stub

            }

        });
        JButton end_right = new JButton("End right");
        end_right.addMouseListener(new MouseInputListener() {

            @Override
            public void mouseClicked(MouseEvent arg0) {
                // TODO Auto-generated method stub
                thread_right.setRunning(false);
            }

            @Override
            public void mouseEntered(MouseEvent arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void mouseExited(MouseEvent arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void mousePressed(MouseEvent arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void mouseReleased(MouseEvent arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void mouseDragged(MouseEvent arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void mouseMoved(MouseEvent arg0) {
                // TODO Auto-generated method stub

            }
            //
        });
        box.add(butt_left);
        box.add(butt_right);
        box.add(end_left);
        box.add(end_right);

        myWindow.setContentPane(box);
    }
}
