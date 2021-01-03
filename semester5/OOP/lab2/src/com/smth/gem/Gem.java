package com.smth.gem;

public class Gem {
    private String name;
    private Preciousness preciouness;
    private String origin;
    private VisualParameters visualParameters;
    private int weight;

    public Gem(String name, Preciousness preciouness, String origin, VisualParameters visualParameters, int weight) {
        this.name = name;
        this.preciouness = preciouness;
        this.origin = origin;
        this.visualParameters = visualParameters;
        this.weight = weight;
    }

    public String getName() {
        return name;
    }

    public Preciousness getPreciouness() {
        return preciouness;
    }

    public String getOrigin() {
        return origin;
    }

    public VisualParameters getVisualParameters() {
        return visualParameters;
    }

    public int getWeight() {
        return weight;
    }

    public void printGem() {
        System.out.print("name: " + name + "\t");
        System.out.print("preciousness: " + preciouness + "\t");
        System.out.print("origin: " + origin + "\t");
        System.out.print("color: " + visualParameters.getColor() + "\t");
        System.out.print("transparency: " + visualParameters.getTransparency() + "\t");
        System.out.print("edges: " + visualParameters.getEdges() + "\t");
        System.out.println("weight: " + weight + "\t");
        System.out.println("*************************************************");
    }
}
