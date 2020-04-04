#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
int main()
{
	int et=0;//et is executed time 
	int n,q;// n is number of processes,   q is time quantum
	int over =0;//used to specify if the given process is completed or not
	printf("Enter number of processes:\t\t");
	scanf("%d",&n);
	int j=0;
	int complete[n];//for process completion order
	int a[n];// array containing arrival time 
	int b[n];//array containing burst time
	int process_turnaround[n];//turnaround time of a given process
	int process_wait[n];//waiting  time of a given process
	int comp[n]={0};
	int i=0;
	int completion_time[n];//to find process completion time 
	int wait=0,turnaround=0;//wait is waiting time and turnaround is turnaround time
	int burst[n];//to store burst time , used for calculations later
	for ( i=0;i<n;i++)//for taking inputs
	{	
		
		printf("\nEnter arrival time of process %d :\t",i+1);
		scanf("%d",&a[i]);
		printf("\nEnter  burst time of process %d  :\t",i+1);
		scanf("%d",&b[i]);
		burst[i]=b[i];//copying because we need to do further calculations
	}
	printf("\nEnter time quantum:\t");
	scanf("%d",&q);
	int rem;//remaining processes
	i=0;
	rem=n;//to retain the value of number of processes
	printf("\nOrder of execution :\n");
	while(rem>0)//loop until all the processes are executed
	{over=0;
	if (comp[i]==1)
	{
		if (i==n-1)//if i reached the max numbered process, reset i
		{
			i=0;
		}
		else 
		{
			i++;
		}
		
	}
	else if (a[i]>et && comp[i]==0){// only do processes which have been arrived at the current time
		if (i==n-1)//if i reached the max numbered process, reset i
		{
			i=0;}
		else 
		{
			i++;
		}
		//printf("Executing %d now\n",i);
	}
	else{
		if (comp[i]==0 && a[i]<=et && b[i]>0 && (b[i]-q)>0)
		{
			//printf("%d executed for %d now\n",i,q);
			et=q+et;
			b[i]=b[i]-q;
			//printf("CURRENT TIME  %d\n",et);
			printf("P[%d]\t\t",i+1);
		}
		else if (comp[i]== 0&& a[i]<=et && b[i]>0 && (b[i]-q)<=0)
		{
			//printf("%d executed for %d now\n",i,b[i]);
			et=et+b[i];
			b[i]=0;
			over =1;
			printf("P[%d]\t\t",i+1);
			//printf("current time: %d\n process %d is over",et,i);
		}
		if (b[i]==0 && over==1)//to check if the process is completed
		{rem--;//decrease remaining processes by 1
			wait=wait+et-burst[i]-a[i];
			turnaround=turnaround+et-a[i];				
			//printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d\n", i, burst[i], et-burst[i]-a[i], et-a[i]);//turnound,wait
			process_wait[i]=et-burst[i]-a[i];
			process_turnaround[i]=process_wait[i]+burst[i];
			//printf("P[%d]\t",i+1);//for printing the order of process completion
			complete[j]=i;
			j++;
			comp[i]=1;
			completion_time[i]=et;//for process completion time
		}
		if (i==n-1)//if i reached the max numbered process, reset i
		{
			i=0;
		}
		else 
		{
			i++;
		}
		}
}
printf("\n\nOrder of Completion\n");
for (i=0;i<n;i++){
	printf("P[%d]\t\t",complete[i]+1);
}
printf("\n\n\nProcess\t\t Arrival Time\t\tBurst Time\t\tCompletion Time\t\tWaiting Time\t\tTurnaround Time\n");

for (i=0;i<n;i++)
{
	printf("P[%d]\t\t   %d\t\t\t     %d\t\t\t   %d\t\t\t\t%d\t\t     %d\n",i+1,a[i],burst[i],completion_time[i],process_wait[i],process_turnaround[i]);
}
	float average_wait_time ;
	average_wait_time= wait*1.0/n;
    float average_turnaround_time ;
	average_turnaround_time= turnaround*1.0/n;
      printf("Average Waiting Time: %f\n", average_wait_time);
      printf("\nAvg Turnaround Time: %f", average_turnaround_time);
      return 0;
}
