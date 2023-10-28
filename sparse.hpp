#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>
#include <initializer_list>
#include <unordered_map>

#ifndef SPARSE_H
#define SPARSE_H

#include <concepts>

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

namespace sparse {
    using std::vector;
    using std::size_t;
    using std::fill;
    using std::cout;
    using std::endl;
    using std::out_of_range;
    using std::initializer_list;
    using std::unordered_map;

template <Numeric T>
class DiaMatrix {
private:
    size_t rows_ = 0;
    size_t cols_ = 0;
    vector<vector<T>> data_;
    unordered_map<int, size_t> offsets_;

public:
    DiaMatrix() = default;
    ~DiaMatrix() = default;

    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }
    size_t size() const { return rows_ * cols_; }
    bool empty() const { return rows_ == 0 || cols_ == 0; }

    T& operator()(size_t i, size_t j);
    const T& operator()(size_t i, size_t j) const;

    DiaMatrix<T>& operator*=(const T& scalar);

    template <Numeric U> friend DiaMatrix<U> diags(const vector<U>& diagonals, const vector<int>& offsets, size_t rows, size_t cols);
    template <Numeric U> friend DiaMatrix<U> diags(initializer_list<U> diagonals, initializer_list<int> offsets, size_t rows, size_t cols);

    void print_() const;
};

template <Numeric T> T& DiaMatrix<T>::operator()(size_t i, size_t j) {
    if(i >= rows_ || j >= cols_)
        throw out_of_range("DiaMatrix::operator(): index out of range");

    auto it = offsets_.find(i-j);
    if(it != offsets_.end())
        return data_[it->second][j];
    return T{};
}

template <Numeric T> const T& DiaMatrix<T>::operator()(size_t i, size_t j) const {
    if(i >= rows_ || j >= cols_)
        throw out_of_range("DiaMatrix::operator(): index out of range");

    auto it = offsets_.find(i-j);
    if(it != offsets_.end()) {
        return data_[it->second][j];
    }
    static T default_value{};
    return default_value;
}

template <Numeric T> DiaMatrix<T>& DiaMatrix<T>::operator*=(const T& scalar) {
    for(auto& row : data_) {
        for(auto& element : row) {
            element *= scalar;
        }
    }
    return *this;
}

template <Numeric T> void DiaMatrix<T>::print_() const {
    for(size_t i = 0; i < rows_; ++i) {
        for(size_t j = 0; j < cols_; ++j) {
            cout<<(*this)(i, j)<<" ";
        }
        cout<<endl;
    }
}

template <Numeric U> DiaMatrix<U> diags(const vector<U>& diagonals, const vector<int>& offsets, size_t rows, size_t cols) {
    DiaMatrix<U> result;
    result.rows_ = rows;
    result.cols_ = cols;

    for(size_t i = 0; i < offsets.size(); ++i) {
        if(0<=offsets[i] && offsets[i]<rows) {
            result.data_.push_back(vector<U>(cols, diagonals[i]));
            fill(result.data_.back().end()-offsets[i], result.data_.back().end(), U{});
            result.offsets_.insert({offsets[i], i});
        } else if (offsets[i]>-rows && offsets[i]<0) {
            result.data_.push_back(vector<U>(cols, diagonals[i]));
            fill(result.data_.back().begin(), result.data_.back().begin()-offsets[i], U{});
            result.offsets_.insert({offsets[i], i});
        } else {
            throw out_of_range("diags: offset out of range");
        }
    }
    return result;
}

template <Numeric U> DiaMatrix<U> diags(initializer_list<U> diagonals, initializer_list<int> offsets, size_t rows, size_t cols) {
    return diags(vector<U>(diagonals), vector<int>(offsets), rows, cols);
}

} // namespace sparse

#endif // SPARSE_H
