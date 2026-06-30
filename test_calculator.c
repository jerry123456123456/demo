/**
 * test_calculator.c
 * 单元测试（使用标准库 assert）
 *
 * 编译：gcc -DUNIT_TEST calculator.c test_calculator.c -lm -o test_calculator
 * 运行：./test_calculator
 */
#include <stdio.h>
#include <assert.h>
#include <math.h>

/* 声明被测函数 */
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
long   modulo(long a, long b);

#define EPSILON 1e-9
#define ASSERT_DOUBLE_EQ(a, b) assert(fabs((a) - (b)) < EPSILON)

void test_add() {
    ASSERT_DOUBLE_EQ(add(1, 2),    3);
    ASSERT_DOUBLE_EQ(add(-1, 1),   0);
    ASSERT_DOUBLE_EQ(add(0.1, 0.2), 0.3);
    printf("[PASS] test_add\n");
}

void test_subtract() {
    ASSERT_DOUBLE_EQ(subtract(5, 3),  2);
    ASSERT_DOUBLE_EQ(subtract(0, 5), -5);
    printf("[PASS] test_subtract\n");
}

void test_multiply() {
    ASSERT_DOUBLE_EQ(multiply(3, 4),   12);
    ASSERT_DOUBLE_EQ(multiply(-2, 5), -10);
    ASSERT_DOUBLE_EQ(multiply(0, 99),   0);
    printf("[PASS] test_multiply\n");
}

void test_divide() {
    ASSERT_DOUBLE_EQ(divide(10, 2), 5);
    ASSERT_DOUBLE_EQ(divide(7, 2),  3.5);
    printf("[PASS] test_divide\n");
}

void test_modulo() {
    assert(modulo(10, 3) == 1);
    assert(modulo(9,  3) == 0);
    assert(modulo(-7, 3) == -1);
    printf("[PASS] test_modulo\n");
}

int main(void) {
    printf("=== Running Tests ===\n");
    test_add();
    test_subtract();
    test_multiply();
    test_divide();
    test_modulo();
    printf("=== All Tests Passed ===\n");
    return 0;
}
