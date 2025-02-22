#include "./include/basic/matrix3.h"
#include <iostream>
using namespace std;
int main() {
    mat3 m(
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    );
    mat3 n;
    n = m.transpose();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << n.e[i][j] << " ";
        }
        cout << endl;
    }
}