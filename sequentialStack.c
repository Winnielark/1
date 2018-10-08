/********************************************************************************
* @File name: sequentialStack.c
* @Author: Zhong Yingjia
* @Version: 4.0
* @Date: 2018.8.10
* @Description: The functions of stack.
********************************************************************************/

#include"sequentialStack.h"

/* Interfaces for the 1st stack for char elements*/

/*  Initialize the sequential stack
*/
State InitStack(SequentialStackChar *s)
{
	s->top=0;
	return SUCCEEDED;
}


/*  Release the memory of the sequential stack
*/
void DestroyStack(SequentialStackChar *s)
{
	if(s!=NULL){
		free(s);
	}
	s=NULL;
}


/*  Check if the stack is empty.
    Return SUCCEEDED to indicate the stack is empty.
    Return FAILED to indicate the stack is NOT empty.
 */
State StackEmpty(SequentialStackChar *s)
{
	if(s->top==0){
		return SUCCEEDED;
	}
	return FAILED;
}


/*  If the stack is NOT full, push e into it and return SUCCEEDED to indicate a successful push.
    If the stack is full, merely return FAILED to indicate an unsuccessful push.
 */
State Push(SequentialStackChar *s, ElemType e)
{
	if(s->top>=MaxSize){
		printf("The stack(char) is full! \n");
		return FAILED;
	}
	s->data[s->top++]=e;
	return SUCCEEDED;
}


/*  If the stack is NOT empty, pop the top of the stack into e and return SUCCEEDED to indicate a successful pop.
    If the stack is empty, merely return FAILED to indicate an unsuccessful pop.
 */
State Pop(SequentialStackChar *s, ElemType *e)
{
	if(s->top==0){
		//printf("empty stack!\n");
		return FAILED;
	}
	*e=s->data[--s->top];
	return SUCCEEDED;
}


/*  If the stack is NOT empty, assign the top of the stack to e and return SUCCEEDED to indicate a successful gettop.
    If the stack is empty, merely return FAILED to indicate an unsuccessful gettop.
 */
State GetTop(SequentialStackChar *s, ElemType *e)
{
	if(s->top==0){
		//printf("empty stack!\n");
		return FAILED;
	}
	*e=s->data[s->top-1];
	return SUCCEEDED;
}




/* Interfaces for the 2nd stack for double elements*/

/*  Initialize the sequential stack
 */
State InitStackDouble(SequentialStackDouble *s)
{
	s->top=0;
	return SUCCEEDED;
}

/*  Release the memory of the sequential stack
 */
void DestroyStackDouble(SequentialStackDouble *s)
{
	if(s!=NULL){
		free(s);
	}
}


/*  Check if the stack is empty.
 Return SUCCEEDED to indicate the stack is empty.
 Return FAILED to indicate the stack is NOT empty.
 */
State StackEmptyDouble(SequentialStackDouble *s)
{
	if(s->top==0){
		return SUCCEEDED;
	}
	return FAILED;
}


/*  If the stack is NOT full, push e into it and return SUCCEEDED to indicate a successful push.
    If the stack is full, merely return FAILED to indicate an unsuccessful push.
 */
State PushDouble(SequentialStackDouble *s, ElemTypeDouble e)
{
	if(s->top>=MaxSize){
		printf("The stack(double) is full! \n");
		return FAILED;
	}
	s->data[s->top++]=e;
	return SUCCEEDED;
}


/*  If the stack is NOT empty, pop the top of the stack into e and return SUCCEEDED to indicate a successful pop.
    If the stack is empty, merely return FAILED to indicate an unsuccessful pop.
 */
State PopDouble(SequentialStackDouble *s, ElemTypeDouble *e)
{
	if(s->top==0){
		//printf("empty stack!\n");
		return FAILED;
	}
	*e=s->data[--s->top];
	return SUCCEEDED;
}


/*  If the stack is NOT empty, assign the top of the stack to e and return SUCCEEDED to indicate a successful gettop.
    If the stack is empty, merely return FAILED to indicate an unsuccessful gettop.
 */
State GetTopDouble(SequentialStackDouble *s, ElemTypeDouble *e)
{
	if(s->top==0){
		//printf("empty stack!\n");
		return FAILED;
	}
	*e=s->data[s->top-1];
	return SUCCEEDED;
}

