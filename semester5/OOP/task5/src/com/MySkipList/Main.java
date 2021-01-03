package com.MySkipList;

import java.util.ArrayList;

public class Main {

    public static void main(String[] args) throws InterruptedException {
	// write your code here
        SkipList skipList = new SkipList(15);
        ArrayList<Thread> thrs = new ArrayList<>();
        for(int i = 0; i < 1000; ++i) {
            thrs.add(new Thread(()->{
                for (int j = 0; j < 1000; ++j) {
                    skipList.add(j);
                }
            }));
            thrs.get(i).start();
        }
        for (int i = 0; i < 1000; ++i) {
            thrs.get(i).join();
        }
        ArrayList<Thread> thrs2 = new ArrayList<>();
        for (int i = 0; i < 500; ++i) {
            thrs2.add(new Thread(()-> {
                for (int j = 0; j < 500; ++j) {
                    skipList.remove(j);
                }
            }));
            thrs2.get(i).start();
        }
        for (int i = 0; i < 500; ++i) {
            thrs2.get(i).join();
        }
        System.out.println(skipList);
    }
}
