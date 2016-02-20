#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	int file = open("/dev/khalebiosdriver", O_RDWR);
	
	if(file < 0)
	{
		perror("open");
		exit(errno);
	}
	
	char buf[20];
	size_t nbytes;
	nbytes = sizeof(buf);
	//while(1){
	ssize_t bytes_read = read(file, buf, nbytes);
	printf("%zu",bytes_read);
	//}
	close(file);
	
	return 0;
}
