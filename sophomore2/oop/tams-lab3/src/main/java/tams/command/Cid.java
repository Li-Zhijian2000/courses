package tams.command;

import java.io.PrintStream;

import tams.person.IDNum;

/**
 * CID
 */
public class Cid {
    public static void run(PrintStream out, String ID) {
        out.println(IDNum.checkIDNum(ID) ? "true" : "false");
    }
}