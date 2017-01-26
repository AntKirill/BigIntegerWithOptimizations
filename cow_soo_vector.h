
#ifndef BIGINT_COW_SOO_VECTOR_H
#define BIGINT_COW_SOO_VECTOR_H

#include <bits/stdc++.h>

template <typename T>
struct cow_soo_vector {
    cow_soo_vector() : ptr_on_vector(std::make_shared<std::vector<T>>()) {}

    cow_soo_vector(cow_soo_vector<T> &rhs) : ptr_on_vector(rhs.ptr_on_vector), number(rhs.number) {}

    void operator=(const cow_soo_vector<T> &rhs) {
        ptr_on_vector = rhs.ptr_on_vector;
        number = rhs.number;
        tag = rhs.tag;
    }

    void operator=(const std::vector<T> &rhs) {
        if (rhs.size() > 1) {
            ptr_on_vector = std::make_shared<std::vector<T>>(rhs);
            tag = BIG;
        } else if (rhs.size() == 1) {
            number = rhs[0];
            tag = SMALL;
        } else {
            clear();
            tag = EMPTY;
        }
    }

    T& operator[](const size_t i) {
        if (tag == SMALL) return number;
        else {
            make_writable(ptr_on_vector);
            return (*ptr_on_vector)[i];
        }
    }

    T operator[](const size_t i) const {
        if (tag == SMALL) return number;
        else return (*ptr_on_vector)[i];
    }

    void push_back(const T x) {
        if (tag == EMPTY) {
            number = x;
            tag = SMALL;
        } else if (tag == SMALL) {
            tag = BIG;
            ptr_on_vector = std::make_shared<std::vector<T>>();
            ptr_on_vector->push_back(number);
            ptr_on_vector->push_back(x);
        } else {
            make_writable(ptr_on_vector);
            ptr_on_vector->push_back(x);
        }
    }

    void clear() {
        if (tag == EMPTY) return;
        if (tag == SMALL) tag = EMPTY;
        else if (tag == BIG) {
            make_writable(ptr_on_vector);
            ptr_on_vector->clear();
            tag = EMPTY;
        }
    }

    void resize(const size_t s) {
        if (s == 0) {
            clear();
            return;
        }
        if (tag == EMPTY) {
            if (s == 1) {
                tag = SMALL;
            } else {
                tag = BIG;
                ptr_on_vector = std::make_shared<std::vector<T>>();
                ptr_on_vector->resize(s);
            }
        } else if (tag == SMALL) {
            if (s > 1) {
                tag = BIG;
                ptr_on_vector = std::make_shared<std::vector<T>>();
                ptr_on_vector->resize(s);
            }
        } else if (tag == BIG) {
            if (s == 1) {
                clear();
                tag = SMALL;
                number = 0;
            } else {
                ptr_on_vector->resize(s);
            }
        }
    }

    size_t size() const {
        if (tag == EMPTY) return 0;
        else if (tag == SMALL) return 1;
        else return ptr_on_vector->size();
    }

    typename std::vector<T>::iterator begin() {
        //if (tag == EMPTY || tag == SMALL) return nullptr;
        make_writable(ptr_on_vector);
        return ptr_on_vector->begin();
    }

    typename std::vector<T>::iterator begin() const {
        return ptr_on_vector->begin();
    }

    typename std::vector<T>::iterator end() {
        make_writable(ptr_on_vector);
        return ptr_on_vector->end();
    }

    typename std::vector<T>::iterator end() const {
        return ptr_on_vector->end();
    }

    T& back() {
        if (tag == SMALL) return number;
        else {
            make_writable(ptr_on_vector);
            return ptr_on_vector->back();
        }
    }

    T back() const {
        if (tag == SMALL) return number;
        else return ptr_on_vector->back();

    }

    void erase(typename std::vector<T>::iterator it) {
        if (tag == EMPTY) return;
        if (tag == SMALL) {
            tag = EMPTY;
        } else {
            make_writable(ptr_on_vector);
            if (size() == 2) {
                tag = SMALL;
                ptr_on_vector->erase(it);
                number = (*ptr_on_vector)[0];
                ptr_on_vector->clear();
            } else {
                ptr_on_vector->erase(it);
            }
        }
    }

    void pop_back() {
        if (tag == EMPTY) return;
        if (tag == SMALL) {
            tag = EMPTY;
        } else {
            make_writable(ptr_on_vector);
            if (size() == 2) {
                tag = SMALL;
                number = (*ptr_on_vector)[0];
                ptr_on_vector->clear();
            } else {
                ptr_on_vector->pop_back();
            }
        }
    }

private:

    enum {EMPTY, SMALL, BIG} tag = EMPTY;

    std::shared_ptr<std::vector<T>> ptr_on_vector;

    T number;

    void make_writable(std::shared_ptr<std::vector<T>> &ptr) {
        if (tag == BIG && !ptr.unique()) {
            ptr = std::make_shared<std::vector<T>>(*ptr);
        }
    }
};

#endif //BIGINT_COW_SOO_VECTOR_H
