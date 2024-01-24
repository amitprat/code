package programs.graph;

import programs.types.Pair;

import java.util.*;
import java.util.stream.Collectors;

import static java.util.function.Predicate.not;

public class FriendGraph<T> {
    private final Map<String, Node> people;
    private final int levelLimit = 2;

    FriendGraph() {
        people = new HashMap<>();
    }

    public static void test() {
        FriendGraph<Node> obj = new FriendGraph<Node>();
        obj.add(new Node("A"));
        obj.add(new Node("B"));
        obj.add(new Node("C"));
        obj.add(new Node("D"));
        obj.add(new Node("E"));
        obj.add(new Node("F"));
        obj.add(new Node("G"));
        obj.add(new Node("H"));
        obj.addFriend("A", "B");
        obj.addFriend("B", "C");
        obj.addFriend("B", "G");
        obj.addFriend("C", "E");
        obj.addFriend("D", "F");
        obj.addFriend("D", "C");
        obj.addFriend("D", "H");

        System.out.println("Graph: ");
        System.out.println(obj.toString());

//        for (programs.Node node : obj) {
//            System.out.println(node.toString());
//        }
//
        System.out.println("D and B's Mutual Friend List: ");
        Set<Node> nodes = obj.findMutualFriends("D", "B");
        for (Node node : nodes) {
            System.out.println(node.toString());
        }
//
        System.out.println("Friend suggestion to A: ");
        nodes = obj.suggestFriends("A");
        for (Node node : nodes) {
            System.out.println(node.toString());
        }
//
//        obj.delete("D");

    }

    boolean add(Node node) {
        people.put(node.name, node);
        return true;
    }

    Node get(String name) {
        if (people.containsKey(name)) {
            return people.get(name);
        }
        return null;
    }

    boolean addFriend(String first, String second) {
        if (!people.containsKey(first)) return false;
        if (!people.containsKey(second)) return false;

        Node firstNode = people.get(first);
        Node secondNode = people.get(second);

        firstNode.addFriend(secondNode);
        //secondNode.addFriend(firstNode);

        return true;
    }

    Set<Node> findMutualFriends(String first, String second) {
        Set<Node> firstFriends = people.get(first).friends;
        Set<Node> secondFriends = people.get(second).friends;
        return firstFriends.stream().filter(secondFriends::contains).collect(Collectors.toSet());
    }

    Set<Node> suggestFriends(String name) {
        Node node = people.get(name);
        Set<Node> suggestions = new HashSet<>();
        suggestFriendsInternal(node, node,1, suggestions);
        return suggestions;
    }

    void suggestFriendsInternal(Node root, Node cur, int curLevel, Set<Node> suggestions) {
        if (curLevel > levelLimit) return;
        for (Node friend : cur.friends) {
            Set<Node> curSuggestion = friend.friends.stream().filter(not(root.friends::contains)).collect(Collectors.toSet());
            curSuggestion = curSuggestion.stream().filter(x->x.name != root.name).collect(Collectors.toSet());
            suggestions.addAll(curSuggestion);
            suggestFriendsInternal(root,friend, curLevel + 1, suggestions);
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Map.Entry<String, Node> entry : people.entrySet()) {
            sb.append(entry.getValue().toString());
            sb.append("\n");
            sb.append("Friends : ");
            for (Node friend : entry.getValue().friends) {
                sb.append(friend.toString());
                sb.append(", ");
            }
            sb.append("\n\n");
        }
        return sb.toString();
    }

    private static class Node {
        String name;
        Set<Node> friends;
        List<String> newsFeed;
        List<Pair<Node, String>> wall;

        Node(String name) {
            this.name = name;
            this.friends = new HashSet<>();
            this.newsFeed = new ArrayList<>();
            this.wall = new ArrayList<>();
        }

        boolean addFriend(Node other) {
            friends.add(other);
            return true;
        }

        boolean post(String message) {
            newsFeed.add(message);
            for (Node friend : friends) {
                friend.publish(this, message);
            }

            return true;
        }

        boolean publish(Node other, String message) {
            wall.add(new Pair<>(other, message));
            return true;
        }

        @Override
        public String toString() {
            StringBuilder sb = new StringBuilder();
            sb.append("{");
            sb.append("Name: " + name);
//            sb.append("\n");

//            sb.append("Friends: {");
//            for (programs.Node friend : friends) sb.append("{Name: " + friend.name + "}");
//            sb.append("}");
//            sb.append("\n");

//            sb.append("NewsFeed: {");
//            for (String news : newsFeed) {
//                sb.append(news);
//                sb.append("\n");
//            }
//            sb.append("}");
//
//            sb.append("Wall: {");
//            for (Pair<programs.Node, String> w : wall) {
//                sb.append(w.getKey().name + ":" + w.getValue());
//                sb.append("\n");
//            }
//            sb.append("}");
            sb.append("}");

            return sb.toString();
        }
    }
}