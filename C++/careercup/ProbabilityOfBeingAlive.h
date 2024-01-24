#include "../ds/Point.h"
#include "../header.h"

/*
https://careercup.com/question?id=15556758

There is an island which is represented by square matrix NxN.
A person on the island is standing at any given co-ordinates (x,y). He can move in any direction one step right, left, up, down on the island. If he steps outside the island, he dies.

Let island is represented as (0,0) to (N-1,N-1) (i.e NxN matrix) & person is standing at given co-ordinates (x,y). He is allowed to move n steps on the island (along the matrix). What is the probability that he is alive after he walks n steps on the island?

Write a psuedocode & then full code for function
" float probabilityofalive(int x,int y, int n) ".

I presume that the probabilities of move up/donw/left/right are equal(0.25).
Then P(x, y, n, step) = (P(x-1, y, n, step-1) + P(x+1, y, n, step-1) + P(x, y-1, n, step-1) + P(x, y+1, n, step-1)) / 4.
(x, y) is the position. (n) is the size of island. (step) is the remaining step.
The following code is my Java implementation with some simple tests.
Dynamic Programming is also used.

  public static double probabilityOfAlive(int x, int y, int n)
  {
    if (x < 0 || x > (n - 1) || y < 0 || y > (n - 1) || n < 1) {return 0.0;}
    return probabilityOfAlive(x, y, n, n, new HashMap<String, Double>());
  }

  private static double probabilityOfAlive(int x, int y, int n, int step, HashMap<String, Double> map)
  {
    if (0 == step) {return 1.0;}
    // if the state is already calculated, return from HashMap
    String key = "";
    {
      StringBuffer sb = new StringBuffer();
      sb.append(x + ",");
      sb.append(y + ",");
      sb.append(step + ".");
      key = sb.toString();
    }
    if (map.containsKey(key)) {return map.get(key);}
    // calculate the probability of a state
    double probability = 0.0;
    if (x > 0) {probability += 0.25 * probabilityOfAlive(x - 1, y, n, step - 1, map);}
    if (x < (n - 1)) {probability += 0.25 * probabilityOfAlive(x + 1, y, n, step - 1, map);}
    if (y > 0) {probability += 0.25 * probabilityOfAlive(x, y - 1, n, step - 1, map);}
    if (y < (n - 1)) {probability += 0.25 * probabilityOfAlive(x, y + 1, n, step - 1, map);}
    // save the result to HashMap and return
    map.put(key, probability); return probability;
  }
*/
class ProbabilityOfBeingAlive {
   public:
    static void test() {
        ProbabilityOfBeingAlive obj;
        unordered_map<string, double> visited;
        double prob = obj.getProb({0, 0}, 10, 20, visited);

        cout << "Result: " << prob << endl;
    }

   private:
    double getProb(Point startPos, int n, int steps, unordered_map<string, double> &visited) {
        if (!isValid(startPos, n))
            return 0.0;
        if (steps == 0)
            return 1.0;

        string key = to_string(startPos.x) + ":" + to_string(startPos.y) + ":" + to_string(steps);
        if (visited.find(key) != visited.end())
            return visited[key];

        double value = 0.25 * getProb({startPos.x, startPos.y - 1}, n, steps - 1, visited) +
                       0.25 * getProb({startPos.x, startPos.y + 1}, n, steps - 1, visited) +
                       0.25 * getProb({startPos.x - 1, startPos.y}, n, steps - 1, visited) +
                       0.25 * getProb({startPos.x + 1, startPos.y}, n, steps - 1, visited);

        visited[key] = value;

        return visited[key];
    }

    bool isValid(Point pos, int n) {
        return pos.x < n && pos.y < n && pos.x >= 0 && pos.y >= 0;
    }
};