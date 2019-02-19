#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Expression_Read(char *Expression);
bool Character_Check(char *Expression);
bool Syntax_Check(char *Expression);
void Type_Change(char *Expression, double *Stack);
double Value_Solve(double *Stack);

int main(void)
{
    char *Expression;
    double *Stack;
    double Solution;
    bool Judge;

    Expression = (char *)malloc(100 * sizeof(char));
    Stack = (double *)malloc(100 * sizeof(double));
    printf("Enter the mathematical expression (nonempty): ");
    Expression_Read(Expression);

    Judge = Character_Check(Expression);
    if (Judge) {
        Judge = Syntax_Check(Expression);
        if (Judge) {
            Type_Change(Expression, Stack);
            Solution = Value_Solve(Stack);
            printf("The value of this mathematical expression is %.3f.\n", Solution);
        }
        else
            printf("There exists illegal syntax in the expression!\n");
    }
    else
        printf("There exists illegal character in the expression!\n");

    printf("Press ENTER to quit.\n");
    free(Expression);
    free(Stack);
    getchar();

    return 0;
}

void Expression_Read(char *Expression)
{
    char sym;
    int num = 1;

    *Expression = 0;
    sym = getchar();
    while (sym != '\n') {
        if (sym == ' ' || sym == '\t') {
            sym = getchar();
            continue;
        }
        *(Expression + num++) = sym;
        sym = getchar();
    }
    *(Expression + num) = 0;
}

bool Character_Check(char *Expression)
{
    int pos = 1;
    bool flag = true;

    while (*(Expression + pos)) {
        if (*(Expression + pos) >= 48 && *(Expression + pos) <= 57) {
            pos++;
            continue;
        }
        if (*(Expression + pos) == '.' || *(Expression + pos) == '^') {
            pos++;
            continue;
        }
        if (*(Expression + pos) == '(' || *(Expression + pos) == ')') {
            pos++;
            continue;
        }
        if (*(Expression + pos) == '*' || *(Expression + pos) == '/') {
            pos++;
            continue;
        }
        if (*(Expression + pos) == '+' || *(Expression + pos) == '-') {
            pos++;
            continue;
        }
        flag = false;
        break;
    }

    return flag;
}

bool Syntax_Check(char *Expression)
{
    int pos = 1, count = 0;
    bool flag = true;

    while (*(Expression + pos)) {
        if (*(Expression + pos) == '(')
            count++;
        else if (*(Expression + pos) == ')')
            count--;
        if (count < 0) {
            flag = false;
            break;
        }
        if (*(Expression + pos) == '(') {
            if (*(Expression + pos - 1) >= 48 && *(Expression + pos - 1) <= 57 || *(Expression + pos - 1) == ')') {
                flag = false;
                break;
            }
            if (*(Expression + pos + 1) == 0 || *(Expression + pos + 1) == ')') {
                flag = false;
                break;
            }
        }
        else if (*(Expression + pos) == ')') {
            if (*(Expression + pos - 1) == 0) {
                flag = false;
                break;
            }
        }
        else if (*(Expression + pos) == '.') {
            if (*(Expression + pos - 1) < 48 || *(Expression + pos - 1) > 57) {
                flag = false;
                break;
            }
            if (*(Expression + pos + 1) < 48 || *(Expression + pos + 1) > 57) {
                flag = false;
                break;
            }
        }
        else if (*(Expression + pos) == '^' || *(Expression + pos) == '*' || *(Expression + pos) == '/' || *(Expression + pos) == '+') {
            if (*(Expression + pos - 1) < 48 || *(Expression + pos - 1) > 57)
                if (*(Expression + pos - 1) != ')') {
                    flag = false;
                    break;
                }
            if (*(Expression + pos + 1) < 48 || *(Expression + pos + 1) > 57)
                if (*(Expression + pos + 1) != '(') {
                    flag = false;
                    break;
                }
        }
        else if (*(Expression + pos) == '-') {
            if (*(Expression + pos - 1) < 48 || *(Expression + pos - 1) > 57)
                if (*(Expression + pos - 1) != ')' && *(Expression + pos - 1) != '(')
                    if (*(Expression + pos - 1) != 0) {
                        flag = false;
                        break;
                    }
            if (*(Expression + pos + 1) < 48 || *(Expression + pos + 1) > 57)
                if (*(Expression + pos + 1) != '(') {
                    flag = false;
                    break;
                }
        }
        pos++;
    }

    return flag;
}

void Type_Change(char *Expression, double *Stack)
{
    int byte, pos = 1, num = 0;
    double int_part, float_part;

    while (*(Expression + pos)) {
        switch(*(Expression + pos)) {
            case '^':
                *(Stack + num++) = -94;
            break;
            case '*':
                *(Stack + num++) = -42;
            break;
            case '/':
                *(Stack + num++) = -47;
            break;
            case '+':
                *(Stack + num++) = -43;
            break;
            case '-':
                if (*(Expression + pos - 1) == 0 || *(Expression + pos - 1) == '(')
                    *(Stack + num++) = 0;
                *(Stack + num++) = -45;
            break;
            case '(':
                *(Stack + num++) = -40;
            break;
            case ')':
                *(Stack + num++) = -41;
            break;
            default:
                int_part = float_part = 0;
                while (*(Expression + pos) >= 48 && *(Expression + pos) <= 57) {
                    int_part = 10 * int_part + *(Expression + pos) - 48;
                    pos++;
                }
                if (*(Expression + pos) == 46) {
                    byte = 10;
                    pos++;
                }
                while (*(Expression + pos) >= 48 && *(Expression + pos) <= 57) {
                    float_part = float_part + (*(Expression + pos) - 48) * 1.0 / byte;
                    byte *= 10;
                    pos++;
                }
                *(Stack + num++) = int_part + float_part;
                pos--;
            break;
        }
        pos++;
    }
    *(Stack + num) = -1;
}

double Value_Solve(double *Stack)
{
    double *sym, *num;
    double result;
    int top = 0, rear = 0, pos = 0;

    sym = (double *)malloc(100 * sizeof(double));
    num = (double *)malloc(100 * sizeof(double));
    while (*(Stack + pos) != -1) {
        if (*(Stack + pos) >= 0)
            *(num + rear++) = *(Stack + pos);
        else if (*(Stack + pos) == -40)
            *(sym + top++) = *(Stack + pos);
        else if (*(Stack + pos) == -41) {
            top--;
            while (*(sym + top) != -40) {
                rear--;
                if (*(sym + top) == -94)
                    *(num + rear - 1) = pow(*(num + rear - 1), *(num + rear));
                else if (*(sym + top) == -42)
                    *(num + rear - 1) *= *(num + rear);
                else if (*(sym + top) == -47)
                    *(num + rear - 1) /= *(num + rear);
                else if (*(sym + top) == -43)
                    *(num + rear - 1) += *(num + rear);
                else if (*(sym + top) == -45)
                    *(num + rear - 1) -= *(num + rear);
                top--;
            }
        }
        else if (*(Stack + pos) == -94) {
            top--;
            while (top >= 0 && *(sym + top) == -94) {
                rear--;
                *(num + rear - 1) = pow(*(num + rear - 1), *(num + rear));
                top--;
            }
            top++;
            *(sym + top++) = *(Stack + pos);
        }
        else if (*(Stack + pos) == -42 || *(Stack + pos) == -47) {
            top--;
            while (top >= 0 && *(sym + top) != -40 && *(sym + top) != -43 && *(sym + top) != -45) {
                rear--;
                if (*(sym + top) == -94)
                    *(num + rear - 1) = pow(*(num + rear - 1), *(num + rear));
                else if (*(sym + top) == -42)
                    *(num + rear - 1) *= *(num + rear);
                else if (*(sym + top) == -47)
                    *(num + rear - 1) /= *(num + rear);
                top--;
            }
            top++;
            *(sym + top++) = *(Stack + pos);
        }
        else if (*(Stack + pos) == -43 || *(Stack + pos) == -45) {
            top--;
            while (top >= 0 && *(sym + top) != -40) {
                rear--;
                if (*(sym + top) == -94)
                    *(num + rear - 1) = pow(*(num + rear - 1), *(num + rear));
                else if (*(sym + top) == -42)
                    *(num + rear - 1) *= *(num + rear);
                else if (*(sym + top) == -47)
                    *(num + rear - 1) /= *(num + rear);
                else if (*(sym + top) == -43)
                    *(num + rear - 1) += *(num + rear);
                else if (*(sym + top) == -45)
                    *(num + rear - 1) -= *(num + rear);
                top--;
            }
            top++;
            *(sym + top++) = *(Stack + pos);
        }
        pos++;
    }
    top--;
    while (top >= 0) {
        rear--;
        if (*(sym + top) == -94)
            *(num + rear - 1) = pow(*(num + rear - 1), *(num + rear));
        else if (*(sym + top) == -42)
            *(num + rear - 1) *= *(num + rear);
        else if (*(sym + top) == -47)
            *(num + rear - 1) /= *(num + rear);
        else if (*(sym + top) == -43)
            *(num + rear - 1) += *(num + rear);
        else if (*(sym + top) == -45)
            *(num + rear - 1) -= *(num + rear);
        top--;
    }
    result = *(num + rear - 1);
    free(sym);
    free(num);

    return result;
}
