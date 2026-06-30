/**
 * calculator.c
 * 简单四则运算计算器（含取模）
 *
 * 用法：./calculator <num1> <op> <num2>
 *   op: + - * / %
 *
 * 示例：
 *   ./calculator 10 + 3   => 13
 *   ./calculator 10 % 3   => 1
 */

/* stdio.h：提供 printf / fprintf / stderr 等标准输入输出函数 */
#include <stdio.h>
/* stdlib.h：提供 exit() / EXIT_FAILURE / EXIT_SUCCESS / atof() */
#include <stdlib.h>

/* ── 基础运算函数 ─────────────────────────────────────────────────
   参数和返回值都用 double，支持小数运算。
   函数体只有一行，直接写在同一行节省篇幅。                        */

double add(double a, double b)      { return a + b; }  /* 加法 */
double subtract(double a, double b) { return a - b; }  /* 减法 */
double multiply(double a, double b) { return a * b; }  /* 乘法 */

/* 除法：需要单独处理除数为 0 的情况 */
double divide(double a, double b) {
    if (b == 0) {
        /* 错误信息写到 stderr（标准错误流），不影响 stdout 的正常输出 */
        fprintf(stderr, "Error: division by zero\n");
        /* exit(EXIT_FAILURE) 终止整个进程，返回非 0 状态码给 shell。
           注意：这里在 main 里调用是可以的，因为已经是最外层。
           如果是工具函数/库函数，应该 return 错误码而不是 exit。  */
        exit(EXIT_FAILURE);
    }
    return a / b;
}

/* 取模运算：% 只对整数有意义，所以参数和返回值用 long 而非 double */
long modulo(long a, long b) {
    if (b == 0) {
        fprintf(stderr, "Error: modulo by zero\n");
        exit(EXIT_FAILURE);
    }
    return a % b;  /* C 语言的 % 是整数取余，结果符号与被除数 a 相同 */
}

/* ── 条件编译：区分"主程序模式"和"单元测试模式" ─────────────────
   编译测试时加 -DUNIT_TEST 标志，main() 会被整个跳过，
   避免和 test_calculator.c 里的 main() 产生"重复定义"链接错误。
   编译主程序时不加该标志，main() 正常编译进去。                   */
#ifndef UNIT_TEST

/* main：程序入口，负责解析命令行参数、调用运算函数、输出结果 */
int main(int argc, char *argv[]) {
    /* argc 是命令行参数个数（含程序名本身）。
       ./calculator 10 + 3 → argc=4，argv=["./calculator","10","+","3"] */
    if (argc != 4) {
        /* 参数数量不对，打印用法提示后退出 */
        fprintf(stderr, "Usage: %s <num1> <op> <num2>\n", argv[0]);
        fprintf(stderr, "  op: + - * / %%\n");  /* %% 是 % 的转义写法 */
        return EXIT_FAILURE;                     /* return 非 0 = 程序失败 */
    }

    /* atof：把字符串 "10.5" 转成 double 10.5（来自 stdlib.h） */
    double a  = atof(argv[1]);
    /* argv[2][0]：取运算符字符串的第一个字符，如 "+" 取 '+' */
    char   op = argv[2][0];
    double b  = atof(argv[3]);
    double result;

    /* 根据运算符分发到对应函数 */
    switch (op) {
        case '+': result = add(a, b);                        break;
        case '-': result = subtract(a, b);                   break;
        case '*': result = multiply(a, b);                   break;
        case '/': result = divide(a, b);                     break;
        case '%':
            /* modulo 参数是 long，需要把 double 强制转型为 long（截断小数）
               结果再转回 double 存入 result，方便统一用 printf 输出      */
            result = (double)modulo((long)a, (long)b);
            break;
        default:
            fprintf(stderr, "Error: unknown operator '%c'\n", op);
            return EXIT_FAILURE;
    }

    /* %.6g：最多 6 位有效数字，自动去掉多余的尾零（如 3.0 显示为 3）  */
    printf("%.6g %c %.6g = %.6g\n", a, op, b, result);
    return EXIT_SUCCESS;  /* return 0 = 程序正常结束 */
}

#endif /* UNIT_TEST */
