package com.Sweets;

import org.junit.jupiter.api.Test;

import java.sql.PreparedStatement;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

public class Present {
    private ArrayList<Candy> candies;

    public Present(ArrayList<Candy> candies) {
        this.candies = candies;
    }

    public int getWeight() {
        int answer = 0;
        for (Candy candy : candies) {
            answer += candy.getWeight();
        }
        return answer;
    }

    public ArrayList<Candy> getCandies() {
        return candies;
    }

    public ArrayList<Candy> getCandiesInRange(int beg, int end) {
        ArrayList<Candy> answer = new ArrayList<>();
        for (Candy candy : candies) {
            if (candy.getSugar() >= beg && candy.getSugar() <= end) {
                answer.add(candy);
            }
        }
        return answer;
    }

    public void sort(Type type) {
        if (type == Type.SUGAR) {
            candies.sort(new SortBySugar());
        } else if (type == Type.WEIGHT) {
            candies.sort(new SortByWeight());
        }

    }
}

