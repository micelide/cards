#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <time.h>

/** * * * * * * * * * * * D E F I N E S * * * * * * * * * * * **/
int testNum = 10000;

/** * * * * * * * * * * * F U N C T I O N S * * * * * * * * * * * **/
void printCalculations(int numcalls, struct timeval *start, struct timeval *finish)
{
	printf("* * * * * * Analysis * * * * * * *\n");
	time_t begin = (start->tv_sec*1e6 + start->tv_usec);
	time_t end = (finish->tv_sec*1e6 + finish->tv_usec);
	time_t tot = end - begin;
	printf("Manual timval: %f\n", (float)tot);
	printf("Total processes forked: %f\n", pow(2,numcalls) );
	printf("Start time: \t%f\nEnd time: \t%f\n", (float)begin, (float)end);
	printf("Total elapsed time: %f seconds\n", (float)tot);
	printf("Average time per run: %f microseconds\n", (float)(tot/pow(2,numcalls)));
}

void test4(char *p1, char *p2, char *p3, char *p4)
{
	char *args[] = {"./testcard", "4", p1, p2, p3, p4, NULL};
	
	int status = 0;

	pid_t pid = fork();
	if(pid < 0)
	{
		printf("fork error\n");
	}
	else if(pid == 0)
	{
		status = execvp(args[0], args);
		if(status < 0)
		{
			printf("error occurred in exec\n");
			printf("%s\n", strerror(errno));
		}
	}
	else
	{
		wait(NULL);
	}
}
long avg(int count, float old, long new)
{
	long oldAvg = old*(count);
	oldAvg += new;
	return (oldAvg/count+1);
}
/** * * * * * * * * * * * * M A I N * * * * * * * * * * * * **/
int main(int argc, char **argv)
{
	if(argc != 6)
	{
		printf("Try again with 5 arguments\n");
	}
	int i = 0;
	clock_t start = clock();
	for(i = 0; i < testNum; i++)
	{
		test4(argv[2], argv[3], argv[4], argv[5]);
	}
	clock_t end = clock();
	float tot = (float)(end - start);
	printf("* * * * * * Analysis * * * * * * *\n");
	printf("Total runs: %d\n", i);
	printf("Total time: %f\n", tot);
	printf("Average: \t%f\n", (tot/i));

	return 0; 
}

