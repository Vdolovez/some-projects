#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int i, ppid, pid[6], status[5], result[5];
    char *son[] = {"son1", "son2", "son3", "son4", "son5"};
    int option[] = { WUNTRACED, WUNTRACED, WUNTRACED, WUNTRACED, WUNTRACED};

    pid[5] = getpid();
    ppid = getppid();
    printf("Father parameters was: pid=%i ppid=%i\n", pid[5],ppid);
    for (i = 0; i < 5; i++)
    {
        if((pid[i] = fork()) == 0)
        {
            execl(son[i], son[i], NULL);
        }
    }

    system("ps xf > file.txt");
    for (i = 0; i < 5; i++)
    {
        result[i] = waitpid(pid[i], &status[i], option[i]);
        printf("%d) Child with pid = %d is finished with status %d\n", (1+i), result[i], status[i]);
    }

    for(i = 0; i < 5; i++)
        if (WIFEXITED(status[i]) == 0) //если равен 0, то не успешно завершился
        {
            printf("Proccess pid = %d was failed.\n", pid[i]);
        }
        else
        {
            printf("Proccess pid = %d was success.\n", pid[i]);
        }
    return 0;
}
