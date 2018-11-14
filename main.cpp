//#include <GL/glut.h>
#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {
  Matrix<int> a(5,5);
  a.print();
    system("PAUSE");
    return EXIT_SUCCESS;
}
