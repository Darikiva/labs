package vinnie;

import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;

public class MyThreadPool {
    private Queue<Integer> taskQueue = null;
    private List<PoolThread> threads = new ArrayList<>();
    private boolean stopped = false;

    public int getSize() {
        return taskQueue.size();
    }

    public MyThreadPool(int numThreads, int[][] forest) {
        taskQueue = new ConcurrentLinkedQueue<>();

        for (int i = 0; i < numThreads; ++i) {
            threads.add(new PoolThread(taskQueue, forest));
        }
        for(PoolThread thread: threads) {
            thread.start();
        }
    }

    public synchronized void execute(Integer task){
        if (!stopped) {
            this.taskQueue.add(task);
        }
    }

    public synchronized void stop() {
        stopped = true;
        for (PoolThread thr: threads) {
            thr.doStop();
        }
    }
}