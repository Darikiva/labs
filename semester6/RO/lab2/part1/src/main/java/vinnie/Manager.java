package vinnie;

import java.util.ArrayList;

/**
 * Hello world!
 *
 */
public class Manager {

    final static int THR_NUMBER = 4;
    static Boolean found = false;
    static Integer row = -1;
    static Integer column = -1;

    public void work() {

        int[][] forest = new int[100][100];
        for (int i = 0; i < forest.length; ++i) {
            for (int j = 0; j < forest[0].length; ++j) {
                forest[i][j] = 0;
            }
        }
        forest[25][23] = 1;
        MyThreadPool pool = new MyThreadPool(THR_NUMBER, forest);
        for (int i = 0; i < forest.length; ++i) 
            pool.execute(i);

        while (!found) {}
        pool.stop();
        
    }
}
