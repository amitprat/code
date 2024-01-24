#include "../header.h"

class GenericFunctionTemplates {
   public:
    void append(auto& coll, const auto& second) {
        coll.push_back(second);
    }
};