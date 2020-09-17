/**
 * Human
 */
public class Human {

    private int weight;

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public void loseWeight(int weight) {
        this.weight -= weight;
    }

    public static void main(String[] args) {
        
        Human wang = new Human();
        wang.setWeight(70);
        wang.loseWeight(25);
        System.out.println(wang.getWeight());
    }
}