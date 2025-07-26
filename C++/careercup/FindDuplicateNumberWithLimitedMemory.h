#include "../header.h"

class FindDuplicateNumberWithLimitedMemory {
    class ArrayBitVector {
        vector<int> count;
        vector<int> bitset;
        int countSize = (1 << 20);
        int numPerCount = (1 << 31) / countSize;
        int bitsetSize = (1 << 31) / (countSize * 8 * sizeof(int));

       public:
        ArrayBitVector() {
            count.reserve(countSize);
            count.resize(countSize, 0);
            bitset.reserve(bitsetSize);
            bitset.resize(bitsetSize, 0);
        }

        void insertCount(int num) {
            int pos = getPos(num);
            count[pos]++;
        }

        int findMissingCount() {
            for (int i = 0; i < countSize; i++) {
                if (count[i] != numPerCount) return i;
            }

            return -1;
        }

        pair<int, int> getStartEndIndex(int index) {
            return {countSize * index, countSize * (index + 1) - 1};
        }

        void insertIntoBitset(int num) {
            int index = num / bitsetSize;
            int pos = num % bitsetSize;

            bitset[index] |= (1 << pos);
        }

        int findUnsetBitsetPos() {
            for (int i = 0; i < bitsetSize; i++) {
                for (int j = 0; j < 32; j++) {
                    if (!(bitset[i] && (1 << j))) return i * 32 + j;
                }
            }

            return -1;
        }

        int getMissingNum(int startIndex) {
            return startIndex + findUnsetBitsetPos();
        }

        int getPos(int num) {
            return (num / countSize);
        }
    };

   public:
    int findMissingNumber(string fileName) {
        ArrayBitVector bitvector;
        ifstream in(fileName);
        int num;
        while (in >> num) {
            bitvector.insertCount(num);
        }

        int missingCount = bitvector.findMissingCount();
        auto res = bitvector.getStartEndIndex(missingCount);
        for (auto i = res.first; i <= res.second; i++) {
            bitvector.insertIntoBitset(i);
        }
        auto res1 = bitvector.findMissingCount();
    }
};