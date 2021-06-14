package com.library.service;

import java.util.List;

import com.library.entity.Book;
import com.library.entity.RequestBook;
import com.library.entity.User;
import com.library.repository.RequestBookRepository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class RequestBookService {
    @Autowired
    RequestBookRepository repo;

    public List<RequestBook> findByUser(User user) {
        return repo.findByUser(user);
    }

    public List<RequestBook> findByBook(Book book) {
        return repo.findByBook(book);
    }
}
