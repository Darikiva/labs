package com.library.entity;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.SequenceGenerator;
import javax.persistence.Table;

import lombok.NoArgsConstructor;

@Entity
@Table(name = "reading", schema = "public")
@NoArgsConstructor
public class Reading {
    @Id
    @GeneratedValue(generator = "readings_id_seq", strategy = GenerationType.SEQUENCE)
    @SequenceGenerator(name = "readings_id_seq", sequenceName = "readings_id_seq", allocationSize = 1)
    @Column(name = "id", updatable = false)
    private long id;
    
    @ManyToOne(fetch = FetchType.LAZY)
    private User user;
    
    @ManyToOne(fetch = FetchType.LAZY)
    private Book book;

    public long getId() {
        return id;
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
