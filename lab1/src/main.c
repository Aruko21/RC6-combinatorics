#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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
    if (argc < 3) {
        printf("Usage: %s <m> <n>\n", argv[0]);
        return 1;
    }

    int m_val = atoi(argv[1]);
    int n_val = atoi(argv[2]);

    int *current_vec = (int *)malloc(sizeof(int) * n_val);
    vect_init(&current_vec, m_val, n_val);
    int number = 1;

    print_vec(&current_vec, m_val, number);

    while (!is_final(&current_vec, m_val, n_val)) {
        ++number;
        next_vec(&current_vec, m_val, n_val);
        print_vec(&current_vec, m_val, number);
    }

    return 0;
}
