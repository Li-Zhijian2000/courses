package tams.command;

import java.io.PrintStream;

import tams.Shell.FailType;
import tams.person.IDFormatException;
import tams.person.Person;

/**
 * NP
 */
public class NP {
    public static void np(PrintStream out, String name, String ID) {
        try {
            Person person = new Person();
            person.init(name, ID);
            out.println(person);
        } catch (IDFormatException e) {
            out.println(FailType.ID_illegal);
        }
    }
}