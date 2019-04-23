#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *child;
struct Node {
    int Value;
    child Left;
    child Right;
};
typedef child leaf;

leaf Element_Insert(leaf Root, int Num);
leaf Delete_Min(leaf Root);
leaf Heap_Merge(leaf left, leaf right);
void Levelorder_Traversal(leaf Root);
void Memory_Clear(leaf Root);

int main(void)
{
    leaf Root = NULL;
    int Num;
    char *Command;

    Command = (char *)malloc(10 * sizeof(char));
    printf("Enter \"insert\", \"delete\", \"query\" or \"quit\" command!\n");
    printf("Enter command: ");
    scanf("%s", Command);
    while (strcmp(Command, "quit")) {
        if (strcmp(Command, "insert") == 0) {
            scanf("%d", &Num);
            Root = Element_Insert(Root, Num);
        }
        else if (strcmp(Command, "delete") == 0)
            Root = Delete_Min(Root);
        else if (strcmp(Command, "query") == 0) {
            if (Root) {
                printf("The binary_heap is as follows.\n");
                Levelorder_Traversal(Root);
            }
            else
                printf("The binary_heap is empty!\n");
        }
        else
            printf("Enter \"insert\", \"delete\", \"query\" or \"quit\" command!\n");
        printf("Enter command: ");
        scanf("%s", Command);
    }
    free(Command);
    Memory_Clear(Root);

    return 0;
}

leaf Element_Insert(leaf Root, int Num)
{
    leaf temp = (struct Node *)malloc(sizeof(struct Node));
    temp->Value = Num;
    temp->Left = temp->Right = NULL;
    return Heap_Merge(Root, temp);
}

leaf Delete_Min(leaf Root)
{
    if (Root == NULL) {
        printf("The binary_heap is empty!\n");
        return NULL;
    }
    leaf left = Root->Left;
    leaf right = Root->Right;
    free(Root);
    return Heap_Merge(left, right);
}

leaf Heap_Merge(leaf left, leaf right)
{
    leaf temp;

    if (left == NULL)
        return right;
    if (right == NULL)
        return left;
    if (left->Value > right->Value) {
        temp = right;
        right = left;
        left = temp;
    }
    temp = Heap_Merge(left->Right, right);
    left->Right = left->Left;
    left->Left = temp;

    return left;
}

void Levelorder_Traversal(leaf Root)
{
    int front = 0, rear = 0;
    leaf temp = Root;
    leaf *queue;

    queue = (leaf *)malloc(100 * sizeof(leaf));
    if (temp)
        *(queue + rear++) = temp;
    while (front < rear) {
        printf("%-10d", temp->Value);
        if (temp->Left) {
            printf("%10d->%-10d", temp->Value, temp->Left->Value);
            *(queue + rear++) = temp->Left;
        }
        else
            printf("%10d->NULL      ", temp->Value);
        if (temp->Right) {
            printf("%10d->%-10d", temp->Value, temp->Right->Value);
            *(queue + rear++) = temp->Right;
        }
        else
            printf("%10d->NULL      ", temp->Value);
        putchar('\n');
        front++;
        temp = *(queue + front);
    }
    free(queue);
}

void Memory_Clear(leaf Root)
{
    if (Root) {
        Memory_Clear(Root->Left);
        Memory_Clear(Root->Right);
        free(Root);
    }
}
