package com.library.converter;

import com.library.dto.ReadingDTO;
import com.library.entity.Reading;

public class ReadingConverter {
    static public Reading toEntity(ReadingDTO dto) {
        Reading entity = new Reading();
        entity.setId(dto.getId());
        entity.setBook(dto.getBook());
        entity.setUser(dto.getUser());
        return entity;
    }

    static public ReadingDTO toDTO(Reading entity) {
        ReadingDTO dto = new ReadingDTO();
        dto.setId(entity.getId());
        dto.setBook(entity.getBook());
        dto.setUser(entity.getUser());
        return dto;
    }

    private ReadingConverter(){}
}
