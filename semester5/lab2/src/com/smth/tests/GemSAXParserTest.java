package com.smth.tests;

import com.smth.gem.Color;
import com.smth.gem.Gem;
import com.smth.gem.Preciousness;
import com.smth.gem.VisualParameters;
import com.smth.parsers.GemDOMParser;
import org.junit.jupiter.api.Test;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class GemSAXParserTest {

    @Test
    void parse() throws ParserConfigurationException, SAXException, IOException {
        ArrayList<Gem> gems_test = GemDOMParser.parse("/home/darik/university/labs/semester5/lab2/Gems/test.xml");
        ArrayList<Gem> right_answer = new ArrayList<>();
        right_answer.add(new Gem(
                "test",
                Preciousness.precious,
                "test",
                new VisualParameters(Color.red, 1, 13),
                23
        ));
        for(int i = 0; i < gems_test.size(); ++i) {
            assertEquals(gems_test.get(i).getName(), right_answer.get(i).getName());
            assertEquals(gems_test.get(i).getOrigin(), right_answer.get(i).getOrigin());
            assertEquals(gems_test.get(i).getPreciouness(), right_answer.get(i).getPreciouness());
            assertEquals(gems_test.get(i).getVisualParameters().getColor(), right_answer.get(i).getVisualParameters().getColor());
            assertEquals(gems_test.get(i).getVisualParameters().getTransparency(), right_answer.get(i).getVisualParameters().getTransparency());
            assertEquals(gems_test.get(i).getVisualParameters().getEdges(), right_answer.get(i).getVisualParameters().getEdges());
            assertEquals(gems_test.get(i).getWeight(), right_answer.get(i).getWeight());
        }
    }
}