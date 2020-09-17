// package com.zhijian;

import java.util.Scanner;

public final class Main {

    /**
     * Says hello to the world.
     * 
     * @param args The arguments of the program.
     */
    public static void main(String[] args) {

        try (Scanner scanner = new Scanner(System.in);) {

            int a = scanner.nextInt(), b = scanner.nextInt(), c = scanner.nextInt();
            
            if (outRange(a) || outRange(b) || outRange(c))
                throw new Exception();
            
            if (a + b <= c || b + c <= a || c + a <= b)
                throw new Exception();
            
            if (a == b && b == c)
                System.out.println("equilateral triangle!");
            
            else if (a == b || b == c || c == a)
                System.err.println("isosceles triangle!");
            
            else System.out.println("regular triangle!");

        } catch (Exception e) {
            System.out.println("not a triangle!");
        }
    }

    private static boolean outRange(int a) {
        return a < 1 || a > 10000;
    }
}
