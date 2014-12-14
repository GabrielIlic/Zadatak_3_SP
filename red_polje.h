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
	klijent elements[1000];
	int front, rear;
};

red Q;
red Pom;

int AddOne(int n) {
	return ((n + 1) % 1000);
}

void InitQ(red &Q) {
	Q.front = 0;
	Q.rear = 999;
}

bool IsEmptyQ(red Q) {
	if(AddOne(Q.rear) == Q.front) return 1;
	else return 0;
}

klijent FrontQ(red Q) {
	if(!IsEmptyQ(Q)) return Q.elements[Q.front];
}

void EnQueueQ(klijent x, red &Q) {
	if(AddOne(AddOne(Q.rear)) != Q.front) {
		Q.rear = AddOne(Q.rear);
		Q.elements[Q.rear] = x;
	}
}

void DeQueueQ(red &Q) {
	if(!IsEmptyQ(Q)) Q.front = AddOne(Q.front);
}
