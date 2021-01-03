package com.smth.tests;

import com.smth.parsers.MyValidator;
import org.junit.jupiter.api.Test;
import org.xml.sax.SAXException;

import java.net.MalformedURLException;

import static org.junit.jupiter.api.Assertions.*;

class MyValidatorTest {

    @Test
    void validate() throws MalformedURLException {
        assertTrue(MyValidator.validate("Gems/gems.xml", "Gems/gems.xsd"));
        assertFalse(MyValidator.validate("Gems/extraField.xml", "Gems/gems.xsd"));
        assertFalse(MyValidator.validate("Gems/noField.xml", "Gems/gems.xsd"));
        assertFalse(MyValidator.validate("Gems/wrongData.xml", "Gems/gems.xsd"));
    }
}