#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

int main(){
	clock_t start = clock();
	pid_t pid = getpid();
	pid_t ppid = getppid();
    clock_t end = clock();
	double t = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	printf("pid = %d, ppid = %d\n",pid,ppid);
	printf("duration: %lf\n",t);
	return 0;
}
