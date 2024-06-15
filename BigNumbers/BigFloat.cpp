#include "BigFloat.h"
#include "BigInteger.h"
#include <iostream>
#include <vector>

using SelfRefBigFloat = const BigFloat&;

const BigFloat operator ""_bf(const char *s, size_t size) {
    return BigFloat(std::string(s, size));
}

BigFloat::BigFloat(const BigInteger &num) {
    for (int i = 0; i < num.number.size(); ++i) {
        numberF.number.push_back(num.number[i]);
    }
    numberF.sign = num.sign;
    index = 0;
}

BigFloat::BigFloat(std::string s) {
    if (s.size() == 1 && s[0] == '0') {
        BigFloat::numberF.sign = Sign::zero;
        index = 0;
        return;
    }
    BigFloat::index = 0;
    BigFloat::numberF.sign = Sign::positive;
    if (s.size() == 0) {
        return;
    }
    int ind = 0;
    if (s[0] == '-') {
        BigFloat::numberF.sign = Sign::negative;
        ++ind;
    }
    while (s[ind] == '0' && ind < s.size()) {
        ++ind;
    }
    if (ind == s.size()) {
        BigFloat::numberF.sign = Sign::zero;
        return;
    }
    std::string current;
    int toc = s.find(".");
    if(toc >= 0) {
        BigFloat::index = (s.size() - toc + 7)/9;
        int point = s.size() - 1 - toc;
        std::string pon;
        for (int i = 0; i < (9 - point%9)%9; i++) {
            pon = pon + "0";
        }
        s = s + pon;
    }
    for (long long i = s.size() - 1; i >= ind; --i) {
        if (s[i] == '.') {
            continue;
        }
        current = s[i] + current;
        if(current.size() == 9){
            numberF.number.push_back(stoi(current));
            current = "";
        }
    }
    if(current.size()!= 0) {
        numberF.number.push_back(stoi(current));
    }
    if(index == numberF.number.size()){
        numberF.number.push_back(0);
    }
    BigFloat::delete_leadings_zeroes();
}

void BigFloat::delete_leadings_zeroes() {
    if (numberF.sign == Sign::zero) {
        return;
    }
    std::vector<int> v = numberF.number;
    int cnt = 0;
    while (index > 0 && numberF.number[0] == 0) {
        ++cnt;
        --index;
        numberF.number.erase(numberF.number.begin());
    }
    while(numberF.number[numberF.number.size()-1] == 0 && numberF.number.size() - 1>index){
        numberF.number.pop_back();
    }
}

std::string BigFloat::toString(int x) const {
    if (numberF.sign == Sign::zero) {
        return "0";
    }
    int count = 0;
    std::string output_string;
    for (int j = 0; j < std::to_string(numberF.number[numberF.number.size()-1]).size(); j++) {
        output_string.push_back(std::to_string(numberF.number[numberF.number.size()-1])[j]);
    }
    for (size_t i = numberF.number.size() - 1; i > 0; i--) {
        if(i == index && x != 0) {
            output_string += '.';
        }
        for (int j = 0; j < 9; j++) {
            if(count == x){
                return output_string;
            }
            if(i - 1 < index){
                count++;
            }
            int len = std::to_string(numberF.number[i - 1]).size();
            if ((9 - len) > j) {
                output_string.push_back('0');
            }else {
                output_string.push_back(std::to_string(numberF.number[i - 1])[j - (9-len)]);
            }
        }
    }
    if (numberF.sign == Sign::negative) {
        output_string = "-" + output_string;
    }
    return output_string;
}

void BigFloat::change_precision(int x) {
    if(index >= x){
        return;
    }
    else{
        for(int i = x-index; i > 0; i--){
            numberF.number.insert(numberF.number.begin(), 0);
        }
        index = x;
    }
}

const BigFloat BigFloat::operator-() const {
    BigFloat result = *this;
    if (result.numberF.sign == Sign::positive) {
        result.numberF.sign = Sign::negative;
    } else if (numberF.sign == Sign::negative) {
        result.numberF.sign = Sign::positive;
    }
    return result;
}

int zeroes_of_head(SelfRefBigFloat x){
    int x_digits = x.numberF.number.size();
    for(int i = 0; i < x.index; i++){
        if(x.numberF.number[i] == 0){
            x_digits--;
        }else{
            return x_digits;
        }
    }
    return x_digits;
};

bool operator==(SelfRefBigFloat first, SelfRefBigFloat second) {
    int first_digits = first.numberF.number.size();
    int size_first = zeroes_of_head(first);
    int second_digits = second.numberF.number.size();
    int size_second = zeroes_of_head(second);
    if (first.numberF.sign != second.numberF.sign || size_first != size_second ||
    first.index - (first_digits - size_first) != second.index - (second_digits - size_second)) {
        return false;
    }
    for (size_t i = 0; i < size_second; i++) {
        if (first.numberF.number[(first_digits - size_first) + i] != second.numberF.number[(second_digits - size_second)+i]) {
            return false;
        }
    }
    return true;
}

bool operator<(SelfRefBigFloat first, SelfRefBigFloat second) {
    if (first == second) {
        return false;
    }
    if (first.numberF.sign > second.numberF.sign) {
        return false;
    }
    if (first.numberF.sign < second.numberF.sign) {
        return true;
    }
    if (first.numberF.sign == Sign::negative) {
        return -second < -first;
    }
    int first_digits = first.numberF.number.size();
    int size_first = zeroes_of_head(first);
    int second_digits = second.numberF.number.size();
    int size_second = zeroes_of_head(second);
    if (first_digits - first.index > second_digits - second.index) {
        return false;
    }
    if (first_digits - first.index < second_digits - second.index) {
        return true;
    }
    for (size_t i = 0; i < std::min(first_digits, second_digits + first_digits - first.index); i++) {
        if (first.numberF.number[first_digits - i - 1] > second.numberF.number[second_digits - i - 1]) {
            return false;
        }if (first.numberF.number[first_digits - i - 1] < second.numberF.number[second_digits - i - 1]) {
            return true;
        }
    }
    if(size_first > size_second) {
        return false;
    }if(size_first < size_second){
        return true;
    }
    return true;
}

bool operator!=(SelfRefBigFloat first, SelfRefBigFloat second) {
    return !(first == second);
}

bool operator<=(SelfRefBigFloat first, SelfRefBigFloat second) {
    return !(second < first);
}

bool operator>(SelfRefBigFloat first, SelfRefBigFloat second) {
    return second < first;
}

bool operator>=(SelfRefBigFloat first, SelfRefBigFloat second) {
    return !(first < second);
}

BigFloat& BigFloat::operator+=(SelfRefBigFloat other) {
    BigFloat temp = other;
    if(temp.index > index){
        this -> change_precision(other.index);
    }else{
        temp.change_precision(index);
    }
    numberF += temp.numberF;
    delete_leadings_zeroes();
    return *this;
}

BigFloat& BigFloat::operator-=(SelfRefBigFloat other) {
    BigFloat temp = other;
    if(temp.index > index){
        this -> change_precision(other.index);
    }else{
        temp.change_precision(index);
    }
    numberF -= temp.numberF;
    delete_leadings_zeroes();
    return *this;
}

BigFloat& BigFloat::operator*=(SelfRefBigFloat other) {
    BigFloat temp = other;
    numberF *= temp.numberF;
    index += temp.index;
    for(int i = numberF.number.size(); i <= index; i++){
        numberF.number.push_back(0);
    }
    delete_leadings_zeroes();
    return *this;
}

BigFloat& BigFloat::operator/=(SelfRefBigFloat other){
    BigFloat temp = other;
    this ->change_precision(120);
    numberF /= other.numberF;
    index -= temp.index;
    if(numberF.number.size() <= index){
        for(int i = index - numberF.number.size(); i >= 0; i--){
            numberF.number.push_back(0);
        }
    }
    return *this;
}

const BigFloat operator+(SelfRefBigFloat first, SelfRefBigFloat second) {
    BigFloat sum = first;
    sum += second;
    if(sum.numberF.number.size() <= sum.index){
        for(int i = sum.index - sum.numberF.number.size(); i >= 0; i--){
            sum.numberF.number.push_back(0);
        }
    }
    return sum;
}

const BigFloat operator-(SelfRefBigFloat first, SelfRefBigFloat second) {
    BigFloat difference = first;
    difference -= second;
    if(difference.numberF.number.size() <= difference.index){
        for(int i = difference.index - difference.numberF.number.size(); i >= 0; i--){
            difference.numberF.number.push_back(0);
        }
    }
    return difference;
}

const BigFloat operator*(SelfRefBigFloat first, SelfRefBigFloat second) {
    BigFloat product = first;
    product *= second;
    if(product.numberF.number.size() <= product.index){
        for(int i = product.index - product.numberF.number.size(); i >= 0; i--){
            product.numberF.number.push_back(0);
        }
    }
    return product;
}

const BigFloat operator/(SelfRefBigFloat first, SelfRefBigFloat second) {
    BigFloat quotient = first;
    quotient /= second;
    return quotient;
}