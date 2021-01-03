package Test;

import com.Sweets.Candy;
import com.Sweets.Toffy;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class ToffyTest {
    @Test
    void getWeight() {
        Candy toffy = new Toffy(5, 5, "wow");
        assertEquals(toffy.getSugar(), 5);
    }

    @Test
    void getSugar() {
        Candy toffy = new Toffy(5, 5, "wow");
        assertEquals(toffy.getWeight(), 5);
    }

    @Test
    void getMaker() {
        Candy toffy = new Toffy(5, 5, "wow");
        assertEquals(toffy.getMaker(), "wow");
    }

    @Test
    void setWeight() {
        Candy toffy = new Toffy(5, 5, "wow");
        toffy.setWeight(10);
        assertEquals(toffy.getWeight(), 10);
    }

    @Test
    void setSugar() {
        Candy toffy = new Toffy(5, 5, "wow");
        toffy.setSugar(10);
        assertEquals(toffy.getSugar(), 10);
    }

    @Test
    void setMaker() {
        Candy toffy = new Toffy(5, 5, "wow");
        toffy.setMaker("nowow");
        assertEquals(toffy.getMaker(), "nowow");
    }
}