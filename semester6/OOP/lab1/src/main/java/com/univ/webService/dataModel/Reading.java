package com.univ.webService.dataModel;

import java.sql.Date;

public class Reading {
    private int user_id;
    private int book_id;
    private Date date;

    Reading(int user_id, int book_id, Date date){
        this.setUser_id(user_id);
        this.setBook_id(book_id);
        this.setDate(date);
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public int getBook_id() {
        return book_id;
    }

    public void setBook_id(int book_id) {
        this.book_id = book_id;
    }

    public int getUser_id() {
        return user_id;
    }

    public void setUser_id(int user_id) {
        this.user_id = user_id;
    }
}
