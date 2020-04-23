/*
 2019038066 김도염 자료구조 5주차 과제
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();


int main(void)
{
	QueueType *cQ = createQueue(MAX_QUEUE_SIZE);
	element data;

	char command;

    printf("------- [2019038066] [Kim Do Yeom] -------");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}


QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
    if (cQ->front==cQ->rear) /*원형큐이기 때문에 앞과 뒤가 같다면 비어있다.
                                그런데 정말 그럴까라는 생각이 들었는데 원
                                형큐는 공간 한개를 비워놓기 때문에 그리고 큐를
                                지울때도 rear를 한칸 뒤로 옮기는 것이 규칙이기에
                                front와 rear가 같지 않고선 큐가 빌 수 없다.*/
        return 1;//그러므로 참값을 반환
    return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{   
    if (cQ->front==(cQ->rear+1)%MAX_QUEUE_SIZE)/*여기서는 모듈러 연산을 썼는데 의미는
                                                front 앞에 rear가 있다는 뜻인데 이
                                                역시 큐의 특성상 중간에 띄어질 이유가
                                                없기 때문에 앞선 말이 맞다면 해당 큐
                                                는 꽉 찬 것이다.*/
        return 1;// 그러므로 참!
   return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
    if (isFull(cQ))//해당 큐가 가득 찼으면?
        return 0;//오류값 전달, 가득 찼는데 뭘 더 추가해?
    cQ->rear=(cQ->rear+1)%MAX_QUEUE_SIZE;//후미를 한칸 뒤로 옮긴 후
    cQ->queue[cQ->rear] = item;//해당 후미에 새로운 item값 저장
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{  
    if(isEmpty(cQ))//해당 큐가 비었으면
        return 0;//오류값 전달, 비었는데 뭘 지워
    cQ->front=(cQ->front+1)%MAX_QUEUE_SIZE;//있으면 front값을 한칸 뒤로
    return cQ->queue[cQ->front];/*여기서 큐는 정말 삭제가 아니라 지정하는 이름만
                                옮기는 것이기에 위치만 반환해줌*/
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

