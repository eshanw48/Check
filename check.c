#include<stdio.h>
#include<stdlib.h>

struct Node{
char *data;
int type;
struct Node *next;
};

typedef enum {false,true} bool;  //false = 0, true = 1

int expressions = 0;
int expression = 1;
int logical = 0;
int arithmetic = 0;
int error = 0;

char* tok(char* string, const char* delim);
void InsertNode(struct Node *head, struct Node *variables);
void printLinkedList(struct Node *head);
void semicolon(struct Node *ptr);
void parse(struct Node *head);

int main(int argc, char** argv){

if(argc < 2){
		
	printf("too few arguments\n");
	return;
}
else if(argc > 2){
	printf("too many arguments\n");
	return;
}else if(argc == 2){
	char temp[2]= "";
	struct Node *ptr = malloc(sizeof(struct Node));
	char *p_str,*token;
	ptr->data = temp;
	int i = 0;

	/* Adding the tokens into a Linked List */
        for (i = 1, p_str = argv[1]; ; i++, p_str = NULL)
    {
	struct Node *node = malloc(sizeof(struct Node));
        token = tok(p_str, " " );
        if (token == NULL)
            break;
        node->data = token;
	node->next = NULL;
	InsertNode(ptr, node);

    }
	if(ptr->next != NULL) /* Make sure ptr->next does not access memory it does not have to avoid a segmentation fault */
{
	ptr = ptr->next;
}
	semicolon(ptr); /* calls the semicolon function to make a semicolon into its own token */

	parse(ptr);	/* parses through the tokens to check for errors */
}


return 0;
}

/* Tokenier function that splits a string into tokens */
char *tok(char* string,const char *delim)
{
    static char *ptr;
    const char *del;
    char *p;
    if(string != NULL)
    {
        ptr=string;
        p=string;
    }
    else
    {
        if(*ptr == '\0')
            return NULL;

        p=ptr;
    }

    while(*ptr != '\0')
    {
        del=delim;
        while(*del != '\0')
        {
            if(*ptr == *del)
            {
                if(ptr == p)
                {
                    p++;
                    ptr++;
                }
                else
                {
                    *ptr='\0';
                    ptr++;

                    return p;
                }
            }
            else
            {
                del++;
            }
        }
        ptr++;
    }
    return p;
}
/* Inserts a node into the Linked List */
void InsertNode(struct Node *head, struct Node *variables){
	struct Node *ptr = malloc(sizeof(struct Node*));
	for(ptr = head; ptr->next != NULL; ptr = ptr->next){
	;
	}
	ptr->next = variables;
	return;
}
/* Prints the Linked List */
void printLinkedList(struct Node *head){
	struct Node *current_node = head;
   	while ( current_node != NULL) {
        printf("%s\n", current_node->data);
        current_node = current_node->next;
    }	
}
/* Splits the semiclon from the expression into its own seperate token */
void semicolon(struct Node *ptr){
struct Node *tempptr = ptr;
while(tempptr != NULL){
  char *tokendata = tempptr->data;

int i = 0;
while(tokendata[i] !='\0'){
  if(tokendata[i] == ';'){
    tokendata[i] = '\0';
	
    expression++;
	
    struct Node *temp = malloc(sizeof(struct Node));

    temp->data = ";";

    temp->next = tempptr->next;

    tempptr->next=temp; 

    if(tempptr->next != NULL){ 
      tempptr=tempptr->next;
    }

  }

  i++;
}
tempptr=tempptr->next;
}

}
/* Checks for errors */
void parse(struct Node *head)
{
	struct Node *currentNode = head;
	struct Node *prev = malloc(sizeof(struct Node*));	

	prev->data = ";"; 
	prev->next = head;
	prev->type = 3;

	char* prevdata;
	char* tokdata;
	 	
	while(currentNode != NULL)  
	
{	
	char* tokdata = currentNode->data; 
	char* prevdata = prev->data;

	int operand = false;
        int operator = false;	
	int prevOperand = false;
	int prevOperator = false;


	if(tokdata[0] == '\0')
{
        printf("Error: Scan error in expression");
	printf(" 0: incomplete expression\n");
        printf("\"\"\n");
	error = 1;
	break;
}       

	if(tokdata[0] == ';')
{
	expressions++;
}


	currentNode->type = 0;
	prev->type = 0;
	
	// 1 IS ARITHMETIC OPERATOR
	// 2 IS LOGICAL OPERATOR
	// 3 IS SEMICOLON
	// 4 IS ARITHMETIC OPERAND
	// 5 IS LOGICAL OPERAND 


	if(tokdata[0] == '+' || tokdata[0] == '-' || tokdata[0] == '/' || tokdata[0] == '*')
{
        arithmetic++;
        operator = true;
	currentNode->type = 1;
}

        if(tokdata[0] == 'A' && tokdata[1] == 'N' && tokdata[2] == 'D' || tokdata[0] == 'N' && tokdata[1] == 'O' && tokdata[2] == 'T' || tokdata[0] == 'O' && tokdata[1] == 'R')
{

        logical++;
        operator = true;
	currentNode->type = 2;
}

	if(tokdata[0] == ';')
{
	currentNode->type = 3;
}

	if((tokdata[0] == '0' || tokdata[0] == '1' || tokdata[0] == '2' || tokdata[0] == '3' || tokdata[0] == '4' || tokdata[0] == '5' || tokdata[0] == '6' || tokdata[0] == '7' || tokdata[0] == '8' ||
        tokdata[0] == '9'))
{
	currentNode->type = 4;
}
	
	if(tokdata[0] == 't' && tokdata[1] == 'r' && tokdata[2] == 'u' && tokdata[3] == 'e' || tokdata[0] == 'f' && tokdata[1] == 'a' && tokdata[2] == 'l' && tokdata[3] == 's' && tokdata[4] == 'e')
{
	currentNode->type = 5;
}


	if(prevdata[0] == '+' || prevdata[0] == '-' || prevdata[0] == '/' || prevdata[0] == '*')
{
	prev->type = 1;
}

	
	if(prevdata[0] == 'A' && prevdata[1] == 'N' && prevdata[2] == 'D' || prevdata[0] == 'N' && prevdata[1] == 'O' && prevdata[2] == 'T' || prevdata[0] == 'O' && prevdata[1] == 'R')
{
	prev->type = 2;
}

	if(prevdata[0] == ';')
{
	prev->type = 3;
}

	if((prevdata[0] == '0' || prevdata[0] == '1' || prevdata[0] == '2' || prevdata[0] == '3' || prevdata[0] == '4' || prevdata[0] == '5' || prevdata[0] == '6' || prevdata[0] == '7' || prevdata[0] == '8' || prevdata[0] == '9'))
{
	prev->type = 4;
}

	if(prevdata[0] == 't' && prevdata[1] == 'r' && prevdata[2] == 'u' && prevdata[3] == 'e' || prevdata[0] == 'f' && prevdata[1] == 'a' && prevdata[2] == 'l' && prevdata[3] == 's' && prevdata[4] == 'e')
{
	prev->type = 5;
}

	if(currentNode->type == 0 && (prev->type == 4 || prev->type == 5)) //unknown operator
{
	printf("Error: Parse error in expression ");
	printf("%d", expressions);
	printf(": Unknown Operator in:");
	printf("\n%s", tokdata);
	printf("\n"); 
	error = 1;
}

	if(currentNode->type == 0 && (prev->type == 1 || prev->type == 2)) //unknown operand
{
	printf("Error: Parse error in expression ");
        printf("%d", expressions);
        printf(": Unknown Operand in:");
        printf("\n%s", tokdata);
        printf("\n");
	error = 1;
}


	if((currentNode->type == 1 || currentNode->type == 2) && (prev->type == 1 || prev->type == 2 || prev->type == 0))
{
	printf("Error: Parse error in expression ");
        printf("%d", expressions);
        printf(": Unexpected Operator in:");
        printf("\n%s", tokdata);
        printf("\n");
        error = 1;
}

	if(currentNode->type == 3 && prev->type != 3)
{
	printf("Error: Scan error in expression ");
        printf("%d", expressions);
        printf(": Expression incomplete in:");
        printf("\n%s", tokdata);
        printf("\n");
        error = 1;

}

	if((currentNode->type == 3) && prev->type == 3)
{
	printf("Error: Scan error in expression ");
        printf("%d", expressions);
        printf(": Expression incomplete in:");
        printf("\n%s", tokdata);
        printf("\n");
        error = 1;
}

	if((currentNode->type == 4 || currentNode->type == 5) && (prev->type == 4 || prev->type == 5 || prev->type == 0)) 
{
	printf("Error: Parse error in expression ");
        printf("%d", expressions);
        printf(": Unexpected Operand in:");
        printf("\n%s", tokdata);
        printf("\n");
        error = 1;
}


	if(currentNode->type == 0 && (prev->type == 0 || prev->type == 3) )
{
	printf("Error: Parse error in expression ");
        printf("%d", expressions);
        printf(": Unknown Identifier in:");
        printf("\n%s", tokdata);
        printf("\n");
        error = 1;

}

//Below are mismatch cases

	if(currentNode->type == 2 && prev->type == 4)
{
	printf("Error: Parse error in expression ");
        printf("%d", expressions);
        printf(": Operand Type Mismatch in:");
        printf("\n%s", tokdata);
        printf("\n");
        error = 1;

}

	if(currentNode->type == 4 && prev->type == 2)
{
	printf("Error: Parse error in expression ");
        printf("%d", expressions);
        printf(": Operator Type Mismatch in:");
        printf("\n%s", tokdata);
        printf("\n");
        error = 1;
}

	if(currentNode->type == 1 && prev->type == 5)
{
	printf("Error: Parse error in expression ");
        printf("%d", expressions);
        printf(": Operand Type Mismatch in:");
        printf("\n%s", tokdata);
        printf("\n");
        error = 1;
}

	if(currentNode->type == 5 && prev->type == 1)
{
	printf("Error: Parse error in expression ");
        printf("%d", expressions);
        printf(": Operator Type Mismatch in:");
        printf("\n%s", tokdata);
        printf("\n");
        error = 1;
}

currentNode = currentNode->next;
prev = prev->next;

}

	if(error == 0)
{
	printf("Found %d ", expression);
        printf("expressions: %d ", logical);
        printf("logical and %d ", arithmetic);
        printf("arithmetic. \n");
        printf("OK.\n");
}
else
{

 	printf("Found %d ", expression);
        printf("expressions: %d ", logical);
        printf("logical and %d ", arithmetic);
        printf("arithmetic. \n");
}
}
