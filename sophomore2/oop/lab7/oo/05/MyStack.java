import java.util.LinkedList;

public class MyStack<T> {
    private LinkedList<T> values = new LinkedList<T>();

    public void push(T t) {
        values.push(t);
    }

    public T pull() {
        return values.poll();
    }

    public T peek() {
        return values.peek();
    }

    public static void main(String[] args) {
        MyStack<Double> stack = new MyStack();

        stack.push(1.4);
        stack.push(2.020);

        System.out.println(stack.pull());
        System.out.println(stack.peek());
    }
}
