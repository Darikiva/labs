package com.univ.webService.dataModel;

public class User {
    private int id;
    private String name;
    private String surname;
    private String phoneNumber;
    private int idAreaCode;
    private int idBilling;
    private String login;
    private String password;
    private boolean isAdmin;

    public User() {
    }

    public User(int idAbonent, String name, String surname, String phoneNumber, int idAreaCode,
                   int idBilling, String login, String password, Boolean isAdmin) {
        this.id = idAbonent;
        this.name = name;
        this.surname = surname;
        this.phoneNumber = phoneNumber;
        this.idAreaCode = idAreaCode;
        this.idBilling = idBilling;
        this.login = login;
        this.password = password;
        this.isAdmin = isAdmin;
    }

    public User(int id, String name, String surname, String login, String password, boolean isAdmin)
    {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.login = login;
        this.password = password;
        this.isAdmin = isAdmin;
    }

    public String getLogin() {
        return login;
    }

    public String getPassword() {
        return password;
    }

    public boolean getIsAdmin() {
        return isAdmin;
    }

    public int getIdAbonent() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getSurname() {
        return surname;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public int getIdAreaCode() {
        return idAreaCode;
    }

    public int getIdBilling() {
        return idBilling;
    }

    public void setIdAbonent(int idAbonent) {
        this.id = idAbonent;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public void setIdAreaCode(int idAreaCode) {
        this.idAreaCode = idAreaCode;
    }

    public void setIdBilling(int idBilling) {
        this.idBilling = idBilling;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setIsAdmin(Boolean isAdmin) {
        this.isAdmin = isAdmin;
    }
}
