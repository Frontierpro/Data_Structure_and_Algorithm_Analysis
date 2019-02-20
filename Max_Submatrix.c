#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **Matrix_Create(int Row, int Col);
void Out_Put(int **Matrix, int Row, int Col);
int Algorithm_One(int **Matrix, int Row, int Col, int *Index);
int Algorithm_Two(int **Matrix, int Row, int Col);
int Algorithm_Three(int **Matrix, int Row, int Col);
void Memory_Clear(int **Matrix, int Row);

int main(void)
{
    int Row, Col, Sum;
    int *Index;
    int **Matrix;

    printf("Enter the rows (positive) of the matrix: ");
    scanf("%d", &Row);
    printf("Enter the columns (positive) of the matrix: ");
    scanf("%d", &Col);
    Index = (int *)malloc(4 * sizeof(int));
    *Index = *(Index + 1) = *(Index + 2) = *(Index + 3) = -1;
    printf("The random_created matrix is as follows.\n");
    Matrix = Matrix_Create(Row, Col);
    Out_Put(Matrix, Row, Col);

    Sum = Algorithm_One(Matrix, Row, Col, Index);
    if (*Index >= 0 && *(Index + 1) >= 0 && *(Index + 2) >= 0 && *(Index + 2) >= 0) {
        printf("The maximum submatrix is from position (%d,%d) to (%d,%d).\n", *Index + 1, *(Index + 1) + 1, *(Index + 2) + 1, *(Index + 3) + 1);
        printf("The value of the maximum submatrix solved by algorithm_one is %d.\n", Sum);
        Sum = Algorithm_Two(Matrix, Row, Col);
        printf("The value of the maximum submatrix solved by algorithm_two is %d.\n", Sum);
        Sum = Algorithm_Three(Matrix, Row, Col);
        printf("The value of the maximum submatrix solved by algorithm_three is %d.\n", Sum);
    }
    else
        printf("All submatrixes are nonpositive.\n");

    printf("Press ENTER to quit.\n");
    Memory_Clear(Matrix, Row);
    free(Index);
    getchar();
    getchar();

    return 0;
}

int **Matrix_Create(int Row, int Col)
{
    int row, col, temp;
    int **matrix;

    matrix = (int **)malloc(Row * sizeof(int *));
    for (row = 0; row < Row; row++)
        *(matrix + row) = (int *)malloc(Col * sizeof(int));
    srand((int)time(NULL));
    for (row = 0; row < Row; row++)
        for (col = 0; col < Col; col++) {
            temp = rand() % 10;
            if (rand() % 2)
                *(*(matrix + row) + col) = temp;
            else
                *(*(matrix + row) + col) = -temp;
        }

    return matrix;
}

void Out_Put(int **Matrix, int Row, int Col)
{
    int row, col;

    for (row = 0; row < Row; row++) {
        for (col = 0; col < Col; col++)
            printf("%3d", *(*(Matrix + row) + col));
        putchar('\n');
    }
}

int Algorithm_One(int **Matrix, int Row, int Col, int *Index)
{
    int head, tail_row, tail_col, pos, temp, sum = 0, left = 0;
    int *prev;

    prev = (int *)malloc(Col * sizeof(int));
    for (head = 0; head < Row; head++) {
        for (pos = 0; pos < Col; pos++)
            *(prev + pos) = 0;
        for (tail_row = head; tail_row < Row; tail_row++) {
            left = temp = 0;
            for (tail_col = 0; tail_col < Col; tail_col++) {
                *(prev + tail_col) += *(*(Matrix + tail_row) + tail_col);
                temp += *(prev + tail_col);
                if (temp > sum) {
                    *Index = head;
                    *(Index + 1) = left;
                    *(Index + 2) = tail_row;
                    *(Index + 3) = tail_col;
                    sum = temp;
                }
                else if (temp < 0) {
                    left = tail_col + 1;
                    temp = 0;
                }
            }
        }
    }
    free(prev);

    return sum;
}

int Algorithm_Two(int **Matrix, int Row, int Col)
{
    int head_row, head_col, tail_row, tail_col, pos, temp, sum = 0;
    int *prev;

    prev = (int *)malloc(Col * sizeof(int));
    for (head_row = 0; head_row < Row; head_row++)
        for (head_col = 0; head_col < Col; head_col++) {
            for (pos = 0; pos < Col; pos++)
                *(prev + pos) = 0;
            for (tail_row = head_row; tail_row < Row; tail_row++) {
                temp = 0;
                for (tail_col = head_col; tail_col < Col; tail_col++) {
                    *(prev + tail_col) += *(*(Matrix + tail_row) + tail_col);
                    temp += *(prev + tail_col);
                    if (temp > sum)
                        sum = temp;
                }
            }
        }
    free(prev);

    return sum;
}

int Algorithm_Three(int **Matrix, int Row, int Col)
{
    int head_row, head_col, tail_row, tail_col, pos_row, pos_col, temp, sum = 0;

    for (head_row = 0; head_row < Row; head_row++)
        for (head_col = 0; head_col < Col; head_col++)
            for (tail_row = head_row; tail_row < Row; tail_row++)
                for (tail_col = head_col; tail_col < Col; tail_col++) {
                    temp = 0;
                    for (pos_row = head_row; pos_row <= tail_row; pos_row++)
                        for (pos_col = head_col; pos_col <= tail_col; pos_col++)
                            temp += *(*(Matrix + pos_row) + pos_col);
                    if (temp > sum)
                        sum = temp;
                }

    return sum;
}

void Memory_Clear(int **Matrix, int Row)
{
    int pos;

    for (pos = 0; pos < Row; pos++)
        free(*(Matrix + pos));
    free(Matrix);
}
