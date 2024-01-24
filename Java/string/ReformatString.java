package programs.string;

import java.util.ArrayList;
import java.util.Arrays;

class ReformatString {
    public static void test() {
        ArrayList<String> stringsIn = new ArrayList<String>();
        ArrayList<String> stringsOut = new ArrayList<String>();

        // Example input1: "aabb12cc345"
        // Example output1: "a1a2b3b4c5c"
        // Example input2: "a1aa"
        // Example output2: "aaa1"

        stringsIn.add(null);
        stringsOut.add("");

        stringsIn.add("");
        stringsOut.add("");

        stringsIn.add("1");
        stringsOut.add("1");

        stringsIn.add("12");
        stringsOut.add("12");

        stringsIn.add("123");
        stringsOut.add("123");

        stringsIn.add("a");
        stringsOut.add("a");

        stringsIn.add("ab");
        stringsOut.add("ab");

        stringsIn.add("abc");
        stringsOut.add("abc");

        stringsIn.add("a1");
        stringsOut.add("a1");

        stringsIn.add("a11");
        stringsOut.add("1a1");

        stringsIn.add("a1a");
        stringsOut.add("a1a");

        stringsIn.add("a11a");
        stringsOut.add("1a1a");

        stringsIn.add("a111a");
        stringsOut.add("1a1a1");

        stringsIn.add("a11a2");
        stringsOut.add("1a1a2");

        stringsIn.add("a11a11");
        stringsOut.add("aa1111");

        stringsIn.add("a11abc");
        stringsOut.add("aabc11");

        stringsIn.add("9a11abc234bnsdbvs38sbbcahdbckafs8723cbsffbcsf78234bcbkjcibcd62384bcsbjkdc2346782675256295928572495249768");
        stringsOut.add("");

        stringsIn.add("aabb12cc345");
        stringsIn.add("a1aa");

        stringsOut.add("a1a2b3b4c5c");
        stringsOut.add("aaa1");

        int numCorrect = 0;

        for (int i = 0; i < stringsIn.size(); i++) {
            String result = reformatStingMod(stringsIn.get(i));
            System.out.println("Correct: " + stringsOut.get(i) + " Mine: " + result);
            if (result.equals(stringsOut.get(i))) {
                numCorrect++;
            }
        }

        System.out.println("Correct: " + numCorrect + " out of total: " + stringsIn.size());

        return;
    }

    public static String reformatStingMod(String str) {
        if (str == null || str.length() == 0) {
            return "";
        }

        int digitCount = 0;
        int charCount = 0;

        int len = str.length();
        for (int i = 0; i < len; i++) {
            if (Character.isDigit(str.charAt(i))) digitCount++;
            if (Character.isLetter(str.charAt(i))) charCount++;
        }
        if (charCount == digitCount || charCount == digitCount + 1)
            return reformatString(str, true, true, charCount, digitCount);
        if (digitCount == charCount + 1) return reformatString(str, false, true, charCount, digitCount);
        else return reformatString(str, true, false, charCount, digitCount);
    }

    public static String reformatString(String str, boolean isCharAtFront, boolean isAlternative, int charCount, int digitCount) {
        char[] charArr = new char[str.length()];
        if (isAlternative) {
            int index = 0;
            int charIndex = isCharAtFront ? 0 : 1;
            int digitIndex = isCharAtFront ? 1 : 0;
            while (index < str.length()) {
                if (Character.isDigit(str.charAt(index))) {
                    charArr[charIndex] = str.charAt(index);
                    charIndex += 2;
                }
                if (Character.isLetter(str.charAt(index))) {
                    charArr[digitIndex] = str.charAt(index);
                    digitIndex += 2;
                }
                index++;
            }
        } else {
            int index = 0;
            int charIndex = 0;
            int digitIndex = charCount;
            while (index < str.length()) {
                if (Character.isLetter(str.charAt(index))) charArr[charIndex++] = str.charAt(index);
                else charArr[digitIndex++] = str.charAt(index);
                index++;
            }
        }
        return Arrays.toString(charArr);
    }
}
