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
#include <stdio.h>
#include <stdlib.h>

double add(double a, double b)      { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }

double divide(double a, double b) {
    if (b == 0) {
        fprintf(stderr, "Error: division by zero\n");
        exit(EXIT_FAILURE);
    }
    return a / b;
}

/* 取模：仅整数 */
long modulo(long a, long b) {
    if (b == 0) {
        fprintf(stderr, "Error: modulo by zero\n");
        exit(EXIT_FAILURE);
    }
    return a % b;
}

#ifndef UNIT_TEST
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <num1> <op> <num2>\n", argv[0]);
        fprintf(stderr, "  op: + - * / %%\n");
        return EXIT_FAILURE;
    }

    double a  = atof(argv[1]);
    char   op = argv[2][0];
    double b  = atof(argv[3]);
    double result;

    switch (op) {
        case '+': result = add(a, b);                          break;
        case '-': result = subtract(a, b);                     break;
        case '*': result = multiply(a, b);                     break;
        case '/': result = divide(a, b);                       break;
        case '%': result = (double)modulo((long)a, (long)b);   break;
        default:
            fprintf(stderr, "Error: unknown operator '%c'\n", op);
            return EXIT_FAILURE;
    }

    printf("%.6g %c %.6g = %.6g\n", a, op, b, result);
    return EXIT_SUCCESS;
}
#endif /* UNIT_TEST */
