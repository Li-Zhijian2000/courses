public class Test {
    public static void main(String[] args) {
        ShapeSequence seq = new ShapeSequence(5);
        seq.add(new Rectangle(1.0, 1.0));
        seq.add(new Ellipse(1.0, 1.0));
        seq.add(new Rhombus(1.0, 1.0));

        // output: [rectangle, ellipse, rhombus]
        System.out.println(seq);

        // it.current() is a Rectangle
        ShapeSequence.SequenceIterator it = seq.iterator();
        ShapeSequence.SequenceIterator it2 = seq.iterator();

        // output: false
        System.out.println(it == it2);

        // output: true
        System.out.println(it.equals(it2));

        ShapeSequence seq2 = new ShapeSequence(5);
        seq2.add(new Rectangle(1.0, 1.0));
        seq2.add(new Ellipse(1.0, 1.0));
        seq2.add(new Rhombus(1.0, 1.0));

        // output: false
        System.out.println(it2.equals(seq2.iterator()));

        // output: Rectangle@xxxxxxx
        System.out.println(it.current());

        // it.current() is a Ellipse
        it.moveNext();

        // output: false
        System.out.println(it.equals(it2));

        // output: Ellipse@xxxxxxx
        System.out.println(it.current());

        // it.current() is a Rhombus
        it.moveNext();

        // output: Rhombus@xxxxxxx
        System.out.println(it.current());

        // output: false
        System.out.println(it.isEnd());

        // it reaches the end of seq
        it.moveNext();

        // output: true
        System.out.println(it.isEnd());

        // noooooooooooo
        // System.out.println(it.current());

        // move it2 to the end of seq
        it2.moveNext();
        it2.moveNext();
        it2.moveNext();

        // do nothing
        it2.moveNext();
        it2.moveNext();
        it2.moveNext();

        // output: true
        System.out.println(it.equals(it2));

        // fulfill seq
        seq.add(new Rectangle(1.0, 1.0));
        seq.add(new Ellipse(1.0, 1.0));

        // output: [rectangle, ellipse, rhombus, rectangle, ellipse]
        System.out.println(seq);

        // output: false
        System.out.println(it.isEnd());

        // do nothing
        seq.add(new Rhombus(1.0, 1.0));

    }
}