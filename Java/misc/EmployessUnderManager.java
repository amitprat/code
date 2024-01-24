package programs.misc;

import java.util.*;

public class EmployessUnderManager {
    private final Map<String, List<String>> employees = new HashMap<>();

    public static void test() {
        EmployessUnderManager obj = new EmployessUnderManager();
        obj.add("A", "C");
        obj.add("B", "C");
        obj.add("C", "F");
        obj.add("D", "E");
        obj.add("E", "F");
        obj.add("F", "F");

        obj.printEmployees();
    }

    private void printEmployees() {
        HashSet<String> empSet = new HashSet<>();
        employees.entrySet().forEach(s -> {
            empSet.add(s.getKey());
            for (var e : s.getValue()) empSet.add(e);
        });
        for (var emp : empSet) {
            var res = countEmployees(emp);
            System.out.println(emp + " : " + res);
        }
    }

    private List<String> countEmployees(String manager) {
        List<String> result = new ArrayList<>();
        if (!employees.containsKey(manager)) return result;

        for (var emp : employees.get(manager)) {
            if (emp.equals(manager)) continue;
            result.add(emp);
            result.addAll(countEmployees(emp));
        }

        return result;
    }

    private void add(String employee, String manager) {
        if (!employees.containsKey(manager)) {
            employees.put(manager, new ArrayList<>());
        }
        employees.get(manager).add(employee);
    }
}
