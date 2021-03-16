package com.univ.webService.dataModel;

public class Book {
    private int id;
    private String name;
    private int amount;
    private final int total_amount;

    public Book(int id, String name, int amount, int total_amount) {
        this.setId(id);
        this.setName(name);
        this.setAmount(amount);
        this.total_amount = total_amount;
    }

    public int getTotal_amount() {
        return total_amount;
    }

    public int getAmount() {
        return amount;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }
}
