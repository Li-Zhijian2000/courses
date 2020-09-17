class Wheel {
    private String name;

    public Wheel(String name) {
        this.name = name;
    }

    public getName() {
        return this.name;
    }
}

class Engine {
    private String name;

    public Engine(String name) {
        this.name = name;
    }

    public getName() {
        return this.name;
    }
}

public class Vehicle {
    protected Engine engine;
    protected Wheel wheel;
    protected int wheelCount;

    public void setWheelCount(int wheelCount) {
        this.wheelCount = wheelCount;
    }
}
