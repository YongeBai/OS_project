#include "library/syscalls.h"
#include "library/string.h"
#include "../kernel/string.h"
#include "../include/kernel/types.h"

int main() {
    printf("start sender.\n");
    const char *fname = "named_pipe";

    char buffer[] = "Hey Mama\n";
    // creating named pipe
    int res = syscall_make_named_pipe(fname);
    printf("sender: syscall_make_named_pipe:%d\n",res);

    // opening named pipe
    int fd = syscall_open_named_pipe(fname);
    printf("sender: syscall_open_named_pipe:%d\n",fd);

    if(fd >= 0){
        // writing message to named pipe
        syscall_object_write(fd, buffer, strlen(buffer), 0); // write the message to the named pipe
        syscall_process_sleep(1000);
        return 1; 
        } 

    else {
        printf("%d: Error opening named pipe.\n", syscall_process_self());
        return 1;
    }

  return 1;
}