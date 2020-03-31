#include "TStiva.h"

void afisInt(void* a) {
	printf("%d", *(int*)a);
}

int cmpInt(void *a, void *b) {
	int x = *(int*)a ;
	int y = *(int*)b;
	if(x > y)
		return -1;
	else if( x == y)
		return 0;
	else
		return 1;

}

/* returneaza prioritatea simbolului */
int getPriority(char symbol) {

	switch (symbol) {
		case '/':
		case '*':
			return 2;

		case '+':
		case '-':
			return 1;

		default:
			return 0;
	}
}

/*
	returneaza stringul "<operand1> <op> <operand2>"
	ajuta la generarea unei forme infixate
 */
char *SmartConcatInfix(char *operand1, char *op, char *operand2) {
	char *result = (char *)calloc(strlen(operand1) +
					  	strlen(operand2) + strlen(op) + 4,
				      	sizeof(char));
	
	strcat(result, operand1);
	strcat(result, " ");
	strcat(result, op);
	strcat(result, " ");
	strcat(result, operand2);

	free(operand1);
	free(operand2);
	free(op);

	return result;
}

/*
	returneaza stringul "<equation> <op>"
	ajuta la generarea unei forme postfixate
 */
void SmartConcatPostfix(char *equation, char *op) {
	strcat(equation, op);
	strcat(equation, " ");
	free(op);
}

/* TODO EX 1 */


int main() {
	char postfix[30] = "a b * c d / + e f * g * - h -";
	char infix[30] = "a * b + c / d - e * f * g - h";
	char prefix[30] = "+ * a b - / c d - * * e f g h";

	/* Exemplu de apeluri functii pe stiva */
	TStiva s = InitS();
	int vec[5] = {2,3,1,5,4};
	int *x;

	for (int i = 0; i < 5; i++) {
		/* elementele puse pe stiva trebuie alocate pe heap */
		x = malloc(sizeof(int));
		*x = vec[i];
		Push(s, x);
	}

	AfisareS(s, afisInt);

	afisInt(Top(s));		// print 4
	printf(" TOP\n");
	afisInt(Pop(s));		// print 4
	printf(" POP\n");
	afisInt(Top(s));		// print 5 (noul varf)
	printf(" NEW TOP\n");
	AfisareS(s,afisInt);
	SortareS(s, cmpInt);	// merge doar daca a fost implementata
	AfisareS(s, afisInt);
	DistrS(s);
	printf("\n");
	/* apeluri functii conversie */
	TStiva operatori = InitS();

	char *eqPost = calloc(30,sizeof(char));
	if(!eqPost)
		return 1;
	char *token;
	token = strtok(postfix," ");
	char checkLetter;
	while(token)
	{
		checkLetter = token[0];
		if(checkLetter >= 'a' && checkLetter <= 'z'){
			char *letter = malloc(2);
			if(!letter){
				free(eqPost);
				return 1;
			}
			strcpy(letter,token);
			SmartConcatPostfix(eqPost,letter);
		}
		else 
		{
			char *op = malloc(2);
			strcpy(op,token);

			if(NrES(operatori) == 0)
				Push(operatori,op);
			else {	
				char *elemVarf = (char*)Top(operatori);
				if(getPriority(op[0]) > getPriority(elemVarf[0]))
					Push(operatori,op);
				else{
					while(getPriority(op[0]) <= getPriority(elemVarf[0])){
						Pop(operatori);
						SmartConcatPostfix(eqPost,elemVarf);	
						elemVarf = Top(operatori);
						if(!elemVarf)
							break;
							
					}
					Push(operatori,op);
					}
				}	
		}	
		token = strtok(NULL," ");
	}
	SmartConcatPostfix(eqPost,Pop(operatori));
	printf("%s",eqPost);
    return 1;
}