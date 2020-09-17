package person;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

enum Sex {
    F, M;
}

/**
 * IDNum
 */
public class IDNum {

    private String idNumber;
    private String birthday;
    private Sex sex;

    public static boolean checkIDNum(String idNumber) {
        if (idNumber.length() != 18)
            return false;

        if (!verifyCode(idNumber))
            return false;

        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");

        try {
            dateFormat.setLenient(false);
            dateFormat.parse(idNumber.substring(Constants.BIRTHDAY_BEGIN_INDEX, Constants.BIRTHDAY_END_INDEX));

        } catch (ParseException e) {
            return false;
        }
        return true;
    }

    public IDNum(String idNumber) {
        this.idNumber = idNumber;
        this.parse();
    }

    public String getBirthday() {
        return this.birthday;
    }

    public Sex getSex() {
        return this.sex;
    }

    @Override
    public String toString() {
        return this.idNumber;
    }

    private static boolean verifyCode(String idNumber) {
        final int[] W = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2, 1 };

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

    private void parse() {
        try {
            SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
            Date date = dateFormat.parse(
                    this.idNumber.toString().substring(Constants.BIRTHDAY_BEGIN_INDEX, Constants.BIRTHDAY_END_INDEX));
            dateFormat.applyPattern("yyyy/MM/dd");
            this.birthday = dateFormat.format(date);

            char ch = this.idNumber.toString().charAt(Constants.SEX_INDEX);
            this.sex = (Character.getNumericValue(ch) % 2 == 1) ? Sex.M : Sex.F;
            
        } catch (ParseException e) {
        }
    }
}