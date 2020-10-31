#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_vec(int *vector, const int m, int number) {
    printf("[%d]: ", number);

    for (int i = 0; i < m; ++i) {
        printf("%d", vector[i]);
    }

    printf("\n");
}

void transpose_incr(int *vector, const size_t transp_size, const int n) {
    static int transp_number = 1;

    if (transp_size >= n) {
        print_vec(vector, transp_size, transp_number);
        ++transp_number;
        return;
    }

    int max_m = transp_size + 1;

    for (int m = 1; m <= max_m; ++m) {
        int *tmp_vec = (int *)calloc(sizeof(int), n);
        memcpy(tmp_vec, vector, sizeof(int) * transp_size);
        tmp_vec[transp_size] = m;
        for (int i = 0; i < transp_size; ++i) {
            if (tmp_vec[i] >= m) {
                tmp_vec[i] += 1;
            }
        }

        transpose_incr(tmp_vec, transp_size + 1, n);
        free(tmp_vec);
    }
}


int main(int argc, const char** argv) {
    if (argc < 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n_val = atoi(argv[1]);

    int *transp_vec = (int *)calloc(sizeof(int), n_val);

    transp_vec[0] = 1;
    transpose_incr(transp_vec, 1, n_val);

    free(transp_vec);

    return 0;
}
