package com.lab2;

import org.junit.Test;
import org.junit.Assert;

public class RC4Tests {
    @Test (expected = IllegalArgumentException.class)
    public void throwNulllStr() {
    	RC4 rc4 = new RC4(5);
    	rc4.encode(null);   	
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void throwEmptyStr() {
    	RC4 rc4 = new RC4(5);
    	String s = "";
    	rc4.encode(s);   	
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void throwTooSmallN() {
    	RC4 rc4 = new RC4(0);  	
    }
    
    @Test (expected = IllegalArgumentException.class)
    public void throwTooBigN() {
    	RC4 rc4 = new RC4(257);  	
    }
    
    @Test
    public void correctEnciphering() {
    	RC4 rc4 = new RC4(45);
    	String msg = "Hello world it's meeeeeeeeeeee";
		String cmsg = rc4.encode(msg);
		String dcmsg = rc4.decode(cmsg);
    	Assert.assertEquals(msg, dcmsg);
    }
}