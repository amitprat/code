package Java.types;

public class Interval implements Comparable {
    public int start, end;

    public Interval(int start, int end) {
        this.start = start;
        this.end = end;
    }

    @Override
    public String toString() {
        return "Interval{" +
                "start=" + start +
                ", end=" + end +
                '}';
    }

    @Override
    public int compareTo(Object o) {
        return this.start - ((Interval) o).start;
    }
}
