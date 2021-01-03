package com.testClient;

import java.io.Serializable;

public class Person implements Serializable {
    private String name_;
    private String surname_;
    private int age_;
    private int arr[];
    public String getName_() {
        return name_;
    }
    public String getSurname_() {
        return surname_;
    }
    public int getAge_() {
        return age_;
    }
    public int[] getArr() {
        return arr;
    }
    public Person(String name, String sirname, int age) {
        arr = new int[age];
        name_ = name;
        surname_ = sirname;
        age_ = age;
        for(int i = 0; i < age; ++i) arr[i] = i;
    }

}
