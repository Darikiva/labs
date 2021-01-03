package com.smth.parsers;

import com.smth.gem.Color;
import com.smth.gem.Gem;
import com.smth.gem.Preciousness;
import com.smth.gem.VisualParameters;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;
import javax.xml.stream.events.XMLEvent;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class GemStAXParser{
    private static final XMLInputFactory factory = XMLInputFactory.newInstance();

    public static ArrayList<Gem> parse(String XMLpath, String XSDpath) throws XMLStreamException, IOException {
        if (XSDpath != null)
            if (!MyValidator.validate(XMLpath, XSDpath)) return new ArrayList<>();
        InputStream s = Files.newInputStream(Path.of(XMLpath));
        XMLStreamReader reader = factory.createXMLStreamReader(s);
        ArrayList<Gem> gems = new ArrayList<>();
        while (reader.hasNext()) {
            int event = reader.next();
            if (event == XMLEvent.START_ELEMENT && reader.getLocalName().equals("gem")) {
                gems.add(getGem(reader));
            }
        }
        return gems;
    }

    private static Gem getGem(XMLStreamReader reader) throws XMLStreamException {
        Map<String, String> fields = new HashMap<>();
        VisualParameters visualParameters = null;
        int event = 0;
        boolean flag = true;
        do {
            event = reader.next();
            if (event == XMLEvent.START_ELEMENT) {
                if (reader.getLocalName().equals("visualParameters")) {
                    visualParameters = new VisualParameters(
                            Color.valueOf(reader.getAttributeValue(reader.getNamespaceURI(), "color")),
                            Integer.parseInt(reader.getAttributeValue(reader.getNamespaceURI(), "transparency")),
                            Integer.parseInt(reader.getAttributeValue(reader.getNamespaceURI(), "edges"))
                    );
                } else
                fields.put(reader.getLocalName(), reader.getAttributeValue(reader.getNamespaceURI(), "value"));
            }
            if (event != XMLEvent.CHARACTERS) {
                if ((reader.getLocalName().equals("gem") && event == XMLEvent.END_ELEMENT)) flag = false;
            }
        } while (flag);
        return new Gem(
                fields.get("name"),
                Preciousness.valueOf(fields.get("preciousness")),
                fields.get("origin"),
                visualParameters,
                Integer.parseInt(fields.get("weight"))
        );
    }
}
