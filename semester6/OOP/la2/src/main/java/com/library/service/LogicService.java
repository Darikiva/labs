package com.library.service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Set;

import com.library.converter.UserConverter;
import com.library.dto.UserDTO;
import com.library.entity.Reading;
import com.library.entity.RequestBook;
import com.library.entity.User;
import com.library.repository.BookRepository;
import com.library.repository.UserRepository;

import org.keycloak.KeycloakPrincipal;
import org.keycloak.KeycloakSecurityContext;
import org.keycloak.representations.AccessToken;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Service;

import lombok.var;

@Service
public class LogicService {
    UserService userService;
    BookService bookService;
    ReadingService readingService;
    RequestBookService requestBookService;

    @Autowired
    public LogicService(UserService userService, BookService bookService, ReadingService readingService,
            RequestBookService requestBookService) {
        this.userService = userService;
        this.bookService = bookService;
        this.readingService = readingService;
        this.requestBookService = requestBookService;
    }

    public void returnBook(long id_user, int id_book) {
        var user = userService.findById(id_user);
        var book = bookService.findById(id_book);
        if (book.isPresent()) {
            int amount = book.get().getAmount();
            book.get().setAmount(amount + 1);
            if (user.isPresent()) {
                var reading = readingService.findByBookAndUser(book.get(), user.get());
                readingService.deleteReading(reading);
            }
        }
    }

    public void takeBook(long id_user, int id_book) {
        var user = userService.findById(id_user);
        var book = bookService.findById(id_book);
        if (book.isPresent()) {
            int amount = book.get().getAmount();
            book.get().setAmount(amount - 1);
            if (user.isPresent()) {
                Reading new_reading = new Reading();
                new_reading.setBook(book.get());
                new_reading.setUser(user.get());
                readingService.saveReading(new_reading);
            }
        }
    }

    public void requestBook(long id_user, int id_book) {
        var user = userService.findById(id_user);
        var book = bookService.findById(id_book);
        if (book.isPresent()) {
            if (user.isPresent()) {
                RequestBook new_request = new RequestBook();
                new_request.setBook(book.get());
                new_request.setUser(user.get());
                new_request.setAccepted(false);
                requestBookService.save(new_request);
            }
        }
    }

    public void unrequestBook(long id_user, int id_book) {
        var user = userService.findById(id_user);
        var book = bookService.findById(id_book);
        if (book.isPresent()) {
            if (user.isPresent()) {
                RequestBook new_request = new RequestBook();
                new_request.setBook(book.get());
                new_request.setUser(user.get());
                new_request.setAccepted(false);
                requestBookService.delete(new_request);
            }
        }
    }

}
