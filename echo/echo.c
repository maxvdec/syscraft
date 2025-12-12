#include <stdio.h>

#define SYS_WRITE 0x4
#define SYS_EXIT 0x1

#define WRITE_STDOUT 0x1

long syscall3(long syscall, long arg1, long arg2, long arg3) {
    __asm__ __volatile__("mov x0, %0\n"
                         "mov x1, %1\n"
                         "mov x2, %2\n"
                         "mov x16, %3\n"
                         "svc #0x80"
                         :
                         : "r"(arg1), "r"(arg2), "r"(arg3), "r"(syscall));

    long result;
    __asm__ __volatile__("mov %0, x0" : "=r"(result));
    return result;
}

long syscall1(long syscall, long arg1) {
    __asm__ __volatile__("mov x0, %0\n"
                         "mov x16, %1\n"
                         "svc #0x80"
                         :
                         : "r"(arg1), "r"(syscall));

    long result;
    __asm__ __volatile__("mov %0, x0" : "=r"(result));
    return result;
}

void print(const char *message) {
    int length = 0;
    while (message[length] != '\0') {
        length++;
    }

    syscall3(SYS_WRITE, WRITE_STDOUT, (long)message, length);
}

void exit(int code) {
    syscall1(SYS_EXIT, code);
    __builtin_unreachable();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print("Usage: <message> \n");
        return 1;
    }

    print(argv[1]);
    print("\n");
    return 0;
}

void _start() {
    __asm__ __volatile__("mov x0, x0\n" // argc
                         "mov x1, x1\n" // argv
                         "bl main\n"    // call main
                         "mov x1, x0\n" // move return value to x1
                         "mov x0, #0\n" // exit code 0
                         "bl exit\n"    // call exit
    );
}
