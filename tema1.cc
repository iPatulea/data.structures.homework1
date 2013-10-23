/*Ionut Patulea
313CA*/
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "stack.h"
#include "queue.h"
using namespace std;
class posta{
private:
	queue<int> *q,qaux;
	stack<int> *s,saux;
	int **v;
public:
	int n;
	posta(int nr){
		int i;
		q=new queue<int>[nr];
		s=new stack<int>[nr];
		v=new int*[nr];
		for (i=0;i<nr;i++)
			v[i]=new int[6];
		for (i=0;i<nr;i++)
			q[i].enqueue(-1);
	}
	void OPEN_WINDOW(int windID,int weightMIN,int weightMAX,int Q,int K){
		q[windID].dequeue();
		v[windID][0]=weightMIN;
		v[windID][1]=weightMAX;
		v[windID][2]=Q;
		v[windID][3]=K;
		v[windID][4]=0;
		v[windID][5]=0;
	}
	void ADD_PERSON(int persID,int packweight,int windID){
		q[windID].enqueue(persID);
		q[windID].enqueue(packweight);
	}
	void PROCESS(int windID,int n_people){
		int i,j,persID,packweight;
		for (i=1;i<=n_people;i++)
		{
			persID=q[windID].dequeue();
			packweight=q[windID].dequeue();
			if (packweight>=v[windID][0] && packweight<=v[windID][1])
			{
				if (v[windID][4]<v[windID][2] && v[windID][5]+packweight<=v[windID][3])
				{
					s[windID].push(packweight);
					v[windID][4]++;
					v[windID][5]+=packweight;
					continue;
				}
				while(!s[windID].isEmpty())
					s[windID].pop();
				s[windID].push(packweight);
				v[windID][4]=1;
				v[windID][5]=packweight;
				continue;
			}
			j=(windID+1)%n;
			while (q[j].front()==-1 && !q[j].isEmpty())
				j=(j+1)%n;
			ADD_PERSON(persID,packweight,j);
		}
	}
	void PROCESS_ALL(int windID){
		int j,persID,packweight;
		while(!q[windID].isEmpty())
		{
			persID=q[windID].dequeue();
			packweight=q[windID].dequeue();
			if (packweight>=v[windID][0] && packweight<=v[windID][1])
			{
				if (v[windID][4]<v[windID][2] && v[windID][5]+packweight<=v[windID][3])
				{
					s[windID].push(packweight);
					v[windID][4]++;
					v[windID][5]+=packweight;
					continue;
				}
				while(!s[windID].isEmpty())
					s[windID].pop();
				s[windID].push(packweight);
				v[windID][4]=1;
				v[windID][5]=packweight;
				continue;
			}
			j=(windID+1)%n;
			while (q[j].front()==-1 && !q[j].isEmpty())
				j=(j+1)%n;
			ADD_PERSON(persID,packweight,j);
		}
	}
	void PRINT_STACKS(){
		int i,pack,sem;
		printf("STACKS:\n");
		for (i=0;i<n;i++)
			if (q[i].front()!=-1  || q[i].isEmpty())
			{
				sem=0;
				printf("%d: ",i);
				while (!s[i].isEmpty())
				{
					pack=s[i].pop();
					if (sem==0)
						printf("%d",pack);
					else
						printf(", %d",pack);
					saux.push(pack);
					sem=1;
				}
				printf("\n");
				while (!saux.isEmpty())
					s[i].push(saux.pop());
			}
	}
	void FLUSH_STACKS(){
		int i,pack,sem;
		printf("FLUSHING:\n");
		for (i=0;i<n;i++)
			if (q[i].front()!=-1 || q[i].isEmpty())
			{
				sem=0;
				printf("%d: ",i);
				while (!s[i].isEmpty())
				{
					pack=s[i].pop();
					if (sem==0)
						printf("%d",pack);
					else
						printf(", %d",pack);
					sem=1;
				}
				printf("\n");
			}
	}
	void PRINT_QUEUES(){
		int i,sem,persID,packweight;
		printf("QUEUES:\n");
		for (i=0;i<n;i++)
			if (q[i].front()!=-1 || q[i].isEmpty())
			{
				sem=0;
				printf("%d: ",i);
				while (!q[i].isEmpty())
				{
					persID=q[i].dequeue();
					packweight=q[i].dequeue();
					if (sem==0)
						printf("(%d, %d)",persID,packweight);
					else
						printf(", (%d, %d)",persID,packweight);
					sem=1;
					qaux.enqueue(persID);
					qaux.enqueue(packweight);
				}
				printf("\n");
				while (!qaux.isEmpty())
					q[i].enqueue(qaux.dequeue());
			}
	}
};
int main(int argc,char *argv[])
{
	FILE *f;
	int nr,winID,weightMIN,weightMAX,Q,K,persID,packweight,n_people;
	char *com;
	com=new char[30];
	f=fopen(argv[1],"r");
	fscanf(f,"%d",&nr);
	posta P(nr);
	P.n=nr;
	while (!feof(f))
	{
		fscanf(f,"%s",com);
		if (feof(f))
			break;
		if (!strcmp(com,"OPEN_WINDOW"))
		{
			fscanf(f,"%d %d %d %d %d",&winID,&weightMIN,&weightMAX,&Q,&K);
			P.OPEN_WINDOW(winID,weightMIN,weightMAX,Q,K);
			continue;
		}
		if (!strcmp(com,"ADD_PERSON"))
		{
			fscanf(f,"%d %d %d",&persID,&packweight,&winID);
			P.ADD_PERSON(persID,packweight,winID);
			continue;
		}
		if (!strcmp(com,"PROCESS"))
		{
			fscanf(f,"%d %d",&winID,&n_people);
			P.PROCESS(winID,n_people);
			continue;
		}
		if (!strcmp(com,"PROCESS_ALL"))
		{
			fscanf(f,"%d",&winID);
			P.PROCESS_ALL(winID);
			continue;
		}
		if (!strcmp(com,"PRINT_STACKS"))
		{
			P.PRINT_STACKS();
			continue;
		}
		if (!strcmp(com,"FLUSH_STACKS"))
		{
			P.FLUSH_STACKS();
			continue;
		}
		if (!strcmp(com,"PRINT_QUEUES"))
		{
			P.PRINT_QUEUES();
			continue;
		}
	}
	return 0;
}
