package Java.types;

public class Triplet<F, S, T> {
    public F first;
    public S second;
    public T third;

    public Triplet(F first, S second, T third) {
        this.first = first;
        this.second = second;
        this.third = third;
    }

    @Override
    public String toString() {
        return "{" +
                "first=" + first +
                ", second=" + second +
                ", third=" + third +
                '}';
    }
}
