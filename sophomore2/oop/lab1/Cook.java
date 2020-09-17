class Person {

    protected String name;

    protected Person(String name) {
        this.name = name;
    }
}

class Chef extends Person {
    
    public Chef(String name) {
        super(name);
    }

    public void cook(String thing) {

        System.out.println(this.name + " cooks " + thing);
    }
}
class Buyer extends Person {
    
    public Buyer(String name) {
        super(name);
    }

    public void buy(String thing) {

        System.out.println(this.name + " buys " + thing);
    }
}
public class Cook {

    public static void main(String[] args) {
        
        Buyer aunt = new Buyer("Aunt"), 
              mother = new Buyer("Mother"), 
              i = new Buyer("I");
        
        Chef father = new Chef("father"),
             uncle = new Chef("Uncle");

        aunt.buy("牛奶");
        i.buy("鸡肉");
        mother.buy("牛肉");

        father.cook("西红柿炒蛋");
        uncle.cook("鸡汤");
    }
}