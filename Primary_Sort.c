#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Random_Initial(int *List, int Num);
int Num_Count(int Num);
void Array_Copy(int *List, int *Sort, int Num);
void Selection_Sort(int *Sort, int Num);
void Bubble_Sort(int *Sort, int Num);
void Insertion_Sort(int *Sort, int Num);
void Shell_Sort(int *Sort, int Num);
void Out_Put(int *Array, int Num, int Count);

int main(void)
{
    int Num, Count;
    int *List, *Sort;

    printf("Enter the length (positive) of the sorting list: ");
    scanf("%d", &Num);
    List = (int *)malloc(Num * sizeof(int));
    Sort = (int *)malloc(Num * sizeof(int));
    printf("The random_initial list is as follows.\n");
    Random_Initial(List, Num);
    Count = Num_Count(Num);
    Out_Put(List, Num, Count + 1);

    Array_Copy(List, Sort, Num);
    Selection_Sort(Sort, Num);
    printf("The sorting result solved by selection_sort is as follows.\n");
    Out_Put(Sort, Num, Count + 1);
    Array_Copy(List, Sort, Num);
    Bubble_Sort(Sort, Num);
    printf("The sorting result solved by bumble_sort is as follows.\n");
    Out_Put(Sort, Num, Count + 1);
    Array_Copy(List, Sort, Num);
    Insertion_Sort(Sort, Num);
    printf("The sorting result solved by insertion_sort is as follows.\n");
    Out_Put(Sort, Num, Count + 1);
    Array_Copy(List, Sort, Num);
    Shell_Sort(Sort, Num);
    printf("The sorting result solved by shell_sort is as follows.\n");
    Out_Put(Sort, Num, Count + 1);

    printf("Press ENTER to quit.\n");
    free(List);
    free(Sort);
    getchar();
    getchar();

    return 0;
}

void Random_Initial(int *List, int Num)
{
    int pos, left, right, temp;

    for (pos = 0; pos < Num; pos++)
        *(List + pos) = pos;
    srand((int)time(NULL));
    for (left = 0; left < Num; left++) {
        right = rand() % (Num - left) + left;
        temp = *(List + left);
        *(List + left) = *(List + right);
        *(List + right) = temp;
    }
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

void Array_Copy(int *List, int *Sort, int Num)
{
    int pos;
    
    for (pos = 0; pos < Num; pos++)
        *(Sort + pos) = *(List + pos);
}

void Selection_Sort(int *Sort, int Num)
{
    int left, right, temp;

    for (left = 0; left < Num; left++)
        for (right = left + 1; right < Num; right++)
            if (*(Sort + left) > *(Sort + right)) {
                temp = *(Sort + left);
                *(Sort + left) = *(Sort + right);
                *(Sort + right) = temp;
            }
}

void Bubble_Sort(int *Sort, int Num)
{
    int left, right, temp;

    for (right = Num - 1; right > 0; right--)
        for (left = 0; left < right; left++)
            if (*(Sort + left) > *(Sort + left + 1)) {
                temp = *(Sort + left);
                *(Sort + left) = *(Sort + left + 1);
                *(Sort + left + 1) = temp;
            }
}

void Insertion_Sort(int *Sort, int Num)
{
    int left, right, temp;

    for (right = 1; right < Num; right++) {
        temp = *(Sort + right);
        left = right - 1;
        while (left >= 0 && *(Sort + left) > temp) {
            *(Sort + left + 1) = *(Sort + left);
            left--;
        }
        *(Sort + left + 1) = temp;
    }
}

void Shell_Sort(int *Sort, int Num)
{
    int left, right, temp, part = Num / 2;

    while (part) {
        for (right = part; right < Num; right += part) {
            temp = *(Sort + right);
            left = right - part;
            while (left >= 0 && *(Sort + left) > temp) {
                *(Sort + left + part) = *(Sort + left);
                left -= part;
            }
            *(Sort + left + part) = temp;
        }
        part /= 2;
    }
}

void Out_Put(int *Array, int Num, int Count)
{
    int pos;

    for (pos = 0; pos < Num; pos++)
        printf("%-*d", Count, *(Array + pos));
    putchar('\n');
}
