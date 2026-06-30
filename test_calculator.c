/**
 * test_calculator.c
 * 单元测试（使用标准库 assert）
 *
 * 编译：gcc -DUNIT_TEST calculator.c test_calculator.c -lm -o test_calculator
 * 运行：./test_calculator
 */

/* stdio.h：提供 printf */
#include <stdio.h>
/* assert.h：提供 assert() 宏。
   assert(条件)：条件为假时打印位置信息并终止程序，测试失败时立刻暴露。 */
#include <assert.h>
/* math.h：提供 fabs()（浮点数取绝对值），用于比较两个 double 是否"足够接近"
   编译时需要加 -lm 链接数学库                                               */
#include <math.h>

/* ── 声明被测函数 ────────────────────────────────────────────────────────────
   calculator.c 和 test_calculator.c 会一起编译成一个可执行文件。
   这里只声明函数签名（prototype），告诉编译器"这些函数在别的 .c 文件里"，
   链接阶段才会把实际实现连进来。                                             */
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
long   modulo(long a, long b);

/* ── 浮点数比较宏 ────────────────────────────────────────────────────────────
   浮点数不能直接用 == 比较（精度问题，如 0.1+0.2 != 0.3）。
   EPSILON = 1e-9（0.000000001），两数之差的绝对值小于它就认为"相等"。
   fabs(a-b)：先求差再取绝对值，消除正负号影响。                             */
#define EPSILON 1e-9
#define ASSERT_DOUBLE_EQ(a, b) assert(fabs((a) - (b)) < EPSILON)

/* ── 各运算的测试函数 ─────────────────────────────────────────────────────── */

void test_add() {
    ASSERT_DOUBLE_EQ(add(1, 2),     3);   /* 基本正数 */
    ASSERT_DOUBLE_EQ(add(-1, 1),    0);   /* 负数 + 正数 = 0 */
    ASSERT_DOUBLE_EQ(add(0.1, 0.2), 0.3); /* 浮点边界：0.1+0.2 在二进制中有精度误差，
                                             EPSILON 容差保证这里能通过             */
    printf("[PASS] test_add\n");
}

void test_subtract() {
    ASSERT_DOUBLE_EQ(subtract(5, 3),  2);  /* 正数减法 */
    ASSERT_DOUBLE_EQ(subtract(0, 5), -5);  /* 0 减正数得负数 */
    printf("[PASS] test_subtract\n");
}

void test_multiply() {
    ASSERT_DOUBLE_EQ(multiply(3, 4),    12);  /* 基本乘法 */
    ASSERT_DOUBLE_EQ(multiply(-2, 5),  -10);  /* 负数 × 正数 = 负数 */
    ASSERT_DOUBLE_EQ(multiply(0, 99),    0);  /* 任何数 × 0 = 0 */
    printf("[PASS] test_multiply\n");
}

void test_divide() {
    ASSERT_DOUBLE_EQ(divide(10, 2), 5);    /* 整除 */
    ASSERT_DOUBLE_EQ(divide(7, 2),  3.5);  /* 非整除，结果是小数 */
    /* 注意：divide(x, 0) 会调用 exit()，不在这里测试（需要专门的"死亡测试"框架） */
    printf("[PASS] test_divide\n");
}

void test_modulo() {
    assert(modulo(10, 3) ==  1);   /* 10 ÷ 3 余 1 */
    assert(modulo(9,  3) ==  0);   /* 9 能被 3 整除，余 0 */
    assert(modulo(-7, 3) == -1);   /* C 语言取余：结果符号与被除数相同，-7 % 3 = -1 */
    printf("[PASS] test_modulo\n");
}

/* ── 测试入口 ────────────────────────────────────────────────────────────────
   依次调用所有测试函数。任意一个 assert 失败，程序会立刻崩溃并打印失败位置，
   不会继续跑后续测试（快速失败策略）。                                        */
int main(void) {
    printf("=== Running Tests ===\n");
    test_add();
    test_subtract();
    test_multiply();
    test_divide();
    test_modulo();
    printf("=== All Tests Passed ===\n");
    return 0;  /* 所有断言通过，程序正常退出，CI 读取到退出码 0 = 测试成功 */
}
