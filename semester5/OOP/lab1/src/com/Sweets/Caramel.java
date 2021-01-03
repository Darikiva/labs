package com.Sweets;

public class Caramel extends Candy {
    private int sugar;
    private int weight;
    private String maker;

    public Caramel(int sugar, int weight, String maker) {
        this.sugar = sugar;
        this.weight = weight;
        this.maker = maker;
    }

    @Override
    public int getWeight() {
        return weight;
    }

    @Override
    public int getSugar() {
        return sugar;
    }

    @Override
    public String getMaker() {
        return maker;
    }

    @Override
    public void setWeight(int weight) {
        this.weight = weight;
    }

    @Override
    public void setSugar(int sugar) {
        this.sugar = sugar;
    }

    @Override
    public void setMaker(String maker) {
        this.maker = maker;
    }

}
