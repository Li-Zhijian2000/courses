package phone;

import phone.Mobilephone.Brand;
import phone.Mobilephone.HuaweiModel;
import phone.Mobilephone.SamsangModel;

public class MobilephoneTest {
    public static void main(String[] args) {
        Mobilephone huaweiMate30 = new Mobilephone(Brand.HUAWEI, HuaweiModel.MATE30);
        System.out.println(huaweiMate30);

        Mobilephone samsangNote10 = new Mobilephone(Brand.SAMSANG, SamsangModel.NOTE10);
        System.out.println(samsangNote10);
    }
}