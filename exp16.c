#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 50
//Adjacency matrix for storing ε-transitions only
bool epstable[MAX][MAX]={false};
int numstates,numtrans;
//Read an NFA with ε-transitions (Only ε-transitions are stored)
void get_enfa()
{
    char transition[MAX],*p;
    printf("Enter the number of states n, states will be named from q0 to q(n-1)\n");
    scanf("%d",&numstates);
    printf("Enter the total number of transitions\n");
    scanf("%d",&numtrans);
    printf("Enter all the transitions as state symbol state(no space in between), eg q0aq1, use # for epsilon\n");
    for(int i=0;i<numtrans;i++)
    {
        scanf("%s",&transition);
        printf("%s",transition);
        if((p=strchr(transition,'#'))!=NULL) //Only ε-transitions
        {
            int i,j;
            sscanf(transition,"q%d",&i); //state on left ε transition
            j = atoi(p+2);         //state in right ε transition
            epstable[i][j] = true; //Adjacency matrix of ε transitions
        }
    }
}
void findeclose(int state, bool visited[]) //recursively finds ε-closure of a state
{
    visited[state] = true; //Mark the state as in ε-closure
    for(int i=0;i<numstates;i++)
    {
        if(epstable[state][i]&&!visited[i]) //If there is an ε-transition 
        {                                   //and not already considered
            findeclose(i,visited); //Recursively find the ε-closure of reachable state
        }                                    
    }

}
//Prints the ε-closure of all states.
void printeclose()
{
    for(int i=0;i<numstates;i++)
    {
        bool visited[MAX] = {false};
        char outstr[MAX]={'\0'},tempstr[MAX]={'\0'};
        findeclose(i,visited);
        printf("ε-closure(q%d)={",i);
        for(int j=0;j<numstates;j++)
        {
            if(visited[j])
            {
                sprintf(tempstr,"q%d,",j);
                strcat(outstr,tempstr);
            }
        }
        outstr[strlen(outstr)-1]='\0'; //remove last comma
        printf("%s}\n",outstr);
    }
}
int main()
{
    get_enfa();
    printeclose();
    return 0;
}
