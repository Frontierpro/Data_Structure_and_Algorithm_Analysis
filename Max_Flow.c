#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Infinity 1e5

struct Node {
    int Start;
    bool Flag;
};
typedef struct Node path;

int **Map_Create(int Num);
int Num_Count(int Num);
int **Read_Map(int **Map, int Num, int Count);
void Max_Flow(int **Map, int Num, int Head, int Tail);
int Find_Path(int **Map, int Num, path *queue, int *stack, int top, int Tail);
void Map_Renew(int **Map, int Num, int *stack, int top);
int Flow_Calculate(int **Map, int **Graph, int Num, int Head);
void Out_Put(int **Map, int **Graph, int Num, int Head, int Count);
void Memory_Clear(int **Matrix, int Num);

int main(void)
{
    int Num, Head, Tail, Flow, Count;
    int **Map, **Graph;

    printf("Enter the number (positive) of nodes in the graph: ");
    scanf("%d", &Num);
    Map = Map_Create(Num);
    Count = Num_Count(Num);
    printf("The random_created map is as follows.\n");
    Graph = Read_Map(Map, Num, Count);

    printf("Enter the source node and destination node: ");
    scanf("%d %d", &Head, &Tail);
    Max_Flow(Map, Num, Head, Tail);
    Flow = Flow_Calculate(Map, Graph, Num, Head);
    if (Flow) {
        printf("The distribution of the flow is as follows.\n");
        Out_Put(Map, Graph, Num, Head, Count);
        printf("And the max_flow from %d to %d is %d.\n", Head, Tail, Flow);
    }
    else
        printf("The max_flow from %d to %d is %d.\n", Head, Tail, Flow);

    printf("Press ENTER to quit.\n");
    Memory_Clear(Map, Num);
    Memory_Clear(Graph, Num);
    getchar();
    getchar();

    return 0;
}

int **Map_Create(int Num)
{
    int row, col;
    int **map;

    map = (int **)malloc(Num * sizeof(int *));
    for (row = 0; row < Num; row++)
        *(map + row) = (int *)malloc(Num * sizeof(int));
    for (row = 0; row < Num; row++)
        for (col = 0; col < Num; col++)
            *(*(map + row) + col) = 0;
    srand((int)time(NULL));
    for (row = 0; row < Num; row++) {
        for (col = 0; col < row; col++) {
            if (*(*(map + col) + row))
                continue;
            *(*(map + row) + col) = rand() % (Num / 3 + 2);
            if (*(*(map + row) + col))
                *(*(map + row) + col) = 0;
            else
                *(*(map + row) + col) = rand() % 99 + 1;
        }
        col++;
        while (col < Num) {
            *(*(map + row) + col) = rand() % (Num / 3 + 2);
            if (*(*(map + row) + col))
                *(*(map + row) + col) = 0;
            else
                *(*(map + row) + col) = rand() % 99 + 1;
            col++;
        }
    }

    return map;
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

int **Read_Map(int **Map, int Num, int Count)
{
    int row, col;
    int **graph;

    graph = (int **)malloc(Num * sizeof(int *));
    for (row = 0; row < Num; row++)
        *(graph + row) = (int *)malloc(Num * sizeof(int));
    for (row = 0; row < Num; row++)
        for (col = 0; col < Num; col++) {
            *(*(graph + row) + col) = * (*(Map + row) + col);
            if (*(*(Map + row) + col))
                printf("%*d->%-*d:%2d; ", Count, row, Count, col, *(*(Map + row) + col));
        }
    putchar('\n');

    return graph;
}

void Max_Flow(int **Map, int Num, int Head, int Tail)
{
    path *queue;
    int *stack, top, pos, min, row, col;

    stack = (int *)malloc(Num * sizeof(int));
    queue = (struct Node *)malloc(Num * sizeof(struct Node));
    while (true) {
        for (top = 0; top < Num; top++) {
            (*(queue + top)).Start = 0;
            (*(queue + top)).Flag = false;
        }
        *stack = Head;
        (*(queue + Head)).Flag = true;
        top = Find_Path(Map, Num, queue, stack, 1, Tail);
        if (top)
            Map_Renew(Map, Num, stack, top);
        else
            break;
    }
    free(stack);
}

int Find_Path(int **Map, int Num, path *queue, int *stack, int top, int Tail)
{
    int row = *(stack + top - 1), col = (*(queue + row)).Start;

    while (col < Num) {
        if (*(*(Map + row) + col) > 0 && (*(queue + col)).Flag == false)
            break;
        col++;
    }
    if (col == Num) {
        top--;
        (*(queue + row)).Flag = false;
        if (top == 0)
            return top;
    }
    else {
        *(stack + top++) = col;
        (*(queue + col)).Flag = true;
        (*(queue + row)).Start = col + 1;
        if (col == Tail) 
            return top;
    }
    top = Find_Path(Map, Num, queue, stack, top, Tail);

    return top;
}

void Map_Renew(int **Map, int Num, int *stack, int top)
{
    int pos, row, col, min = Infinity;

    for (pos = 0; pos < top - 1; pos++) {
        row = *(stack + pos);
        col = *(stack + pos + 1);
        if (min > *(*(Map + row) + col))
            min = *(*(Map + row) + col);
    }
    for (pos = 0; pos < top - 1; pos++) {
        row = *(stack + pos);
        col = *(stack + pos + 1);
        *(*(Map + row) + col) -= min;
        *(*(Map + col) + row) += min;
    }
}

int Flow_Calculate(int **Map, int **Graph, int Num, int Head)
{
    int sum = 0, col;

    for (col = 0; col < Num; col++)
        if (*(*(Graph + Head) + col))
            sum += *(*(Graph + Head) + col) - *(*(Map + Head) + col);

    return sum;
}

void Out_Put(int **Map, int **Graph, int Num, int Head, int Count)
{
    int row, col;

    for (row = 0; row < Num; row++)
        for (col = 0; col < Num; col++)
            if (*(*(Graph + row) + col) && *(*(Graph + row) + col) - *(*(Map + row) + col))
                printf("%*d->%-*d:%2d; ", Count, row, Count, col, *(*(Graph + row) + col) - * (*(Map + row) + col));
    putchar('\n');
}

void Memory_Clear(int **Matrix, int Num)
{
    int row;

    for (row = 0; row < Num; row++)
        free(*(Matrix + row));
    free(Matrix);
}
