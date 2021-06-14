package com.library.converter;

import com.library.dto.UserDTO;
import com.library.entity.User;

import org.springframework.stereotype.Component;

@Component
public class UserConverter {
    static public UserDTO toDTO(User entity) {
        UserDTO dto = new UserDTO();
        dto.setId(entity.getId());
        dto.setName(entity.getName());
        dto.setSurname(entity.getSurname());
        dto.setLogin(entity.getLogin());
        dto.setPassword(entity.getPassword());
        dto.setAdmin(entity.isAdmin());
        dto.setRole(entity.getRole());
        return dto;
    }

    static public User toEntity(UserDTO dto){
        User entity = new User();
        entity.setId(dto.getId());
        entity.setName(dto.getName());
        entity.setSurname(dto.getSurname());
        entity.setLogin(dto.getLogin());
        entity.setPassword(dto.getPassword());
        entity.setAdmin(dto.isAdmin());
        entity.setRole(dto.getRole());
        return entity;
    }

    private UserConverter(){}
}
