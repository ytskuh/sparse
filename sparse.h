
#ifndef SPARSE_H
#define SPARSE_H

namespace sparse {

template <typename T>
class DiaMatrix {
private:
    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    std::vector<std::vector<T>> data_;
    std::vector<std::size_t> offsets;

public:
    DiaMatrix() = default;
    ~DiaMatrix() = default;

    std::size_t rows() const { return rows_; }
    std::size_t cols() const { return cols_; }
    std::size_t size() const { return rows_ * cols_; }
    bool empty() const { return rows_ == 0 || cols_ == 0; }

    T& operator()(std::size_t i, std::size_t j);
    const T& operator()(std::size_t i, std::size_t j) const;

    template <typename U>
    friend DiaMatrix<U> diags(const std::vector<U>& diagonals, const std::vector<int>& offsets, std::size_t rows, std::size_t cols, bool wrap);


    void print_() const;
};

#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>

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

template <typename U>
DiaMatrix<U> diags(const vector<U>& diagonals, const vector<int>& offsets, size_t rows, size_t cols, bool wrap = false) {
    DiaMatrix<U> result;
    result.rows_ = rows;
    result.cols_ = cols;
    if(wrap) {
        for(size_t i = 0; i < offsets.size(); ++i) {
            result.data_.push_back(vector<U>(cols, diagonals[i]));
            result.offsets.push_back(offsets[i]%rows);
        }
    } else {
        for(size_t i = 0; i < offsets.size(); ++i) {
            if(0<=offsets[i] && offsets[i]<rows) {
                result.data_.push_back(vector<U>(cols, diagonals[i]));
                fill(result.data_.back().end()-offsets[i], result.data_.back().end(), U{});
                result.offsets.push_back(offsets[i]);
            } else if (offsets[i]>-rows && offsets[i]<0) {
                result.data_.push_back(vector<U>(cols, diagonals[i]));
                fill(result.data_.back().begin(), result.data_.back().begin()+offsets[i], U{});
                result.offsets.push_back(offsets[i]);
            }
        }
    }
    return result;
}

} // namespace sparse

#endif // SPARSE_H
