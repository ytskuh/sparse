#include <iostream>

#include "sparse.hpp"

using namespace std;
using namespace sparse;

int main() {
    DiaMatrix<double> a;

    a = diags({1.1, 2.0, 3.0}, {-1, 0, 4}, 5, 5);

    a.print_();
    return 0;
}
