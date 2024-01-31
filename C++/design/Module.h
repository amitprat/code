#pragma once
#include "../header.h"

export module Foo;

namespace Bar {
int f_internal() {
    return 10;
}

export int f() {
    return f_internal();
}
}  // namespace Bar