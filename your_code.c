#include "your_code.h"
#include <stdlib.h>
#include <stdio.h>


// Write the implementations of the functions that do the real work here

ASTNode* CreateNumNode(int num)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = NUM; 
        node->num = num;
        return node;
}


ASTNode* CreateIdentNode(char* name)
{


}

// Take a statement node and a statement list node and connect them together
// to form a bigger statement list node (add the statement to the statement list).
// Return a pointer to the bigger list that resulted from this linking
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList)
{

}


void AddDeclaration(char* name)
{


}

// Commented out in this assignment 
/*void GenerateILOC(ASTNode* node);
{

}*/

