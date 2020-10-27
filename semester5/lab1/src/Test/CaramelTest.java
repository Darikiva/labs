package Test;

import com.Sweets.Candy;
import com.Sweets.Caramel;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CaramelTest {

    @Test
    void getWeight() {
        Candy caramel = new Caramel(5, 5, "wow");
        assertEquals(caramel.getWeight(), 5);
    }

    @Test
    void getSugar() {
        Candy caramel = new Caramel(5, 5, "wow");
        assertEquals(caramel.getSugar(), 5);
    }

    @Test
    void getMaker() {
        Candy caramel = new Caramel(5, 5, "wow");
        assertEquals(caramel.getMaker(), "wow");
    }

    @Test
    void setWeight() {
        Candy caramel = new Caramel(5, 5, "wow");
        caramel.setWeight(10);
        assertEquals(caramel.getWeight(), 10);
    }

    @Test
    void setSugar() {
        Candy caramel = new Caramel(5, 5, "wow");
        caramel.setSugar(15);
        assertEquals(caramel.getSugar(), 15);
    }

    @Test
    void setMaker() {
        Candy caramel = new Caramel(5, 5, "wow");
        caramel.setMaker("nowow");
        assertEquals(caramel.getMaker(), "nowow");
    }
}