#include <iostream>
#include <cassert>
#include "../hpp/Matrix.hpp"

using namespace std;

void test1() {
    TMatrix myMatrix(2, 3);
    int col = myMatrix.GetColumns();
    int row = myMatrix.GetRows();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            myMatrix[i][j] = 3;
        }
    }
    cout << "LOL" << endl;
    myMatrix *= 2;
    cout << "LOL" << endl;
    TMatrix m2(myMatrix);
    m2 *= 5;
    TMatrix m3 = myMatrix + m2;
    TMatrix m4(2, 3);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            m4[i][j] = 30;
        }
    }
    assert(m2 == m4);
}

void test2() {
    TMatrix matrixExample(3, 25);
    assert(matrixExample.GetRows() == 3 && matrixExample.GetColumns() == 25);
}

void test3() {
    TMatrix matrixExample;
    assert(matrixExample.GetRows() == 5 && matrixExample.GetColumns() == 5);
    
}

void test4() {
    TMatrix matrixExample(4, 4);
    matrixExample[1][3] = 2;
    matrixExample[3][3] = 5;
    assert(matrixExample[1][3] == 2 && matrixExample[3][3] == 5);
}

void test5() {
    TMatrix matrixExample(4, 4);
    int col = matrixExample.GetColumns();
    int row = matrixExample.GetRows();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrixExample[i][j] = 3;
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            assert(matrixExample[i][j] == 3);
        }
    }
    matrixExample *= 3;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            assert(matrixExample[i][j] == 9);
        }
    }
}

void test6() {
    TMatrix matrixExample1(4, 4);
    int col = matrixExample1.GetColumns();
    int row = matrixExample1.GetRows();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrixExample1[i][j] = 3;
        }
    }
    TMatrix matrixExample2(4, 4);
    col = matrixExample2.GetColumns();
    row = matrixExample2.GetRows();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrixExample2[i][j] = 3;
        }
    }
    TMatrix matrixExample3(4, 4);
    matrixExample3 = matrixExample1 + matrixExample2;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            assert(matrixExample3[i][j] == 6);
        }
    }
}

void test7() {
    TMatrix matrixExample1(4, 4);
    int col = matrixExample1.GetColumns();
    int row = matrixExample1.GetRows();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrixExample1[i][j] = 3;
        }
    }
    TMatrix matrixExample2(3, 4);
    col = matrixExample2.GetColumns();
    row = matrixExample2.GetRows();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrixExample2[i][j] = 3;
        }
    }
    TMatrix matrixExample3(4, 4);
    matrixExample3 = matrixExample1 + matrixExample2;
}

void test8() {
    TMatrix matrixExample1(3, 4);
    TMatrix matrixExample2(4, 4);
    assert(matrixExample1 != matrixExample2);
}

void test9() {
    TMatrix matrixExample1(4, 4);
    int col = matrixExample1.GetColumns();
    int row = matrixExample1.GetRows();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrixExample1[i][j] = 3;
        }
    }
    TMatrix matrixExample2(4, 4);
    col = matrixExample2.GetColumns();
    row = matrixExample2.GetRows();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrixExample2[i][j] = 3;
        }
    }
    assert(matrixExample1 == matrixExample2);
}

void test10() {
    TMatrix matrixExample1(4, 4);
    int col = matrixExample1.GetColumns();
    int row = matrixExample1.GetRows();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrixExample1[i][j] = 3;
        }
    }
    cout << endl << matrixExample1 << endl;
}

void test11() {
    TMatrix matrixExample1(3, 4);
    TMatrix matrixExample2(4, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            matrixExample1[i][j] = 3;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            matrixExample2[i][j] = 6;
        }
    }
    matrixExample2 = matrixExample1;
    assert(matrixExample2.GetColumns() == 4 && matrixExample2.GetRows() == 3 && matrixExample2[1][1] == 3);
}

int main() {
    cout << "test1 ";
    test1();
    cout << "OK" << endl;
    cout << "test2 ";
    test2();
    cout << "OK" << endl;
    cout << "test3 ";
    test3();
    cout << "OK" << endl;
    cout << "test4 ";
    test4();
    cout << "OK" << endl;
    cout << "test5 ";
    test5();
    cout << "OK" << endl;
    cout << "test6 ";
    test6();
    cout << "OK" << endl;
    cout << "test7 ";
    test7();
    cout << "OK" << endl;
    cout << "test8 ";
    test8();
    cout << "OK" << endl;
    cout << "test9 ";
    test9();
    cout << "OK" << endl;
    cout << "test10 ";
    test10();
    cout << "OK" << endl;
    cout << "test11 ";
    test11();
    cout << "OK" << endl;
    return 0;
}