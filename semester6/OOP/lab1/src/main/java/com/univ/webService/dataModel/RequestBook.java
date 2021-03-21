package com.univ.webService.dataModel;

public class RequestBook {
    private int id_user;
    private int id_book;
    private boolean accepted;

    public RequestBook( int id_user, int id_book, boolean accepted) {
        this.setId_user(id_user);
        this.setId_book(id_book);
        this.setAccepted(accepted);
    }

    public boolean isAccepted() {
        return accepted;
    }

    public void setAccepted(boolean accepted) {
        this.accepted = accepted;
    }

    public int getId_user() {
        return id_user;
    }

    public void setId_user(int id_user) {
        this.id_user = id_user;
    }

    public int getId_book() {
        return id_book;
    }

    public void setId_book(int id_book) {
        this.id_book = id_book;
    }

}
