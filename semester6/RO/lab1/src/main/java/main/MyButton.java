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
                if (mySide == Side.LEFT) {
                    m_thread_left.setRunning(true);
                    m_thread_left.setPriority(2);
                    m_thread_right.setPriority(1);
                } else {
                    m_thread_right.setRunning(true);
                    m_thread_left.setPriority(1);
                    m_thread_right.setPriority(2);
                }
            }

            @Override
            public void mouseEntered(MouseEvent arg0) {

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
