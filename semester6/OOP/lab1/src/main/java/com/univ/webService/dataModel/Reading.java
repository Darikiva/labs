package com.univ.webService.dataModel;

import java.sql.Date;

public class Reading {
    private int id_user;
    private int id_book;

    public Reading(int user_id, int book_id){
        this.setUser_id(user_id);
        this.setBook_id(book_id);
    }

    public int getBook_id() {
        return id_book;
    }

    public void setBook_id(int book_id) {
        this.id_book = book_id;
    }

    public int getUser_id() {
        return id_user;
    }

    public void setUser_id(int user_id) {
        this.id_user = user_id;
    }
}
