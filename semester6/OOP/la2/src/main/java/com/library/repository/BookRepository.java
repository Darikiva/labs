package com.library.repository;

import java.util.List;
import java.util.Optional;

import com.library.entity.Book;

import org.springframework.data.jpa.repository.JpaRepository;

public interface BookRepository extends JpaRepository<Book, Long> {
    Optional<Book> findById(long id);
    
    List<Book> findByName(String name);
}
