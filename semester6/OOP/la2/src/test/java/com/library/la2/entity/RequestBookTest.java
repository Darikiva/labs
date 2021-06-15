package com.library.la2.entity;

import org.springframework.boot.test.context.SpringBootTest;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.library.entity.RequestBook;

@SpringBootTest
public class RequestBookTest {

    @SpringBootTest
    public class BookTest {
        @Test
        public void testEqual() {
            var entity1 = new RequestBook();
            // entity1.
            // assertTrue(entity1.canEqual(entity1));
            assertTrue(entity1.equals(entity1));
            var entity2 = new RequestBook();
            
            assertFalse(entity1.equals(entity2));

            entity1 = entity2;
            assertTrue(entity1.equals(entity2));

            var o = new Object();
            assertFalse(entity1.equals(o));
        }

        @Test
        public void testHashCode() {
            var entity1 = new RequestBook();
            var entity2 = new RequestBook();
            var entity3 = new RequestBook();
            entity3.setId(5);

            assertTrue(entity1.hashCode() == entity1.hashCode());
            assertTrue(entity1.hashCode() != entity2.hashCode());
            assertTrue(entity1.hashCode() != entity3.hashCode());
            assertTrue(entity2.hashCode() != entity3.hashCode());
            assertTrue(entity3.hashCode() == entity3.hashCode());

        }

        @Test
        public void testToString() {
            var entity = new RequestBook();
            assertTrue(entity.toString() instanceof String);
            assertTrue(entity.toString() != null);
        }
    }
}
