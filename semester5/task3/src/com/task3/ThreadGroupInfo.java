package com.task3;

public class ThreadGroupInfo extends Thread {
    ThreadGroup group;

    public ThreadGroupInfo(ThreadGroup group) {
        this.group = group;
    }

    public void PrintInfo() {
        GroupInfo(group, 0);
    }

    private void GroupInfo(ThreadGroup group, int number) {
        Thread thrs[] = new Thread[group.activeCount()];
        int wow = group.enumerate(thrs, false);
        for(int j = 0; j < wow; ++j) {
            for (int i = 0; i < number; ++i) System.out.print('\t');
             System.out.println(thrs[j].getName());
        }
        ThreadGroup groups[] = new ThreadGroup[group.activeGroupCount()];

        int wow1 = group.enumerate(groups, false);
        for (int i = 0; i < wow1; ++i) {
            GroupInfo(groups[i], number + 1);
        }
//        System.out.println("--------------------------------");
    }

    public void run() {
        while (group.activeCount() > 0) {
            PrintInfo();
            System.out.println("**********************************");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
