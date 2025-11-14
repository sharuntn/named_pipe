#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
	int fd_1,fd_2,n,i;
	int arr[100] = {0};		
	char *fifo1 = "fifo_1";
	char *fifo2 = "fifo_2";
	mkfifo(fifo1, 0666);
	mkfifo(fifo2, 0666);
	pid_t pid;
	pid = fork();
		
	if (pid<0)
	{
		printf("Process Cannot be created");
		exit(0);
	}
	else if (pid > 0)
	{
		printf("Enter the Limit N:");
		scanf("%d", &n);
		fd_1 = open(fifo1,O_WRONLY);
		if (fd_1 < 0)
		{
			perror("Open Failed");
			exit(0);
		}
		write(fd_1, &n, sizeof(n));
		close(fd_1);
		fd_2 = open(fifo2,O_RDONLY);
		wait(NULL);
		if(fd_2 < 0)
		{
			perror("Open Failed");
			exit(0);
		}
		read(fd_2, arr, sizeof(arr));
		close(fd_2);
		printf("Odd numbers upto %d : ", n);
		for (i = 1; i <= n; i++)
        	{
            	if (arr[i] != 0)  
                printf("%d ", arr[i]);
        	}
        	printf("\n");
		
	}
	else
	{
		fd_1 = open(fifo1,O_RDONLY);
		if(fd_1 < 0)
		{
			perror("Open failed");
			exit(0);
		}
		read(fd_1, &n, sizeof(n));
		for(i=1; i<=n; i++)
		{
			if(i % 2 != 0)
			{
				arr[i] = i;
			}
		}
		close(fd_1);
		fd_2 = open(fifo2,O_WRONLY);
		if(fd_2 < 0)
		{
			perror("Open Failed");
			exit(0);
		}
		write(fd_2, arr, sizeof(arr));
		close(fd_2);
	}
	return 0;
}	
		
