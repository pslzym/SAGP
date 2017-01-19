#include <stdio.h>
#include <stdarg.h>

double average(int count, ...);

int main(void)
{
    double avg;
    avg = average(3, 2, 1, 5);
    printf("%f\n", avg);

    return 0;
}

double average(int count, ...)
{
    va_list ap;

    int i, cnt = 0;
    double tot = 0;
    va_start(ap, count);
    for (i = count; i; i = va_arg(ap, int), cnt++)
        tot += i;

    va_end(ap);
    return tot;
}
