//
// Created by thomas on 29.09.18.
//

#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H

#include <iostream>
#include <unordered_set>
#include <cmath>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

using namespace std;

class Graph {
private:
    int **matrix_graph, n, **ij_matrix, start, end;

    int find_min(unordered_set<int> &wave, int j) {
        for (int i = 0; i < this->n; i++) {
            if (wave.find(i) != wave.end() && matrix_graph[j][i] == 1) {
                return i;
            }
        }
        return -1;
    }

public:

    ~Graph() {
        for (int i = 0; i < this->n; i++) {
            delete[] matrix_graph[i];
            delete[] ij_matrix[i];
        }
        delete[] matrix_graph;
        delete[] ij_matrix;
    }

    void make_graph_from_matrix(int n, int **matrix, bool sand=false) {
        int zeros = 0, ij_start = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (matrix[i][j] != 1)
                    zeros++;
        this->n = zeros;
        this->matrix_graph = new int *[this->n];
        this->ij_matrix = new int *[this->n];

        for (int i = 0; i < this->n; i++) {
            this->matrix_graph[i] = new int[this->n];
            this->ij_matrix[i] = new int[2];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0 || (sand &&  matrix[i][j] == -1)) {
                    this->ij_matrix[ij_start][0] = i;
                    this->ij_matrix[ij_start][1] = j;
                    ij_start++;
                } else if (matrix[i][j] == 2) {
                    this->ij_matrix[ij_start][0] = i;
                    this->ij_matrix[ij_start][1] = j;
                    this->start = ij_start;
                    ij_start++;
                } else if (matrix[i][j] == 3) {
                    this->ij_matrix[ij_start][0] = i;
                    this->ij_matrix[ij_start][1] = j;
                    this->end = ij_start;
                    ij_start++;
                }
            }
        }

        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++) {
                this->matrix_graph[i][j] = 0;
                if ((abs(this->ij_matrix[i][0] - this->ij_matrix[j][0]) == 1 &&
                     this->ij_matrix[i][1] == this->ij_matrix[j][1]) ||
                    (abs(this->ij_matrix[i][1] - this->ij_matrix[j][1]) == 1 &&
                     this->ij_matrix[i][0] == this->ij_matrix[j][0])) {
                    this->matrix_graph[i][j] = 1;
                    this->matrix_graph[j][i] = 1;
                }
            }
        }

    }

    void print_graph() {
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++) {
                cout << " " << this->matrix_graph[i][j];
            }
            cout << endl;
        }

        cout << endl;
        for (int i = 0; i < this->n; i++)
            cout << i << "->" << "(" << this->ij_matrix[i][0] << "; " << this->ij_matrix[i][1] << ");" << endl;

    }

    int find_da_wae(int *way) {
        int iter = 0;
        unordered_set<int> history;
        auto *wave = new unordered_set<int>[this->n];

        history.insert(this->start);
        wave[iter].insert(this->start);
        iter++;

        while (history.find(this->end) == history.end()) {
            unordered_set<int>::iterator itr;
            // пробегаемся по вершинам и ищем их образы
            for (itr = wave[iter - 1].begin(); itr != wave[iter - 1].end(); itr++) {
                for (int i = 0; i < this->n; i++) {
                    if (this->matrix_graph[*itr][i] == 1 && history.find(i) == history.end()) {
                        wave[iter].insert(i);
                        history.insert(i);
                    }
                }
            }
            iter++;

            if (iter > this->n) {
                delete[] wave;
                return 0;
            }
        }


        way[iter] = this->end;
        way[0] = this->start;
        for (int i = iter - 1; i > 0; i--)
            way[i] = find_min(wave[i - 1], way[i + 1]);


        delete[] wave;

        return iter + 1;
    }

    int print_da_way(int n, int **matrix) {
        auto *way = new int[this->n + 1];
        int length = find_da_wae(way);

        if (length == 0) {
            cout << "Do you know da wae?" << endl;
            return length;
        }


        for (int i = 2; i < length - 1; i++)
            matrix[this->ij_matrix[way[i]][0]][this->ij_matrix[way[i]][1]] = 5;


        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                if (matrix[i][j] == 5)
                    cout << " *";
                else
                    cout << " " << matrix[i][j];
            cout << endl;
        }

        delete[] way;
        return length;
    }


};


class SquareMatrix {
private:
    int **matrix, n;

public:
    ~SquareMatrix() {
        for (int i = 0; i < this->n; i++)
            delete[] this->matrix[i];
        delete[] this->matrix;
    }

    void input_matrix(QString path, int nsize) {
        this->n = nsize;

        if (path == QString("blank")) {
            this->matrix = new int *[n];
            for (int i = 0; i < this->n; i++)
                this->matrix[i] = new int[n];
            for (int i = 0; i < this->n; i++)
                for (int q = 0; q < this->n; q++)
                    this->matrix[i][q] = 0;
        return;
        }
        else if (path == QString("generate")) {
            this->matrix = new int *[n];
            for (int i = 0; i < this->n; i++)
                this->matrix[i] = new int[n];
            for (int i = 0; i < this->n; i++)
                for (int q = 0; q < this->n; q++)
                    this->matrix[i][q] = qrand() % 2;
        return;
        }

        QFile file(path);
        if (file.open(QIODevice::ReadOnly)) {
                QTextStream stream(&file);
                stream >> this->n;
                this->matrix = new int *[n];
                for (int i = 0; i < this->n; i++)
                    this->matrix[i] = new int[n];

                for (int i = 0; i < this->n; i++)
                    for (int q = 0; q < this->n; q++)
                        stream >> this->matrix[i][q];
        } else {
            QMessageBox::information(0, "error", file.errorString());
        }


    }

    void output_matrix(QString path) {
        QFile file(path);
        if (file.open(QIODevice::WriteOnly)) {
                QTextStream stream(&file);
                stream << this->n << "\n";

                for (int i = 0; i < this->n; i++){
                    for (int q = 0; q < this->n; q++)
                        stream << this->matrix[i][q] << " ";
                    stream << "\n";
                }
        } else {
            QMessageBox::information(0, "error", file.errorString());
        }


    }

    int** get_matrix() {
        return this->matrix;
    }
    int get_n() {
        return this->n;
    }
    int get_value(int i, int j) {
        return this->matrix[i][j];
    }

    void set_value(int i, int j, int x) {
        this->matrix[i][j] = x;
    }
    void print_matrix() {
        for (int i = 0; i < this->n; i++) {
            for (int q = 0; q < this->n; q++)
                cout << " " << this->matrix[i][q];
            cout << endl;
        }
    }


    void print_line_sums() {
        int buff_sum;
        bool flag;

        cout << "Sums of lines without negatives:" << endl;
        for (int i = 0; i < this->n; i++) {
            buff_sum = 0;
            flag = true;

            for (int j = 0; j < this->n; j++) {
                if (this->matrix[i][j] < 0) {
                    flag = false;
                    break;
                } else
                    buff_sum += this->matrix[i][j];
            }

            if (flag) {
                cout << "i = " << i << ": " << buff_sum << ";" << endl;
            }
        }
    }

    void print_min_of_main_diagonal() {
        int buff = 0, min = this->matrix[this->n - 1][0];
        int start_i = this->n - 2, start_j = 0;

        for (int i = 0; i < this->n * 2 - 2; i++) {
            buff = 0;
            bool flag = false;
            int shift = 0;
            while (start_i + shift < this->n && start_j + shift < this->n) {
                buff += this->matrix[start_i + shift][start_j + shift];
                shift++;
                flag = true;
            }
            if (buff < min && flag)
                min = buff;

            if (start_i >= 1)
                start_i--;
            else
                start_j++;

        }

        cout << "Minimum of parallel to main diagonals: " << min << ";" << endl;
    }

    void print_sums_of_collateral_diagonals() {
        auto *sums = new int[this->n * 2 - 1];

        for (int i = 0; i < this->n * 2 - 1; i++)
            sums[i] = 0;

        for (int i = 0; i < this->n; ++i)
            for (int j = 0; j < this->n; ++j)
                sums[i + j] += this->matrix[i][j];

        cout << "Sums of collateral diagonals:" << endl;
        for (int i = 0; i < this->n * 2 - 1; i++)
            cout << "i = " << i << ": " << sums[i] << ";" << endl;


        delete[] sums;
    };


    bool can_be_graphed() {
        bool two = false, three = false;
        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->n; ++j)
                if (matrix[i][j] < -1 || matrix[i][j] > 3)
                    return false;
                else if (matrix[i][j] == 2)
                    two = true;
                else if (matrix[i][j] == 3)
                    three = true;
        return two && three;
    }

    int find_way() {
        if (!this->can_be_graphed()) {
            cout << "This matrix cannot be graphed, I won't find da wae" << endl;
            return 0;
        }

        int **new_matrix = new int *[n];

        for (int i = 0; i < this->n; i++)
            new_matrix[i] = new int[n];
        for (int i = 0; i < this->n; i++)
            for (int q = 0; q < this->n; q++)
                new_matrix[i][q] = this->matrix[i][q];

        Graph graph1{}, graph2{};

        graph1.make_graph_from_matrix(this->n, this->matrix);

        int res1 = graph1.print_da_way(this->n, this->matrix);

        graph2.make_graph_from_matrix(this->n, new_matrix, true);
        int res2 = graph2.print_da_way(this->n, new_matrix);
        int res = 0;

        if ((res2 && res1 && res2 - res1 < 0  && double(res1 - res2) / res1 >= 0.2) || (res2 && !res1)) {
            for (int i = 0; i < this->n; i++)
                for (int q = 0; q < this->n; q++)
                    this->matrix[i][q] = new_matrix[i][q];
            res = res2;
        } else {
            res = res1;
        }

        // graph.print_graph();

        for (int i = 0; i < this->n; i++)
            delete [] new_matrix[i];

        delete [] new_matrix;

        return res;
    }
};


#endif //LAB3_MATRIX_H
