package com.library.service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import com.library.converter.BookConverter;
import com.library.dto.BookDTO;
import com.library.entity.Book;
import com.library.repository.BookRepository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class BookService {
    @Autowired
    private BookRepository repo;

    @Autowired
    public BookService(BookRepository repo) {
        this.repo = repo;
    }

    public Optional<Book> findById(long id) {
        return repo.findById(id);
    }

    public List<Book> findByName(String name) {
        return repo.findByName(name);
    }

    public List<BookDTO> getBooks() {
        List<Book> books = repo.findAll();
        List<BookDTO> answer = new ArrayList<>();
        for (Book book : books) {
            answer.add(BookConverter.toDTO(book));
        }
        return answer;
    }
}
