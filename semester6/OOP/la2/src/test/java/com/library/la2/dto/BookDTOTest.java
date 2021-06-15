package com.library.la2.dto;

import org.springframework.boot.test.context.SpringBootTest;

import static org.junit.jupiter.api.Assertions.assertEquals;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.library.dto.BookDTO;

import org.junit.jupiter.api.Test;

@SpringBootTest
public class BookDTOTest {

    @Test
    void testGettersSetters() {
        var entity = new BookDTO();
        entity.setAmount(1);
        assertEquals(1, entity.getAmount());

        entity.setId(1);
        assertEquals(1, entity.getId());

        entity.setName("darik");
        assertEquals("darik", entity.getName());

        entity.setTotal_amount(1);
        assertEquals(1, entity.getTotal_amount());
    }

    @Test
    void testEqual() {

        var dto1 = new BookDTO();
        // assertTrue(dto1.canEqual(dto1));
        assertTrue(dto1.equals(dto1));

        var dto2 = new BookDTO();
        dto2.setAmount(5);
        assertFalse(dto1.equals(dto2));

        var o = new Object();
        assertFalse(dto1.equals(o));
    }

    @Test
	public void testHashCode() {
		var dto1 = new BookDTO();
		var dto2 = new BookDTO();
		var dto3 = new BookDTO();
		dto3.setAmount(5);
		
		assertTrue(dto1.hashCode()==dto1.hashCode());
		assertTrue(dto1.hashCode()!=dto2.hashCode());
		assertTrue(dto1.hashCode()!=dto3.hashCode());
		assertTrue(dto2.hashCode()!=dto3.hashCode());
		assertTrue(dto3.hashCode()==dto3.hashCode());
	}
	
	@Test
	public void testToString() {
		var dto = new BookDTO();
		assertTrue(dto.toString() instanceof String);
		assertTrue(dto.toString() != null);
	}
}
