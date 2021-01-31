package main;

import java.awt.event.MouseEvent;

import javax.swing.JButton;
import javax.swing.event.MouseInputListener;

public class MyButton extends JButton {

    MyThread m_thread_left, m_thread_right;
    final Side mySide;
    MyButton(String name, MyThread thread_left, MyThread thread_right, Side side) {
        super(name);
        this.mySide = side;
        this.m_thread_left = thread_left;
        this.m_thread_right = thread_right;
        this.addMouseListener(new MouseInputListener() {

            @Override
            public void mouseClicked(MouseEvent arg0) {
                // TODO Auto-generated method stub
                if (mySide == Side.LEFT) {
                    m_thread_left.setPrior(true);
                    m_thread_right.setPrior(false);
                    if (!m_thread_left.isAlive()) {
                        m_thread_left.start();
                    }
                } else {
                    m_thread_left.setPrior(false);
                    m_thread_right.setPrior(true);
                    if (!m_thread_right.isAlive()) {
                        m_thread_right.start();
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
