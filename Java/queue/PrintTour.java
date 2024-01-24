package programs.queue;

import java.util.ArrayList;
import java.util.List;

public class PrintTour {
    static void test() {
        PrintTour obj = new PrintTour();
        List<Node> nodes = new ArrayList<>();
        nodes.add(obj.new Node(6, 4));
        nodes.add(obj.new Node(3, 6));
        nodes.add(obj.new Node(7, 3));

        List<Node> result = obj.getTour(nodes);
        for (Node n : result) {
            System.out.println(n.toString());
        }
    }

    List<Node> getTour(List<Node> nodes) {
        int start = 0, end = 0;
        int size = nodes.size();
        List<Node> validNodes = new ArrayList<>();
        int curPetrol = 0;
        do {
            while (curPetrol < 0 && start != end) {
                Node n = validNodes.remove(start++);
                curPetrol -= n.petrol - n.distance;
                start = (start + 1) % size;
            }

            validNodes.add(nodes.get(end));
            curPetrol += nodes.get(end).petrol - nodes.get(end).distance;
            end = (end + 1) % size;
        } while (start != end);

        return validNodes;
    }

    class Node {
        int petrol;
        int distance;

        Node(int petrol, int distance) {
            this.petrol = petrol;
            this.distance = distance;
        }

        @Override
        public String toString() {
            return petrol + ":" + distance;
        }
    }
}
