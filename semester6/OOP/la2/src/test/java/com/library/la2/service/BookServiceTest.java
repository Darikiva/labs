package com.library.la2.service;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import com.library.entity.Book;
import com.library.repository.BookRepository;
import com.library.service.BookService;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.*;
@SpringBootTest
public class BookServiceTest {

    @MockBean
    private BookRepository bookRepository;

    @Autowired
    private BookService bookService;

    @Test
    public void getAllBooks() {
        List<Book> books = new ArrayList<>();
        when(bookRepository.findAll()).thenReturn(books);
        assertEquals(books, bookService.getBooks());
        verify(bookRepository, times(1)).findAll();
    }
}
