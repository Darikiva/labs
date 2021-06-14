package com.library.dto;

import com.library.entity.Book;
import com.library.entity.User;

import lombok.NoArgsConstructor;

@NoArgsConstructor
public class RequestBookDTO {
    private long id;
    private User user;
    private Book book;
    private boolean accepted;

    public long getId() {
        return id;
    }

    public boolean isAccepted() {
        return accepted;
    }

    public void setAccepted(boolean accepted) {
        this.accepted = accepted;
    }

    public void setId(long id) {
        this.id = id;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public Book getBook() {
        return book;
    }

    public void setBook(Book book) {
        this.book = book;
    }
}
