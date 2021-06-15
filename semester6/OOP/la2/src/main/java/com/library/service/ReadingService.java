package com.library.service;

import java.util.List;

import com.library.entity.Book;
import com.library.entity.Reading;
import com.library.entity.User;
import com.library.repository.ReadingRepository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ReadingService {
    @Autowired
    private ReadingRepository repo;

    public List<Reading> findByUser(User user) {
        return repo.findByUser(user);
    }

    public List<Reading> findByBook(Book book) {
        return repo.findByBook(book);
    }

    public Reading findByBookAndUser(Book book, User user) {
        var readings = repo.findByUser(user);
        for (Reading reading : readings) {
            if (reading.getBook().getId() == book.getId()) {
                return reading;
            }
        }
        return null;
    }

    public void saveReading(Reading reading) {
        repo.save(reading);
    }

    public void deleteReading(Reading reading) {
        repo.delete(reading);
    }
}
