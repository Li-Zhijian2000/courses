public class Person {
    void speakHello() { 
        System.out.print("您好，很高兴认识您");
        System.out.println(" nice to meet you");
    }
}
  
class Xiti {    
    public static void main(String args[]) {
        Person zhang = new Person();
        zhang.speakHello();
    }
}