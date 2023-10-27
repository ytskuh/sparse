#include <vector>
#include <cstdio>
#include <algorithm>

#include "sparse.h"

using namespace std;
using namespace sparse;

int main() {
    DiaMatrix<int> a;
    a = diags(vector<int>{1, 2, 3}, vector<int>{-1, 0, 1}, 5, 5);
    a.print_();
    return 0;
}
