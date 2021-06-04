package com.lab2;

import java.util.*;

public class RC4 {
    private Character[] key;
    private Character[] S;
    private static final Random rand = new Random();

    public RC4(int n) {
        if (n < 1 || n > 256) {
            throw new IllegalArgumentException("Invalid length");
        }
        key = new Character[n];
        for (int i = 0; i < n; ++i) {
            key[i] = (char) rand.nextInt();
        }
    }

    public String encode(String str) {
        return convert(str);
    }

    public String decode(String str) {
        return convert(str);
    }

    private String convert(String str) {
        if (str == null || str.length() == 0) {
            throw new IllegalArgumentException("Invalid str");
        }

        Character[] keystream = getKey(str.length());
        StringBuilder strbld = new StringBuilder();

        for (int i = 0; i < str.length(); ++i) {
            char c = (char) (str.charAt(i) ^ keystream[i]);
            strbld.append(c);
        }
        return strbld.toString();
    }

    private void KSA() {
        S = new Character[256];
        for (int i = 0; i < 256; ++i) {
            S[i] = (char) i;
        }

        int i = 0, j = 0;
        for (i = 0; i < 256; ++i) {
            j = (j + S[i] + key[i % key.length]) % 256;
            swap(S, i, j);
        }

    }

    private Character[] getKey(int length) {
        KSA();
        Character[] key = new Character[length];
        int i = 0, j = 0;
        for (int k = 0; k < length; ++k) {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
            swap(S, i, j);
            int t = (S[i] + S[j]) % 256;
            key[k] = S[t];
        }
        return key;
    }

    public static final <T> void swap(T[] a, int i, int j) {
        T t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

}
