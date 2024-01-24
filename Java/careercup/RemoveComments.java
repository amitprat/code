package programs.careercup;

import java.io.*;

public class RemoveComments {
    public static void test() {
        try (Reader reader = new BufferedReader(new InputStreamReader(new FileInputStream(new File("F:\\Java\\CodeProject\\src\\programs\\careercup\\file.log"))))) {

            int r;
            boolean isPartOfString = false;
            boolean isCommentOn = false;
            char prevChar = '\u0000';
            while ((r = reader.read()) != -1) {
                char ch = (char) r;
                if (isPartOfString) {
                    System.out.print(ch);
                    if (ch == '"') isPartOfString = false;
                    continue;
                }
                if (isCommentOn && !isPartOfString) continue;
                if (ch == '"') isPartOfString = true;

                if (prevChar == '\u0000' && ch == '/') {
                    prevChar = ch;
                    continue;
                }
                if (prevChar == '/') {
                    if (ch == '*') isCommentOn = true;
                    else {
                        prevChar = '\u0000';
                        System.out.print(prevChar + ch);
                    }
                } else {
                    System.out.print(ch);
                }
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
