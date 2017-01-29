
#ifndef BIGINT_COW_SOO_VECTOR_H
#define BIGINT_COW_SOO_VECTOR_H

#include <bits/stdc++.h>

template <typename T>
struct cow_soo_vector {
    cow_soo_vector() {}

    cow_soo_vector(cow_soo_vector<T> &rhs) : ptr_on_vector(rhs.ptr_on_vector), number(rhs.number), tag(rhs.tag) {}

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

    inline void push_back(const T x) {
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
                (*ptr_on_vector)[0] = number;
            }
        } else if (tag == BIG) {
//            if (s == 1) {
//                clear();
//                tag = SMALL;
//                number = 0;
//            } else {
//                ptr_on_vector->resize(s);
//            }
            make_writable(ptr_on_vector);
            ptr_on_vector->resize(s);
        }
    }

    inline size_t size() const {
        if (tag == EMPTY) return 0;
        else if (tag == SMALL) return 1;
        else return ptr_on_vector->size();
    }

    typename std::vector<T>::iterator begin() {
        if (tag == SMALL) {
            badjob[0] = number;
            return badjob.begin();
        };
        make_writable(ptr_on_vector);
        return ptr_on_vector->begin();
    }

    typename std::vector<T>::iterator begin() const {
        if (tag == SMALL) {
            badjob[0] = number;
            return badjob.begin();
        };
        return ptr_on_vector->begin();
    }

    typename std::vector<T>::iterator end() {
        if (tag == SMALL) {
            badjob[0] = number;
            return badjob.end();
        };
        make_writable(ptr_on_vector);
        return ptr_on_vector->end();
    }

    typename std::vector<T>::iterator end() const {
        if (tag == SMALL) {
            badjob[0] = number;
            return badjob.end();
        };
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

    inline void make_writable(std::shared_ptr<std::vector<T>> &ptr) {
        if (tag == BIG && !ptr.unique()) {
            ptr = std::make_shared<std::vector<T>>(*ptr);
        }
    }

    std::vector<T> badjob = std::vector<T>(1);

};


#endif //BIGINT_COW_SOO_VECTOR_H
