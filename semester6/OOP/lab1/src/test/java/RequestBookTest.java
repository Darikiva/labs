import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

import com.univ.webService.dataModel.RequestBook;

import org.junit.Test;

public class RequestBookTest {
    @Test
    public void test() {
        RequestBook requestBook = new RequestBook(1, 1, true);
        assertEquals(1, requestBook.getId_book());
        assertEquals(1, requestBook.getId_user());
        assert(requestBook.isAccepted());

        requestBook.setId_book(2);
        requestBook.setId_user(3);
        requestBook.setAccepted(false);


        assertEquals(2, requestBook.getId_book());
        assertEquals(3, requestBook.getId_user());
        assertFalse(requestBook.isAccepted());
    }
}
