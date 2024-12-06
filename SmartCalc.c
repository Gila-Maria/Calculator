#include "SmartCalc.h"

//  int main() {
//          char str[BUFFER] = "2x";
//          double x = 0;
//          double result = 0;
//          //printf("\033[100mВнесите пример:\033[0m\n");
//          // fgets(str, BUFFER, stdin);
//          //printf("\033[100mВнесите значение x:\033[0m\n");
//          // scanf("%lf", &x);
//          process(str, x, &result);
//          printf("\033[100mРезультат:\033[0m %lf\n", result);
//          return 0;
//  }

int process(const char *input, double x, double *result) {
  char new_str[BUFFER] = "";
  *result = 0;
  int error = checking(input, new_str);
  if (!error) {
    my_stack *list = NULL;
    my_stack *stack = NULL;
    error = parsing(new_str, &list);
    if (!error) {
      polish_notation(list, &stack);
      my_stack_to_list(&stack, x);
      calculation(&stack);
      *result = stack->value;
    }
    delete_list(list);
    delete_list(stack);
  }
  return error;
}

int checking(const char *input, char *new_str) {
  int error = OK;
  int lenght = strlen(input);
  int j = 0;
  for (int i = 0; i < lenght; i++) {
    if (input[i] == 32) {
      continue;
    } else {
      new_str[j] = input[i];
      j++;
    }
  }
  lenght = strlen(new_str);
  if (check_brace(new_str, lenght)) {
    error = ERROR;
  } else if (check_last(new_str, lenght - 1)) {
    error = ERROR;
  } else if (check_input(new_str, lenght)) {
    error = ERROR;
  }
  return error;
}

int check_brace(const char *str, int lenght) {
  int error = OK;
  int o_brace = 0, c_brace = 0;
  for (int i = 0; i < lenght; i++) {
    if (str[i] == '(') {
      o_brace++;
      if (str[i + 1] == ')') {
        error = ERROR;
        break;
      }
    }
    if (str[i] == ')') {
      c_brace++;
      if ((str[i + 1] == '(') || c_brace > o_brace) {
        error = ERROR;
        break;
      }
    }
  }
  if (o_brace != c_brace) error = ERROR;
  return error;
}

int check_last(const char *str, int i) {
  return (str[i] != ')' && str[i] != 'x' && (str[i] < '0' || str[i] > '9'));
}

int check_input(char *str, int lenght) {
  int error = OK;
  for (int i = 0; i < lenght; i++) {
    if (error) {
      break;
    } else if ((str[i] >= '0' && str[i] <= '9') || str[i] == ')') {
      if (check_number(str, i)) error = ERROR;
    } else if (str[i] == '(') {
      continue;
    } else if (str[i] == '.') {
      if (check_point(str, i)) error = ERROR;
    } else if (str[i] == 'x' || str[i] == 'X') {
      if (checking_x(str, i)) error = ERROR;
    } else if (simple_sign(str[i])) {
      if (check_sign(str, i)) error = ERROR;
    } else if (not_simple_sign(str[i])) {
      if (i == 0 || str[i - 1] == '(' || check_sign(str, i)) error = ERROR;
    } else if (str[i] == 'm') {
      int end = (i + 3);
      if (end >= lenght) {
        error = ERROR;
      } else {
        if (check_mod(str, i))
          error = ERROR;
        else
          i += 2;
      }
    } else if (str[i] == 'c' || str[i] == 't') {
      if (!check_function(str, i, COS) || !check_function(str, i, TAN)) {
        i += 3;
      } else {
        error = ERROR;
      }
    } else if (str[i] == 's') {
      if (!check_function(str, i, SIN)) {
        i += 3;
      } else if (!check_function(str, i, SQRT)) {
        i += 4;
      } else {
        error = ERROR;
      }
    } else if (str[i] == 'a') {
      if (!check_function(str, i, ACOS) || !check_function(str, i, ASIN) ||
          !check_function(str, i, ATAN)) {
        i += 4;
      } else {
        error = ERROR;
      }
    } else if (str[i] == 'l') {
      if (!check_function(str, i, LN)) {
        i += 2;
      } else if (!check_function(str, i, LOG)) {
        i += 3;
      } else {
        error = ERROR;
      }
    } else {
      error = ERROR;
    }
  }
  return error;
}

int check_number(const char *str, int i) {
  int error = OK;

  if (str[i + 1] == '(' || str[i + 1] == 's' || str[i + 1] == 'c') {
    error = ERROR;
  }
  if (str[i + 1] == 't' || str[i + 1] == 'a' || str[i + 1] == 'l') {
    error = ERROR;
  }
  if (i != 0 && str[i] != ')') {
    if (str[i - 1] == ')') error = ERROR;
  }
  return error;
}

int check_point(const char *str, int i) {
  int error = OK;
  if (i == 0) {
    error = ERROR;
  } else {
    if (str[i + 1] < '0' || str[i + 1] > '9') error = ERROR;
    if (str[i - 1] < '0' || str[i - 1] > '9') error = ERROR;
  }
  return error;
}

int checking_x(const char *str, int i) {  // xx
  int error = OK;
  if (check_number(str, i)) {
    error = ERROR;
  } else {
    if ((str[i + 1] >= '0' && str[i + 1] <= '9') || str[i + 1] == '.')
      error = ERROR;
    if (i != 0) {
      if ((str[i - 1] >= '0' && str[i - 1] <= '9') || str[i - 1] == '.')
        error = ERROR;
    }
  }
  return error;
}

int simple_sign(char sign) { return (sign == '+' || sign == '-'); }

int not_simple_sign(char sign) {
  return (sign == '*' || sign == '/' || sign == '^');
}

int check_sign(char *str, int i) {
  int error = OK;
  if (simple_sign(str[i + 1]) || not_simple_sign(str[i + 1])) error = ERROR;
  if (str[i + 1] == ')' || str[i + 1] == 'm' || str[i + 1] == '\0')
    error = ERROR;
  if (i != 0) {
    if (simple_sign(str[i - 1]) || not_simple_sign(str[i - 1])) error = ERROR;
    if (str[i - 1] == 'd') error = ERROR;
  }
  return error;
}

int check_mod(char *str, int i) {
  int error = OK;
  if (i == 0) {
    error = ERROR;
  } else {
    if (simple_sign(str[i + 3]) || not_simple_sign(str[i + 3])) error = ERROR;
    if (simple_sign(str[i - 1]) || not_simple_sign(str[i - 1])) error = ERROR;
    if (str[i - 1] == '(' || str[i + 3] == ')') error = ERROR;
    if (str[i + 1] != 'o' || str[i + 2] != 'd') error = ERROR;
  }
  return error;
}

int check_function(char *str, int i, int f) {
  int error = OK;
  if (sign_before_function(str, i)) {
    error = ERROR;
  } else {
    if (f == COS) {
      if (strncmp(&str[i], "cos(", 4)) error = ERROR;
    } else if (f == SIN) {
      if (strncmp(&str[i], "sin(", 4)) error = ERROR;
    } else if (f == TAN) {
      if (strncmp(&str[i], "tan(", 4)) error = ERROR;
    } else if (f == ACOS) {
      if (strncmp(&str[i], "acos(", 5)) error = ERROR;
    } else if (f == ASIN) {
      if (strncmp(&str[i], "asin(", 5)) error = ERROR;
    } else if (f == ATAN) {
      if (strncmp(&str[i], "atan(", 5)) error = ERROR;
    } else if (f == SQRT) {
      if (strncmp(&str[i], "sqrt(", 5)) error = ERROR;
    } else if (f == LN) {
      if (strncmp(&str[i], "ln(", 3)) error = ERROR;
    } else if (f == LOG) {
      if (strncmp(&str[i], "log(", 4)) error = ERROR;
    }
  }
  return error;
}

int sign_before_function(char *str, int i) {
  int error = OK;
  if (i != 0 && str[i - 1] != '(' && str[i - 1] != 'd') {
    if (!(simple_sign(str[i - 1]) || not_simple_sign(str[i - 1])))
      error = ERROR;
  }
  return error;
}

int parsing(char *str, my_stack **list) {
  int error = OK;
  char str_number[BUFFER];
  int n = 0;
  int point = 0;
  for (size_t i = 0; i < strlen(str); i++) {
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
      if (str[i] == '.') point++;
      str_number[n++] = str[i];
      if ((str[i + 1] < '0' || str[i + 1] > '9') && str[i + 1] != '.') {
        if (point > 1) {
          error = ERROR;
          break;
        }
        str_number[n] = '\0';
        push_to_list(list, str_number, 0, NUMBER);
        n = 0;
        point = 0;
      }
    } else if (str[i] == '(') {
      push_to_list(list, "0", 0, OPEN_BRACE);
    } else if (str[i] == ')') {
      push_to_list(list, "0", 0, CLOSE_BRACE);
    } else if (str[i] == 'x' || str[i] == 'X') {
      push_to_list(list, "0", 0, Xx);
    } else if (str[i] == '+') {
      if (un_sign(str, i)) {
        push_to_list(list, "0", 1, UN_PLUS);
      } else {
        push_to_list(list, "0", 1, PLUS);
      }
    } else if (str[i] == '-') {
      if (un_sign(str, i)) {
        push_to_list(list, "0", 1, UN_MINUS);
      } else {
        push_to_list(list, "0", 1, MINUS);
      }
    } else if (str[i] == '*') {
      push_to_list(list, "0", 2, MULT);
    } else if (str[i] == '/') {
      push_to_list(list, "0", 2, DIV);
    } else if (str[i] == 'm') {
      push_to_list(list, "0", 2, MOD);
    } else if (str[i] == '^') {
      push_to_list(list, "0", 3, POW);
    } else if (str[i] == 'c') {
      push_to_list(list, "0", 4, COS);
      i += 2;
    } else if (str[i] == 's' && str[i + 1] == 'i') {
      push_to_list(list, "0", 4, SIN);
      i += 2;
    } else if (str[i] == 's' && str[i + 1] == 'q') {
      push_to_list(list, "0", 4, SQRT);
      i += 3;
    } else if (str[i] == 't') {
      push_to_list(list, "0", 4, TAN);
      i += 2;
    } else if (str[i] == 'a' && str[i + 1] == 'c') {
      push_to_list(list, "0", 4, ACOS);
      i += 3;
    } else if (str[i] == 'a' && str[i + 1] == 's') {
      push_to_list(list, "0", 4, ASIN);
      i += 3;
    } else if (str[i] == 'a' && str[i + 1] == 't') {
      push_to_list(list, "0", 4, ATAN);
      i += 3;
    } else if (str[i] == 'l' && str[i + 1] == 'n') {
      push_to_list(list, "0", 4, LN);
      i += 1;
    } else if (str[i] == 'l' && str[i + 1] == 'o') {
      push_to_list(list, "0", 4, LOG);
      i += 2;
    }
  }
  return error;
}

void push_to_list(my_stack **list, char *str, int priority, type_t type) {
  if (*list == NULL) {
    *list = create_list(str, priority, type);
  } else {
    add_list(*list, str, priority, type);
  }
}

my_stack *create_list(char *str, int priority, type_t type) {
  my_stack *new = (my_stack *)malloc(sizeof(my_stack));
  sscanf(str, "%lf", &new->value);
  new->priority = priority;
  new->type = type;
  new->next = NULL;
  return new;
}

void add_list(my_stack *head, char *str, int priority, type_t type) {
  my_stack *tmp = head;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = create_list(str, priority, type);
}

int un_sign(const char *str, int i) { return (i == 0 || str[i - 1] == '('); }

void polish_notation(my_stack *list, my_stack **stack) {
  my_stack *tmp = NULL;

  while (list) {
    if (list->type != 4) {
      if (list->type == 1 || list->type == 2) {
        push(stack, list->value, list->priority, list->type);
      } else {
        while (1) {
          if (greater_priority(tmp, list->priority) || list->type == 3) {
            push(&tmp, list->value, list->priority, list->type);
            break;
          } else {
            push(stack, tmp->value, tmp->priority, tmp->type);
            pop(&tmp);
          }
        }
      }
    } else {
      while (tmp->type != 3) {
        push(stack, tmp->value, tmp->priority, tmp->type);
        pop(&tmp);
      }
      pop(&tmp);
    }
    list = list->next;
  }

  while (tmp) {
    push(stack, tmp->value, tmp->priority, tmp->type);
    pop(&tmp);
  }
}

void push(my_stack **stack, double value, int priority, type_t type) {
  if (*stack == NULL) {
    create_stack(stack, value, priority, type);
  } else {
    push_up(stack, value, priority, type);
  }
}

void create_stack(my_stack **top, double value, int priority, type_t type) {
  my_stack *tmp = (struct my_stack *)malloc(sizeof(struct my_stack));
  tmp->value = value;
  tmp->priority = priority;
  tmp->type = type;
  tmp->next = NULL;
  *top = tmp;
}

void push_up(my_stack **top, double value, int priority, type_t type) {
  my_stack *tmp = (struct my_stack *)malloc(sizeof(struct my_stack));
  tmp->value = value;
  tmp->priority = priority;
  tmp->type = type;
  tmp->next = *top;
  *top = tmp;
}

void pop(my_stack **stack) {
  if (*stack != NULL) {
    my_stack *tmp = (*stack)->next;
    free(*stack);
    *stack = tmp;
  }
}

int greater_priority(my_stack *tmp, int priority) {
  return (tmp == NULL || priority > tmp->priority);
}

void my_stack_to_list(my_stack **stack, double value_x) {
  my_stack *list = NULL;
  while (*stack) {
    if ((*stack)->type == Xx) {
      (*stack)->type = NUMBER;
      (*stack)->value = value_x;
    }
    push(&list, (*stack)->value, (*stack)->priority, (*stack)->type);
    pop(stack);
  }
  *stack = list;
}

void calculation(my_stack **stack) {
  while ((*stack)->next != NULL) {
    my_stack *tmp1, *tmp2, *tmp3;
    tmp1 = *stack;
    tmp2 = tmp1->next;
    if (tmp2->next != NULL) tmp3 = tmp2->next;
    if (tmp2->type == NUMBER) {
      while (1) {
        if (tmp3->priority) {
          break;
        }
        tmp1 = tmp2;
        tmp2 = tmp1->next;
        tmp3 = tmp2->next;
      }
      if (tmp3->type >= 5 && tmp3->type <= 10) {
        count_arithmetic(stack, tmp1, tmp2, tmp3);
      } else {
        count_function(stack, tmp2, tmp3);
      }
    } else {
      count_function(stack, tmp1, tmp2);
    }
  }
}

void count_arithmetic(my_stack **stack, my_stack *tmp1, my_stack *tmp2,
                      my_stack *tmp3) {
  double result = 0;
  double a = tmp1->value;
  double b = tmp2->value;
  if (tmp3->type == PLUS) {
    result = a + b;
  } else if (tmp3->type == MINUS) {
    result = a - b;
  } else if (tmp3->type == MULT) {
    result = a * b;
  } else if (tmp3->type == DIV) {
    result = a / b;
  } else if (tmp3->type == POW) {
    result = pow(a, b);
  } else if (tmp3->type == MOD) {
    result = fmod(a, b);
  }
  tmp1->value = result;
  tmp1->priority = 0;
  tmp1->type = NUMBER;
  delete_element(stack, tmp2);
  delete_element(stack, tmp3);
}

void delete_element(my_stack **original, my_stack *element) {
  my_stack *tmp;
  tmp = *original;
  if (*original == element) {
    tmp = (*original)->next;
    free(*original);
    *original = tmp;
  } else {
    while (tmp->next != element) {
      tmp = tmp->next;
    }
    tmp->next = element->next;
    free(element);
  }
}

void count_function(my_stack **stack, my_stack *tmp1, my_stack *tmp2) {
  double a = tmp1->value;
  double result = 0;
  if (tmp2->type == SIN) {
    result = sin(a);
  } else if (tmp2->type == COS) {
    result = cos(a);
  } else if (tmp2->type == TAN) {
    result = tan(a);
  } else if (tmp2->type == ASIN) {
    result = asin(a);
  } else if (tmp2->type == ACOS) {
    result = acos(a);
  } else if (tmp2->type == ATAN) {
    result = atan(a);
  } else if (tmp2->type == SQRT) {
    result = sqrt(a);
  } else if (tmp2->type == LOG) {
    result = log10(a);
  } else if (tmp2->type == LN) {
    result = log(a);
  } else if (tmp2->type == UN_PLUS) {
    result = +a;
  } else if (tmp2->type == UN_MINUS) {
    result = -a;
  }
  tmp1->value = result;
  tmp1->priority = 0;
  tmp1->type = NUMBER;
  delete_element(stack, tmp2);
}

void delete_list(my_stack *head) {
  while (head != NULL) {
    my_stack *old_head = head;
    head = head->next;
    free(old_head);
  }
}

void annuity_credit(double credit_amount, int time, double rate,
                    double *monthly_payment, double *overpayment,
                    double *total_payment) {
  double rate_month = rate / 100 / 12;
  *monthly_payment =
      credit_amount * ((rate_month * pow((1 + rate_month), time)) /
                       (pow((1 + rate_month), time) - 1));
  *total_payment = (*monthly_payment) * time;
  *overpayment = (*total_payment) - credit_amount;
  *monthly_payment = rounding(*monthly_payment);
  *total_payment = rounding(*total_payment);
  *overpayment = rounding(*overpayment);
}

void credit_differentiated(double credit_amount, int time, double rate,
                           double *max_payment, double *min_payment,
                           double *overpayment, double *total_payment) {
  double body_credit_monthly = credit_amount / time;
  for (int i = 0; i < time; i++) {
    double percent_monthly = credit_amount * (rate / 100) * 30.4166667 / 365;
    if (i == 0) *max_payment = body_credit_monthly + percent_monthly;
    if (i == time - 1) *min_payment = body_credit_monthly + percent_monthly;
    credit_amount -= body_credit_monthly;
    *overpayment += percent_monthly;
  }
  *total_payment = *overpayment + body_credit_monthly * time;
  *max_payment = rounding(*max_payment);
  *min_payment = rounding(*min_payment);
  *total_payment = rounding(*total_payment);
  *overpayment = rounding(*overpayment);
}

double rounding(double value) { return round(value * 100) / 100; }

void deposit_count(double deposit, int time, double rate, double nalog_rate,
                   int period_payment, int capitalization, double add_deposit,
                   double remove_deposit, int month, double *profit,
                   double *tax, double *deposit_end) {
  *profit = 0;
  *tax = 0;
  *deposit_end = 0;
  *deposit_end = deposit;
  // int count_changing = 0; // кол-во пополнений и списаний
  // double changing[count_changing][2] = {0}; // матрица в первом столбе -
  // номер дня пополнения, во 2ом изменения по депозиту (+/- сумма) как-то
  //заполнить матрицу double non_taxable_amount = nalog_rate / 100 * 1000000;
  int i = 0;
  while (i < time) {
    int period = 0;  //кол-во дней в периоде
    // int flag_new_year = 0;
    for (int j = 0; j < period_payment; j++) {
      int days;
      how_many_days(month, &days);
      period += days;
      month++;
      if (month == 13) {
        month = 1;
        // year++; //это используется для отслеживания смены года
        // flag_new_year = 1;
      }
    }
    if ((time - i) < period) period = time - i;

    double min_deposit_period = 0;
    min_deposit_period = *deposit_end;
    // if (count_changing) {
    //     for (int j = i + 1; j <= i + 1 + period; j++) {  //j пробегает по
    //     периоду и ищет пополненине или списание
    //         for (int y = 0; y < count_changing; y++){  //привидение типов
    //         нужно сделать
    //             if (j == changing[y][0]) {
    //                 *deposit_end += changing[y][1];
    //                 if (min_deposit_period > *deposit_end) min_deposit_period
    //                 = *deposit_end;
    //             }
    //         }
    //     }
    // }

    double profit_for_period = 0;
    profit_for_period = (min_deposit_period * rate * period / 365) / 100;
    *profit += profit_for_period;
    if (capitalization) {
      *deposit_end += profit_for_period;
    }
    if (add_deposit) {
      *deposit_end += add_deposit;
    }
    if (remove_deposit) {
      *deposit_end -= remove_deposit;
    }
    //вариант рассчета с необлогаемой суммой налога (нужно доработать)
    // if (*profit > non_taxable_amount && flag_new_year == 0)   //расчет за год
    //      *tax = *profit - non_taxable_amount * 0.13; // 13% НДФЛ

    i += period;
  }
  if (rate > 12.5) {
    *tax = *profit * nalog_rate / 100;
  }
}

void how_many_days(int month, int *days) {
  if (month == 2) {
    *days = 28;
  } else if (month == 4 || month == 6 || month == 9 || month == 11) {
    *days = 30;
  } else {
    *days = 31;
  }
}
