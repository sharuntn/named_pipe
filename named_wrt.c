#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    int fd_1,fd_2,n,m;
    char *fifo1 = "fifo_1";
    char *fifo2 = "fifo_2";
    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);    

    while (1)
    {
        printf("Enter the Limit N (0 to stop): ");
        scanf("%d", &n);

        fd_1 = open(fifo1, O_WRONLY);
        if (fd_1 < 0)
        {
            perror("open failed");
            break;
        }

        write(fd_1, &n, sizeof(n));
        printf("Sent: %d\n", n);
        close(fd_1);

	 if (n == 0)
        {
            printf("Writer exiting...\n");
            break;
        }
   
        fd_2 = open(fifo2, O_RDONLY);
        if (fd_2 == -1)
        {
            perror("open failed");
            return 1;
        }
       
    
        printf("Odd numbers received: ");
	while (read(fd_2, &m, sizeof(m))>0) {
           if (m == -1)
                break;
            printf("%d ", m);
            }
        
	printf("\n");
    close(fd_2);
    }

    return 0;
}

