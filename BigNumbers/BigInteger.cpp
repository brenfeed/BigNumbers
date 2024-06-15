#include "BigInteger.h"

using SelfRefBigInt = const BigInteger&;

BigInteger::BigInteger(const long long& other) {
    if (other < 0) {
        sign = Sign::negative;
    } else if (other == 0) {
        sign = Sign::zero;
    } else {
        sign = Sign::positive;
    }
    long long copy = std::abs(other);
    while (copy != 0) {
        number.push_back(copy % kSystem);
        copy /= kSystem;
    }
}

BigInteger::BigInteger(const std::string other) {
    if (other.size() == 1 && other[0] == '0') {
        BigInteger::sign = Sign::zero;
        return;
    }
    if (other.size() == 0) {
        return;
    }
    BigInteger::sign = Sign::positive;
    int ind = 0;
    if (other[0] == '-') {
        BigInteger::sign = Sign::negative;
        ++ind;
    }
    while (other[ind] == '0' && ind < other.size()) {
        ++ind;
    }
    if (ind == other.size()) {
        BigInteger::sign = Sign::zero;
        return;
    }
    std::string current;
    for (int i = other.size() - 1; i >= ind; --i) {
        current = other[i] + current;
        if(current.size() == 9){
            number.push_back(stoi(current));
            current = "";
        }
    }
    if(current.size() != 0) {
        number.push_back(stoi(current));
    }
}

const BigInteger BigInteger::operator-() const {
    BigInteger result = *this;
    if (result.sign == Sign::positive) {
        result.sign = Sign::negative;
    } else if (sign == Sign::negative) {
        result.sign = Sign::positive;
    }
    return result;
}

std::string BigInteger::toString() const {
    if (sign == Sign::zero) {
        return "0";
    }
    std::string output_string;
    for (size_t i = number.size(); i > 0; i--) {
        for (size_t j = 0; j < (kDigit_size - std::to_string(number[i - 1]).size()) && i != number.size(); j++) {
            output_string += '0';
        }
        for (size_t j = 0; j < std::to_string(number[i - 1]).size(); j++) {
            output_string.push_back(std::to_string(number[i - 1])[j]);
        }
    }
    if (sign == Sign::negative) {
        output_string = "-" + output_string;
    }
    return output_string;
}

bool operator==(SelfRefBigInt first, SelfRefBigInt second) {
    if (first.signum() != second.signum() || first.digits().size() != second.digits().size()) {
        return false;
    }
    for (size_t i = 0; i < first.digits().size(); i++) {
        if (first.digits()[i] != second.digits()[i]) {
            return false;
        }
    }
    return true;
}

bool operator<(SelfRefBigInt first, SelfRefBigInt second) {
    if (first == second) {
        return false;
    }
    if (first.signum() > second.signum()) {
        return false;
    } if (first.signum() < second.signum()) {
        return true;
    } if (first.signum() == Sign::negative) {
        return -second < -first;
    } if (first.digits().size() > second.digits().size()) {
        return false;
    } if (first.digits().size() < second.digits().size()) {
        return true;
    } for (size_t i = first.digits().size(); i > 0; i--) {
        if (first.digits()[i - 1] > second.digits()[i - 1]) {
            return false;
        } if (first.digits()[i - 1] < second.digits()[i - 1]) {
            return true;
        }
    }
    return true;
}

bool operator!=(SelfRefBigInt first, SelfRefBigInt second) {
    return !(first == second);
}

bool operator<=(SelfRefBigInt first, SelfRefBigInt second) {
    return !(second < first);
}

bool operator>(SelfRefBigInt first, SelfRefBigInt second) {
    return second < first;
}

bool operator>=(SelfRefBigInt first, SelfRefBigInt second) {
    return !(first < second);
}

BigInteger BigInteger::abs() const {
    BigInteger copy = *this;
    if (copy.sign == Sign::negative) {
        copy.sign = Sign::positive;
    }
    return copy;
}

void BigInteger::remove_zeros() {
    while (!number.empty() && number.back() == 0) {
        number.pop_back();
    } if (number.empty()) {
        sign = Sign::zero;
    }
}

void BigInteger::shift() {
    if (number.empty()) {
        number.push_back(0);
        return;
    }
    number.push_back(number[number.size() - 1]);
    for (size_t i = number.size() - 2; i > 0; i--) {
        number[i] = number[i - 1];
    }
    number[0] = 0;
}

BigInteger& BigInteger::operator+=(SelfRefBigInt other) {
    if (sign == Sign::zero) {
        *this = other;
        return *this;
    } if (other.sign == Sign::zero) {
        return *this;
    } if (sign == Sign::positive && other.sign == Sign::positive) {
        int memory = 0;
        for (size_t i = 0; i < std::max(number.size(), other.number.size()) || memory != 0; i++) {
            if (i == number.size()) {
                number.push_back(0);
            }
            int second = 0;
            if (i < other.number.size()) {
                second = other.number[i];
            }
            number[i] += memory + second;
            memory = number[i] >= kSystem;
            if (memory != 0) {
                number[i] -= kSystem;
            }
        }
        return *this;
    } if (sign == Sign::negative && other.sign == Sign::negative) {
        *this = -(abs() += other.abs());
        return *this;
    } if (sign == Sign::positive && other.sign == Sign::negative) {
        *this -= -other;
        return *this;
    }
    *this = -*this;
    *this = -(*this -= other);
    return *this;
}

BigInteger& BigInteger::operator-=(SelfRefBigInt other) {
    if (sign == Sign::zero) {
        *this = -other;
        return *this;
    } if (other.sign == Sign::zero) {
        return *this;
    }
    if (sign == Sign::positive && other.sign == Sign::positive) {
        if (*this < other) {
            BigInteger copy = other;
            copy -= *this;
            *this = -copy;
            return *this;
        }
        if (*this == other) {
            sign = Sign::zero;
        }
        int memory = 0;
        for (size_t i = 0; i < number.size() || memory != 0; i++) {
            int second = 0;
            if (i < other.number.size()) {
                second = other.number[i];
            }
            number[i] -= memory + second;
            memory = number[i] < 0;
            if (memory != 0) {
                number[i] += kSystem;
            }
        }
        remove_zeros();
        return *this;
    } if (other.sign == Sign::negative) {
        *this += -other;
        return *this;
    }
    *this = -*this;
    *this += other;
    *this = -*this;
    return *this;
}

BigInteger& BigInteger::operator*=(SelfRefBigInt other) {
    BigInteger product;
    if (sign == Sign::zero || other.sign == Sign::zero) {
        sign = Sign::zero;
        return *this;
    }
    if (sign == other.sign) {
        product.sign = Sign::positive;
    } else {
        product.sign = Sign::negative;
    }
    product.number.resize(number.size() + other.number.size());
    for (size_t i = 0; i < number.size(); i++) {
        int memory = 0;
        for (size_t j = 0; j < other.number.size() || memory != 0; j++) {
            int digit = 0;
            if (j < other.number.size()) {
                digit = other.number[j];
            }
            long long current_product = product.number[i + j] + static_cast<long long>(number[i]) * digit + memory;
            product.number[i + j] = current_product % kSystem;
            memory = current_product / kSystem;
        }
    }
    product.remove_zeros();
    *this = product;
    return *this;
}

BigInteger& BigInteger::operator/=(SelfRefBigInt other) {
    if (other.sign == Sign::zero){
        std::cout << "lol" << std::endl;
        exit(0);
    };
    BigInteger quotient;
    if (sign == Sign::zero) {
        return *this;
    }
    if (sign == other.sign) {
        quotient.sign = Sign::positive;
    } else {
        quotient.sign = Sign::negative;
    }
    quotient.number.resize(number.size());
    BigInteger current;
    for (size_t i = number.size(); i > 0; i--) {
        current.shift();
        current.number[0] = number[i - 1];
        current.remove_zeros();
        if (current.number[current.number.size() - 1] != 0) {
            current.sign = Sign::positive;
        } else {
            current.sign = Sign::zero;
        }
        int incomplete_quotient = 0;
        int left = 0;
        int right = kSystem;
        while (left <= right) {
            int median = (left + right) / 2;
            if (other.abs() * median <= current) {
                incomplete_quotient = median;
                left = median + 1;
            } else {
                right = median - 1;
            }
        }
        quotient.number[i - 1] = incomplete_quotient;
        current -= incomplete_quotient * other.abs();
    }
    quotient.remove_zeros();
    *this = quotient;
    return *this;
}

const BigInteger operator+(SelfRefBigInt first, SelfRefBigInt second) {
    BigInteger sum = first;
    sum += second;
    return sum;
}

const BigInteger operator-(SelfRefBigInt first, SelfRefBigInt second) {
    BigInteger difference = first;
    difference -= second;
    return difference;
}

const BigInteger operator*(SelfRefBigInt first, SelfRefBigInt second) {
    BigInteger product = first;
    product *= second;
    return product;
}

const BigInteger operator/(SelfRefBigInt first, SelfRefBigInt second) {
    BigInteger quotient = first;
    quotient /= second;
    return quotient;
}