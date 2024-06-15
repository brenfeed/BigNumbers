#ifndef LINUX_TOP_BIGFLOAT_H
#define LINUX_TOP_BIGFLOAT_H
#pragma once
#include "BigInteger.h"
#include <iostream>
#include <vector>

/**
 * @class BigFloat
 * @brief Класс для представления и манипулирования большими числами с плавающей запятой.
 */
class BigFloat {
public:
    using SelfRefBigFloat = const BigFloat&;

    /**
     * @brief Унарный оператор минус.
     * @return Новый BigFloat с противоположным знаком.
     */
    const BigFloat operator-() const;

    friend bool operator!=(SelfRefBigFloat, SelfRefBigFloat);
    friend bool operator==(SelfRefBigFloat, SelfRefBigFloat);
    friend bool operator<(SelfRefBigFloat, SelfRefBigFloat);
    friend bool operator<=(SelfRefBigFloat, SelfRefBigFloat);
    friend bool operator>(SelfRefBigFloat, SelfRefBigFloat);
    friend bool operator>=(SelfRefBigFloat, SelfRefBigFloat);

    /**
     * @brief Оператор присваивания сложения.
     * @param other BigFloat для сложения.
     * @return Ссылка на текущий BigFloat после сложения.
     */
    BigFloat& operator+=(SelfRefBigFloat other);

    /**
     * @brief Оператор присваивания вычитания.
     * @param other BigFloat для вычитания.
     * @return Ссылка на текущий BigFloat после вычитания.
     */
    BigFloat& operator-=(SelfRefBigFloat other);

    /**
     * @brief Оператор присваивания умножения.
     * @param other BigFloat для умножения.
     * @return Ссылка на текущий BigFloat после умножения.
     */
    BigFloat& operator*=(SelfRefBigFloat other);

    /**
     * @brief Оператор присваивания деления.
     * @param other BigFloat для деления.
     * @return Ссылка на текущий BigFloat после деления.
     */
    BigFloat& operator/=(SelfRefBigFloat other);

    friend const BigFloat operator+(SelfRefBigFloat left, SelfRefBigFloat right);
    friend const BigFloat operator-(SelfRefBigFloat left, SelfRefBigFloat right);
    friend const BigFloat operator*(SelfRefBigFloat left, SelfRefBigFloat right);
    friend const BigFloat operator/(SelfRefBigFloat left, SelfRefBigFloat right);

    /**
     * @brief Конструктор BigFloat из строки.
     * @param other Строка, представляющая число.
     */
    BigFloat(const std::string other);

    /**
     * @brief Конструктор BigFloat из BigInteger.
     * @param num BigInteger для инициализации.
     */
    BigFloat(const BigInteger& num);

    /**
     * @brief Конструктор по умолчанию.
     */
    BigFloat() {};

    /**
     * @brief Деструктор по умолчанию.
     */
    ~BigFloat() = default;

    /**
     * @brief Преобразует BigFloat в строковое представление.
     * @param x Количество знаков после запятой.
     * @return Строка, представляющая BigFloat.
     */
    std::string toString(int x) const;

    BigInteger numberF; ///< Основное целочисленное представление.
    int index; ///< Позиция десятичной точки.

private:
    /**
     * @brief Изменяет точность BigFloat.
     * @param x Новая точность.
     */
    void change_precision(int x);

    /**
     * @brief Удаляет ведущие нули из числа.
     */
    void delete_leadings_zeroes();

    /**
     * @brief Считает количество ведущих нулей в BigFloat.
     * @param x Проверяемый BigFloat.
     * @return Количество ведущих нулей.
     */
    int zeroes_of_head(SelfRefBigFloat x);
};

/**
 * @brief Литеральный оператор для создания BigFloat из строки.
 * @param s Строка, представляющая число.
 * @param size Размер строки.
 * @return Новый BigFloat, созданный из строки.
 */
const BigFloat operator ""_bf(const char *s, size_t size);

#endif // LINUX_TOP_BIGFLOAT_H

