#include <iostream>
  
struct Point {
    int x;
    int y;
};
  
int main() {
    Point p = {1, 2};
    auto[x, y] = p; // Creates and initializes x and y variables
    std::cout << x << std::endl;
    std::cout << y << std::endl;     
    return 0;
}