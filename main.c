#include<iostream>
#include<cstdlib>
#include<queue>
#include<cstdio>

using namespace std;
typedef struct process
{
  int id,arrival_time,burst_time,completion_time,st,pr;
  float waiting_time,turnaround_time;
}process;
process p[100],p1[100],temp;
queue<int> q1;
int accept(int ch);
void turnwait(int n);
void display(int n);
void ganttrr(int n);

int main()
{
  int i,n,ts,ch,j,x;
  p[0].turnaround_time=0;
  p[0].waiting_time=0;
  n=accept(ch);
  ganttrr(n);
  turnwait(n);
 display(n);
 return 0;
}

int accept(int ch)
{
  int i,n;
  printf("Enter the Total Number of Process: ");
  scanf("%d",&n);
 if(n==0)
  {
    printf("Invalid");
    exit(1);
  }
  cout<<endl;
  for(i=1;i<=n;i++)
  {
    printf("Enter an Arrival Time of the Process P%d: ",i);
    scanf("%d",&p[i].arrival_time);
    p[i].id=i;
  }
 cout<<endl;
  for(i=1;i<=n;i++)
  {
    printf("Enter a Burst Time of the Process P%d: ",i);
    scanf("%d",&p[i].burst_time);
  } 
  for(i=1;i<=n;i++)
   {
    p1[i]=p[i];
 }
  return n;
}

void ganttrr(int n)
{ 
  int i,ts,m,nextval,nextarr;  
  nextval=p1[1].arrival_time;
  i=1;
  cout<<"\nEnter the Time Slice or Quantum: ";
  cin>>ts;
  for(i=1;i<=n && p1[i].arrival_time<=nextval;i++)
   {
    q1.push(p1[i].id);
 }
  while(!q1.empty()) 
  { 
    m=q1.front();
    q1.pop();
    if(p1[m].burst_time>=ts)
     {
      nextval=nextval+ts;
  } 
    else
     {
      nextval=nextval+p1[m].burst_time;
    }   
    if(p1[m].burst_time>=ts)
     {
      p1[m].burst_time=p1[m].burst_time-ts;
  } 
    else
     {
      p1[m].burst_time=0;
  }   
    while(i<=n&&p1[i].arrival_time<=nextval)
    {
      q1.push(p1[i].id);
      i++;
    }
    if(p1[m].burst_time>0)
     {
      q1.push(m);
  }
    if(p1[m].burst_time<=0)
     {
      p[m].completion_time=nextval;
     }   
  }
}

void turnwait(int n)
{
  int i; 
  for(i=1;i<=n;i++)
  {
    p[i].turnaround_time=p[i].completion_time-p[i].arrival_time;
    p[i].waiting_time=p[i].turnaround_time-p[i].burst_time;
    p[0].turnaround_time=p[0].turnaround_time+p[i].turnaround_time;
    p[0].waiting_time=p[0].waiting_time+p[i].waiting_time;
  }
  p[0].turnaround_time=p[0].turnaround_time/n;
  p[0].waiting_time=p[0].waiting_time/n;
}

void display(int n)
{
  int i;
  cout<<"\n=====================================================\n"; 
 cout<<"\n\nHere AT = Arrival Time\nBT = Burst Time\nTAT = Turn Around Time\nWT = Waiting Time\nCT = Completion Time\n";

  cout<<"\n===================TABLE==============================\n";
  printf("\nProcess\tAT\tBT\tCT\tTAT\t\tWT");
 
  for(i=1;i<=n;i++)
 {
  printf("\nP%d\t%d\t%d\t%d\t%f\t%f",p[i].id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
 }
  cout<<"\n=====================================================\n"; 
   printf("\nAverage Turn Around Time: %f",p[0].turnaround_time);
   printf("\nAverage Waiting Time: %f\n",p[0].waiting_time);
}
