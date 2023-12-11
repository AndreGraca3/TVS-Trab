#include <systemd/sd-daemon.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <pthread.h>

#define BUFSIZE 1024

void terror(char *msg) {
	perror(msg);
	pthread_exit((void *)(intptr_t)1);
}

void * process_connection(void * ptr) {
	int conn_fd = (int)(intptr_t)ptr;

	char buf[BUFSIZE];
	int len;

	len = read(conn_fd, buf, BUFSIZE);
	if (len < 0) {
		terror("ERROR reading from socket");
	}
	buf[len] = 0;
	printf("server received %d bytes: %s\n", len, buf);

	char* command = strtok(buf, " \n");
	printf("Command received %s\n", command);
	char args[100];
	char* temp = strtok(NULL, " \n");
	while(temp != NULL) {
		strcat(args, temp);
		strcat(args, " ");
		temp = strtok(NULL, " \n");
	}
	printf("Arguments received %s\n", args);

	char cmd[100];

	if(strcmp(command, "reset") == 0) {
		strcpy(cmd, "sudo /opt/isel/tvs/tvsapp/bin/tvsapp-reset.sh ");
		system(strcat(cmd, args));
	} else if(strcmp(command, "inc") == 0) {
		strcpy(cmd, "sudo /opt/isel/tvs/tvsapp/bin/tvsapp-inc.sh ");
		system(strcat(cmd, args));
	} else if(strcmp(command, "dec") == 0) {
		strcpy(cmd, "sudo /opt/isel/tvs/tvsapp/bin/tvsapp-dec.sh ");
		system(strcat(cmd, args));
	} else if(strcmp(command, "stop") == 0) {
		strcpy(cmd, "sudo /opt/isel/tvs/tvsapp/bin/tvsapp-stop.sh ");
		system(strcat(cmd, args));
	} else if(strcmp(command, "start") == 0) {
		system("sudo /opt/isel/tvs/tvsapp/bin/tvsapp-start.sh");
	} else if(strcmp(command,"status") == 0) {
		int saved_stdout = dup(1);
		dup2(conn_fd, 1);
		system("sudo /opt/isel/tvs/tvsapp/bin/tvsapp-status.sh");
		dup2(saved_stdout, 1);
	}
	exit(0);
}

void error(char *msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char * argv[]) {
	puts(":: START ::");

	int nfds = sd_listen_fds(0);
	if (nfds != 1) {
		fprintf(stderr, "Zero or more than one fds! Panic.\n");
		exit(1);
	}

	int main_fd = SD_LISTEN_FDS_START;

	puts(":: LISTENING ::");

	for (;;) {

		struct sockaddr_un cli_addr;
		unsigned int cli_addr_len = sizeof cli_addr;

		int conn_fd = accept(main_fd, (struct sockaddr *)&cli_addr, &cli_addr_len);
		if (conn_fd < 0) {
			close(main_fd);
			error("ERROR on accept");
		}

		printf("server established connection with client\n");

		pthread_t thread;
		pthread_create(&thread, NULL, process_connection, (void *)(intptr_t)conn_fd);
		pthread_detach(thread);
	}

	close(main_fd);

	puts(":: END ::");
	return 0;
}

