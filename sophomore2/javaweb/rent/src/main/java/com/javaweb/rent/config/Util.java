package com.javaweb.rent.config;

import java.util.Random;

public class Util {
    
    private Util() {}

    public static String generateActivationKey() {
        Random random = new Random();
        return random.nextInt(100000) + "";
    }
}