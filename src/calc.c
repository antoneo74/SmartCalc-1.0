#include "calc.h"

Node* CreateNewNode(char c, int priority, int binary, double number) {
  Node* tmp = (Node*)malloc(sizeof(Node));
  tmp->c = c;
  tmp->priority = priority;
  tmp->binary = binary;
  tmp->number = number;
  tmp->next = NULL;
  return tmp;
}

void AddToHead(char c, int priority, int binary, double number, Node** head) {
  Node* tmp = CreateNewNode(c, priority, binary, number);
  if (*head) {
    tmp->next = *head;
  }
  *head = tmp;
}
void AddToTail(char c, int priority, int binary, double number, Node** head) {
  Node* tmp = CreateNewNode(c, priority, binary, number);
  if (*head) {
    Node* step = *head;
    while (step->next != 0) {
      step = step->next;
    }
    step->next = tmp;
  } else {
    *head = tmp;
  }
}

void RemoveNodeFromHead(Node** head) {
  if (*head) {
    Node* tmp = *head;
    *head = tmp->next;
    free(tmp);
    tmp = NULL;
  }
}

void RemoveAll(Node** head) {
  Node* tmp = *head;
  while (tmp) {
    tmp = tmp->next;
    RemoveNodeFromHead(head);
  }
  tmp = NULL;
  *head = NULL;
}

/* Проверка является ли символ числом
   1 - число
   0 - символ
*/
int isdigital(char c) {
  int res = 0;
  if (c >= '0' && c <= '9') {
    res = 1;
  }
  return res;
}

void parse_action(const char** string, Node** digital, int oper) {
  if (*string == strstr(*string, "sin")) {
    AddToTail('s', 3, 0, 0, digital);
    *string = *string + 3;
  } else if (*string == strstr(*string, "cos")) {
    AddToTail('c', 3, 0, 0, digital);
    *string = *string + 3;
  } else if (*string == strstr(*string, "tan")) {
    AddToTail('t', 3, 0, 0, digital);
    *string = *string + 3;
  } else if (*string == strstr(*string, "mod")) {
    AddToTail('m', 2, 1, 0, digital);
    *string = *string + 3;
  } else if (*string == strstr(*string, "ln")) {
    AddToTail('l', 3, 0, 0, digital);
    *string = *string + 2;
  } else if (*string == strstr(*string, "log")) {
    AddToTail('L', 3, 0, 0, digital);
    *string = *string + 3;
  } else if (*string == strstr(*string, "asin")) {
    AddToTail('S', 3, 0, 0, digital);
    *string = *string + 4;
  } else if (*string == strstr(*string, "acos")) {
    AddToTail('C', 3, 0, 0, digital);
    *string = *string + 4;
  } else if (*string == strstr(*string, "atan")) {
    AddToTail('T', 3, 0, 0, digital);
    *string = *string + 4;
  } else if (*string == strstr(*string, "sqrt")) {
    AddToTail('Q', 3, 0, 0, digital);
    *string = *string + 4;
  } else if (*(*string) == '(' || *(*string) == ')') {
    AddToTail(*(*string), 0, 0, 0, digital);
    *string = *string + 1;
  } else if (*(*string) == '+' || *(*string) == '-') {
    if (oper) {
      AddToTail(*(*string), 4, 0, 0, digital);
    } else {
      AddToTail(*(*string), 1, 1, 0, digital);
    }
    *string = *string + 1;
  } else if (*(*string) == '*' || *(*string) == '/') {
    AddToTail(*(*string), 2, 1, 0, digital);
    *string = *string + 1;

  } else if (*(*string) == '^') {
    AddToTail(*(*string), 3, 1, 0, digital);
    *string = *string + 1;
  }
}

/* Вытаскиваем числа из строки */
int CreateNumber(const char** string, Node** digital) {
  int error = 0;
  int dot_flag = 0;
  int counter = 0;
  double number = 0;

  while (*(*string) == '.' || isdigital(*(*string))) {
    if (dot_flag) counter++;
    if (*(*string) == '.' && dot_flag) {
      error = 1;
      break;
    } else if (*(*string) == '.' && !dot_flag) {
      dot_flag = 1;
    } else {
      number = number * 10 + (*(*string) - '0');
    }
    *string = *string + 1;
  }
  if (!error) {
    number /= pow(10, counter);
    AddToTail('z', 0, 0, number, digital);
  }
  return error;
}

/* Разбивка входной строки на лексемы */
int parse(const char* string, Node** digital, double x) {
  int error = 0;
  int oper = 1;
  for (; *string && !error; string++) {
    if (*string == 'X') {
      AddToTail('z', 0, 0, x, digital);
      oper = 0;
      string++;
    } else if (*string == '.' || isdigital(*string)) {
      error = CreateNumber(&string, digital);
      if (error) break;
      oper = 0;
    } else if (*string == ')') {
      parse_action(&string, digital, oper);
      oper = 0;
    } else if (*string == ' ') {
      continue;
    } else {
      parse_action(&string, digital, oper);
      oper = 1;
    }
    string = string - 1;
  }
  if (error) RemoveAll(digital);
  return error;
}

int createRPN(Node** digital, Node** rpn, Node** stack) {
  int error = 0;
  Node* tmp = *digital;
  while (tmp && !error) {
    if (tmp->c == 'z') {
      AddToTail(tmp->c, tmp->priority, tmp->binary, tmp->number, rpn);
    } else if (tmp->c == 's' || tmp->c == 'c' || tmp->c == 't' ||
               tmp->c == 'S' || tmp->c == 'C' || tmp->c == 'T' ||
               tmp->c == 'l' || tmp->c == 'L' || tmp->c == 'Q' ||
               tmp->c == '(') {
      AddToHead(tmp->c, tmp->priority, tmp->binary, tmp->number, stack);
    } else if (tmp->c == ')') {
      while (*stack && (*stack)->c != '(') {
        AddToTail((*stack)->c, (*stack)->priority, (*stack)->binary,
                  (*stack)->number, rpn);
        RemoveNodeFromHead(stack);
      }
      if (*stack == NULL)
        error = 1;
      else
        RemoveNodeFromHead(stack);
    } else {
      while (*stack != NULL && tmp->priority <= (*stack)->priority) {
        AddToTail((*stack)->c, (*stack)->priority, (*stack)->binary,
                  (*stack)->number, rpn);
        RemoveNodeFromHead(stack);
      }
      AddToHead(tmp->c, tmp->priority, tmp->binary, tmp->number, stack);
    }
    tmp = tmp->next;
    RemoveNodeFromHead(digital);
  }
  if (*stack && !error) {
    Node* head_stack = *stack;
    while (head_stack) {
      if (head_stack->c == '(') {
        error = 1;
        break;
      }
      AddToTail(head_stack->c, head_stack->priority, head_stack->binary,
                head_stack->number, rpn);
      head_stack = head_stack->next;
      RemoveNodeFromHead(stack);
    }
  }
  if (error) {
    RemoveAll(digital);
    RemoveAll(rpn);
    RemoveAll(stack);
  }

  return error;
}

double Calc(double first_operand, double second_operand, char action) {
  double result = 0;
  switch (action) {
    case '+':
      result = first_operand + second_operand;
      break;
    case '-':
      result = first_operand - second_operand;
      break;
    case '*':
      result = first_operand * second_operand;
      break;
    case '/':
      result = first_operand / second_operand;
      break;
    case '^':
      result = pow(first_operand, second_operand);
      break;
    case 'm':
      result = fmod(first_operand, second_operand);
      break;
    case 's':
      result = sin(first_operand);
      break;
    case 'c':
      result = cos(first_operand);
      break;
    case 't':
      result = tan(first_operand);
      break;
    case 'S':
      result = asin(first_operand);
      break;
    case 'C':
      result = acos(first_operand);
      break;
    case 'T':
      result = atan(first_operand);
      break;
    case 'l':
      result = log(first_operand);
      break;
    case 'L':
      result = log10(first_operand);
      break;
    case 'Q':
      result = sqrt(first_operand);
      break;
  }
  return result;
}

int Calculate(Node** rpn, double* result) {
  int error = 0;
  Node* stack = NULL;
  if (*rpn) {
    while (*rpn && !error) {
      if ((*rpn)->c == 'z') {
        AddToHead((*rpn)->c, (*rpn)->priority, (*rpn)->binary, (*rpn)->number,
                  &stack);
      } else {
        if (!stack) {
          error = 1;
        } else {
          double first_operand = 0;
          double second_operand = 0;
          char action = (*rpn)->c;
          int binary = (*rpn)->binary;

          if ((action == '+' || action == '-') && !binary) {
            stack->number = (action == '-' ? -stack->number : stack->number);

          } else {
            if (binary) {
              second_operand = stack->number;
              RemoveNodeFromHead(&stack);
              if (stack) {
                first_operand = stack->number;
                RemoveNodeFromHead(&stack);
              } else {
                error = 1;
              }

            } else {
              first_operand = stack->number;
              RemoveNodeFromHead(&stack);
            }
            double res = Calc(first_operand, second_operand, action);
            AddToHead('z', 0, 0, res, &stack);
          }
        }
      }
      RemoveNodeFromHead(rpn);
    }
    if (!error) {
      *result = stack->number;
      RemoveNodeFromHead(&stack);
    }
    if (error) RemoveAll(rpn);
  }
  return error;
}

int push_button_equal(const char* string, double* result, double x) {
  Node* digital = NULL;
  Node* rpn = NULL;
  Node* stack = NULL;

  int error = parse(string, &digital, x);
  if (!error) {
    error = createRPN(&digital, &rpn, &stack);
    if (!error) {
      error = Calculate(&rpn, result);
    }
  }

  return error;
}

/* Начисленные проценты за период */
double Accrued_interest(double deposit, double percent, int days,
                        int daysOfYear) {
  double result = deposit * percent * days / daysOfYear / 100;

  return result;
}

/* Сумма налога, если полученный доход превышает необлагаемую сумму */
double Tax(double accurent, double stavkaCBR, double stavkaNDFL) {
  double non_taxable_amount = 1000000 * stavkaCBR / 100;
  double result = 0;
  if (accurent > non_taxable_amount) {
    result = (accurent - non_taxable_amount) * stavkaNDFL / 100;
  }

  return result;
}

double Anuitet(double body, double period, double percent) {
  double monthly_payment = 0;
  double monthly_percent = percent / 1200;
  monthly_payment =
      body * monthly_percent / (1 - pow(1 + monthly_percent, -period));

  return monthly_payment;
}

double Pereplata(double body, double monthly_payment, double period) {
  double pereplata = 0;
  pereplata = monthly_payment * period - body;

  return pereplata;
}

double Monthly_percent_payment(double body, double percent) {
  double result = 0;
  result = body * percent / 1200;
  return result;
}
