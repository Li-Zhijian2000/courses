class ShapeSequence {

    final private Shape[] shapes;
    private int size;
    final private int maxSize;

    public ShapeSequence(int size) {
        if (size < 0)
            size = 0;

        this.shapes = new Shape[size];
        this.maxSize = size;
        this.size = 0;
    }

    public void add(Shape shape) {
        if (this.size < this.maxSize)
            shapes[this.size++] = shape;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("[");
        SequenceIterator it = this.iterator();
        while (!it.isEnd()) {
            String name = it.current().getClass().getName();
            sb.append(Character.toLowerCase(name.charAt(0))).append(name.substring(1));
            it.moveNext();

            if (!it.isEnd())
                sb.append(", ");
            else
                sb.append("]");
        }
        return sb.toString();
    }

    public SequenceIterator iterator() {
        return new SequenceIterator();
    }

    public class SequenceIterator {

        private int index;
        final ShapeSequence container;

        public SequenceIterator() {
            this.index = 0;
            this.container = ShapeSequence.this;
        }

        public boolean isEnd() {
            return this.index == ShapeSequence.this.size;
        }

        public Shape current() {
            if (isEnd())
                return null;
            return ShapeSequence.this.shapes[index];
        }

        public void moveNext() {
            if (!isEnd())
                this.index++;
        }

        @Override
        public boolean equals(Object obj) {
            if (obj == null)
                return false;

            if (this == obj)
                return true;

            if (obj instanceof SequenceIterator) {
                SequenceIterator o = (SequenceIterator) obj;
                if (this.container != o.container)
                    return false;
                return this.index == o.index;
            }
            return false;
        }
    }
}