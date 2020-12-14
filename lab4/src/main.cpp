#include <iostream>
#include <vector>
#include <string>


std::ostream& operator<<(std::ostream &out, std::vector<int> &vec) {
    if (vec.empty()) {
        out << "[]";
        return out;
    }

    out << vec[0];
    for (int i = 1; i < vec.size(); ++i) {
        out << " + " << vec[i];
    }
    return out;
}


int parts_count(int n) {
    if (n < 0) {
        return 0;
    }

    if (n == 0) {
        return 1;
    }

    int result = 0;
    for (int k = (n - 1) / 2 + 1; k > 0; --k) {
        int sign = (k - 1) % 2 == 0 ? 1 : -1;
        result += sign * parts_count(n - (3 * k * k - k) / 2);
        result += sign * parts_count(n - (3 * k * k + k) / 2);
    }

    return result;
}


void print_erlich_part(std::vector<int> &vec) {
    std::string output;
    for (int i = vec.size() - 1; i > -1; --i){
        if (vec[i] > 0) {
            std::cout << vec[i] << "*" << i + 1 << " ";
        }
    }
    std::cout << std::endl;
}

void gindenburg(int n) {
    std::cout << "Partitions of number '" << n << "' by Gindenburg's algorithm:" << std::endl;

    for (int i = 1; i <= n; ++i) {
        std::cout << "- Number of terms: " << i << std::endl;

        std::vector<int> partition(i, 0);

        int j = 0;
        for (j = 0; j < i; ++j) {
            partition[j] = 1;
        }

        partition[j - 1] = n - j + 1;

        std::cout << partition << std::endl;

        while (partition[i - 1] - partition[0] > 1) {
            j = 0;
            for (j = i - 2; j > -1; --j) {
                if (partition[i - 1] - partition[j] >= 2) {
                    partition[j] += 1;
                    break;
                }
            }

            for (int k = j; k < i - 1; ++k) {
                partition[k] = partition[j];
            }

            int sum = 0;

            for (j = 0; j < i - 1; ++j){
                sum += partition[j];
            }

            partition[j] = n - sum;

            std::cout << partition << std::endl;
        }
    }
}

void erlich(int n) {
    std::cout << "Partitions of number '" << n << "' by Erlich's algorithm:" << std::endl;

    std::vector<int> partition(n, 0);

    for (int i = 0; i < n; ++i) {
        partition[i] = 0;
    }

    partition[0] = n;

    print_erlich_part(partition);

    int i = 0;
    int k = 0;
    while (partition[n - 1] != 1) {
        if (partition[i] > 1) {
            partition[i + 1] += 1;
            partition[i] -= 2;
            partition[0] += 2 * (i + 1) - (i + 2);
            i = 0;

            print_erlich_part(partition);
            continue;
        }
        if (partition[i] == 1) {
            int j = 0;
            for (j = i + 1; j < n; ++j) {
                if (partition[j] > 0) {
                    break;
                }
            }

            partition[j + 1] += 1;
            k = partition[i] * (i + 1) + partition[j] * (j + 1) - (j + 2);
            partition[i] = partition[j] = 0;
            partition[0] = k;
            i = 0;
            print_erlich_part(partition);
            continue;
        }
        ++i;
    }
}


int main(int argc, const char **argv) {
    int n = atoi(argv[1]);

    std::cout << "Partitions count for '" << n << "' = " << parts_count(n) << std::endl;

    gindenburg(9);
    erlich(9);
}   