package com.library.controller;

import java.util.List;

import javax.annotation.security.RolesAllowed;

import com.library.dto.UserDTO;
import com.library.entity.User;
import com.library.converter.UserConverter;
import com.library.dto.BookDTO;
import com.library.dto.RequestBookDTO;
import com.library.service.BookService;
import com.library.service.LogicService;
import com.library.service.RequestBookService;
import com.library.service.UserService;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestHeader;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/user")
@CrossOrigin(origins = "http://localhost:3000")
public class UserController {
    private UserService userService;
    private BookService bookService;
    private RequestBookService requestBookService;
    private LogicService logicService;

    @Autowired
    public UserController(UserService userService, BookService bookService, RequestBookService requestBookService,
            LogicService logicService) {
        this.userService = userService;
        this.bookService = bookService;
        this.requestBookService = requestBookService;
        this.logicService = logicService;
    }

    @RolesAllowed({ "admin", "user" })
    @GetMapping(value = "/list_books")
    public ResponseEntity<List<BookDTO>> getAllBooks(@RequestHeader String Authorization) {
        var answer = bookService.getBooks();
        System.out.println(answer.size());
        if (answer.size() > 0)
        {
            System.out.println(answer.get(0).getName());
        }
        return ResponseEntity.ok(bookService.getBooks());
    }

    @RolesAllowed({ "admin", "user" })
    @GetMapping(value = "/list_requests")
    public ResponseEntity<List<RequestBookDTO>> getAllRequests(@RequestHeader String Authorization) {
        User user = UserConverter.toEntity(userService.getUserDto(Authorization));
        return ResponseEntity.ok(requestBookService.findByUser(user));
    }

    @RolesAllowed({ "user" })
    @PostMapping(value = "/take_book")
    public ResponseEntity<List<RequestBookDTO>> takeBook(@RequestHeader String Authorization, int id_book) {
        User user = UserConverter.toEntity(userService.getUserDto(Authorization));
        logicService.takeBook(user.getId(), id_book);
        return ResponseEntity.ok(requestBookService.findByUser(user));
    }

    @RolesAllowed({ "user" })
    @PostMapping(value = "/return_book")
    public ResponseEntity<List<RequestBookDTO>> returnBook(@RequestHeader String Authorization, int id_book) {
        User user = UserConverter.toEntity(userService.getUserDto(Authorization));
        logicService.returnBook(user.getId(), id_book);
        return ResponseEntity.ok(requestBookService.findByUser(user));
    }

    @RolesAllowed({ "user" })
    @PostMapping(value = "/request_book")
    public ResponseEntity<List<RequestBookDTO>> requestBook(@RequestHeader String Authorization, int id_book) {
        User user = UserConverter.toEntity(userService.getUserDto(Authorization));
        logicService.requestBook(user.getId(), id_book);
        return ResponseEntity.ok(requestBookService.findByUser(user));
    }

    @RolesAllowed({ "user" })
    @PostMapping(value = "/unrequest_book")
    public ResponseEntity<List<RequestBookDTO>> unrequestBook(@RequestHeader String Authorization, int id_book) {
        User user = UserConverter.toEntity(userService.getUserDto(Authorization));
        logicService.unrequestBook(user.getId(), id_book);
        return ResponseEntity.ok(requestBookService.findByUser(user));
    }
}
