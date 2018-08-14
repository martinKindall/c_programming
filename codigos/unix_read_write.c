#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE 8192

int main()
{
	size_t nbytes = 1;
	char bufTxt[BUFSIZE];

	int fd = open("hola.txt", O_RDONLY);

	ssize_t leidos;
	ssize_t escritos;

	while((leidos = read(fd, bufTxt, nbytes)) > 0)
	{
		escritos = write(1, bufTxt, leidos);
	}

	char bufOutput[50];
	strcpy(bufOutput, "hola mundo");

	strcat(bufOutput, " talcahuano\n");

	write(1, bufOutput, 50);

	return 0;
}