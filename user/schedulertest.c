#include "library/syscalls.h"
#include "library/stdio.h"
#include "library/errno.h"

int create_process(const char *exec, int priority)
{
    int pfd = syscall_open_file(KNO_STDDIR, exec, 0, 0);

    if (pfd >= 0)
    {
        int pid = syscall_process_prun(pfd, 0, &exec, priority);
        if (pid > 0)
        {
            printf("created %s with priority %d\n", exec, priority);
        }
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
    // number of processes
    int n = 5;

    // change add processes here
    const char *processes[] = {"bin/process1.exe", "bin/process2.exe", "bin/process3.exe", "bin/process4.exe", "bin/process5.exe"};

    // change add/change priorities here
    int priorities[] = {9, 7, 2, 1, 5};

    // iteratively create processes
    for (int i = 0; i < n; i++)
    {
        create_process(processes[i], priorities[i]);
    }
    // run all processes
    syscall_run_all();
    return 0;
}