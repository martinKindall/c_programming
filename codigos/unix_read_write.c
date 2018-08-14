#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 8192

int main()
{
	size_t nbytes = 1;
	// char buf[] = {'h', 'o', 'l', 'a'};
	char* buf = "hola";
	char bufTxt[BUFSIZE];

	int fd = open("hola.txt", O_RDONLY);

	ssize_t leidos;
	ssize_t escritos;

	while((leidos = read(fd, bufTxt, nbytes)) > 0)
	{
		escritos = write(1, bufTxt, leidos);
	}

	return 0;
}