package com.library.converter;

import com.library.dto.BookDTO;
import com.library.entity.Book;

public class BookConverter {
    static public BookDTO toDTO(Book entity) {
        BookDTO dto = new BookDTO();
        dto.setId(entity.getId());
        dto.setName(entity.getName());
        dto.setAmount(entity.getAmount());
        dto.setTotal_amount(entity.getTotalAmount());
        return dto;
    }
    
    static public Book toEntity(BookDTO dto) {
        Book entity = new Book();
        entity.setId(dto.getId());
        entity.setName(dto.getName());
        entity.setAmount(dto.getAmount());
        entity.setTotalAmount(dto.getTotal_amount());
        return entity;
    }

    private BookConverter(){}
}
