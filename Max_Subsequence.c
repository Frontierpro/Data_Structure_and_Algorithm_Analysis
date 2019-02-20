#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Sequence_Create(int *Sequence, int Num);
void Out_Put(int *Sequence, int Num);
int Algorithm_One(int *Sequence, int *Index, int Num);
int Algorithm_Two(int *Sequence, int Num);
int Algorithm_Three(int *Sequence, int Num);
int Divide_Merge(int *Sequence, int Left, int Right);

int main(void)
{
    int Num, Sum;
    int *Sequence, *Index;

    printf("Enter the length (positive) of the sequence: ");
    scanf("%d", &Num);
    Sequence = (int *)malloc(Num * sizeof(int));
    Index = (int *)malloc(2 * sizeof(int));
    *Index = *(Index + 1) = -1;
    printf("The random_created sequence is as follows.\n");
    Sequence_Create(Sequence, Num);
    Out_Put(Sequence, Num);

    Sum = Algorithm_One(Sequence, Index, Num);
    if (*Index >= 0 && *(Index + 1) >= 0) {
        printf("The maximum subsequence is from position %d to position %d.\n", *Index + 1, *(Index + 1) + 1);
        printf("The value of the maximum subsequence solved by algorithm_three is %d.\n", Sum);
        Sum = Algorithm_Two(Sequence, Num);
        printf("The value of the maximum subsequence solved by algorithm_two is %d.\n", Sum);
        Sum = Algorithm_Three(Sequence, Num);
        printf("The value of the maximum subsequence solved by algorithm_one is %d.\n", Sum);
        Sum = Divide_Merge(Sequence, 0, Num - 1);
        printf("The value of the maximum subsequence solved by divide_merge is %d.\n", Sum);
    }
    else
        printf("All subsequences are nonpositive.\n");

    printf("Press ENTER to quit.\n");
    free(Sequence);
    free(Index);
    getchar();
    getchar();

    return 0;
}

void Sequence_Create(int *Sequence, int Num)
{
    int pos, temp;

    srand((int)time(NULL));
    for (pos = 0; pos < Num; pos++) {
        fab = rand() % 10;
        if (rand() % 2)
            *(Sequence + pos) = temp;
        else
            *(Sequence + pos) = -temp;
    }
}

void Out_Put(int *Sequence, int Num)
{
    int pos;

    for (pos = 0; pos < Num; pos++)
        printf("%3d", *(Sequence + pos));
    putchar('\n');
}

int Algorithm_One(int *Sequence, int *Index, int Num)
{
    int pos, temp = 0, sum = 0, left = 0;

    for (pos = 0; pos < Num; pos++) {
        temp += *(Sequence + pos);
        if (temp > sum) {
            *Index = left;
            *(Index + 1) = pos;
            sum = temp;
        }
        else if (temp < 0) {
            left = pos + 1;
            temp = 0;
        }
    }

    return sum;
}

int Algorithm_Two(int *Sequence, int Num)
{
    int left, right, temp, sum = 0;

    for (left = 0; left < Num; left++) {
        temp = 0;
        for (right = left; right < Num; right++) {
            temp += *(Sequence + right);
            if (temp > sum)
                sum = temp;
        }
    }

    return sum;
}

int Algorithm_Three(int *Sequence, int Num)
{
    int left, right, pos, temp, sum = 0;

    for (left = 0; left < Num; left++)
        for (right = left; right < Num; right++) {
            temp = 0;
            for (pos = left; pos <= right; pos++)
                temp += *(Sequence + pos);
            if (temp > sum)
                sum = temp;
        }

    return sum;
}

int Divide_Merge(int *Sequence, int Left, int Right)
{
    int pos, temp, middle, left_max, right_max, left_sum = 0, right_sum = 0;

    if (Right < 0)
        return 0;
    if (Left == Right) {
        if (*(Sequence + Left) < 0)
            return 0;
        return *(Sequence + Left);
    }
    middle = (Left + Right) / 2;
    left_max = Divide_Merge(Sequence, Left, middle);
    right_max = Divide_Merge(Sequence, middle + 1, Right);

    temp = 0;
    for (pos = middle; pos >= Left; pos--) {
        temp += *(Sequence + pos);
        if (temp > left_sum)
            left_sum = temp;
    }
    temp = 0;
    for (pos = middle + 1; pos <= Right; pos++) {
        temp += *(Sequence + pos);
        if (temp > right_sum)
            right_sum = temp;
    }

    if ((left_sum + right_sum) > left_max && (left_sum + right_sum) > right_max)
        return left_sum + right_sum;
    if (left_max > right_max)
        return left_max;
    return right_max;
}
