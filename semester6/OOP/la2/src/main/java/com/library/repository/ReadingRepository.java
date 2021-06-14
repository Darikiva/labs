package com.library.repository;

import java.util.List;

import com.library.entity.Book;
import com.library.entity.Reading;
import com.library.entity.User;

import org.springframework.data.jpa.repository.JpaRepository;

public interface ReadingRepository extends JpaRepository<Reading, Long> {
    List<Reading> findByUser(User user);

    List<Reading> findByBook(Book book);
}
