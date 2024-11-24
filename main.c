#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>

void write_buf(char *buf, size_t size)
{
	printf("  ");
	for (int i = 0; i < size; i++)
	{
		if (buf[i] == '\n')
		{
			printf(".");
		} else
		{
			putchar(buf[i]);
		}
	}
}

int main(int argc, char **argv)
{
	FILE *f = NULL;
	if (argc > 1) {
		f = fopen(argv[1], "r");
	} else if (argc == 1) {
		f = stdin;
	}

	if (f == NULL)
	{
		fprintf(stderr, "could not open file for reading: [%d] %s\n", errno, strerror(errno));
		return EXIT_FAILURE;
	}

	const size_t buflen = 16;

	char buf[buflen] = {0};
	ssize_t r = 0;
	int i = 0;
	char c[3] = {0};
	int l = 0;
	while ((r = read(fileno(f), &buf, buflen)) > 0)
	{
		printf("%08d: ", l * 10);

		for (int j = 0; j < buflen; j++)
		{
			if ((j != 0 && i % 2 == 0))
			{
				printf(" ");

			}
			if (j >= r)
			{
				i++;
				printf("  ");
				continue;
			}

			int n = sprintf(c, "%hhx", buf[j]);
			if (n == 1) {
				printf("0");
			}

			printf("%s", c);


			i++;
		}

		write_buf(buf, r);

		printf("\n");
		l++;
	}


	fclose(f);

	return EXIT_SUCCESS;
}
