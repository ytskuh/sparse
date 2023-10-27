#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>

#include "sparse.h"

namespace sparse {
    using std::vector;
    using std::size_t;
    using std::fill;
    using std::cout;
    using std::endl;

template <typename T>
T& DiaMatrix<T>::operator()(size_t i, size_t j) {
    if(i >= rows_ || j >= cols_) {
        throw std::out_of_range("DiaMatrix::operator(): index out of range");
    }
    for(size_t k = 0; k < offsets.size(); ++k) {
        if(offsets[k] == i-j) {
            return data_[k][j];
        }
    }
    return T{};
}

template <typename T>
void DiaMatrix<T>::print_() const {
    for(size_t i = 0; i < rows_; ++i) {
        for(size_t j = 0; j < cols_; ++j) {
            cout<<(*this)(i, j)<<" ";
        }
        cout<<endl;
    }
}

} // namespace sparse
