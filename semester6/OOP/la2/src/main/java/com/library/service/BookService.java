package com.library.service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import com.library.entity.Book;
import com.library.repository.BookRepository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class BookService {
    @Autowired
    static private BookRepository repo;

    public Optional<Book> findById(long id) {
        return repo.findById(id);
    }

    public List<Book> findByName(String name) {
        return repo.findByName(name);
    }

    public List<Book> getBooks()
    {
        return repo.findAll();
    }
}
