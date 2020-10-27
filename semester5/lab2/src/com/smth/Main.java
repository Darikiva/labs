package com.smth;

import com.smth.gem.Gem;
import com.smth.parsers.GemStAXParser;
import org.xml.sax.SAXException;


import javax.xml.parsers.ParserConfigurationException;
import javax.xml.stream.XMLStreamException;
import java.io.IOException;
import java.util.ArrayList;

public class Main {

    public static void main(String[] args) throws ParserConfigurationException, SAXException, IOException, XMLStreamException {
	// write your code here
        ArrayList<Gem> gems = GemStAXParser.parse("Gems/gems.xml");
        for (Gem gem: gems) {
            gem.printGem();
        }
    }
}
