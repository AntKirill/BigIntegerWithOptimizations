#ifndef BIGINT_BIG_INTEGER_H
#define BIGINT_BIG_INTEGER_H

#include <iosfwd>
#include "cow_soo_vector.h"
#include <cstdint>

struct big_integer;

static bool zerocheck(big_integer &a);

static void afterMultSignValidation(big_integer &th, bool xsign);

static void extracode(big_integer &a);

static void normalcode(big_integer &a);

static big_integer &abstractLogicOperation(big_integer &a, big_integer b,
                                           uint_fast32_t (*logicFunc)(uint_fast32_t, uint_fast32_t),
                                           bool (*check)(bool, bool));

static bool cmpPosSigns(big_integer const &a, big_integer const &b);

static big_integer mult(big_integer const &b, uint_fast32_t x);

static big_integer &divWithMod(big_integer &th, int_fast32_t const x, bool div);

static big_integer &divWithModBig(big_integer &th, big_integer const &rhs, bool div);

struct big_integer {

    big_integer();

    big_integer(big_integer const &other);

    big_integer(int64_t a);

    explicit big_integer(std::string const &str);

    ~big_integer();

    big_integer &operator=(big_integer const &other);

    big_integer &operator=(int64_t other);

    big_integer &operator+=(big_integer rhs);

    big_integer &operator-=(big_integer const &rhs);

    big_integer &operator*=(big_integer const &rhs);

    big_integer &operator*=(int32_t const x);

    big_integer &operator/=(big_integer const &rhs);

    big_integer &operator/=(int32_t const x);

    big_integer &operator%=(big_integer const &rhs);

    big_integer &operator%=(int32_t const x);

    big_integer &operator&=(big_integer const &rhs);

    big_integer &operator|=(big_integer const &rhs);

    big_integer &operator^=(big_integer const &rhs);

    big_integer &operator<<=(int rhs);

    big_integer &operator>>=(int rhs);

    big_integer operator+() const;

    big_integer operator-() const;

    big_integer operator~() const;

    big_integer &operator++();

    big_integer operator++(int);

    big_integer &operator--();

    big_integer operator--(int);

    friend bool operator==(big_integer const &a, big_integer const &b);

    friend bool operator!=(big_integer const &a, big_integer const &b);

    friend bool operator<(big_integer const &a, big_integer const &b);

    friend bool operator>(big_integer const &a, big_integer const &b);

    friend bool operator<=(big_integer const &a, big_integer const &b);

    friend bool operator>=(big_integer const &a, big_integer const &b);

    friend std::string to_string(big_integer const &a);

    friend bool zerocheck(big_integer &a);

    friend void afterMultSignValidation(big_integer &th, bool xsign);

    friend void extracode(big_integer &a);

    friend void normalcode(big_integer &a);

    friend big_integer &abstractLogicOperation(big_integer &a, big_integer b,
                                               uint32_t (*logicFunc)(uint32_t, uint32_t),
                                               bool (*check)(bool, bool));

    friend bool cmpPosSigns(big_integer const &a, big_integer const &b);

    friend big_integer mult(big_integer const &b, uint32_t x);

    friend big_integer &divWithModBig(big_integer &th, big_integer const &rhs, bool div);

    friend big_integer &divWithMod(big_integer &th, int32_t const x, bool div);

private:
    cow_soo_vector<uint32_t> number;
    bool sign;
};

big_integer operator+(big_integer a, big_integer const &b);

big_integer operator-(big_integer a, big_integer const &b);

big_integer operator*(big_integer a, big_integer const &b);

big_integer operator*(big_integer a, int32_t const x);

big_integer operator/(big_integer a, big_integer const &b);

big_integer operator/(big_integer a, int32_t const x);

big_integer operator%(big_integer a, big_integer const &b);

big_integer operator%(big_integer a, int32_t const x);

big_integer operator&(big_integer a, big_integer const &b);

big_integer operator|(big_integer a, big_integer const &b);

big_integer operator^(big_integer a, big_integer const &b);

big_integer operator<<(big_integer a, int b);

big_integer operator>>(big_integer a, int b);

bool operator==(big_integer const &a, big_integer const &b);

bool operator!=(big_integer const &a, big_integer const &b);

bool operator<(big_integer const &a, big_integer const &b);

bool operator>(big_integer const &a, big_integer const &b);

bool operator<=(big_integer const &a, big_integer const &b);

bool operator>=(big_integer const &a, big_integer const &b);

std::string to_string(big_integer const &a);

std::ostream &operator<<(std::ostream &s, big_integer const &a);

void operator>>(std::istream &s, big_integer &a);

#endif //BIGINT_BIG_INTEGER_H