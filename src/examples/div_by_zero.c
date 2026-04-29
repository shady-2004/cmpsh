#include <stdio.h>

int main() {
    int x = 10;
    int y = 0;
    int result = x / y;  // This will cause SIGFPE (Floating Point Exception)
    printf("Result: %d\n", result);
    return 0;
}