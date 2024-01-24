package programs.misc;

import java.util.*;

public class MyIterator implements Iterator {
    private final Iterator iterator;
    private final Collection arrayList = new ArrayList();

    MyIterator(Collection collection) {
        extractAll(collection);
        iterator = arrayList.iterator();
    }

    public static void test() {
        Collection<List<Integer>> collection = Arrays.asList(Arrays.asList(1, 2), Arrays.asList(3, 4));
        MyIterator iterator = new MyIterator(collection);
        while (iterator.hasNext()) {
            System.out.print(iterator.next() + ", ");
        }
        System.out.println();
    }

    void extractAll(Collection collection) {
        Iterator<List<Integer>> itr = collection.iterator();
        while (itr.hasNext()) {
            for (Integer i : itr.next()) arrayList.add(i);
        }
    }

    @Override
    public boolean hasNext() {
        return iterator.hasNext();
    }

    @Override
    public Object next() {
        return iterator.next();
    }
}
