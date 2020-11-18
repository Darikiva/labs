package com.smth.parsers;

import com.smth.gem.Color;
import com.smth.gem.Gem;
import com.smth.gem.Preciousness;
import com.smth.gem.VisualParameters;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class GemDOMParser {
    public static ArrayList<Gem> parse(String XMLpath, String XSDpath) throws IOException, SAXException, ParserConfigurationException {
        if (XSDpath != null)
            if (!MyValidator.validate(XMLpath, XSDpath)) return new ArrayList<>();

        ArrayList<Gem> gems = new ArrayList<>();
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();

        DocumentBuilder builder = factory.newDocumentBuilder();

        Document document = builder.parse(new File(XMLpath));
        NodeList gemsElements = document.getDocumentElement().getElementsByTagName("gem");
        for(int i = 0; i < gemsElements.getLength(); ++i) {
            Node gemElement = gemsElements.item(i);
//            if (gemElement.getChildNodes().item(0).getNodeType() != Node.TEXT_NODE)
//            System.out.println("shobl");
            gems.add(getGem(gemElement));
//            else System.out.println(gemElement.getNodeName());
        }
        return gems;
    }

    private static Gem getGem(Node gemElement) {
        NodeList childs = gemElement.getChildNodes();
        Map<String, String> fields = new HashMap<>();
        VisualParameters visualParameters = null;
        for(int i = 0; i < childs.getLength(); ++i) {
//            System.out.println(childs.item(0).getNodeName());
            if (childs.item(i).getNodeType() == Node.TEXT_NODE) {
            }
            else if (childs.item(i).getNodeName() == "visualParameters") {
                Node vpNode = childs.item(i);
                visualParameters = new VisualParameters(
                        Color.valueOf(vpNode.getAttributes().getNamedItem("color").getNodeValue()),
                        Integer.parseInt(vpNode.getAttributes().getNamedItem("transparency").getNodeValue()),
                        Integer.parseInt(vpNode.getAttributes().getNamedItem("edges").getNodeValue())
                );
            }
            else fields.put(childs.item(i).getNodeName(), childs.item(i).getAttributes().getNamedItem("value").getNodeValue());
        }
        return new Gem(
                fields.get("name"),
                Preciousness.valueOf(fields.get("preciousness")),
                fields.get("origin"),
                visualParameters,
                Integer.parseInt(fields.get("weight"))
        );
    }
}
