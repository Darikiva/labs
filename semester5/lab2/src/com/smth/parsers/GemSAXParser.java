package com.smth.parsers;


import com.smth.gem.Color;
import com.smth.gem.Gem;
import com.smth.gem.Preciousness;
import com.smth.gem.VisualParameters;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class GemSAXParser {
    private static ArrayList<Gem> gems = new ArrayList<>();
    public static ArrayList<Gem> parse(String XMLpath, String XSDpath) throws ParserConfigurationException, SAXException, IOException {
        if (XSDpath != null)
            if (!MyValidator.validate(XMLpath, XSDpath)) return new ArrayList<>();
        SAXParserFactory factory = SAXParserFactory.newInstance();
        SAXParser parser = factory.newSAXParser();

        AdvancedXMLHandler handler = new AdvancedXMLHandler();
        parser.parse(new File(XMLpath), handler);

        return gems;
    }

    private static class AdvancedXMLHandler extends DefaultHandler {
        private String lastElementName = null;
        private VisualParameters visualParameters = null;
        Map<String, String> fields = new HashMap<>();

        @Override
        public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
            if (lastElementName != null) {
                if (qName.equals("visualParameters")) {
                    visualParameters = new VisualParameters(
                            Color.valueOf(attributes.getValue("color")),
                            Integer.parseInt(attributes.getValue("transparency")),
                            Integer.parseInt(attributes.getValue("edges"))
                    );
                }
                fields.put(qName,attributes.getValue("value"));
            }
            else if (qName.equals("gem")) lastElementName = localName;
//            System.out.println(qName);
        }

        @Override
        public void endElement(String uri, String localName, String qName) throws SAXException {
            if (qName.equals("gem")) {
                lastElementName = null;
                gems.add(new Gem(
                        fields.get("name"),
                        Preciousness.valueOf(fields.get("preciousness")),
                        fields.get("origin"),
                        visualParameters,
                        Integer.parseInt(fields.get("weight"))
                ));
                lastElementName = null;
                fields.clear();
            }
        }
    }
}
