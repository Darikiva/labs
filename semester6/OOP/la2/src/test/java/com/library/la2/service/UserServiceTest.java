package com.library.la2.service;

import org.springframework.boot.test.context.SpringBootTest;
import org.junit.jupiter.api.Test;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import com.library.dto.UserDTO;
import com.library.entity.User;
import com.library.repository.UserRepository;
import com.library.service.UserService;

import static org.mockito.Mockito.*;

@SpringBootTest
public class UserServiceTest {
    
    @MockBean
    private UserRepository userRepository;

    @MockBean
    private UserService userService;

    @Test
    public void getAllUsers() {
        List<User> users = new ArrayList<>();
        when(userRepository.findAll()).thenReturn(users);
        List<UserDTO> dto = userService.getAllUsers();
        Assertions.assertEquals(users, dto);
    }

    @Test
    public void findUserById() {
        User user = new User();
        user.setId(1);
        user.setLogin("darik");
        user.setPassword("mypassword");
        user.setSurname("ivashyn");
        user.setRole("user");

        when(userRepository.findById(anyLong())).thenReturn(Optional.of(user));
        Assertions.assertEquals(user, userService.findById(anyLong()));
        verify(userRepository, times(1)).findById(anyLong());
    }
}
