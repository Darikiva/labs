package com.task3;

import java.util.ArrayList;

public class Main {

    public static int wow = 0;
    public static ArrayList threads = new ArrayList();

    public static void main(String[] args) {
        ThreadGroup group = new ThreadGroup("main group");
        ThreadGroup subgroup1 = new ThreadGroup(group,"subgroup1");
        ThreadGroup subgroup2 = new ThreadGroup(group,"subgroup2");

        ThreadGroup subsubgroup1 = new ThreadGroup(subgroup1, "subsubgroup1");
        for(int i = 0; i < 3; ++i) {
            Thread new_thr = new Thread(group,"thr" + i) {
                public void run() {
                    try {
                        Thread.sleep(3500);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            };
            new_thr.start();

            Thread sub_thr1 = new Thread(subgroup1, "subthr1" + i) {
                public void run() {
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            };
            sub_thr1.start();

            Thread sub_thr2 = new Thread(subgroup2, "subthr2" + i) {
                public void run() {
                    try {
                        Thread.sleep(2500);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            };
            sub_thr2.start();

            Thread subsub_thr1 = new Thread(subsubgroup1, "subsubthr1" + i) {
                public void run() {
                    try {
                        sleep(1500);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            };
            subsub_thr1.start();
        }

        ThreadGroupInfo info = new ThreadGroupInfo(group);
        info.run();
    }
}
