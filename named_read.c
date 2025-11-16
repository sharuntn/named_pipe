#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()

{

    int fd_1,fd_2,n, i;
    char *fifo1 = "fifo_1";
    char *fifo2 = "fifo_2";
    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    while (1)
    {
        fd_1 = open(fifo1, O_RDONLY);
        if (fd_1 == -1)
        {
            perror("open failed");
            return 1;
        }
    if (read(fd_1, &n, sizeof(n)) <= 0)
        {
            close(fd_1);
            continue;
        }
        if (n == 0)
	  {
            printf("Reader exiting...\n");
            close(fd_1);
            break;
        }
        printf("Received: %d\n", n);
        close(fd_1);
        fd_2 = open(fifo2,O_WRONLY);
        if (fd_2 < 0)
        {
            perror("open failed");
            break;
        }
        printf("Odd numbers up to %d: ", n);
        for (i = 1; i <= n; i++)
        {
            if (i % 2 != 0)
            {
            printf("%d ", i);
            
            if (write(fd_2, &i, sizeof(i)) != sizeof(i)) {
                    perror("write to fifo2 failed");
                   	break;
                }
        }}
        int end = -1;
        write(fd_2, &end, sizeof(end));
    printf("\n");
    close(fd_2);
    
    }
    return 0;
    }
