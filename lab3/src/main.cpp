#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>


class Matrix {
private:
    size_t rows_count;
    size_t cols_count;
    int **values;

    class MatrixRow {
    public:
        explicit MatrixRow(int* array) : array(array) { }

        int operator[](int index) {
            return array[index];
        }
    private:
        int* array;
    };

public:
    explicit Matrix(std::string &filename) {
        std::ifstream fin(filename.c_str());
        if (!fin) {
            std::string errMsg = "Cannot open file '" + filename + "'";
            throw std::invalid_argument(errMsg);
        }

        size_t rows = 0;
        size_t cols = 0;
        fin >> rows >> cols;

        rows_count = rows;
        cols_count = cols;

        int **matrix = new int* [rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new int [cols];
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                fin >> matrix[i][j];
            }
        }
        fin.close();

        values = matrix;
    }

    MatrixRow operator[](int index) {
        return MatrixRow(values[index]);
    }

    size_t getRows() {
        return this->rows_count;
    }

    size_t getCols() {
        return this->cols_count;
    }

    ~Matrix() {
        for (int i = 0; i < rows_count; ++i) {
            delete values[i];
        }
        delete values;
    }
};

std::ostream& operator<<(std::ostream &out, std::vector<int> &vec) {
    if (vec.empty()) {
        out << "[]";
    }

    out << "[" << vec[0] + 1;
    for (int i = 1; i < vec.size(); ++i) {
        out << ", " << vec[i] + 1;
    }
    out << "]";
    return out;
}


bool is_value_in_vector(std::vector<int> &vec, int value) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == value) {
            return true;
        }
    }

    return false;
}

int find_value_in_vector(std::vector<int> &vec, int value) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == value) {
            return i;
        }
    }

    return -1;
}

std::vector<int> HallTransversal(Matrix &matrix) {
    std::vector<int> transversal;
    transversal.reserve(6);

    std::vector<std::vector<int>> s_families;

    for (size_t i = 0; i < matrix.getRows(); ++i) {
        std::vector<int> s_array;
        for (size_t j = 0; j < matrix.getCols(); ++j) {
            if (matrix[i][j] == 1) {
                s_array.push_back(j);
            }
        }
        // TODO: what if there is only zeros?
        s_families.push_back(s_array);
    }

    std::cout << "Initialisation S families: " << std::endl;
    for (size_t i = 0; i < matrix.getRows(); ++i) {
        std::cout << "S[" << i << "]: " << s_families[i] << std::endl;
    }
    std::cout << std::endl;

    // Initialisation of T0
    int s_wrote = 0;
    int max_index = -1;
    for (size_t i = 0; i < s_families.size(); ++i) {
        std::vector<int> s_array = s_families[i];
        bool found_index = false;

        for (size_t k = 0; k < s_array.size(); ++k) {
            if (s_array[k] > max_index) {
                max_index = s_array[k];

                transversal.push_back(s_array[k]);
                found_index = true;
                break;
            }
        }

        if (found_index) {
            s_wrote++;
        } else {
            break;
        }
    }

    // Algorithm
    for (int i = s_wrote; i < s_families.size(); ++i) {
        std::cout << std::endl << "New iteration from S[" << i << "]" << std::endl;

        std::vector<int> l0 = s_families[i];

        std::cout << "" << "l0 is: " << l0 << std::endl;

        std::vector<int> l_list = l0;
        std::vector<std::vector<int>> l_families;
        for (int k = 0; k < l_list.size(); ++k) {
            std::vector<int> tmp_vec = {i};
            l_families.push_back(tmp_vec);
        }

        for (int k = 0; k < l_list.size(); ++k) {
            int curr_member = l_list[k];

            std::cout << "L list now: " << l_list << std::endl;
            std::cout << "Current member is '" << curr_member + 1<< "'" << std::endl;

            if (is_value_in_vector(transversal, curr_member)) {
                for (int s_i = 0; s_i <= s_wrote; ++s_i) {
                    if (is_value_in_vector(s_families[s_i], curr_member)) {
                        std::vector<int> ext_family = s_families[s_i];

                        // Extension of l_list
                        for (int r = 0; r < s_families[s_i].size(); ++r) {
                            int tmp_value = ext_family[r];
                            int l_list_index = find_value_in_vector(l_list, tmp_value);

                            if (l_list_index == -1) {
                                l_list.push_back(tmp_value);
                                std::vector<int> tmp_vec = {s_i};
                                l_families.push_back(tmp_vec);
                            } else {
                                if (!is_value_in_vector(l_families[l_list_index], s_i)) {
                                    l_families[l_list_index].push_back(s_i);
                                }
                            }
                        }
                    }
                }

            } else {
                std::cout << "Tranversal replacing:" << std::endl;
                std::cout << "L list is:  '" << l_list << "'" << std::endl;
                std::cout << "L families is: ";
                for (int z = 0; z < l_families.size(); z++) {
                    std::cout << l_families[z] << " ";
                }
                std::cout << std::endl;

                int s_from = -1;
                while (!is_value_in_vector(l0, curr_member)) {

                    int member_index = find_value_in_vector(l_list, curr_member);
                    int new_s_from = l_families[member_index][0];

                    if (new_s_from == s_from) {
                        s_from = l_families[member_index][1];
                    } else {
                        s_from = new_s_from;
                    }

                    int to_replace = curr_member;
                    curr_member = transversal[s_from];
                    transversal[s_from] = to_replace;

                    std::cout << "Transversal is " << transversal << std::endl;
                }

                transversal.push_back(curr_member);
                std::cout << "Transversal is " << transversal << std::endl;
                break;
            }
        }
    }

    return transversal;
}

int main(int argc, const char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <file_name>" << std::endl;
        return 1;
    }

    std::string file_name = argv[1];

    Matrix* matrix = nullptr;

    try {
        matrix = new Matrix(file_name);
    } catch (std::invalid_argument &err) {
        std::cerr << "Error while matrix creation occured: " << err.what() << std::endl;
        return 1;
    }

    std::vector<int> result = HallTransversal(*matrix);

    std::cout << std::endl << "Result transversal is: " << result << std::endl;

    free(matrix);

    return 0;
}
