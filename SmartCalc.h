#ifndef _SMARTCALC_H_
#define _SMARTCALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief допустимая длина обрабатываемой строки
 */
#define BUFFER 512

/** @brief код ошибки, заменяет на 0
 */
#define OK 0

/** @brief код ошибки, заменяет на 1
 */
#define ERROR 1

/** @brief тип элемента
 *  @param NUMBER число
 *  @param Xx  - икс
 *  @param OPEN_BRACE открывающая скобка
 *  @param CLOSE_BRACE закрывающая скобка
 *  @param PLUS плюс
 *  @param MINUS минус
 *  @param MULT умножение
 *  @param DIV деление
 *  @param MOD остаток от деления
 *  @param POW степень
 *  @param COS косинус
 *  @param SIN синус
 *  @param TAN тангенс
 *  @param ACOS аркосинус
 *  @param ASIN арксинус
 *  @param ATAN арктангенс
 *  @param SQRT квадратный корень
 *  @param LOG десятичный логарифм
 *  @param LN натуральный логарифм
 *  @param UN_PLUS унарный плюс
 *  @param UN_MINUS унарный минус
 */
typedef enum type_t {
  NUMBER = 1,
  Xx,
  OPEN_BRACE,
  CLOSE_BRACE,
  PLUS,
  MINUS,
  MULT,
  DIV,
  MOD,
  POW,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LOG,
  LN,
  UN_PLUS,
  UN_MINUS
} type_t;

/** @brief структура, хранящая параменты элементов в стэке
 *  @param value значение
 *  @param priority приоритет операции
 *  @param type тип элемента (см. структуру выше)
 *  @param *next хранит адрес следующей структуры
 */
typedef struct my_stack {
  double value;
  int priority;
  type_t type;
  struct my_stack *next;
} my_stack;

/*
 приоритет вычисления:
 0) number, x, (, )
 1) + -
 2) * / mod
 3) ^
 4) cos, sin, tan, acos, asin, atan, sqrt, ln, log
*/

/** @brief функция выполняющая, функцию main
 *  @param *input строка ввода
 *  @param x значение x
 *  @param *result переменная, хранящая результат вычисления
 */
int process(const char *input, double x, double *result);

/** @brief функция копирует строку без пробелов и вызывает функции проверок
 *  @param *input строка ввода
 *  @param *new_str новая строка
 */
int checking(const char *input, char *new_str);

/** @brief функция проверяет ввод (скобки)
 *  @param *str строка ввода
 *  @param lenght длина строки
 */
int check_brace(const char *str, int lenght);

/** @brief функция проверяет ввод (последний элемент)
 *  @param *str строка ввода
 *  @param i номер последнего элемента
 */
int check_last(const char *str, int i);

/** @brief функция проверяет ввод (каждый элемент)
 *  @param *str строка ввода
 *  @param lenght длина строки
 */
int check_input(char *str, int lenght);

/** @brief функция проверяет ввод (корректность записи числa)
 *  @param *str строка ввода
 *  @param i номер элемента в строке
 */
int check_number(const char *str, int i);

/** @brief функция проверяет ввод (корректность записи точки)
 *  @param *str строка ввода
 *  @param i номер элемента в строке
 */
int check_point(const char *str, int i);

/** @brief функция проверяет ввод (корректность записи x)
 *  @param *str строка ввода
 *  @param i номер элемента в строке
 */
int checking_x(const char *str, int i);

/** @brief функция проверяет знак (является ли это + или - )
 *  @param sign знак в виде элемента
 */
int simple_sign(char sign);

/** @brief функция проверяет знак (является ли это * или / или ^ )
 *  @param sign знак в виде элемента
 */
int not_simple_sign(char sign);

/** @brief функция проверяет ввод (корректность записи знака)
 *  @param *str строка ввода
 *  @param i номер элемента в строке
 */
int check_sign(char *str, int i);

/** @brief функция проверяет ввод (корректность записи mod)
 *  @param *str строка ввода
 *  @param i номер элемента в строке
 */
int check_mod(char *str, int i);

/** @brief функция проверяет ввод (корректность записи функций)
 *  @param *str строка ввода
 *  @param i номер элемента в строке
 *  @param f параметр функции, как типа
 */
int check_function(char *str, int i, int f);

/** @brief функция проверяет ввод (корректность записи знака перед функцией)
 *  @param *str строка ввода
 *  @param i номер элемента в строке
 */
int sign_before_function(char *str, int i);

/** @brief функция парсинга строки
 *  @param *str строка ввода
 *  @param **list адрес стэка(листа) куда кладем элементы строки
 */
int parsing(char *str, my_stack **list);

/** @brief функция в зависимости существует лист или нет  - создает или
 * добавляет элемент в лист (вызывая функции ниже)
 *  @param **list адрес листа куда кладем элементы строки
 *  @param *str строка ввода
 *  @param priority приоритетность операций
 *  @param type тип элемента
 */
void push_to_list(my_stack **list, char *str, int priority, type_t type);

/** @brief функция создает лист
 *  @param *str строка ввода
 *  @param priority приоритетность операций
 *  @param type тип элемента
 */
my_stack *create_list(char *str, int priority, type_t type);

/** @brief функция добавляет элемент в лист
 *  @param *head адрес листа куда кладем элемент строки
 *  @param *str строка ввода
 *  @param priority приоритетность операций
 *  @param type тип элемента
 */
void add_list(my_stack *head, char *str, int priority, type_t type);

/** @brief функция проверяет знак (унарный ли он)
 *  @param *str строка ввода
 *  @param i номер элемента в строке
 */
int un_sign(const char *str, int i);

/** @brief функция, выполняющая польскую нотацию
 *  @param *list адрес листа откуда берем элементы
 *  @param **stack адрес стэка куда кладем элементы
 */
void polish_notation(my_stack *list, my_stack **stack);

/** @brief функция в зависимости существует  стэк или нет  - создает или
 * добавляет элемент в стэк (вызывая функции ниже)
 *  @param **stack адрес стэка
 *  @param value значение
 *  @param priority приоритетность операций
 *  @param type тип элемента
 */
void push(my_stack **stack, double value, int priority, type_t type);

/** @brief функция создания стэка
 *  @param **top адрес вершины стэка
 *  @param value значение
 *  @param priority приоритетность операций
 *  @param type тип элемента
 */
void create_stack(my_stack **top, double value, int priority, type_t type);

/** @brief функция добавления элемента в стэк
 *  @param **top адрес вершины стэка
 *  @param value значение
 *  @param priority приоритетность операций
 *  @param type тип элемента
 */
void push_up(my_stack **top, double value, int priority, type_t type);

/** @brief функция перехода к следующему элементу в стэке (снимает как тарелки
 * из стопки)
 *  @param **stack адрес вершины стэка
 */
void pop(my_stack **stack);

/** @brief функция сравнения приоритетности временного стека и основного стека
 *  @param *tmp адрес вершины временного стэка
 *  @param priority приоритетность операций
 */
int greater_priority(my_stack *tmp, int priority);

/** @brief функция преобразования листа в стэк (и заменными x на значения)
 *  @param **stack адрес вершины стэка
 *  @param value_x
 */
void my_stack_to_list(my_stack **stack, double value_x);

/** @brief функция выполнения расчетов
 *  @param **stack адрес вершины стэка
 */
void calculation(my_stack **stack);

/** @brief функция подсчета арифметических операций
 *  @param **stack адрес стэка
 *  @param *tmp1 элемент стека, участвующий в расчете
 *  @param *tmp2 элемент стека, участвующий в расчете
 *  @param *tmp3 элемент стека, участвующий в расчете
 */
void count_arithmetic(my_stack **stack, my_stack *tmp1, my_stack *tmp2,
                      my_stack *tmp3);

/** @brief функция подсчета арифметических операций
 *  @param **original адрес стэка
 *  @param *element элемент, который нужно удалить
 */
void delete_element(my_stack **original, my_stack *element);

/** @brief функция подсчета операций с функцией или унарным знаком
 *  @param **stack адрес стэка
 *  @param *tmp1 элемент стека, участвующий в расчете
 *  @param *tmp2 элемент стека, участвующий в расчете
 */
void count_function(my_stack **stack, my_stack *tmp1, my_stack *tmp2);

/** @brief функция удаления листа
 *  @param *head адрес листа
 */
void delete_list(my_stack *head);

/** @brief функция кредитного аннуитетного калькулятора
 *  @param credit_amount сумма кредита
 *  @param time срок
 *  @param rate процентная ставка
 *  @param *monthly_payment ежемесячный платеж
 *  @param *overpayment переплата по кредиту
 *  @param *total_payment общая выплата
 */
void annuity_credit(double credit_amount, int time, double rate,
                    double *monthly_payment, double *overpayment,
                    double *total_payment);

/** @brief функция кредитного дифференцированного калькулятора
 *  @param credit_amount сумма кредита
 *  @param time срок
 *  @param rate процентная ставка
 *  @param *max_payment максимальный ежемесячный платеж
 *  @param *min_payment минимальный ежемесячный платеж
 *  @param *overpayment переплата по кредиту
 *  @param *total_payment общая выплата
 */
void credit_differentiated(double credit_amount, int time, double rate,
                           double *max_payment, double *min_payment,
                           double *overpayment, double *total_payment);

/** @brief функция округления
 *  @param value значение, которое нужно округлить
 */
double rounding(double value);

/** @brief функция депозитного калькулятора калькулятора
 *  @param deposit сумма вклада
 *  @param time срок
 *  @param rate процентная ставка
 *  @param nalog_rate налоговая ставка
 *  @param period_payment периодичность выплат
 *  @param capitalization (1 - есть, 0 - нет)
 *  @param add_deposit сумма пополнений (раз в период)
 *  @param remove_deposit сумма списаний (раз в период)
 *  @param month месяц начала вклада
 *  @param *profit начисленные проценты
 *  @param *tax налоги
 *  @param *deposit_end сумма на вкладе к концу срока
 */
void deposit_count(double deposit, int time, double rate, double nalog_rate,
                   int period_payment, int capitalization, double add_deposit,
                   double remove_deposit, int month, double *profit,
                   double *tax, double *deposit_end);

/** @brief функция подсчета сколько дней в месяце
 *  @param month номер месяца
 *  @param *days переменная, в которую записывается кол-во дней в месяце
 */
void how_many_days(int month, int *days);
#endif  // _SMARTCALC_H_
