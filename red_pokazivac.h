#include <iostream>
using namespace std;

struct klijent {
	char i_pr[22];
	char dat[12];
	char spol;
	int ai;
	int bi;
	int ci;
	int di;
};

struct red {
	klijent value;
	red *next;
};

struct rd {
	red *front, *rear;
};

rd Q;
rd Pom;

void InitQ(rd &Q) {
	Q.front = new red;
	Q.front -> next = NULL;
	Q.rear = Q.front;
}

bool IsEmptyQ(rd Q) {
	if(Q.front == Q.rear) return 1;
	else return 0;
}

klijent FrontQ(rd Q) {
	if(!IsEmptyQ(Q)) return Q.front -> next -> value;
}

void EnQueueQ(klijent x, rd &Q) {
	Q.rear -> next = new red;
	Q.rear = Q.rear -> next;
	Q.rear -> next = NULL;
	Q.rear -> value = x;
}

void DeQueueQ(rd &Q) {
	red *T = Q.front;
	if(!IsEmptyQ(Q)) {
		Q.front = Q.front -> next;
		delete T;
	}
}
