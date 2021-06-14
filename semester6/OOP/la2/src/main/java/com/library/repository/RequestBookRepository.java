package com.library.repository;

import java.util.List;

import com.library.entity.Book;
import com.library.entity.RequestBook;
import com.library.entity.User;

import org.springframework.data.jpa.repository.JpaRepository;

public interface RequestBookRepository extends JpaRepository<RequestBook, Long> {
    List<RequestBook> findByUser(User user);

    List<RequestBook> findByBook(Book book);
}
