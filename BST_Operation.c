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
leaf Element_Delete(leaf Root, int Num);
void Levelorder_Traversal(leaf Root);
void Memory_Clear(leaf Root);

int main(void)
{
    leaf Root = NULL;
    int Num;
    char *Command;

    Command = (char *)malloc(10 * sizeof(char));
    printf("Enter \"insert\", \"delete\", \"dir\" or \"quit\" command!\n");
    printf("Enter command: ");
    scanf("%s", Command);
    while (strcmp(Command, "quit")) {
        if (strcmp(Command, "insert") == 0) {
            scanf("%d", &Num);
            Root = Element_Insert(Root, Num);
        }
        else if (strcmp(Command, "delete") == 0) {
            scanf("%d", &Num);
            Root = Element_Delete(Root, Num);
        }
        else if (strcmp(Command, "dir") == 0) {
            if (Root) {
                printf("The binary_search_tree is as follows.\n");
                Levelorder_Traversal(Root);
            }
            else
                printf("The binary_search_tree is empty!\n");
        }
        else
            printf("Enter \"insert\", \"delete\", \"dir\" or \"quit\" command!\n");
        printf("Enter command: ");
        scanf("%s", Command);
    }
    free(Command);
    Memory_Clear(Root);

    return 0;
}

leaf Element_Insert(leaf Root, int Num)
{
    if (Root == NULL) {
        Root = (struct Node *)malloc(sizeof(struct Node));
        Root->Value = Num;
        Root->Left = NULL;
        Root->Right = NULL;
    }
    else {
        if (Num < Root->Value)
            Root->Left = Element_Insert(Root->Left, Num);
        else if (Num > Root->Value)
            Root->Right = Element_Insert(Root->Right, Num);
        else
            printf("This element has been in the binary_search_tree!\n");
    }

    return Root;
}

leaf Element_Delete(leaf Root, int Num)
{
    leaf temp;

    if (Root == NULL)
        printf("There is no such element in the binary_search_tree!\n");
    else if (Num < Root->Value)
        Root->Left = Element_Delete(Root->Left, Num);
    else if (Num > Root->Value)
        Root->Right = Element_Delete(Root->Right, Num);
    else {
        if (Root->Left && Root->Right) {
            Root->Value = Root->Right->Value;
            Root->Right = Element_Delete(Root->Right, Root->Value);
        }
        else {
            temp = Root;
            if (Root->Left == NULL)
                Root = Root->Right;
            else if (Root->Right == NULL)
                Root = Root->Left;
            free(temp);
        }
    }

    return Root;
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
