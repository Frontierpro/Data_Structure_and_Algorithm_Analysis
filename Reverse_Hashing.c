#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Hash_Function(int *Hash, int Num);
int Byte_Count(int Num);
int Top_Sort(int *Hash, int *Queue, int Num);
void Read_Map(int **map, int *front, int *Queue, int *Hash, int Num);
void Out_Put(int *Array, int Num, int Count);

int main(void)
{
    int Num, Count;
    int *Hash, *Queue;

    printf("Enter the capacity of the hash map (positive): ");
    scanf("%d", &Num);
    Hash = (int *)malloc(Num * sizeof(int));
    Queue = (int *)malloc(Num * sizeof(int));
    printf("The hashing function is position = x %% Num.\n");
    printf("With linear probing to deal with collisions.\n");
    Hash_Function(Hash, Num);
    Count = Byte_Count(Num);
    printf("The hashmap generated is as follows.\n");
    Out_Put(Hash, Num, Count + 1);

    Num = Top_Sort(Hash, Queue, Num);
    printf("The order of hashing elements is as follows.\n");
    Out_Put(Queue, Num, Count + 1);

    printf("Press ENTER to quit.\n");
    free(Hash);
    free(Queue);
    getchar();
    getchar();

    return 0;
}

void Hash_Function(int *Hash, int Num)
{
    int pos, temp, count, flag;

    for (pos = 0; pos < Num; pos++)
        *(Hash + pos) = -1;
    srand((int)time(NULL));
    for (count = 0; count < Num; count++) {
        flag = 0;
        temp = rand() % (3 * Num);
        pos = temp % Num;
        while (*(Hash + pos) != -1) {
            if (*(Hash + pos) == temp) {
                flag = 1;
                break;
            }
            pos++;
            pos %= Num;
        }
        if (flag)
            continue;
        *(Hash + pos) = temp;
    }
}

int Byte_Count(int Num)
{
    int count = 0;

    while (Num) {
        count++;
        Num /= 10;
    }

    return count;
}

int Top_Sort(int *Hash, int *Queue, int Num)
{
    int **map;
    int *front;
    int pos, row, col, top = 0;

    map = (int **)malloc(Num * sizeof(int *));
    for (pos = 0; pos < Num; pos++)
        *(map + pos) = (int *)malloc(Num * sizeof(int));
    front = (int *)malloc(Num * sizeof(int));
    Read_Map(map, front, Queue, Hash, Num);
    
    for (pos = 0; pos < Num; pos++) {
        if (*(front + pos))
            continue;
        if (*(Queue + top) == -1)
            *(Queue + top) = pos;
        else if (*(Hash + pos) < *(Hash + *(Queue + top)))
            *(Queue + top) = pos;
    }
    while (top < Num && *(front + *(Queue + top)) == 0) {
        *(front + *(Queue + top)) = -1;
        row = *(Queue + top);
        col = **(map + row);
        for (pos = 1; pos <= col; pos++)
            (*(front + *(*(map + row) + pos)))--;
        top++;
        for (pos = 0; pos < Num; pos++) {
            if (*(front + pos))
                continue;
            if (*(Queue + top) == -1)
                *(Queue + top) = pos;
            else if (*(Hash + pos) < *(Hash + *(Queue + top)))
                *(Queue + top) = pos;
        }
    }
    top = 0;
    while (top < Num && *(Queue + top) != -1) {
        *(Queue + top) = *(Hash + *(Queue + top));
        top++;
    }

    free(front);
    for (pos = 0; pos < Num; pos++)
        free(*(map + pos));
    free(map);

    return top;
}

void Read_Map(int **map, int *front, int *Queue, int *Hash, int Num)
{
    int pos, row, col, temp;

    for (pos = 0; pos < Num; pos++) {
        *(Queue + pos) = -1;
        if (*(Hash + pos) != -1) {
            **(map + pos) = 0;
            *(front + pos) = 0;
        }
        else {
            **(map + pos) = -1;
            *(front + pos) = -1;
        }
    }
    for (pos = 0; pos < Num; pos++) {
        if (*(Hash + pos) == -1)
            continue;
        row = *(Hash + pos) % Num;
        while (row != pos) {
            (*(front + pos))++;
            (**(map + row))++;
            col = **(map + row);
            *(*(map + row) + col) = pos;
            row++;
            row %= Num;
        }
    }
}

void Out_Put(int *Array, int Num, int Count)
{
    int pos;

    for (pos = 0; pos < Num; pos++)
        printf("%-*d", Count, *(Array + pos));
    putchar('\n');
}
