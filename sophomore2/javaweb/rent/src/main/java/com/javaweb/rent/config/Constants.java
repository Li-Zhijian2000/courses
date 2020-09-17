package com.javaweb.rent.config;

public class Constants {

    public static final String USERNAME_REGEX = "^[_.@A-Za-z0-9-]*$";

    public static final String TENANT = "ROLE_TENANT";
    public static final String STAFF = "ROLE_STAFF";

    public static final String AUTHORITY_REGEX = "^(ROLE_TENANT)|(ROLE_STAFF)$";


    public static final String STAFF_EMAIL = "13261806700@163.com";
    
    private Constants() {
    }
}