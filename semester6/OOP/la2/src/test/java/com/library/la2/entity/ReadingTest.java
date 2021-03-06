package com.library.la2.entity;

import org.springframework.boot.test.context.SpringBootTest;

import com.library.entity.Reading;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Test;

@SpringBootTest
public class ReadingTest {

    @SpringBootTest
    public class BookTest {
        @Test
        public void testEqual() {
            var entity1 = new Reading();
            // entity1.
            // assertTrue(entity1.canEqual(entity1));
            assertTrue(entity1.equals(entity1));
            var entity2 = new Reading();
            entity2.setId(2);
            assertFalse(entity1.equals(entity2));

            entity1 = entity2;
            assertTrue(entity1.equals(entity2));

            var o = new Object();
            assertFalse(entity1.equals(o));
        }

        @Test
        public void testHashCode() {
            var entity1 = new Reading();
            var entity2 = new Reading();
            var entity3 = new Reading();
            entity3.setId(5);

            assertTrue(entity1.hashCode() == entity1.hashCode());
            assertTrue(entity1.hashCode() != entity2.hashCode());
            assertTrue(entity1.hashCode() != entity3.hashCode());
            assertTrue(entity2.hashCode() != entity3.hashCode());
            assertTrue(entity3.hashCode() == entity3.hashCode());

        }

        @Test
        public void testToString() {
            var entity = new Reading();
            assertTrue(entity.toString() instanceof String);
            assertTrue(entity.toString() != null);
        }
    }

}
