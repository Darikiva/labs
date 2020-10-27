package com.smth.gem;

public class VisualParameters {
    private Color color;
    private int transparency;
    private int edges;

    public VisualParameters(Color color, int transparency, int edges) {
        this.color = color;
        this.transparency = transparency;
        this.edges = edges;
    }
    public VisualParameters(){}

    public Color getColor() {
        return color;
    }

    public int getTransparency() {
        return transparency;
    }

    public int getEdges() {
        return edges;
    }
}
