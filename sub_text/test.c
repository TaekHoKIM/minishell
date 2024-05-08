#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
	// PATH=/usr/local/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin
	// /usr/local/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin
	char	*arg[]={"ls", "-l", NULL};
	char	*arg1[]={"./out", NULL};

	perror("default");
	access("./test/a.out", X_OK);
	perror(">>>>");
	// 패스-->env
	// unset
	// command o
	// ls x
	// ls command not found
	// while (path 탐색){
	// 	패스 + command가 실행가능?
	// }
	execve("./out", arg1, NULL);
	// unset(PATH);
	// execve("/usr/bin/ls", arg1, NULL);
	perror(">>");
	printf("%d\n", errno);
	return (0);
}