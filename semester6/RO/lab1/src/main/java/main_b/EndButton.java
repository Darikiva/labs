package main_b;

import java.awt.event.MouseEvent;
import java.util.concurrent.atomic.AtomicInteger;

import javax.swing.JButton;
import javax.swing.event.MouseInputListener;

public class EndButton extends JButton {

    MyThread m_thread;
    final int m_side;
    final AtomicInteger m_semaphore;

    EndButton(String name, int side, AtomicInteger semaphore) {
        super(name);
        this.m_side = side;
        this.m_semaphore = semaphore;

        this.addMouseListener(new MouseInputListener() {

            @Override
            public void mouseClicked(MouseEvent arg0) {
                if (m_side == -1) {
                    if (Appb.thread_left != null) {
                        Appb.thread_left.setRunning(false);
                        Appb.thread_left = null;
                        m_semaphore.compareAndSet(1, 0);
                    }
                } else if (m_side == 1) {
                    if (Appb.thread_right != null) {
                        Appb.thread_right.setRunning(false);
                        Appb.thread_right = null;
                        m_semaphore.compareAndSet(1, 0);
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
