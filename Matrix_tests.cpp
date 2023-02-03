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
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

TEST(test_fill_edge) {
    Matrix *mat = new Matrix;

    const int width = 1;
    const int height = 1;
    const int value = 0;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);

    for(int r = 0; r < height; ++r){
        for(int c = 0; c < width; ++c){
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
    }

    delete mat;
}

TEST(test_init1) {
    Matrix *mat = new Matrix;

    Matrix_init(mat, 1, 1);
    ASSERT_EQUAL(Matrix_width(mat), 1);
    ASSERT_EQUAL(Matrix_height(mat), 1);
    
    delete mat;
}

TEST(test_init2) {
    Matrix *mat = new Matrix;

    Matrix_init(mat, 3, 5);
    ASSERT_EQUAL(Matrix_width(mat), 3);
    ASSERT_EQUAL(Matrix_height(mat), 5);
    
    delete mat;
}

TEST(test_print_basic) {
    Matrix *mat = new Matrix;
    Matrix_init(mat, 3, 3);
    Matrix_fill(mat, 1);
    
    *Matrix_at(mat, 0, 0) = 2;
    ostringstream expected;
    expected << "3 3\n"
            << "2 1 1 \n"
            << "1 1 1 \n"
            << "1 1 1 \n";
    
    ostringstream actual;
    Matrix_print(mat, actual);
    ASSERT_EQUAL(expected.str(), actual.str());

    delete mat;
}

TEST(test_print_edge1) {
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

TEST(test_print_edge2) {
    Matrix *mat = new Matrix;
    Matrix_init(mat, 2, 3);
    Matrix_fill(mat, 1);
    
    *Matrix_at(mat, 0, 0) = 2;
    ostringstream expected;
    expected << "2 3\n"
            << "2 1 \n"
            << "1 1 \n"
            << "1 1 \n";
    
    ostringstream actual;
    Matrix_print(mat, actual);
    ASSERT_EQUAL(expected.str(), actual.str());

    delete mat;
}

TEST(test_width_basic) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 3, 5);
    
    ASSERT_EQUAL(Matrix_width(mat), 3);
    
    delete mat;
}

TEST(test_height_basic) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 3, 5);
    
    ASSERT_EQUAL(Matrix_height(mat), 5);
    
    delete mat;
}

TEST(test_row_basic) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 5, 3);
    int* ptr = Matrix_at(mat, 2, 2);
    
    ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
    
    delete mat;
}

TEST(test_row_edge) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 1, 1);
    int* ptr = Matrix_at(mat, 0, 0);
    
    ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
    
    delete mat;
}

TEST(test_column_basic) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 5, 3);
    int* ptr = Matrix_at(mat, 2, 4);
    
    ASSERT_EQUAL(Matrix_column(mat, ptr), 4);
    
    delete mat;
}

TEST(test_column_edge) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 1, 1);
    int* ptr = Matrix_at(mat, 0, 0);
    
    ASSERT_EQUAL(Matrix_column(mat, ptr), 0);
    
    delete mat;
}

TEST(test_fill_border_basic) {
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

TEST(test_fill_border_edge1) {
    Matrix *mat1 = new Matrix;
    Matrix *mat2 = new Matrix;
    
    const int width = 2;
    const int height = 2;
    const int value = 42;
    Matrix_init(mat1, width, height);
    Matrix_fill_border(mat1, value);

    Matrix_init(mat2, width, height);
    Matrix_fill(mat2, value);
    
    ASSERT_TRUE(Matrix_equal(mat1, mat2));
    
    delete mat1;
    delete mat2;
}

TEST(test_fill_border_edge2) {
    Matrix *mat1 = new Matrix;
    Matrix *mat2 = new Matrix;
    
    const int width = 1;
    const int height = 1;
    const int value = 42;
    Matrix_init(mat1, width, height);
    Matrix_fill_border(mat1, value);

    Matrix_init(mat2, width, height);
    *Matrix_at(mat2, 0, 0) = value;
    
    ASSERT_TRUE(Matrix_equal(mat1, mat2));
    
    delete mat1;
    delete mat2;
}

TEST(test_max_basic) {
    Matrix *mat = new Matrix;
    
    const int value = 1;
    Matrix_init(mat, 5, 3);
    Matrix_fill(mat, value);
    *Matrix_at(mat, 2, 4) = 2;
    
    ASSERT_EQUAL(Matrix_max(mat), 2);
    
    delete mat;
}

TEST(test_max_edge1) {
    Matrix *mat = new Matrix;
    
    const int value = 1;
    Matrix_init(mat, 5, 3);
    Matrix_fill(mat, value);
    *Matrix_at(mat, 0, 4) = 2;
    *Matrix_at(mat, 1, 3) = 2;
    *Matrix_at(mat, 2, 2) = 2;
    
    ASSERT_EQUAL(Matrix_max(mat), 2);
    
    delete mat;
}

TEST(test_max_edge2) {
    Matrix *mat = new Matrix;
    
    const int value = 1;
    Matrix_init(mat, 1, 1);
    *Matrix_at(mat, 0, 0) = value;
    
    ASSERT_EQUAL(Matrix_max(mat), 1);
    
    delete mat;
}


TEST(test_column_of_min_basic) {
    Matrix *mat = new Matrix;
    
    const int value = 5;
    Matrix_init(mat, 3, 5);
    Matrix_fill(mat, value);
    *Matrix_at(mat, 3, 1) = 3;

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 3, 0, 2), 1);
    
    delete mat;
}

TEST(test_column_of_min_edge1) {
    Matrix *mat = new Matrix;
    
    const int value = 5;
    Matrix_init(mat, 3, 5);
    Matrix_fill(mat, value);
    *Matrix_at(mat, 3, 1) = 3;
    *Matrix_at(mat, 3, 2) = 3;

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 3, 0, 2), 1);
    
    delete mat;
}

TEST(test_column_of_min_edge2) {
    Matrix *mat = new Matrix;

    Matrix_init(mat, 1, 1);
    *Matrix_at(mat, 0, 0) = 3;

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 0), 0);
    
    delete mat;
}

TEST(test_min_value_basic) {
    Matrix *mat = new Matrix;
    
    const int value = 5;
    Matrix_init(mat, 3, 5);
    Matrix_fill(mat, value);
    *Matrix_at(mat, 3, 1) = 3;

    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 3, 0, 2), 3);
    
    delete mat;
}

TEST(test_min_value_edge1) {
    Matrix *mat = new Matrix;
    
    const int value = 5;
    Matrix_init(mat, 3, 5);
    Matrix_fill(mat, value);
    *Matrix_at(mat, 3, 1) = 3;
    *Matrix_at(mat, 3, 2) = 3;

    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 3, 0, 2), 3);
    
    delete mat;
}

TEST(test_min_value_edge2) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 1, 1);
    *Matrix_at(mat, 0, 0) = 3;

    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 0), 3);
    
    delete mat;
}

TEST(test_matrix_at) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 1, 1);
    *Matrix_at(mat, 0, 0) = 3;

    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 3);
    
    delete mat;
}

TEST(test_matrix_at_const) {
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 1, 1);
    *Matrix_at(mat, 0, 0) = 3;

    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 3);
    
    delete mat;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
