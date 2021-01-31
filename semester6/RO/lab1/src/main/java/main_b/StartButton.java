package main_b;

import java.awt.event.MouseEvent;
import java.util.concurrent.atomic.AtomicInteger;

import javax.swing.JButton;
import javax.swing.JSlider;
import javax.swing.event.MouseInputListener;

import main.App;

public class StartButton extends JButton {

    final AtomicInteger m_semaphore;
    final int m_side;
    final JSlider m_slider;

    StartButton(String name, int side, AtomicInteger semaphore, JSlider slider) {
        super(name);
        this.m_semaphore = semaphore;
        this.m_slider = slider;
        this.m_side = side;

        this.addMouseListener(new MouseInputListener() {

            @Override
            public void mouseClicked(MouseEvent arg0) {
                if (m_semaphore.compareAndSet(0, 1)) {
                    if (m_side == -1) {
                        Appb.thread_left = new MyThread(m_slider, -1, true);
                        Appb.thread_left.start();
                    } else if (m_side == 1) {
                        Appb.thread_right = new MyThread(m_slider, 1, true);
                        Appb.thread_right.start();
                    }
                }
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
    }
}
