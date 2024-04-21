#include "library/syscalls.h"
#include "library/stdio.h"
#include "library/errno.h"

int create_process(const char *exec, int priority)
{
    int pfd = syscall_open_file(KNO_STDDIR, exec, 0, 0);

    if (pfd >= 0)
    {
        int pid = syscall_process_prun(pfd, 0, &exec, priority);
        if (pid > 0);
        else
        {
            printf("couldn't run %s: %s\n", exec, strerror(pid));
        }
        syscall_object_close(pfd);
    }
    else
    {
        printf("couldn't find %s: %s\n", exec, strerror(pfd));
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int n = 2;

    const char *processes[] = {"bin/receiver.exe","bin/sender.exe" };

    int priorities[] = {0, 1};
    // creating receiver and sender processes
    for (int i = 0; i < n; i++)
    {
        create_process(processes[i], priorities[i]);
    }
    syscall_run_all();
    return 0;
}