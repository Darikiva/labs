package com.library.service;

import java.util.ArrayList;
import java.util.List;

import com.library.converter.RequestBookConverter;
import com.library.dto.RequestBookDTO;
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

    public List<RequestBookDTO> findByUser(User user) {
        var entities = repo.findByUser(user);
        var dtos = new ArrayList<RequestBookDTO>();
        for (RequestBook entity: entities)
        {
            dtos.add(RequestBookConverter.toDTO(entity));
        }
        return dtos;
    }

    public List<RequestBook> findByBook(Book book) {
        return repo.findByBook(book);
    }

    public void save(RequestBook requestBook) {
        repo.save(requestBook);
    }

    public void delete(RequestBook requestBook) {
        repo.delete(requestBook);
    }
}
