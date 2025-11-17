#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd,n,i;		
	char *fifo = "fifo";
	mkfifo(fifo, 0666);
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
		fd = open(fifo,O_WRONLY);
		if (fd < 0)
		{
			perror("Open Failed");
			exit(0);
		}
		write(fd, &n, sizeof(n));
		printf("Natural numbers till %d : ", n);
		for(i=1; i<=n; i++)
		{	
			printf("%d ", i);
		}
		printf("\n");
		close(fd);
	}
	else
	{
		fd = open(fifo,O_RDONLY);
		if(fd<0)
		{
			perror("Open failed");
			exit(0);
		}
		read(fd, &n, sizeof(n));
		printf("Odd numbers upto %d : ", n);
		for (i=1;i<=n;i++)
		{
			if (i % 2 != 0)
			{
				printf("%d ", i);
			}
		}
		printf("\n");
		close(fd);
	}
return 0;
}

			
