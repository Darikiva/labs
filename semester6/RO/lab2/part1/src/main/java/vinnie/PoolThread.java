package vinnie;

import java.util.Queue;

public class PoolThread extends Thread{
    private Queue<Integer> taskQueue = null;
    private boolean stopped = false;
    int[][] m_forest;

    public PoolThread(Queue<Integer> queue, int[][] forest) {
        taskQueue = queue;
        m_forest = forest;
    }

    @Override
    public void run() {
        while (!stopped) {
            Integer task = taskQueue.poll();
            if (task != null) {
                for (int i = 0; i < m_forest.length; ++i) {
                    if (m_forest[task][i] == 1) {
                        Manager.found = true;
                        Manager.row = task;
                        Manager.column = i;
                        break;
                    }
                }
            }
        }
    }

    public synchronized void doStop() {
        stopped = true;
//        this.interrupt();
    }

    public synchronized boolean isStopped() {
        return stopped;
    }
}
