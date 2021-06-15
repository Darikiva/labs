package com.library.la2.dto;

import org.springframework.boot.test.context.SpringBootTest;

import com.library.dto.ReadingDTO;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;

@SpringBootTest
public class ReadingDTOTest {

    @Test
    void testGettersSetters() {
        var entity = new ReadingDTO();

        entity.setId(1);
        assertEquals(1L, entity.getId());

    }

    @Test
    void testEqual() {

        var dto1 = new ReadingDTO();
        // assertTrue(dto1.canEqual(dto1));
        assertTrue(dto1.equals(dto1));

        var dto2 = new ReadingDTO();
        dto2.setId(5);
        assertFalse(dto1.equals(dto2));

        var o = new Object();
        assertFalse(dto1.equals(o));
    }

    @Test
    public void testHashCode() {
        var dto1 = new ReadingDTO();
        var dto2 = new ReadingDTO();
        var dto3 = new ReadingDTO();
        dto3.setId(5);

        assertTrue(dto1.hashCode() == dto1.hashCode());
        assertTrue(dto1.hashCode() != dto2.hashCode());
        assertTrue(dto1.hashCode() != dto3.hashCode());
        assertTrue(dto2.hashCode() != dto3.hashCode());
        assertTrue(dto3.hashCode() == dto3.hashCode());
    }

    @Test
    public void testToString() {
        var dto = new ReadingDTO();
        assertTrue(dto.toString() instanceof String);
        assertTrue(dto.toString() != null);
    }
}
