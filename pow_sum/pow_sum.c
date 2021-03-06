#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <pthread.h>

#define SIZE 11

int pow_arr[SIZE];
int sum_value;

int convert(void *obj, long *out) {
    char *ptr;

    *out = strtol((char *) obj, &ptr, 10);

    if (*out == LONG_MAX || *out == LONG_MIN)
        return -1;

    return *out ? 1 : 0;
}

void *m_pow(void *count) {
    long powCount;

    convert((char *) count, &powCount);

    for (int i = 0; i < powCount; i++)
        pow_arr[i] = (int) pow(2, i);

    pthread_exit(0);
}

void *m_sum(void *count) {
    long sumCount;

    sum_value = 0;
    convert((char *) count, &sumCount);

    for (int i = 0; i < sumCount; i++)
        sum_value += pow_arr[i];

    pthread_exit(0);
}

int main() {

    pthread_t thSum;
    pthread_t thPow;

    pthread_attr_t attrPow;
    pthread_attr_t attrSum;

    pthread_attr_init(&attrPow);
    pthread_attr_init(&attrSum);

    pthread_create(&thPow, &attrPow, m_pow, SIZE);
    pthread_join(thPow, NULL);

    pthread_create(&thSum, &attrSum, m_sum, SIZE);
    pthread_join(thSum, NULL);

    printf("Soma das potencias = %d\n", sum_value);

    return 0;
}