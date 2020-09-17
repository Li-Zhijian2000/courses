package tams.person;

import java.text.*;

/**
 * IDNum
 */
public final class IDNum {

    private String ID;

    public void init(String ID) throws IDFormatException {
        if (ID == null) {
            ID = "";
        }

        ID = ID.replaceAll("\\s+", "").replace('x', 'X');

        checkID(ID);
        this.ID = ID;
    }

    public static boolean checkIDNum(String ID) {
        try {
            new IDNum().init(ID);
        } catch (IDFormatException e) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return ID;
    }

    private static void checkID(String ID) throws IDFormatException {
        if (ID.length() != 18) {
            throw new IDFormatException();
        }

        if (!verifyCode(ID)) {
            throw new IDFormatException();
        }

        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");

        try {
            dateFormat.setLenient(false);
            dateFormat.parse(ID.substring(Constants.BIRTHDAY_BEGIN_INDEX,
                    Constants.BIRTHDAY_END_INDEX));
        } catch (ParseException e) {
            throw new IDFormatException();
        }
    }

    private static boolean verifyCode(String ID) {
        final int[] W = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2,
                1 };

        int code = 0;

        for (int i = 0; i < 18; i++) {
            char ch = ID.charAt(i);

            if (!(Character.isDigit(ch) || (i == 17 && ch == 'X'))) {
                return false;
            }

            if (ch == 'X') {
                code += 10 * W[i] % 11;
            } else {
                code += Character.getNumericValue(ch) * W[i] % 11;
            }
        }

        return code % 11 == 1;
    }
}