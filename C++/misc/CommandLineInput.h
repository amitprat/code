#include "../header.h"

/*
Don't mix >> and getline.

https://stackoverflow.com/questions/7786994/c-getline-isnt-waiting-for-input-from-console-when-called-multiple-times
*/
class CommandLineInput {
   public:
    static void test() {
        int M = 0;
        cin >> M;

        vector<int> numbers;
        int num;
        // enter ctrl+d to break the input loop
        while (cin >> num) {
            numbers.push_back(num);
        }

        int n = numbers.size();

        if (M > n) cout << "Nil" << endl;

        cout << numbers[n] << endl;
    }

    static void test2() {
        int M = 0;
        string mstr;
        getline(cin, mstr);
        M = stoi(mstr);

        // getline takes third parameter as delim to break the getline. by default, its newline character.
        string numbers;
        getline(cin, numbers);

        vector<int> arr;
        stringstream ss(numbers);

        int num;
        while (ss >> num) {
            arr.push_back(num);
        }

        int n = numbers.size();

        if (M > n) cout << "Nil" << endl;

        cout << numbers[n] << endl;
    }

    static void test3() {
        std::ifstream infile("input.txt");

        // Temporary buffer
        std::string temp;

        vector<string> outputs;

        // Get the input from the input file until EOF
        while (std::getline(infile, temp)) {
            // Add to the list of output strings
            outputs.push_back(temp);
        }
    }

    static void test4() {
        // Store the contents into a vector of strings
        std::vector<std::string> outputs;

        std::cout << "Reading from input.txt....\n";

        // Create the file object (input)
        std::ifstream infile("input.txt");

        // Temporary buffer
        std::string temp;

        // Get the input from the input file until EOF
        while (std::getline(infile, temp)) {
            // Add to the list of output strings
            outputs.push_back(temp);
        }

        // Use a range-based for loop to iterate through the output vector
        for (const auto& i : outputs)
            std::cout << i << std::endl;
    }

    static void test5() {
        std::string input = "abc,def,ghi";
        std::istringstream ss(input);
        std::string token;

        while (std::getline(ss, token, ',')) {
            std::cout << token << '\n';
        }
    }
};