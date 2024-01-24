#include "../header.h"

class ReorderElementsOfArrayBasedOnGivenIndex {
   public:
    static void test() {
        vector<char> elems = {'C', 'D', 'E', 'F', 'G'};
        vector<int> indices = {3, 0, 4, 1, 2};

        ReorderElementsOfArrayBasedOnGivenIndex obj;
        obj.reorderElements2(elems, indices);

        cout << elems << endl;
        cout << indices << endl;
    }

   private:
    void reorderElements(vector<char>& elements, vector<int>& indices) {
        vector<char> res(elements.size());

        for (int i = 0; i < elements.size(); i++) {
            res[indices[i]] = elements[i];
        }

        for (int i = 0; i < elements.size(); i++) {
            elements[i] = res[i];
            indices[i] = i;
        }
    }

   private:
    void reorderElements2(vector<char>& elements, vector<int>& indices) {
        for (int i = 0; i < elements.size(); i++) {
            auto tmp = i;
            while (tmp != indices[tmp]) {
                swap(elements[tmp], elements[indices[tmp]]);
                swap(indices[tmp], indices[indices[tmp]]);
                tmp = indices[tmp];
            }
        }
    }
};