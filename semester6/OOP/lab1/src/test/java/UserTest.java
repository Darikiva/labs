import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

import com.univ.webService.dataModel.User;

import org.junit.Test;
public class UserTest {
    @Test
    public void test() {
        User user = new User(1, "test", "test", "test", "test", true);
        assertEquals("test", user.getLogin());
        assertEquals("test", user.getPassword());
        assertEquals("test", user.getName());
        assertEquals(1, user.getId());
        assertEquals("test", user.getSurname());
        assert(user.getIsAdmin());

        user.setName("name");
        user.setSurname("surname");
        user.setLogin("login");
        user.setPassword("password");
        user.setIdAbonent(2);
        user.setIsAdmin(false);


        assertEquals("login", user.getLogin());
        assertEquals("password", user.getPassword());
        assertEquals("name", user.getName());
        assertEquals(2, user.getId());
        assertEquals("surname", user.getSurname());
        assertFalse(user.getIsAdmin());
    }
}
