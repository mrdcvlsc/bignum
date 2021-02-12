/* Tiny calc
 *
 * Copyright (c) 2021 Al-buharie Amjari <healer.harie@gmail.com>
 *
 * This file is license under MIT license.
 *
 */
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bignum.h>

char expr[100];
char op[100];

bignum num[100];
int num_c = 0;
int op_c = 0;
int cur = 0;
int operand = 0;

int main() {
  printf("'q' to quit\n");
  while (!feof(stdin)) {
  beg:
    cur = 0;
    num_c = 0;
    op_c = 0;
    operand = 0;

    memset(expr, 0, 100);
    memset(op, 0, 100);

    printf("> ");
    fflush(stdout);
    scanf(" %[^\n]%*c", expr);
    if (*expr == (char)'q')
      return 0;
  a:
    while (1) {
      while (expr[cur] == ' ' || expr[cur] == '\n')
        cur++;
      switch (expr[cur]) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': {
        if (operand) {
          fprintf(stderr, "syntax error\n");
          goto beg;
        }
        operand = 1;
        char buff[100];
        int nchar;
        sscanf(expr + cur, "%[0-9\.]%n", buff, &nchar);
        cur += nchar;
        num[num_c++] = (string) buff;
      } break;

      case '+':
        if (!operand) {
          fprintf(stderr, "syntax error\n");
          goto beg;
        }
        operand = 0;
        if (op_c != 0)
          if (op[op_c - 1] == '*' || op[op_c - 1] == '/')
            for (op_c -= 1; op_c > -1; op_c--) {
              switch (op[op_c]) {
              case '*':
                num[num_c - 2] = num[num_c - 2] * num[num_c - 1];
                break;
              case '/':
                num[num_c - 2] = num[num_c - 2] / num[num_c - 1];
                break;
              case '-':
                num[num_c - 2] = num[num_c - 2] - num[num_c - 1];
                break;
              case '+':
                num[num_c - 2] = num[num_c - 2] + num[num_c - 1];
                break;
              }
              num_c--;
              op[op_c] = 0;
            }
	op_c = 0;
        op[op_c++] = '+';
        cur++;
        break;
      case '-':
        if (!operand) {
          if (!isdigit(expr[cur + 1])) {
            fprintf(stderr, "syntax error\n");
            goto beg;
          }
          operand = 1;
          char buff[100] = {0};
          buff[0] = '-';
          int nchar;
          int ret = sscanf(expr + cur + 1, "%[0-9\.]%n", buff + 1, &nchar);
          if (!ret) {
            fprintf(stderr, "syntax error");
            goto beg;
          }
          cur += nchar + 1;
          num[num_c++] = (string) buff;
          goto a;
        }
        operand = 0;
        if (op_c != 0)
          if (op[op_c - 1] == '*' || op[op_c - 1] == '/')
            for (op_c -= 1; op_c > -1; op_c--) {
              switch (op[op_c]) {
              case '*':
                num[num_c - 2] = num[num_c - 2] * num[num_c - 1];
                break;
              case '/':
                num[num_c - 2] = num[num_c - 2] / num[num_c - 1];
                break;
              case '-':
                num[num_c - 2] = num[num_c - 2] - num[num_c - 1];
                break;
              case '+':
                num[num_c - 2] = num[num_c - 2] + num[num_c - 1];
                break;
              }
              num_c--;
              op[op_c] = 0;
            }
	op_c = 0;
        op[op_c++] = '-';
        cur++;
        break;
      case '*':
        if (!operand) {
          fprintf(stderr, "syntax error\n");
          goto beg;
        }
        operand = 0;
        op[op_c++] = '*';
        cur++;
        break;
      case '/':
        if (!operand) {
          fprintf(stderr, "syntax error\n");
          goto beg;
        }
	operand = 0;
        op[op_c++] = '/';
        cur++;
        break;
      case 0:
        if (!operand) {
          fprintf(stderr, "syntax error\n");
          goto beg;
        }
        operand = 0;
        if (op_c != 0)
          for (op_c -= 1; op_c > -1; op_c--) {
            switch (op[op_c]) {
            case '*':
              num[num_c - 2] = num[num_c - 2] * num[num_c - 1];
              break;
            case '/':
              num[num_c - 2] = num[num_c - 2] / num[num_c - 1];
              break;
            case '-':
              num[num_c - 2] = num[num_c - 2] - num[num_c - 1];
              break;
            case '+':
              num[num_c - 2] = num[num_c - 2] + num[num_c - 1];
              break;
            }
            num_c--;
            op[op_c] = 0;
          }
	std::cout << " = " << num[num_c - 1] << std::endl;
        goto beg;
      default:
        fprintf(stderr, "illegal character: '%c'\n", expr[cur]);
        goto beg;
      }
    }
  }

  return 0;
}
