package tams.command;

import java.io.PrintStream;

import tams.person.IDNum;

/**
 * CID
 */
public class CID {

    public static void cid(PrintStream out, String ID) {
        out.println(IDNum.checkIDNum(ID) ? "true" : "false");
    }
}