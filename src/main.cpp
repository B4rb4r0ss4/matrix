#include <iostream>
#include "matrix.h"

int main() {
    // Init matrix code runnning
    Matrix matrix;

    // Matrix loop
    while(matrix.running()) {
        matrix.update();
    }

    return 0;
}
