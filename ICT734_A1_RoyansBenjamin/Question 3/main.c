/* File Name:       main.c
 * Author:          Ben Royans
 * Date Modified:   04/09/2023
 * Assignment:      1
 * Question:        3
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Must have at least 1 command line argument!\n");
		exit(EXIT_FAILURE);
	}

	int n = argc - 1;
	pid_t childrenPID[n];
	
	// Fork and execute command line arguments
	for (int i = 0; i < n; i++)
	{
		// Fork the process
		pid_t curPID = fork();

		if (curPID == -1)
		{
			fprintf(stderr, "Failed to fork process");
			exit(EXIT_FAILURE);
		}
		else if (curPID == 0)
		{
			// This is child process, execute command line argument(s)
			int executionCode = execl(argv[i + 1], argv[i + 1], NULL);

			if (executionCode == -1)
			{
				fprintf(stderr, "Failure to execute command: %s\n", argv[i + 1]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			// This is parent process, store child's PID
			childrenPID[i] = curPID;
		}
	}

	int successfulExecutions = 0;
	int unsuccessfulExecutions = 0;

	for (int i = 0; i < n; i++)
	{
		int status;
		waitpid(childrenPID[i], &status, 0);

		if (WIFEXITED(status))
		{
			switch(WEXITSTATUS(status))
			{
				case 0:
					printf("[%s] has executed successfully\n", argv[i + 1]);
					successfulExecutions++;
					break;
	
				default:
					printf("[%s] has not executed successfully\n", argv[i + 1]);
					unsuccessfulExecutions++;
					break;
			}
		}
	}

	printf("All done, bye-bye!\n");
	
	return (unsuccessfulExecutions == 0) ? 0 : 1;
}
