package com.testClient;

import java.util.ArrayList;

public class Main {

    public static void main(String[] args) throws ClassNotFoundException {
	// write your code here
        ArrayList<Integer> m = new ArrayList<Integer>(1);
        Class c = ArrayList.class;
        ClassInfo.getInfo(ArrayList.class.getName());
    }
}
