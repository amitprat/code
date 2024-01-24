package programs.misc;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

enum State {
    BEGIN,
    NUM,
    DOT,
    SIGN,
    EXP,
    END
}

interface Predicate {
    boolean test(char ch);
}

public class CheckNumber {
    public static void test() {
        StateMachine machine = new StateMachine();
        machine.addStateValidate(State.NUM, (ch) -> IsNum(ch));
        machine.addStateValidate(State.SIGN, (ch) -> IsSign(ch));
        machine.addStateValidate(State.DOT, (ch) -> IsDot(ch));
        machine.addStateValidate(State.EXP, (ch) -> IsExp(ch));
        machine.addState(State.BEGIN, State.SIGN);
        machine.addState(State.BEGIN, State.DOT);
        machine.addState(State.BEGIN, State.NUM);

        machine.addState(State.SIGN, State.NUM);
        machine.addState(State.SIGN, State.DOT);

        machine.addState(State.NUM, State.END);
        machine.addState(State.NUM, State.NUM);
        machine.addState(State.NUM, State.EXP);

        machine.addState(State.DOT, State.NUM);
        machine.addState(State.DOT, State.END);

        machine.addState(State.EXP, State.SIGN);
        machine.addState(State.EXP, State.NUM);

        System.out.println("====Validate Success Cases=====");
        validateAndPrint(machine, "11.0");
        validateAndPrint(machine, "+1.10");
        validateAndPrint(machine, "-1.10");
        validateAndPrint(machine, "-110");
        validateAndPrint(machine, "110");
        validateAndPrint(machine, "11e0");
        validateAndPrint(machine, "10e-1");

        System.out.println("\n====Validate Failure Cases=====\n");
        validateAndPrint(machine, "*110");
        validateAndPrint(machine, "/110");
        validateAndPrint(machine, "s1s1s0");
        validateAndPrint(machine, "str");
        validateAndPrint(machine, ".");
        validateAndPrint(machine, "+");
        validateAndPrint(machine, "-");
        validateAndPrint(machine, "..");
        validateAndPrint(machine, "1.");
        validateAndPrint(machine, "+.");
        validateAndPrint(machine, "+1.1.1");
        validateAndPrint(machine, "11-e0");
        validateAndPrint(machine, "11e.0");
    }

    private static boolean IsExp(char ch) {
        return ch == 'e';
    }

    private static boolean IsNum(char ch) {
        return ch >= '0' && ch <= '9';
    }

    private static boolean IsSign(char ch) {
        return ch == '+' || ch == '-';
    }

    private static boolean IsDot(char ch) {
        return ch == '.';
    }

    private static void validateAndPrint(StateMachine machine, String str) {
        System.out.println("Is " + str + " is valid Num ? = " + machine.validate(str));
    }
}

class StateMachine {
    Map<State, List<State>> stateMap = new HashMap<>();
    Map<State, Predicate> predicateMap = new HashMap<>();

    private boolean dfs(String str, int index, List<State> states, boolean isDotSeen) {
        for (var state : states) {
            if (state == State.END && index == str.length()) return true;
            if (index == str.length()) return false;

            if (state == State.END) continue;
            if (state == State.DOT && isDotSeen) continue;
            if (predicateMap.get(state).test(str.charAt(index)) &&
                    dfs(str, index + 1, stateMap.get(state), state == State.DOT || isDotSeen)) {
                return true;
            }
        }
        return false;
    }

    void addStateValidate(State state, Predicate predicate) {
        predicateMap.put(state, predicate);
    }

    void addState(State from, State to) {
        if (stateMap.containsKey(from)) {
            stateMap.get(from).add(to);
            return;
        }
        List<State> res = new ArrayList<>();
        res.add(to);
        stateMap.put(from, res);
    }

    boolean validate(String str) {
        return dfs(str, 0, stateMap.get(State.BEGIN), false);
    }
}

//class GenericStateMachine<InputT,StateT,PredicatT> {
//    Map<StateT, List<StateT>> stateMap = new HashMap<>();
//    Map<StateT, PredicatT> predicateMap = new HashMap<>();
//
//    private boolean dfs(InputT input, List<StateT> states) {
//        for (var state : states) {
//            if (state == State.END && !input.hasNext()) return true;
//            if (!input.hasNext()) return false;
//
//            if (state == State.END) continue;
//            if (!validate.validState(state)) continue;
//            var item = input.next();
//            if (predicateMap.get(state).test(item) &&
//                    dfs(input, input.next(), stateMap.get(state), state == State.DOT || isDotSeen)) {
//                return true;
//            }
//        }
//        return false;
//    }
//
//    void addStateValidate(State state, Predicate predicate) {
//        predicateMap.put(state, predicate);
//    }
//
//    void addState(State from, State to) {
//        if (stateMap.containsKey(from)) {
//            stateMap.get(from).add(to);
//            return;
//        }
//        List<State> res = new ArrayList<>();
//        res.add(to);
//        stateMap.put(from, res);
//    }
//
//    boolean validate(String str) {
//        return dfs(str, 0, stateMap.get(State.BEGIN), false);
//    }
//}