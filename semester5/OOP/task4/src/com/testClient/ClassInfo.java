package com.testClient;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

public class ClassInfo {
    static public void getInfo(String class_name) throws ClassNotFoundException {
        Class c /*= Class.forName(class_name)*/ = null;
        MyLoader myLoader = new MyLoader();

        try {
            c = myLoader.loadClass(class_name);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }


        
        int mods = c.getModifiers();
        System.out.print(Modifier.toString(mods) + c.getName() + " ");
        System.out.print("extends " + c.getSuperclass().getName());
        Class[] interfaces = c.getInterfaces();
        if (interfaces.length != 0) {
            System.out.print("implements ");
            for (Class cInterface: interfaces) {
                System.out.print(cInterface.getName() + " ");
            }
        }
        System.out.println();
        Field[] fields = c.getDeclaredFields();
        for(Field field: fields) {
            int mod = field.getModifiers();
            System.out.println(Modifier.toString(mod) + " " + field.getType().getName() + " " + field.getName());
        }

        Constructor[] cons = c.getConstructors();
        for(Constructor con: cons) {
            int mod = con.getModifiers();
            System.out.print(Modifier.toString(mod) + " " );
            System.out.print(con.getName() + " (");
            Class[] params = con.getParameterTypes();
            for(Class param: params) {
                System.out.print(param.getName() + ", ");
            }
            System.out.println(") ");
        }
        Method[] methods = c.getDeclaredMethods();
        for(Method method: methods) {
            int mod = method.getModifiers();
            System.out.print(Modifier.toString(mod) + " ");
            System.out.print(method.getReturnType().getName() + " " + method.getName() + " (" );
            Class[] params = method.getParameterTypes();
            for(Class param: params) {
                System.out.print(param.getName() + ", ");
            }
            System.out.println(")");
        }
    }
}
