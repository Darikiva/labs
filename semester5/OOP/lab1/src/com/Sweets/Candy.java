package com.Sweets;

import java.util.Comparator;

abstract public class Candy {
    abstract public int getWeight();

    abstract public int getSugar();

    abstract public String getMaker();

    abstract public void setWeight(int weight);

    abstract public void setSugar(int sugar);

    abstract public void setMaker(String maker);
}

class SortByWeight implements Comparator<Candy> {
    public int compare(Candy lhs, Candy rhs) {
        return lhs.getWeight() - rhs.getWeight();
    }
}

class SortBySugar implements Comparator<Candy> {
    public int compare(Candy lhs, Candy rhs) {
        return lhs.getSugar() - rhs.getSugar();
    }
}