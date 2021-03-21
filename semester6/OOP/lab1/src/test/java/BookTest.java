import static org.junit.Assert.assertEquals;

import com.univ.webService.dataModel.Book;

import org.junit.Test;

public class BookTest {
    @Test
    public void test1() {
        Book book = new Book(1, "test", 1, 1);
        assertEquals(1, book.getId());
        assertEquals(1, book.getAmount());
        assertEquals("test", book.getName());

        book.setAmount(2);
        book.setId(3);
        book.setName("name");


        assertEquals(3, book.getId());
        assertEquals(2, book.getAmount());
        assertEquals("name", book.getName());

    }
}
