#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int M = 4;
const int N = 9;

void vect_init(int **vector, const int m, const int n) {
    for (int i = 0; i < m; ++i) {
        (*vector)[i] = n - i;
    }
}

bool is_final(int **vector, const int m, const int n) {
    for (int i = 0; i < m; ++i) {
        if ((*vector)[i] >= (m - i)) {
            return false;
        }
    }

    return true;
}

void print_vec(int **vector, const int m, int number) {
    printf("[%d]: ", number);

    for (int i = 0; i < m; ++i) {
        printf("%d", (*vector)[i]);
    }

    printf("\n");
}

void next_vec(int **vector, const int m, const int n) {
    for (int i = m - 1; i >= 0; --i) {
        if ((*vector)[i] >= (m - i)) {
            (*vector)[i] -= 1;

            for (int j = i + 1; j < m; ++j) {
                (*vector)[j] = (*vector)[j - 1] - 1;
            }

            break;
        }
    }
}


int main(int argc, const char** argv) {

    int *current_vec = (int *)malloc(sizeof(int) * N);
    vect_init(&current_vec, M, N);
    int number = 1;

    print_vec(&current_vec, M, number);

    while (!is_final(&current_vec, M, N)) {
        ++number;
        next_vec(&current_vec, M, N);
        print_vec(&current_vec, M, number);
    }

    return 0;
}
