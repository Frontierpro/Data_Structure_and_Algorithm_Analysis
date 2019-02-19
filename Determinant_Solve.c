#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double **Determinant_Create(int Num);
int Num_Count(int Num);
void Out_Put(double **Determinant, int Num, int Count);
double Determinant_Solve(double **Determinant, int start, int Num);
void Memory_Clear(double **Determinant, int Num);

int main(void)
{
    int Num, Count;
    double **Determinant;
    double Solution;

    printf("Enter the degree (positive) of the determinant: ");
    scanf("%d", &Num);
    Determinant = Determinant_Create(Num);
    Count = Num_Count(Num);
    printf("The random_created determinant is as follows.\n");
    Out_Put(Determinant, Num, Count + 2);

    printf("The value of this determinant is: ");
    Solution = Determinant_Solve(Determinant, 0, Num);
    printf("%.f\n", Solution);

    printf("Press ENTER to quit.\n");
    Memory_Clear(Determinant, Num);
    getchar();
    getchar();

    return 0;
}

double **Determinant_Create(int Num)
{
    double **determinant;
    int row, col, temp;

    determinant = (double **)malloc(Num * sizeof(double *));
    for (row = 0; row < Num; row++)
        *(determinant + row) = (double *)malloc(Num * sizeof(double));
    srand((int)time(NULL));
    for (row = 0; row < Num; row++)
        for (col = 0; col < Num; col++) {
            temp = rand() % 9;
            if (temp == 0) {
                *(*(determinant + row) + col) = 0;
                continue;
            }
            if (rand() % 4)
                *(*(determinant + row) + col) = (double)temp;
            else
                *(*(determinant + row) + col) = -(double)temp;
        }

    return determinant;
}

int Num_Count(int Num)
{
    int count = 0;

    while (Num) {
        count++;
        Num /= 10;
    }

    return count;
}

void Out_Put(double **Determinant, int Num, int Count)
{
    int row, col;

    for (row = 0; row < Num; row++) {
        for (col = 0; col < Num; col++)
            printf("%*.f", Count, *(*(Determinant + row) + col));
        putchar('\n');
    }
}

double Determinant_Solve(double **Determinant, int start, int Num)
{
    int row, col;
    double coefficient, solution;

    if(start == Num)
        return 1.0;
    for (row = start + 1; row < Num; row++) {
        coefficient = 1.0 * *(*(Determinant + row) + start) / *(*(Determinant + start) + start);
        for (col = start + 1; col < Num; col++)
            *(*(Determinant + row) + col) -= coefficient * *(*(Determinant + start) + col);
    }
    solution = 1.0 * *(*(Determinant + start) + start) * Determinant_Solve(Determinant, start + 1, Num);

    return solution;
}

void Memory_Clear(double **Determinant, int Num)
{
    int row;

    for (row = 0; row < Num; row++)
        free(*(Determinant + row));
    free(Determinant);
}
