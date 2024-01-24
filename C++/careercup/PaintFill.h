#include "../header.h"

class PaintFill {
   public:
    static void test() {
        vector<vector<char>> screen = {
            {'1', '0', '0', '0', '1'},
            {'1', '0', '1', '0', '1'},
            {'0', '1', '0', '0', '1'},
            {'1', '0', '0', '1', '1'},
            {'0', '0', '0', '1', '1'},
        };

        Point p = {2, 2};
        char oldColor = '0';
        char newColor = '1';

        PaintFill obj;
        cout << "Old screen:" << endl;
        cout << screen << endl;
        obj.paint(screen, p, oldColor, newColor);
        cout << "New screen:" << endl;
        cout << screen << endl;
    }

    void paint(vector<vector<char>>& screen, Point p, char oldColor, char newColor) {
        if (p.x < 0 || p.y < 0 || p.x >= screen.size() || p.y >= screen.size()) return;
        if (screen[p.x][p.y] == newColor) return;

        screen[p.x][p.y] = newColor;

        paint(screen, {p.x - 1, p.y}, oldColor, newColor);
        paint(screen, {p.x + 1, p.y}, oldColor, newColor);
        paint(screen, {p.x, p.y - 1}, oldColor, newColor);
        paint(screen, {p.x, p.y + 1}, oldColor, newColor);
    }
};