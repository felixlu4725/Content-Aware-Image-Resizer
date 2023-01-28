// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_matrix_width) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 3, 5);
    
    ASSERT_EQUAL(Matrix_width(mat), 3);
    
    delete mat;
}

TEST(test_matrix_height) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 3, 5);
    
    ASSERT_EQUAL(Matrix_height(mat), 5);
    
    delete mat;
}

TEST(test_matrix_row) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 5, 3);
    int* ptr = Matrix_at(mat, 2, 2);
    
    ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
    
    delete mat;
}

TEST(test_matrix_column) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 5, 3);
    int* const ptr = Matrix_at(mat, 2, 4);
    
    ASSERT_EQUAL(Matrix_column(mat, ptr), 4);
    
    delete mat;
}

TEST(test_matrix_fill_border) {
    Matrix *mat = new Matrix;
    
    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(mat, 3, 5);
    Matrix_fill_border(mat, value);

    for (int r = 0; r < height; ++r){
      for (int c = 0; c < width; ++c){
          if (r == 0 || r == (Matrix_height(mat) - 1) || c == 0 || c == (Matrix_width(mat) - 1))    {
              ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
          }
      }
    }
    
    delete mat;
}

TEST(test_matrix_max) {
    Matrix *mat = new Matrix;
    
    const int value = 1;
    Matrix_init(mat, 5, 3);
    Matrix_fill(mat, value);
    *Matrix_at(mat, 2, 4) = 2;
    
    ASSERT_EQUAL(Matrix_max(mat), 2);
    
    delete mat;
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
