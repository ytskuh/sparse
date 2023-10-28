#include <vector>
#include <iostream>
#include <algorithm>

#include "sparse.h"

using namespace std;
using namespace sparse;

int main() {
    cout<<2;
    DiaMatrix<int> a;
    cout<<2;
    a = diags(vector<int>{1, 2, 3}, vector<int>{-1, 0, 1}, 5, 5);
    cout<<1;
    a.print_();
    return 0;
}
