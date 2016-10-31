#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ECE 1125 Fall 2015 - Lab 2 */
/* Quick and dirty reverse polish notation calculator.
 *
 * by Your name here.
 */

#include <math.h>

#define MAX 1024

int parse_number(const char *tok, double *p_d)
{
	char *endptr;
	double d = strtod(tok, &endptr);
	if (*endptr == '\0') {
		*p_d = d;
		return 0;
	}

	return -1;
}

/* Define struct dc_stack with its members with enough space for at
 * least 1024 elements.
 */

struct dc_stack {
	/* Fill in structure members here. */
	int top;
	double A[MAX];
};

/* Initialize the stack to empty. */
void stack_initialize(struct dc_stack *st)
{
	/* Fill in code here. */
	st->top = -1;
}

/* Return the number of items on the stack. */
int stack_count(const struct dc_stack *st)
{
	/* Fill in working code here.
	 * The return 2 is bogus.
	 */
	return (st->top+1);
}

/* Push an item onto the stack.
 * Return 0 if success and -1 if failure.
 */
int push(struct dc_stack *s, double t)
{
	/* Fill in code here. */
	if (s->top == MAX-1) {
		return -1;
	}
	s->A[s->top+1] = t;
	s->top++;
	return 0;
}

/* Pop an item from the top the stack.
 * Return 0 if success and -1 if failure.
 */
int pop(struct dc_stack *s, double *t)
{
	/* Fill in code here. */
	if (s->top >= 0) {
		*t = s->A[s->top];
		s->top--;
		return 0;
	}
	return -1;
}

/* parse_op() tells the caller whether the string tok is a valid
 * operation, and puts the single character operator into op.
 * Remember, the valid operations are:
 * 'p', 'f', 'c', '+', '-', '*', '/', '%', '^'
 * Return 0 if it is and -1 if it is not.
 */ 
int parse_op(const char *tok, char *op)
{
	//int rc = -1; unused variable

	if (tok == NULL)
		return -1;

	/* Make sure the token length is exactly 1. */
	if (strlen(tok) != 1)
		return -1;

	/* Fill in the rest of the code below. 
	 * Better still, use a switch statement.
	 */
	if (tok[0] == 'p' || tok[0] == 'f' || tok[0] == 'c' || tok[0] == '+' || tok[0] == '-' || tok[0] == '*' || tok[0] == '/' || tok[0] == '%' || tok[0] == '^') {
		*op = tok[0];
		return 0;
	}

	return -1;
}

/* Execute a single character operator.
 */
int apply_op(struct dc_stack *s, const char op)
{
	double A;

	switch (op) {
	case 'p':
	{
		/* Print the value of the top element (but leave it on
		 * the top of the stack.
		 */
		if (pop(s, &A) < 0) {
			printf("dc: stack empty\n");
			return -1;
		}
		else {
			printf("%f\n", A);
			push(s, A);
			return 0;
		}
	}
	case 'f':
	{
		/* Print the value of every element on the stack (but
		 * leave them all in the stack).
		 */

		/* Fill in code here. */
		int i;
		for (i=s->top; i >= 0; i--) {
			printf( " %f\n", s->A[i] );
		}
	}

	case 'c':
	{
		/* Clear the stack by removing every element. */
		stack_initialize(s);
		return 0;
	}

	} /* end switch */

	/* Apply two-operand operators from this point down. */

	/* First check if there are fewer than 2 elements on the
	 * stack. 
	 */
	if (stack_count(s) < 2) {
		printf("dc: stack empty\n");
		return -1;
	}

	/* Pop the operands, perform the computation indicated by
	 * op, and push the result.
	 */

	/* Fill in code here. */
	double tmp1, tmp2, tmp3;
	
	switch (op) {
	case '+':
	{
		pop(s, &tmp1);
		pop(s, &tmp2);
		
		push(s, tmp1 + tmp2);
		return 0;
	}
	
	case '-':
	{
		pop(s, &tmp1);
		pop(s, &tmp2);
		
		push(s, tmp2 - tmp1);
		return 0;
	}
	
	case '*':
	{
		pop(s, &tmp1);
		pop(s, &tmp2);
		
		push(s, tmp1 * tmp2);
		return 0;
	}
	
	case '/':
	{
		pop(s, &tmp1);
		pop(s, &tmp2);
		
		push(s, tmp2 / tmp1);
		return 0;
	}
	
	case '%':
	{
		pop(s, &tmp1);
		pop(s, &tmp2);
		tmp3 = (int) tmp2 % (int) tmp1;
		push(s, (double) tmp3);
		return 0;
	}
	
	case '^':
	{
		pop(s, &tmp1);
		pop(s, &tmp2);
		tmp3 = pow(tmp2, tmp1);
		push(s, tmp3);
		return 0;
	}
	
	} /* end switch */
	return -1;
}


int dcc(FILE *fp)
{
	char buf[256], *tok;
	char op;
	double dd;

	struct dc_stack stack;

	stack_initialize(&stack);

	for (;;) {
		/* Read a line from the input file into buf. */
		if (fgets(buf, sizeof(buf), fp) == NULL)
			break;

		/* Get all the whitespace-delmited tokens from buf. */
		tok = strtok(buf, " \t\n");
		while (tok != NULL) {
			/* This printf may be uncommented for
			 * additional debug output. 
			 */
			//printf("token %s\n", tok);

			if (parse_op(tok, &op) == 0) {
				/* This printf may be uncommented for
				 * additional debug output. 
				 */
				//printf("parsed op %c\n", op);
				apply_op(&stack, op);
			}
			else if (parse_number(tok, &dd) == 0) {
				push(&stack, dd);
			}

			tok = strtok(NULL, " \t\n");
		}
	}

	if (feof(fp))
		return 0;

	return -1;
}


int main(int argc, char *argv[])
{
	int rc;
	FILE *fp;

	if (argc < 2) {
		fp = stdin;
	}
	else {printf("else\n");
		fp = fopen(argv[1], "rb");

		if (!fp) {
			perror("fopen");
			return 1;
		}
	}

	rc = dcc(fp);

	fclose(fp);

	if (rc < 0)
		return 1;

	return 0;
}
