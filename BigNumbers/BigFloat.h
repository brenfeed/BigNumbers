#ifndef LINUX_TOP_BIGFLOAT_H
#define LINUX_TOP_BIGFLOAT_H
#pragma once
#include "BigInteger.h"
#include <iostream>
#include <vector>

class BigFloat{
public:
    using SelfRefBigFloat = const BigFloat&;

    const BigFloat operator-() const;

    friend bool operator!=(SelfRefBigFloat, SelfRefBigFloat);
    friend bool operator==(SelfRefBigFloat, SelfRefBigFloat);
    friend bool operator<(SelfRefBigFloat, SelfRefBigFloat);
    friend bool operator<=(SelfRefBigFloat, SelfRefBigFloat);
    friend bool operator>(SelfRefBigFloat, SelfRefBigFloat);
    friend bool operator>=(SelfRefBigFloat, SelfRefBigFloat);

    BigFloat& operator+=(SelfRefBigFloat);
    BigFloat& operator-=(SelfRefBigFloat);
    BigFloat& operator*=(SelfRefBigFloat);
    BigFloat& operator/=(SelfRefBigFloat);

    friend const BigFloat operator +(SelfRefBigFloat left, SelfRefBigFloat right);
    friend const BigFloat operator -(SelfRefBigFloat left, SelfRefBigFloat right);
    friend const BigFloat operator *(SelfRefBigFloat left, SelfRefBigFloat right);
    friend const BigFloat operator /(SelfRefBigFloat left, SelfRefBigFloat right);

    BigFloat(const std::string other);
    BigFloat(const BigInteger& num);
    BigFloat(){};
    ~BigFloat() = default;
    std::string toString(int x) const;
    BigInteger numberF;
    int index;
private:
    void change_precision(int x);
    void delete_leadings_zeroes();
    int zeroes_of_head(SelfRefBigFloat x);
};
const BigFloat operator ""_bf(const char *s, size_t size);

#endif