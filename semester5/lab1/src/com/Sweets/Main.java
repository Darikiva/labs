package com.Sweets;

import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {
        // write your code here
        ArrayList<Candy> candies = new ArrayList<>();
        for (int i = 0; i < 10; ++i) {
            candies.add(new Caramel(i % 4, i % 9, "caramel_maker"));
        }

        for (int i = 10; i < 20; ++i) {
            candies.add(new Toffy(i % 5, i % 9, "toffy_maker"));
        }

        Present present = new Present(candies);

        for (Candy candy : present.getCandies()) {
            System.out.println("Weight: " + candy.getWeight() + "; Sugar: " + candy.getSugar() + "; Maker:" + candy.getMaker());
        }

        System.out.println();
        System.out.println("The weigth = " + present.getWeight());
        System.out.println();


        System.out.println("Sorting by sugar");
        present.sort(Type.SUGAR);
        for (Candy candy : present.getCandies()) {
            System.out.println("Weight: " + candy.getWeight() + "; Sugar: " + candy.getSugar() + "; Maker:" + candy.getMaker());
        }
        System.out.println();

        System.out.println("Sorting by weight");
        present.sort(Type.WEIGHT);
        for (Candy candy : present.getCandies()) {
            System.out.println("Weight: " + candy.getWeight() + "; Sugar: " + candy.getSugar() + "; Maker:" + candy.getMaker());
        }
        System.out.println();

    }
}
