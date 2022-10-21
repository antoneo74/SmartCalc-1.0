#ifndef SRC_S21_CALC_H_
#define SRC_S21_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 0.0000001

typedef struct Node {
  char c;
  int priority;
  int binary;  // 0 - унарный, 1 - бинарный
  double number;
  struct Node* next;
} Node;

Node* CreateNewNode(char c, int priority, int binary, double number);
void AddToHead(char c, int priority, int binary, double number, Node** head);
void AddToTail(char c, int priority, int binary, double number, Node** head);
void RemoveNodeFromHead(Node** head);
void PrintList(Node* head);
int isdigital(char c);
void parse_action(const char** string, Node** digital, int oper);
int parse(const char* string, Node** digital, double x);
int createRPN(Node** digital, Node** rpn, Node** stack);
double Calc(double first_operand, double second_operand, char action);
int Calculate(Node** rpn, double* result);
int GetOperand(Node** stack, double* operand);
int push_button_equal(const char* string, double* result, double x);
double Tax(double accurent, double stavkaCBR, double stavkaNDFL);
double Accrued_interest(double deposit, double percent, int days,
                        int daysOfYear);
double Anuitet(double body, double period, double percent);
double Pereplata(double body, double monthly_payment, double period);
double Monthly_percent_payment(double body, double percent);
int CreateNumber(const char** string, Node** digital);

#endif  // SRC_S21_CALC_H_