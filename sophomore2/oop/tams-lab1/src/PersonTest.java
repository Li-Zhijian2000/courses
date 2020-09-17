import java.util.Arrays;
/**
 * PersonTest
 */
public class PersonTest {
    public static void main(String[] args) {
        try {
            final int len = args.length;
            if (len == 0) {
                throw new ArgsParserException();
            }
            switch (args[0]) {
                case "cid": 
                    if (len != 2) {
                        throw new ArgsParserException();
                    }
                    cid(Arrays.copyOfRange(args, 1, args.length));
                    break;
                
                case "np":
                    if (len != 3) {
                        throw new ArgsParserException();
                    }
                    np(Arrays.copyOfRange(args, 1, args.length));
                    break;
    
                default:
                    throw new ArgsParserException();
            }
        } catch (ArgsParserException e) {
            System.out.println(inputIllegalError);
        } catch (IDFormatException e) {
            System.out.println(idIllegalError);
        }
    }
    
    private static String inputIllegalError = "Input illegal";
    private static String idIllegalError = "ID illegal";

    private static void cid(String[] input) {
        String ID = "";
        for (String str: input) {
            ID += str;
        }

        if (IDNum.checkIDNum(ID)) {
            System.out.println("true");
        } 
        else {
            System.out.println("false");
        }
    }

    private static void np(String[] input) throws IDFormatException {
        String ID = "";
        for (int i = 1; i < input.length; i++) {
            ID += input[i];
        }
        Person person = new Person();
        person.init(input[0], ID);
        System.out.println(person);
    }
}