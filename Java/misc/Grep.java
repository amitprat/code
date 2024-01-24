package programs.misc;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

public class Grep {
    public static void test() {
        Grep obj = new Grep();
        String path = "D:/gen-cpp";
        String pattern = "hello_func3";
        List<String> result = obj.grep(path, pattern);
        for(String res : result) {
            System.out.println(res);
        }
    }

    List<String> grep(String path, String pattern) {
        try {
            File file = new File(path);
            List<String> result = new ArrayList<>();
            if (file.isFile()) {
                result.addAll(findInFile(path, pattern));
            } else {
                String[] pathNames = file.list();
                if (pathNames != null) {
                    for (String childPath : pathNames) {
                        if (!childPath.isEmpty() || childPath.equals(" ") || childPath.equals("/"))
                            result.addAll(grep(path + "/" + childPath, pattern));
                    }
                }
            }

            return result;
        } catch (Exception e) {
            System.out.println(e.toString());
        }
        return new ArrayList<>();
    }

    List<String> findInFile(String filePath, String pattern) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(filePath));
            String line = br.readLine();
            List<String> result = new ArrayList<>();
            while (line != null) {
                if (isMatch(line, pattern)) {
                    result.add(line);
                }
                line = br.readLine();
            }
        } catch (Exception e) {
            System.out.println(e.toString());
        }
        return new ArrayList<>();
    }

    boolean isMatch(String text, String pattern) {
        int n = text.length();
        int m = pattern.length();
        System.out.println("Text: " + text + ", Pattern: " + pattern);
        for (int i = 0; i <= n - m + 1; i++) {
            int j = 0;
            for (; j < m; j++) {
                if (text.charAt(i+j) != pattern.charAt(j)) break;
            }
            if (j == m) return true;
        }

        return false;
    }
}
