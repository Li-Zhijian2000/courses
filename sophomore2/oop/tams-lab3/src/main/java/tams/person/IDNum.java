package tams.person;

import java.text.*;

/**
 * IDNum
 */
public final class IDNum {

    private String idNumber;

    public void init(String idNumber) throws IDFormatException {
        idNumber = idNumber.replaceAll("\\s+", "").replace('x', 'X');

        checkID(idNumber);
        this.idNumber = idNumber;
    }

    public static boolean checkIDNum(String idNumber) {
        try {
            new IDNum().init(idNumber);
        } catch (IDFormatException e) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return idNumber;
    }

    private static void checkID(String idNumber) throws IDFormatException {
        if (idNumber.length() != 18) {
            throw new IDFormatException();
        }

        if (!verifyCode(idNumber)) {
            throw new IDFormatException();
        }

        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");

        try {
            dateFormat.setLenient(false);
            dateFormat.parse(idNumber.substring(Constants.BIRTHDAY_BEGIN_INDEX,
                    Constants.BIRTHDAY_END_INDEX));
        } catch (ParseException e) {
            throw new IDFormatException();
        }
    }

    private static boolean verifyCode(String idNumber) {
        final int[] W = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2,
                1 };

        int code = 0;

        for (int i = 0; i < 18; i++) {
            char ch = idNumber.charAt(i);

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