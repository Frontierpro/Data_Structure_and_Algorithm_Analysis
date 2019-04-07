#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum color {red, black};

typedef struct Node *parent;
typedef struct Node *child;
struct Node {
    int Value;
    int Empty;
    int Color;
    parent Top;
    child Left;
    child Right;  
};
typedef struct Node *leaf;

leaf Root_Initial(void);
leaf Element_Insert(leaf Root, int Num);
leaf Element_Delete(leaf Root, int Num);
leaf Insert_Adjust(leaf Root, leaf temp);
leaf Delete_Adjust(leaf Root, leaf temp);
leaf BR_Rotation(leaf Root, leaf temp);
leaf BB_Rotation(leaf Root, leaf temp);
leaf Find_Min(leaf Root);
leaf Swap_Color(leaf Root);
leaf Left_Rotation(leaf Root);
leaf Right_Rotation(leaf Root);
leaf Swap_Rotation(leaf Root, leaf top, leaf temp);
void Levelorder_Traversal(leaf Root);
void Memory_Clear(leaf Root);

int main(void) {
    leaf Root;
    int Num;
    char *Command;
    
    Root = Root_Initial();
    Command = (char *)malloc(10 * sizeof(char));
    printf("Enter \"insert\", \"delete\", \"query\" or \"quit\" command!\n");
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
        else if (strcmp(Command, "query") == 0) {
            if (!Root->Empty) {
                printf("The binary_search_tree is as follows.\n");
                Levelorder_Traversal(Root);
            }
            else
                printf("The binary_search_tree is empty!\n");
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

leaf Root_Initial(void)
{
    leaf Root = (struct Node *)malloc(sizeof(struct Node));
    
    Root->Empty = 1;
    Root->Top = Root->Left = Root->Right = NULL;
    Root->Color = black;
    
    return Root;
}

leaf Element_Insert(leaf Root, int Num)
{
    leaf temp = Root;
    
    while (!temp->Empty) {
        if (Num < temp->Value)
            temp = temp->Left;
        else if (Num > temp->Value)
            temp = temp->Right;
        else {
            printf("This element has been in the binary_search_tree!\n");
            return Root;
        }
    }
    if (temp != Root)
        temp->Color = red;
    temp->Empty = 0;
    temp->Value = Num;
    temp->Left = (struct Node *)malloc(sizeof(struct Node));
    temp->Right = (struct Node *)malloc(sizeof(struct Node));
    temp->Left->Left = temp->Left->Right = temp->Right->Left = temp->Right->Right = NULL;
    temp->Left->Color = temp->Right->Color = black;
    temp->Left->Top = temp->Right->Top = temp;
    temp->Left->Empty = temp->Right->Empty = 1;

    return Insert_Adjust(Root, temp);
}

leaf Insert_Adjust(leaf Root, leaf temp)
{
    leaf top;
    
    while (temp->Top && temp->Top->Color == red) {
        top = temp->Top->Top;
        if (top->Left == temp->Top) {
            if (top->Right->Color == red)
                temp = Swap_Color(top);
            else if (temp->Top->Right == temp) {
                top->Left = Right_Rotation(top->Left);
                top->Left->Top = top;
                temp = top->Left->Left;
            }
            else
                return Swap_Rotation(Root, top, temp);
        }
        else {
            if (top->Left->Color == red)
                temp = Swap_Color(top);
            else if (temp->Top->Left == temp) {
                top->Right = Left_Rotation(top->Right);
                top->Right->Top = top;
                temp = top->Right->Right;
            }
            else
                return Swap_Rotation(Root, top, temp);
        }
    }
    Root->Color = black;
    
    return Root;
}

leaf Element_Delete(leaf Root, int Num)
{
    leaf temp = Root, min;
    int color;

    while (!temp->Empty) {
        if (Num < temp->Value)
            temp = temp->Left;
        else if (Num > temp->Value)
            temp = temp->Right;
        else {
            if (temp->Left->Empty == 0 && temp->Right->Empty == 0) {
                min = Find_Min(temp->Right);
                temp->Value = min->Value;
                Num = temp->Value;
                temp = min;
                continue;
            }
            else if (temp->Left->Empty == 0) {
                temp->Left->Top = temp->Top;
                if (temp->Top) {
                    if (temp->Top->Left == temp)
                        temp->Top->Left = temp->Left;
                    else
                        temp->Top->Right = temp->Left;
                }
                else
                    Root = temp->Left;
                min = temp;
                color = temp->Color;
                temp = temp->Left;
                free(min->Right);
                free(min);
            }
            else {
                temp->Right->Top = temp->Top;
                if (temp->Top) {
                    if (temp->Top->Left == temp)
                        temp->Top->Left = temp->Right;
                    else
                        temp->Top->Right = temp->Right;
                }
                else
                    Root = temp->Right;
                min = temp;
                color = temp->Color;
                temp = temp->Right;
                free(min->Left);
                free(min);
            }
            Root->Color = black;
            if (color == black)
                return Delete_Adjust(Root, temp);
            return Root;
        }
    }
    printf("There is no such element in the binary_search_tree!\n");

    return Root;
}

leaf Delete_Adjust(leaf Root, leaf temp)
{
	while (temp->Top && temp->Color == black) {
	    if (temp->Top->Left == temp) {
	        if (temp->Top->Right->Color == red)
	            Root = BR_Rotation(Root, temp);
	        else if (temp->Top->Right->Right->Color == red)
	            return BB_Rotation(Root, temp);
	        else if (temp->Top->Right->Left->Color == red) {
	            temp->Top->Right->Color = red;
	            temp->Top->Right->Left->Color = black;
	            temp->Top->Right = Left_Rotation(temp->Top->Right);
	            temp->Top->Right->Top = temp->Top;
	        }
	        else {
	            temp->Top->Right->Color = red;
	            temp = temp->Top;
	        }
	    }
	    else {
	        if (temp->Top->Left->Color == red)
	            Root = BR_Rotation(Root, temp);
	        else if (temp->Top->Left->Left->Color == red)
	            return BB_Rotation(Root, temp);
	        else if (temp->Top->Left->Right->Color == red) {
	            temp->Top->Left->Color = red;
	            temp->Top->Left->Right->Color = black;
	            temp->Top->Left = Right_Rotation(temp->Top->Left);
	            temp->Top->Left->Top = temp->Top;
	        }
	        else {
	            temp->Top->Left->Color = red;
	            temp = temp->Top;
	        }
	    }
	}
    if (temp->Top)
        temp->Color = black;
	
	return Root;
}

leaf BR_Rotation(leaf Root, leaf temp)
{
    leaf top = temp->Top->Top;
    
    temp->Top->Color = red;
    if (temp->Top->Left == temp) {
        temp->Top->Right->Color = black;
        temp = Right_Rotation(temp->Top);
    }
    else {
        temp->Top->Left->Color = black;
        temp = Left_Rotation(temp->Top);
    }
    temp->Top = top;
    if (top) {
        if (top->Value > temp->Value)
            top->Left = temp;
        else
            top->Right = temp;
        return Root;
    }
    
    return temp;
}

leaf BB_Rotation(leaf Root, leaf temp)
{
    leaf top = temp->Top->Top;
    
    if (temp->Top->Left == temp) {
        temp->Top->Right->Color = temp->Top->Color;
        temp->Top->Color = black;
        temp->Top->Right->Right->Color = black;
        temp = Right_Rotation(temp->Top);
    }
    else {
        temp->Top->Left->Color = temp->Top->Color;
        temp->Top->Color = black;
        temp->Top->Left->Left->Color = black;
        temp = Left_Rotation(temp->Top);
    }
    temp->Top = top;
    if (top) {
        if (top->Value > temp->Value)
            top->Left = temp;
        else
            top->Right = temp;
        return Root;
    }
    
    return temp;
}

leaf Find_Min(leaf Root)
{
    while (!Root->Left->Empty)
        Root = Root->Left;
    
    return Root;
}

leaf Swap_Color(leaf Root)
{
    Root->Left->Color = Root->Right->Color = black;
    Root->Color = red;
    
    return Root;
}

leaf Left_Rotation(leaf Root)
{
    leaf temp = Root->Left;
    Root->Left = temp->Right;
    temp->Right->Top = Root;
    temp->Right = Root;
    Root->Top = temp;
    
    return temp;
}

leaf Right_Rotation(leaf Root)
{
    leaf temp = Root->Right;
    Root->Right = temp->Left;
    temp->Left->Top = Root;
    temp->Left = Root;
    Root->Top = temp;
    
    return temp;
}

leaf Swap_Rotation(leaf Root, leaf top, leaf temp)
{
    top->Color = red;
    temp = temp->Top;
    temp->Color = black;
    top = top->Top;
    if (temp->Top->Left == temp)
        temp = Left_Rotation(temp->Top);
    else
        temp = Right_Rotation(temp->Top);
    temp->Top = top;
    if (top) {
        if (temp->Value < top->Value)
            top->Left = temp;
        else
            top->Right = temp;
        return Root;
    }
    
    return temp;
}

void Levelorder_Traversal(leaf Root)
{
    int front = 0, rear = 0;
    leaf temp = Root;
    leaf *queue;
    
    queue = (leaf *)malloc(100 * sizeof(leaf));
    *(queue + rear++) = temp;
    while (front < rear) {
        printf("%-10d", temp->Value);
        if (!temp->Left->Empty) {
            printf("%10d->%-10d", temp->Value, temp->Left->Value);
            *(queue + rear++) = temp->Left;
        }
        else
            printf("%10d->NULL      ", temp->Value);
        if (!temp->Right->Empty) {
            printf("%10d->%-10d", temp->Value, temp->Right->Value);
            *(queue + rear++) = temp->Right;
        }
        else
            printf("%10d->NULL      ", temp->Value);
        if (temp->Color == red)
            puts("          red");
        else
            puts("          black");
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
