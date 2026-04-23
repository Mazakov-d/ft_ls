#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <error.h>
#include <string.h>

int main() {
	DIR*	dir;

	dir = opendir("srdfc");
	if (dir) {
		closedir(dir);
		return (0);
	}
	ft_printf("strerror: %s\n", strerror(errno));
	perror("Error opendir");
	return (1);
}