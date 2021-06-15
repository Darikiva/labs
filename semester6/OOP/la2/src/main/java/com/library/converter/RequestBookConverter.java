package com.library.converter;

import com.library.dto.RequestBookDTO;
import com.library.entity.RequestBook;

public class RequestBookConverter {
    static public RequestBook toEntity(RequestBookDTO dto) {
        RequestBook entity = new RequestBook();
        entity.setId(dto.getId());
        entity.setBook(dto.getBook());
        entity.setUser(dto.getUser());
        entity.setAccepted(dto.isAccepted());
        return entity;
    }

    static public RequestBookDTO toDTO(RequestBook entity) {
        RequestBookDTO dto = new RequestBookDTO();
        dto.setId(entity.getId());
        dto.setBook(entity.getBook());
        dto.setUser(entity.getUser());
        dto.setAccepted(entity.isAccepted());
        return dto;
    }

    private RequestBookConverter(){}
}
