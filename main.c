#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char* itos(int, int);
const char* formatted_number(const char* str, int number);
int max(int, int);
int multi_max(int count, ...);
void print_table(int size, int table[], int columns);

int main() {
    const char* s = formatted_number("%d %d %d\n%d %d %d\n", multi_max(6, 5, 130, 26, 15, 80, 245));
    printf(s, 5, 130, 26, 15, 80, 245);

    free((char*)s);

    /*int numbers[] = {1, 2, 3, 4, 5, 6};

    print_table(6, numbers, 2);
*/
    return 0;
}

char* itos(int number, int reserve) {
    int digit_number = 1;

    while ((number /= 10) != 0) {
        digit_number++;
    }

    char* number_str = malloc(digit_number * sizeof(char) + 1);

    sprintf(number_str, "%d", digit_number + reserve);

    return number_str;
}

const char* formatted_number(const char* str, int number) {
    size_t curr_size = sizeof(char);
    char* new_str = NULL;
    if ((new_str = malloc(curr_size)) == NULL) {
        perror("Out of storage");
        abort();
    };
    char* editable = new_str;

    while ((*str) != '\0') {
        if ((new_str = realloc(new_str, ++curr_size)) == NULL) {
            perror("Out of storage");
            abort();
        }
        *editable++ = *str;
        if ((*str) == '%') {
            char* digits_str = itos(number, 2);
            while ((*digits_str) != '\0') {
                new_str = realloc(new_str, ++curr_size);
                *editable++ = *digits_str++;
            }
            free(digits_str = 0);
        }
        ++str;
    }

    return new_str;
}

int multi_max(int count, ...) {
    va_list args;
    va_start(args, count);

    int temp_max = va_arg(args, int);

    if (count < 2) {
        return temp_max;
    }

    while(--count > 0) {
        temp_max = max(va_arg(args, int), temp_max);
    }

    va_end(args);

    return temp_max;
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

void print_table(int size, int table[], int columns) {

    int i = 0;

    while (size-- > 0) {
        printf("%d ", table[i]);
        ++i;
        if (i % columns == 0)
            printf("\n");
    }
}
