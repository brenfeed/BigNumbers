#ifndef LINUX_TOP_BIGINTEGER_H
#define LINUX_TOP_BIGINTEGER_H
#pragma once
#include <iostream>
#include <vector>

/**
 * @enum Sign
 * @brief Перечисление для обозначения знака числа.
 */
enum class Sign {
    negative, ///< Отрицательное число
    zero, ///< Нулевое значение
    positive ///< Положительное число
};

/**
 * @class BigInteger
 * @brief Класс для представления и манипулирования большими целыми числами.
 */
class BigInteger {
public:
    using SelfRefBigInt = const BigInteger&;

    /**
     * @brief Унарный оператор минус.
     * @return Новый BigInteger с противоположным знаком.
     */
    const BigInteger operator-() const;

    friend bool operator!=(SelfRefBigInt, SelfRefBigInt);
    friend bool operator==(SelfRefBigInt, SelfRefBigInt);
    friend bool operator<(SelfRefBigInt, SelfRefBigInt);
    friend bool operator<=(SelfRefBigInt, SelfRefBigInt);
    friend bool operator>(SelfRefBigInt, SelfRefBigInt);
    friend bool operator>=(SelfRefBigInt, SelfRefBigInt);

    /**
     * @brief Оператор присваивания сложения.
     * @param other BigInteger для сложения.
     * @return Ссылка на текущий BigInteger после сложения.
     */
    BigInteger& operator+=(SelfRefBigInt other);

    /**
     * @brief Оператор присваивания вычитания.
     * @param other BigInteger для вычитания.
     * @return Ссылка на текущий BigInteger после вычитания.
     */
    BigInteger& operator-=(SelfRefBigInt other);

    /**
     * @brief Оператор присваивания умножения.
     * @param other BigInteger для умножения.
     * @return Ссылка на текущий BigInteger после умножения.
     */
    BigInteger& operator*=(SelfRefBigInt other);

    /**
     * @brief Оператор присваивания деления.
     * @param other BigInteger для деления.
     * @return Ссылка на текущий BigInteger после деления.
     */
    BigInteger& operator/=(SelfRefBigInt other);

    friend const BigInteger operator+(SelfRefBigInt left, SelfRefBigInt right);
    friend const BigInteger operator-(SelfRefBigInt left, SelfRefBigInt right);
    friend const BigInteger operator*(SelfRefBigInt left, SelfRefBigInt right);
    friend const BigInteger operator/(SelfRefBigInt left, SelfRefBigInt right);

    /**
     * @brief Конструктор BigInteger из целого числа.
     * @param other Целое число для инициализации.
     */
    BigInteger(const long long& other);

    /**
     * @brief Конструктор BigInteger из строки.
     * @param other Строка, представляющая целое число.
     */
    BigInteger(const std::string other);

    /**
     * @brief Конструктор по умолчанию.
     */
    BigInteger() {}

    /**
     * @brief Деструктор по умолчанию.
     */
    ~BigInteger() = default;

    /**
     * @brief Преобразует BigInteger в строковое представление.
     * @return Строка, представляющая BigInteger.
     */
    std::string toString() const;

    Sign sign; ///< Знак числа.
    std::vector<int> number; ///< Вектор для хранения цифр числа.

private:
    /**
     * @brief Возвращает абсолютное значение BigInteger.
     * @return Новый BigInteger с положительным знаком.
     */
    BigInteger abs() const;

    /**
     * @brief Возвращает знак числа.
     * @return Константная ссылка на знак числа.
     */
    const Sign& signum() const { return sign; }

    /**
     * @brief Возвращает цифры числа.
     * @return Константная ссылка на вектор цифр.
     */
    const std::vector<int>& digits() const { return number; }

    /**
     * @brief Удаляет ведущие нули из числа.
     */
    void remove_zeros();

    /**
     * @brief Сдвигает число.
     */
    void shift();

    static const size_t kDigit_size = 9; ///< Размер цифры.
    static const int kSystem = 1000000000; ///< Основа системы счисления.
};

#endif // LINUX_TOP_BIGINTEGER_H
