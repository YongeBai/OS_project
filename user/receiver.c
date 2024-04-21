#include "library/syscalls.h"
#include "library/string.h"
#include "../kernel/string.h"
#include "../include/kernel/types.h"

int main() {
    printf("start receiver.\n");
    syscall_process_sleep(10);
    const char *fname = "named_pipe";

    int fd = syscall_open_named_pipe(fname);
    printf("receiver: syscall_open_named_pipe:%d\n",fd);
    if(fd >= 0){
        char received_message[20];
        int r;

        // reading message from named pipe if available or yield
        while((r = syscall_object_read(fd, received_message, 20, -1))==0) {
            syscall_process_yield();
        }
            
        if(r > 0 ){
            received_message[r] = '\0';
            printf("Message received: %s\n", received_message);
        } else {
            printf("Error reading the message %s\n", r);
        }

        syscall_object_close(fd); 
        printf("receiver finish.\n");
        }

    else {
        printf("%d: Error opening named pipe.\n", syscall_process_self());
        return 1;
    }

  return 1;
}