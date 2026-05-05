
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

struct message {
	char source[50];
	char target[50]; 
	char msg[200]; // message body
};

void terminate(int sig) {
	printf("Exiting....\n");
	fflush(stdout);
	exit(0);
}

int main() {
	int server;
	int target;
	int dummyfd;
	struct message req;
	signal(SIGPIPE,SIG_IGN);
	signal(SIGINT,terminate);
	server = open("serverFIFO",O_RDONLY);
	dummyfd = open("serverFIFO",O_WRONLY);

	while (1) {
		// TODO:
		// read requests from serverFIFO
		ssize_t bytesRead = read(server, &req, sizeof(struct message));

		if (bytesRead < 0) {
			perror("read");
			continue;
		}

		if (bytesRead == 0) {
			continue;
		}

		if (bytesRead != sizeof(struct message)) {
			fprintf(stderr, "Partial message received.\n");
			continue;
		}





		printf("Received a request from %s to send the message %s to %s.\n",req.source,req.msg,req.target);

		// TODO:
		// open target FIFO and write the whole message struct to the target FIFO
		// close target FIFO after writing the message
		target = open(req.target, O_WRONLY);

		if (target < 0) {
			perror("open target FIFO");
			continue;
		}

		ssize_t bytesWritten = write(target, &req, sizeof(struct message));

		if (bytesWritten != sizeof(struct message)) {
			perror("write target FIFO");
		}

		close(target);






	}
	close(server);
	close(dummyfd);
	return 0;
}

