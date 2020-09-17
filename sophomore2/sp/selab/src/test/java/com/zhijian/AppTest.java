package com.zhijian;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

/**
 * Unit test for simple App.
 */
class MainTest {
    /**
     * Rigorous Test.
     */
    @Test
    void InputIllegalTest() {
        assertEquals(false, Main.input_judge("q w e"));
        assertEquals(false, Main.input_judge("1.111 1 2"));
        assertEquals(false, Main.input_judge("1.1111 -2 3"));
        assertEquals(false, Main.input_judge("1.111 3 0.9"));
        assertEquals(false, Main.input_judge("0 0 0"));
        assertEquals(false, Main.input_judge("2 1.1 2"));
        assertEquals(false, Main.input_judge("4 1.1 -5"));
        assertEquals(false, Main.input_judge("6 8 -10"));
        assertEquals(false, Main.input_judge("2 1.1 2"));
        assertEquals(false, Main.input_judge("10001 10001 10001"));

    }

    @Test
    void RegularTest() {
        assertEquals(true, Main.regular(3, 4, 5));
        assertEquals(false, Main.regular(1, 2, 3));
        assertEquals(false, Main.regular(3, 2, 1));
        assertEquals(false, Main.regular(2, 3, 1));
        assertEquals(false, Main.regular(10001, 10001, 10001));
    }

    @Test
    void IsoTest() {
        assertEquals(true, Main.iso(3, 4, 3));
        assertEquals(true, Main.iso(3, 3, 4));
        assertEquals(true, Main.iso(4, 3, 3));

    }

    @Test
    void EquTest() {
        assertEquals(true, Main.equ(3, 3, 3));
    }
}
