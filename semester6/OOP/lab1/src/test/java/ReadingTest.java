import static org.junit.Assert.assertEquals;

import com.univ.webService.dataModel.Reading;

import org.junit.Test;

public class ReadingTest {

    @Test
    public void test() {
        Reading reading = new Reading(1, 1);
        assertEquals(1, reading.getBook_id());
        assertEquals(1, reading.getUser_id());

        reading.setBook_id(2);
        reading.setUser_id(3);
        assertEquals(2, reading.getBook_id());
        assertEquals(3, reading.getUser_id());
    }
    
}
