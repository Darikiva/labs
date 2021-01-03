package Test;

import com.Sweets.*;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class PresentTest {

    @Test
    void getWeight() {
        ArrayList<Candy> candies = new ArrayList<>();
        int weight = 0;
        for(int i = 0; i < 5; ++i) {
            candies.add(new Caramel(i % 4 + 1, i % 3 + 1, "wow"));
            weight += i % 3 + 1;
        }
        for(int i = 0; i < 7; ++i) {
            candies.add(new Toffy(i % 3 + 1, i % 4 + 1, "wow"));
            weight += i % 4 + 1;
        }
        Present present = new Present(candies);
        assertEquals(present.getWeight(), weight);
    }

    @Test
    void getCandies() {
        ArrayList<Candy> candies = new ArrayList<>();
        int weight = 0;
        for(int i = 0; i < 5; ++i) {
            candies.add(new Caramel(i % 4 + 1, i % 3 + 1, "wow"));
            weight += i % 3 + 1;
        }
        for(int i = 0; i < 7; ++i) {
            candies.add(new Toffy(i % 3 + 1, i % 4 + 1, "wow"));
            weight += i % 4 + 1;
        }
        Present present = new Present(candies);
        for(int i = 0; i < present.getCandies().size(); ++i) {
            assertEquals(candies.get(i), present.getCandies().get(i));
        }
    }

    @Test
    void getCandiesInRange() {
        ArrayList<Candy> candies = new ArrayList<>();
        int weight = 0;
        for(int i = 0; i < 5; ++i) {
            candies.add(new Caramel(i % 4 + 1, i % 3 + 1, "wow"));
            weight += i % 3 + 1;
        }
        for(int i = 0; i < 7; ++i) {
            candies.add(new Toffy(i % 3 + 1, i % 4 + 1, "wow"));
            weight += i % 4 + 1;
        }
        Present present = new Present(candies);
        ArrayList<Candy> in_range = present.getCandiesInRange(1, 2);
        for(Candy candy : in_range) {
            assertTrue(candy.getSugar() <= 2 && candy.getSugar() >= 1);
        }
    }

    @Test
    void sort() {
        ArrayList<Candy> candies = new ArrayList<>();
        int weight = 0;
        for(int i = 0; i < 5; ++i) {
            candies.add(new Caramel(i % 4 + 1, i % 3 + 1, "wow"));
            weight += i % 3 + 1;
        }
        for(int i = 0; i < 7; ++i) {
            candies.add(new Toffy(i % 3 + 1, i % 4 + 1, "wow"));
            weight += i % 4 + 1;
        }
        Present present = new Present(candies);
        present.sort(Type.SUGAR);
        for (int i = 1; i < present.getCandies().size(); ++i) {
            assertTrue(present.getCandies().get(i).getSugar() >= present.getCandies().get(i - 1).getSugar());
        }

        present.sort(Type.WEIGHT);
        for (int i = 1; i < present.getCandies().size(); ++i) {
            assertTrue(present.getCandies().get(i).getWeight() >= present.getCandies().get(i).getWeight());
        }
    }
}