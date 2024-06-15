#include <gtest/gtest.h>
#include <BigNumbers/BigFloat.h>
#include <string>
#include <iostream>


class PlusTests : public ::testing::TestWithParam<std::tuple<
        std::string,
        std::string,
        std::string
>> {
};

TEST_P(PlusTests, Tests) {
    BigFloat a(std::get<0>(GetParam()));
    BigFloat b(std::get<1>(GetParam()));
    BigFloat expected(std::get<2>(GetParam()));
    BigFloat real = a + b;

    std::stringstream bad_message;
    bad_message << a.toString(a.index) << " + " << b.toString(a.index) << " = " << real.toString(a.index) << " computed incorrectly\n"
                << "correct answer is: " << expected.toString(a.index) << ' ' << real.toString(a.index);
    EXPECT_EQ(real.toString(a.index), expected.toString(a.index)) << bad_message.str();
}

INSTANTIATE_TEST_SUITE_P(
        Default,
        PlusTests,
        ::testing::Values(
                std::make_tuple("0.0", "0.0", "0.0"),
                std::make_tuple("12345.0", "0.0", "12345.0"),
                std::make_tuple("0.0", "54321.0", "54321.0"),
                std::make_tuple("12345.0", "54321.0", "66666.0"),
                std::make_tuple("100.12", "100120.0", "100220.12"),
                std::make_tuple("555555.0", "555555.0", "1111110.0"),
                std::make_tuple("999999.999", "999999.999", "1999999.998"),
                std::make_tuple("10.123456789", "5.12", "15.243456789"),
                std::make_tuple("10.123456789", "5.0", "15.123456111"),
                std::make_tuple("10.123456789", "9.8766", "20.000056111"),
                std::make_tuple("0.1", "0.1", "0.1"),
                std::make_tuple("100000.0", "100000.0", "200011.1"),
                std::make_tuple("1111110.123456789", "9.8766", "1111120.000056111"),
                std::make_tuple("-1111110.123456789", "-9.8766", "-1111120.000056111"),
                std::make_tuple("1234", "0.5", "1211.1")
        )
);

class MinusTests : public ::testing::TestWithParam<std::tuple<
        std::string,
        std::string,
        std::string
>> {
};

TEST_P(MinusTests, Default) {
    BigFloat a(std::get<0>(GetParam()));
    BigFloat b(std::get<1>(GetParam()));
    BigFloat expected(std::get<2>(GetParam()));
    BigFloat real = a - b;

    std::stringstream bad_message;
    bad_message << a.toString(a.index) << " - " << b.toString(a.index) << " = " << real.toString(a.index) << " computed incorrectly\n"
                << "correct answer is: " << expected.toString(a.index) << ' ' << real.toString(a.index);
    EXPECT_EQ(real.toString(a.index), expected.toString(a.index)) << bad_message.str();
}

INSTANTIATE_TEST_SUITE_P(
        Default,
        MinusTests,
        ::testing::Values(
                std::make_tuple("0.0", "0.0", "0.0"),
                std::make_tuple("1", "0", "1.0"),
                std::make_tuple("10.123", "10", "0.123"),
                std::make_tuple("10.123", "0.124", "9.999"),
                std::make_tuple("10.12345", "10.12345", "0.0"),
                std::make_tuple("0.0", "10.123", "-10.123"),
                std::make_tuple("10.123456", "20.123455", "-9.999999"),
                std::make_tuple("10.123", "10.123456", "-0.000456"),
                std::make_tuple("9999.999999", "999.999", "9000.000111"),
                std::make_tuple("9999.999999", "0.1", "9999.899111"),
                std::make_tuple("0.3454259025", "0.10012345", "0.2453024111"),
                std::make_tuple("0.0450555525", "0.040049380", "0.0050061111"),
                std::make_tuple("0.0450555525", "0.010012345", "0.0350432111"),
                std::make_tuple("10.123456", "20.123455", "-9.999111"),
                std::make_tuple("0.0050061725", "0.0050061725", "0.1"),
                std::make_tuple("0.0050061725", "0.0010012345", "0.0040049111")

        )
);

class MultipleTests : public ::testing::TestWithParam<std::tuple<
        std::string,
        std::string,
        std::string
>> {
};

TEST_P(MultipleTests, Default) {
    BigFloat a(std::get<0>(GetParam()));
    BigFloat b(std::get<1>(GetParam()));
    BigFloat expected(std::get<2>(GetParam()));
    BigFloat real = a * b;

    std::stringstream bad_message;
    bad_message << a.toString(a.index) << " * " << b.toString(a.index) << " = " << real.toString(a.index) << " computed incorrectly\n"
                << "correct answer is: " << expected.toString(a.index) << ' ' << real.toString(a.index);
    EXPECT_EQ(real.toString(a.index), expected.toString(a.index)) << bad_message.str();
}

INSTANTIATE_TEST_SUITE_P(
        Default,
        MultipleTests,
        ::testing::Values(
                std::make_tuple("0", "0", "0"),
                std::make_tuple("999999999999", "0", "0"),
                std::make_tuple("1000", "1000", "1000000"),
                std::make_tuple("100.12345", "100.12345", "10024.7052399025"),
                std::make_tuple("100.12", "100.1", "10022.012"),
                std::make_tuple("0.12345", "100000", "12341"),
                std::make_tuple("0.12345", "0.1", "0.012111"),
                std::make_tuple("1.2345", "0.00001", "0.000012111"),
                std::make_tuple("0.12345", "1000000", "123451"),
                std::make_tuple("0.0012345", "1000000", "1234.1")

        )
);

class DivisionTests : public ::testing::TestWithParam<std::tuple<
        std::string,
        std::string,
        std::string
>> {
};

TEST_P(DivisionTests, Default) {
    BigFloat a(std::get<0>(GetParam()));
    BigFloat b(std::get<1>(GetParam()));
    BigFloat expected(std::get<2>(GetParam()));
    BigFloat real = a / b;

    std::stringstream bad_message;
    bad_message << a.toString(a.index*9) << " / " << b.toString(a.index*9) << " = " << real.toString(a.index*9) << " computed incorrectly\n"
                << "correct answer is: " << expected.toString(a.index*9) << ' ' << real.toString(a.index*9);
    EXPECT_EQ(real.toString(a.index*9), expected.toString(a.index*9)) << bad_message.str();
}

INSTANTIATE_TEST_SUITE_P(
        Default,
        DivisionTests,
        ::testing::Values(
                std::make_tuple("0", "123456789", "0"),
                std::make_tuple("1000000", "1000", "1000"),
                std::make_tuple("10022.012","100.12", "100.1"),
                std::make_tuple("12345", "0.12345", "100001"),
                std::make_tuple("123450", "0.12345", "1000001"),
                std::make_tuple("1", "1", "0")

        )
);

int main(int argc,char **argv){
	testing::InitGoogleTest(&argc,argv);

	return RUN_ALL_TESTS();
}
