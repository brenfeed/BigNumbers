
# Название проекта
BigNumberArithmetic

[![Статус разработки](https://img.shields.io/badge/статус-разработка-blue.svg)](https://example.com)
[![Статус билда](https://img.shields.io/badge/билд-проходит-green.svg)](https://example.com)
[![Процент покрытия тестами](https://img.shields.io/badge/покрытие-90%25-yellow.svg)](https://example.com)

## Содержание
1. [Описание](#Описание)
2. [Технологии](#Технологии)
3. [Начало работы](#Начало-работы)
4. [Тестирование](#Тестирование)
5. [Deploy и CI/CD](#Deploy-и-CI/CD)
6. [Contributing](#Contributing)
7. [To do](#To-do)
8. [Команда проекта](#Команда-проекта)

## Описание
BigNumberArithmetic — это библиотека для работы с большими числами и числами с плавающей запятой. Проект решает задачу выполнения арифметических операций над числами, которые выходят за пределы стандартных типов данных C++.

## Технологии
- C++
- CMake
- GoogleTest

## Начало работы

### Предварительные требования
Убедитесь, что у вас установлены следующие инструменты:
- CMake 3.20 или выше
- Компилятор C++ с поддержкой C++17

### Установка
1. Клонируйте репозиторий:
    ```sh
    git clone https://github.com/yourusername/BigNumberArithmetic.git
    cd BigNumberArithmetic
    ```

2. Сборка проекта:
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

## Тестирование
Проект использует GoogleTest для написания и выполнения тестов. Для запуска тестов используйте следующую команду из директории `build`:
```sh
ctest
```

## Deploy и CI/CD
Настройте ваш CI/CD с использованием предпочитаемой платформы, такой как GitHub Actions, GitLab CI или Travis CI, для автоматического выполнения сборки и тестирования при каждом коммите.

## Contributing
Мы приветствуем вклад в проект! Пожалуйста, следуйте этим шагам:
1. Форкните репозиторий.
2. Создайте свою ветку (`git checkout -b feature-foo`).
3. Внесите изменения и зафиксируйте их (`git commit -am 'Добавил новую функцию'`).
4. Отправьте изменения в свою ветку (`git push origin feature-foo`).
5. Создайте новый Pull Request.

## To do
- Реализация дополнительных математических функций.
- Оптимизация производительности.
- Расширение тестового покрытия.

## Команда проекта
- [Картакаев Арсланбек](https://github.com/brenfeed) - Разработчик
- [Пегасов Кирилл](https://github.com/pegasak) - Разработчик

### Содержимое файлов CMakeLists.txt

#### Основной CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.20)
project(123)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(This Project)

option(BUILD_GMOCK "Add GMock for testing" OFF)

set(Sources
        main.cpp
)

add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/BigNumbers
)

add_subdirectory(tests)

add_executable(${This}
        ${Sources}
        ${Headers}
)

target_link_libraries(${This} PUBLIC
        BigNumbers
)
target_include_directories(${This} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
```

#### CMakeLists.txt для тестов
```cmake
cmake_minimum_required(VERSION 3.20)
project(123)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(This tests)
get_filename_component(Parent ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
        DOWNLOAD_EXTRACT_TIMESTAMP False
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(Sources
        arithmetics.cpp
        compares.cpp
        constructors.cpp
)

add_executable(${This}
        ${Sources}
        ${Headers}
)

target_link_libraries(${This} PUBLIC
        gtest_main
        BigNumbers
)

target_include_directories(${This} PUBLIC
        ${Parent}
)

add_test(
        NAME ${This}
        COMMAND ${This}
)
```

### Пример использования

```cpp
#include "BigNumbers/BigFloat.h"
#include "BigNumbers/BigFloat.cpp"
#include "BigNumbers/BigInteger.h"
#include "BigNumbers/BigInteger.cpp"
#include <iostream>
#include <chrono>

#define all(x) x.begin(), x.end()
void show(BigInteger a) {
    std::string temp;
    temp = a.toString();
    std::cout << temp << std::endl;
}

void show(BigFloat a, int x) {
    std::string temp;
    temp = a.toString(x);
    std::cout << temp << std::endl;
}

BigFloat calculate_pi(int idx) {
    clock_t start, finish;
    start = clock();
    BigFloat Pi("0");
    BigFloat deg_16("1");
    std::string prec = "0.";
    int idx1 = idx;
    while (idx1 > 0) {
        prec += '0';
        --idx1;
    }
    prec += '1';
    BigFloat prc(prec);
    BigFloat res("0");
    BigFloat k("0");
    do  {
        res = (BigFloat("1") / deg_16);
        BigFloat res1 = (BigFloat("4") / (BigFloat("8") * k + BigFloat("1"))) - (BigFloat("2") / (BigFloat("8") * k + BigFloat("4"))) -
                        (BigFloat("1") / (BigFloat("8") * k + BigFloat("5"))) - (BigFloat("1") / (BigFloat("8") * k + BigFloat("6")));
        res = res * res1;
        Pi = Pi + res;
        deg_16 = deg_16 * BigInteger("16");
        k = k + BigFloat("1");
    } while(res > prc);
    finish = clock();
    double duration = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout<<duration<<std::endl;
    return Pi;
}
int main(){
    show(calculate_pi(100), 100);
    BigFloat r1("1");
    BigFloat r2("1");
    BigFloat r3("3.1417123456789");
    BigFloat r4 = "9"_bf;

    BigFloat r5 = r1/r2;
    return 0;
}
```
