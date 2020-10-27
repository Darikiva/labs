package com.testClient;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;

public class MyLoader extends ClassLoader {
    @Override
    public Class findClass(String name) throws ClassNotFoundException {
        byte[] b = loadClassFromFile(name);
        return defineClass(name, b, 0, b.length);
    }

    private byte[] loadClassFromFile(String file) {
        InputStream inputStream = getClass().getClassLoader().getResourceAsStream(file.replace('.', File.separatorChar) + ".class");
        byte[] answer;
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        int nextValue = 0;
        try {
            while ((nextValue = inputStream.read()) != -1) {
                byteArrayOutputStream.write(nextValue);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        answer = byteArrayOutputStream.toByteArray();
        return answer;
    }
}
