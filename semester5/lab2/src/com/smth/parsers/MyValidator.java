package com.smth.parsers;

import org.xml.sax.SAXException;

import javax.xml.XMLConstants;
import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;
import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

public class MyValidator {
    public static boolean validate(String XMLpath, String XSDpath) throws MalformedURLException {
        File schemaFile = new File(XSDpath);
        Source xmlFile = new StreamSource(new File(XMLpath));
        SchemaFactory schemaFactory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
        try {
            Schema schema = schemaFactory.newSchema(schemaFile);
            Validator validator = schema.newValidator();
            validator.validate(xmlFile);
//            System.out.println(xmlFile.getSystemId() + " is valid");
            return true;
        } catch (SAXException e) {
//            e.printStackTrace();
//            System.out.println(xmlFile.getSystemId() + " is NOT valid");
            return false;
        } catch (IOException e) {
//            e.printStackTrace();
            return false;
        }
    }
}
