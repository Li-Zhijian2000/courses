package phone;

public class Mobilephone {

    private Brand brand;
    private Model model;

    public Mobilephone(Brand brand, Model model) {
        this.brand = brand;
        this.model = model;
    }

    @Override
    public String toString() {
        return "this phone is " + brand + " " + model;
    }

    public enum Brand {
        HUAWEI, SAMSANG;
    }

    public enum HuaweiModel implements Model {
        P30, P40, MATE30, MATE40
    }

    public enum SamsangModel implements Model {
        S9, S10, NOTE9, NOTE10
    }

    private interface Model {

    }
}