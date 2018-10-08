/********************************************************************************
* @File name: expressionEvaluation.c
* @Author: Zhong Yingjia
* @Version: 4.0
* @Date: 2018.8.10
* @Description: The functions of calculation.
********************************************************************************/

#include"sequentialStack.h" 
#define MAXPOS 100//The max error position of an expression
#define ERRMESLENGTH 200
#define infixLength 100

State IsLowerOrEqual(char TopElem, char Elem);
State err_preprocessor_infixExpression(char*infixExpression);
char ChangeElem(char elem);

/* This function turns a prefix expression stored in 'prefiExpression' into a postfix expression
   and stores it in 'postfixExpression'
   If everything is all right, RETURN SUCCEEDED; otherwise, RETURN FAILED
 */
State infixToPostfix(char *infixExpression, char postfixExpression[])
{
	char e;//Defines tmp for storing the current element and define e to store the top element of the stack
	char *ie;//Infix expression pointer
	char *pe;//Suffix expression pointer


	SequentialStackChar* s=(SequentialStackChar*)malloc(sizeof(SequentialStackChar));
	if(s==NULL)return FAILED;
	InitStack(s);
	
	if (err_preprocessor_infixExpression(infixExpression) == FAILED) {
		DestroyStack(s);
		return FAILED;
	}

	for (ie = infixExpression,pe = postfixExpression;*ie != '\0';ie++) {
		//tmp = *ie++;
		switch (*ie) {
			case '(':
		/*If it is an (, pushes it into the stack. */
				if(Push(s, *ie)==SUCCEEDED);else{
					DestroyStack(s);
					return FAILED;
				}
				break;
			case ')':
		/*If it is an ), pops all the elements in front of ( out of stack. */
				GetTop(s, &e);
				while (e != '(' && StackEmpty(s)==FAILED) {
					Pop(s, &e);
					*pe++ = e;
					GetTop(s, &e);
				}
				if(e=='(')Pop(s, &e);
				break;
		case '+':case '-':case '*':case '/':case '@':case '$':
		/*If it is an operator, pops all the elements which have High-priority out of the stack.
			Then pushes this operator into the stack.
		*/
			GetTop(s, &e);
			if (GetTop(s, &e)==SUCCEEDED) {
				while (StackEmpty(s)==FAILED && IsLowerOrEqual(e, *ie)==SUCCEEDED) {
					Pop(s, &e);
					*pe++ = e;
					GetTop(s, &e);
				}
			}
			if(Push(s, *ie)==SUCCEEDED);else{
				DestroyStack(s);
				return FAILED;
			} 
			break;
		case '0':case'1':case'2':case'3':case'4':
		case '5':case'6':case'7':case'8':case'9':
		/*If it is an operand, outputs directly to the suffix expression. */
			while(*ie>='0'&&*ie<='9'){
				*pe++ = *ie++;
			}
			ie--;
			*pe++='#';
			break;
		default:
		/*If it's another character, it's illegal. */
			break;
		}
	}
	/*pop the remaining elements out of the stack. */
	while (StackEmpty(s)==FAILED) {
		GetTop(s, &e);
		*pe++ = e;
		Pop(s, &e);
	}
	*pe = '\0';
	
	/*Output the error message in the front position*/
	return SUCCEEDED;
	
}


/* This function computes the value of a postfix expression stored in 'postfixExpression'
 and stores the final value in 'value'
 If everything is all right, RETURN SUCCEEDED; otherwise, RETURN FAILED
 */
State computeValueFromPostfix(char *postfixExpression, double *value)
{
	double left, right;
	double result;
	double e, tmp;//Defines tmp for storing the current element and define E to store the top element of the stack
	char *pfE;///Suffix expression pointer

	SequentialStackDouble* s=(SequentialStackDouble*)malloc(sizeof(SequentialStackDouble));
	if(s==NULL)return FAILED;
	InitStackDouble(s);
	

	pfE = postfixExpression;
	while (*pfE != '\0') {
		if (*pfE == '+' || *pfE == '-' || *pfE == '*' || *pfE == '/') {
		/*If it is a binary operator,pops up two top elements. */
			if(PopDouble(s, &e)==SUCCEEDED);else {
				printf("Lack of operand in postfix expression. \n");
				DestroyStackDouble(s);
				return FAILED;
			}
			right = e;
			if(PopDouble(s, &e)==SUCCEEDED);else {
				printf("Lack of operand in postfix expression. \n");
				DestroyStackDouble(s);
				return FAILED;
			}
			left = e;
			switch (*pfE) {
				case '+':
					result = left + right;
					if(PushDouble(s, result)==SUCCEEDED);else{
						DestroyStackDouble(s);
						return FAILED;
					} 
					break;
				case '-':
					result = left - right;
					if(PushDouble(s, result)==SUCCEEDED);else{
						DestroyStackDouble(s);
						return FAILED;
					} 
					break;
				case '*':
					result =left*right;
					if(PushDouble(s, result)==SUCCEEDED);else{
						DestroyStackDouble(s);
						return FAILED;
					} 
					break;
				case '/':
					if (right == 0) {
						printf("Divided By Zero Excepiton. \n");
						return FAILED;
					}
					result =left / right;
					if(PushDouble(s, result)==SUCCEEDED);else{
						DestroyStackDouble(s);
						return FAILED;
					} 
					break;
			}
			pfE++;
		}
		else if(*pfE=='$'){
		/*If it is an unary operator, pops up a top element. */
			if(PopDouble(s,&e)==SUCCEEDED);else{
				DestroyStackDouble(s);
				return FAILED;
			}
			e=-e;
			if(PushDouble(s, e)==SUCCEEDED);else{
				DestroyStackDouble(s);
				return FAILED;
			}
			pfE++;
		}
		else if (*pfE>='0'&&*pfE<='9') {
		/*If it is a number, pushed the digit into the stack. */
			tmp = 0;
			while (*pfE != '#'&&(*pfE>='0'&&*pfE<='9')) {
				tmp = tmp * 10 + (*pfE - '0');
				pfE++;
			}
			if(PushDouble(s, tmp)==SUCCEEDED);else{
				DestroyStackDouble(s);
				return FAILED;
			}
		}
		else if(*pfE=='#'||*pfE=='@') {
			pfE++;
		}
		else{
			printf("Wrong expression!! Illegal character '%c' in the expression. \n",*pfE);
			DestroyStackDouble(s);
			return FAILED;
		}
	}
	if(PopDouble(s, value)==SUCCEEDED);else{
		//printf("Operator missing in postfix expression. \n");
		DestroyStackDouble(s);
		return FAILED;
	}
	if(GetTopDouble(s,&result)==SUCCEEDED){
		printf("Too many operands in postfix expression. \n");
		DestroyStackDouble(s);
		return FAILED;
	}
	DestroyStackDouble(s);
	return SUCCEEDED;
}

/* This function check if the current element's priority is less than or equal to the top of the stack's
 If it is true, RETURN SUCCEEDED; otherwise, RETURN FAILED
 */
State IsLowerOrEqual(char TopElem, char Elem)
{

	int top=-1;
	int e=-1;
	switch(TopElem){
		case'+':case'-':
			top=0;
			break;
		case'*':case'/':
			top=1;
			break;
		case'@':case'$':
			top=2;
			break;
	}
	switch(Elem){
		case'+':case'-':
			e=0;
			break;
		case'*':case'/':
			e=1;
			break;
		case'@':case'$':
			e=2;
			break;
	}
	if(top==-1||e==-1){
		return FAILED;
	}
	if(top>=e){
		return SUCCEEDED;
	}
	return FAILED;
}

/*
	This function preprocesses the input 'infixExpression', 
	and if 'infixExpression' is a true expression, stores the result in 'p_infixExpression'.
	If not,stores the error location in 'pos', the error message is stored in 'errMes'.

	If everything is all right, RETURN SUCCEEDED ; otherwise, RETURN FAILED
*/
State err_preprocessor_infixExpression(char*infixExpression)
{
	int BraceNum=0;
	char FrontValidChar='\0';//Record the previous valid character that is not ' ' or '\t'
	int space=0;
	int Illeal=0;//Illegal character @ or $

	int i;
	//Change the unary operators + and - to @ and $
	for(i=0;infixExpression[i]=='\t'||infixExpression[i]==' ';i++);
	if(infixExpression[i]=='\0'){
		printf("Wrong expression!! No operands in the expression! \n");
		return FAILED;
	}
	if(infixExpression[i]=='+'){
		infixExpression[i++]='@';
	}else if(infixExpression[i]=='-'){
		infixExpression[i++]='$';
	}
	while(infixExpression[i]!='\0'){
		if(infixExpression[i]=='@'||infixExpression[i]=='$'){
			Illeal=1;
			infixExpression[i+1]='\0';
			break;
		}
		if(infixExpression[i]=='('){
			do{
				i++;
			}while(infixExpression[i]==' '||infixExpression[i]=='\t');
			if(infixExpression[i]=='+'){
				infixExpression[i++]='@';
			}else if(infixExpression[i]=='-'){
				infixExpression[i++]='$';
			}
		}else{
			i++;
		}
	}

	//error-handling
	for(i=0;infixExpression[i]!='\0';i++){
		switch(infixExpression[i]){
			case '+':case '-':case '*':case '/':
				if(FrontValidChar=='+'||FrontValidChar=='-'||FrontValidChar=='*'
				||FrontValidChar=='/'||FrontValidChar=='@'||FrontValidChar=='$'){
					printf("Wrong expression!! Operator '%c' immediately follows '%c' in the expression. \n",infixExpression[i],ChangeElem(FrontValidChar));
					return FAILED;
				}else if(FrontValidChar=='('){
					printf("Wrong expression!! No operand between '(' and '%c'. \n",infixExpression[i]);
					return FAILED;
				}else if(FrontValidChar=='\0'){
					printf("Wrong expression!! No operand before the first '%c'. \n",infixExpression[i]);
					return FAILED;
				}
				FrontValidChar=infixExpression[i];
				space=0;
				break;
			case '0':case '1':case '2':case '3':case '4':
			case '5':case '6':case '7':case '8':case '9':
				if(FrontValidChar==')'){
					printf("Wrong expression!! No operator between a number and ')'. \n");
					return FAILED;
				}else if((FrontValidChar>='0'&&FrontValidChar<='9')&&space==1){
					printf("Wrong expression!! No operator between two operands. \n");
					return FAILED;
				}
				space=0;
				FrontValidChar=infixExpression[i];
				break;
			case '(':
				if(FrontValidChar>='0'&&FrontValidChar<='9'){
					printf("Wrong expression!! No operator between a number and '('. \n");
					return FAILED;
				}else if(FrontValidChar==')'){
					printf("Wrong expression!! No operator between ')' and '('. \n");
					return FAILED;
				}
				BraceNum++;
				space=0;
				FrontValidChar=infixExpression[i];
				break;
			case ')':
				if(FrontValidChar=='+'||FrontValidChar=='-'||FrontValidChar=='*'
				||FrontValidChar=='/'||FrontValidChar=='@'||FrontValidChar=='$'){
					printf("Wrong expression!! No operand between '%c' and ')' \n.",ChangeElem(FrontValidChar));
					return FAILED;
				}else if(FrontValidChar=='('){
					printf("Wrong expression!! No operand between '(' and ')'. \n");
					return FAILED;
				}
				BraceNum--;
				if(BraceNum<0){
					printf("Wrong expression!! No matched '(' before ')'. \n");
					return FAILED;
				}
				space=0;
				FrontValidChar=infixExpression[i];
				break;
			case '@':case '$':
				if(Illeal==1){
					printf("Wrong expression!! Illegal character '%c' in the expression. \n",infixExpression[i]);
					return FAILED;
				}
				space=0;
				FrontValidChar=infixExpression[i];
				break;
			case ' ':case '\t':
				if(FrontValidChar=='@'||FrontValidChar=='$'){
					printf("Wrong expression!! A space follows a unary '%c'.\n",ChangeElem(FrontValidChar));
					return FAILED;
				}
				space=1;
				break;
			default:
				if((infixExpression[i]>0&&infixExpression[i]<32)||infixExpression[i]==127){
					printf("Wrong expression!! Illegal character '\\%o' in the expression. \n",infixExpression[i]);
					return FAILED;
				}else{
					printf("Wrong expression!! Illegal character '%c' in the expression. \n",infixExpression[i]);
					return FAILED;
				}
		}
	}
	if(FrontValidChar=='*'||FrontValidChar=='/'||FrontValidChar=='+'||FrontValidChar=='-'){
		printf("Wrong expression!! No operand after the last '%c' in the expression. \n",FrontValidChar);
		return FAILED;
	}
	if(FrontValidChar=='@'||FrontValidChar=='$'){
		printf("Wrong expression!!  No operand after a unary '%c'. \n",ChangeElem(FrontValidChar));
		return FAILED;
	}
	if(BraceNum!=0){
		printf("Wrong expression!! No matched ')' after '('. \n");
		return FAILED;
	}
	return SUCCEEDED;
}

char ChangeElem(char elem)
{
	if(elem=='@')return '+';
	else if(elem=='$')return '-';	
	else return elem;
}







