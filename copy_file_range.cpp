#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	
	//int pipefd[2];
	//int result = pipe(pipefd);
	off64_t result;
	off64_t len;
	
	if(argc!=3){
		printf("Usage:%s<source><destination>\n", argv[0]);
		return -1;
	}

	int fd_in = open(argv[1], O_RDONLY, 0);
    if(fd_in == -1){
        perror("readwrite: open");
        return -1;
    }

    int fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd_out == -1){
        perror("readwrite: creat");
        return -1;
    }

    struct stat stat_src;
    fstat(fd_in, &stat_src);
    len = stat_src.st_size;

	// splice
	/*do {
		result = splice(fd_in, 0, pipefd[1], NULL, len, SPLICE_F_MORE | SPLICE_F_MOVE);
		result = splice(pipefd[0], NULL, fd_out, 0, len, SPLICE_F_MORE | SPLICE_F_MOVE);

		if(result == -1){
			perror("splice");
			return -1;
		}

		len -= result;
	} while (len > 0);*/

	// sendfile
	//sendfile(fd_out, fd_in, 0, len);

	// copy_file_range
	do {
		result = copy_file_range(fd_in, NULL, fd_out, NULL, len, 0);

		if (result == -1) {
			perror("copy_file_range");
			return -1;
		}

		len -= result;
	} while (len > 0 && result > 0);


	//close(pipefd[0]);
	//close(pipefd[1]);
	close(fd_in);
	close(fd_out);

	return 0;
}