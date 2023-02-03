// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

const Pixel red = {255, 0, 0};
const Pixel green = {0, 255, 0};
const Pixel blue = {0, 0, 255};
const Pixel white = {255, 255, 255};

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_nxn) {
  Image *img = new Image; // create an Image in dynamic memory

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

TEST(test_print_1x1) {
  Image *img = new Image;
  Image_init(img, 1, 1);

  Image_set_pixel(img, 0, 0, white);
  ostringstream expected;
  expected << "P3\n"
           << "1 1\n"
           << "255\n"
           << "255 255 255 \n";
  ostringstream actual;
  Image_print(img, actual);

  ASSERT_EQUAL(expected.str(), actual.str());

  delete img;
}

TEST(test_print_1xn) {
  Image *img = new Image;

  Image_init(img, 1, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 1, 0, blue);

  ostringstream s;
  Image_print(img, s);

  ostringstream correct;
  correct << "P3\n1 2\n255\n";
  correct << "255 0 0 \n";
  correct << "0 0 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img;
}

TEST(test_print_nx1) {
  Image *img = new Image;

  Image_init(img, 2, 1);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);

  ostringstream s;
  Image_print(img, s);

  ostringstream correct;
  correct << "P3\n2 1\n255\n";
  correct << "255 0 0 0 255 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img;
}

TEST(test_image_init_nxn) {
  Image *img = new Image;
  Image_init(img, 2, 2);

  ASSERT_EQUAL(Image_width(img), 2);
  ASSERT_EQUAL(Image_height(img), 2);

  delete img;
}

TEST(test_image_init_fromInput) {
  Image *img = new Image;
  string input = "P3 2 2\t255 5 0 1\n0\n255 \n0 \n0 0 90 \t255 \n255 \t45 \n";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);

  string output_correct = "P3\n2 2\n255\n5 0 1 0 255 0 \n0 0 90 255 255 45 \n";
  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct);

  delete img;
}

TEST(test_image_width) {
  Image *img = new Image;
  Image_init(img, 1, 2);

  ASSERT_EQUAL(Image_width(img), 1);

  delete img;
}

TEST(test_image_height) {
  Image *img = new Image;
  Image_init(img, 1, 2);

  ASSERT_EQUAL(Image_height(img), 2);

  delete img;
}

TEST(test_image_get_pixel) {
  Image *img = new Image;

  Image_init(img, 1, 1);
  Image_set_pixel(img, 0, 0, white);

  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).r, 255);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).g, 255);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).b, 255);

  delete img;
}

TEST(test_image_set_pixel) {
  Image *img = new Image;

  Image_init(img, 1, 1);
  Image_set_pixel(img, 0, 0, white);

  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).r, 255);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).g, 255);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).b, 255);

  delete img;
}

TEST(test_image_fill_nxn) {
  Image *img = new Image;

  Image_init(img, 2, 2);
  Image_fill(img, white);

  ostringstream expected;
  expected << "P3\n"
           << "2 2\n"
           << "255\n"
           << "255 255 255 255 255 255 \n"
           << "255 255 255 255 255 255 \n";
  ostringstream actual;
  Image_print(img, actual);

  ASSERT_EQUAL(expected.str(), actual.str());

  delete img;
}

TEST(test_image_fill_1xn) {
  Image *img = new Image;

  Image_init(img, 1, 2);
  Image_fill(img, white);

  ostringstream expected;
  expected << "P3\n"
           << "1 2\n"
           << "255\n"
           << "255 255 255 \n"
           << "255 255 255 \n";
  ostringstream actual;
  Image_print(img, actual);

  ASSERT_EQUAL(expected.str(), actual.str());

  delete img;
}

TEST(test_image_fill_nx1) {
  Image *img = new Image;

  Image_init(img, 2, 1);
  Image_fill(img, white);

  ostringstream expected;
  expected << "P3\n"
           << "2 1\n"
           << "255\n"
           << "255 255 255 255 255 255 \n";
  ostringstream actual;
  Image_print(img, actual);

  ASSERT_EQUAL(expected.str(), actual.str());

  delete img;
}

TEST(test_image_fill_1x1) {
  Image *img = new Image;

  Image_init(img, 1, 1);
  Image_fill(img, white);

  ostringstream expected;
  expected << "P3\n"
           << "1 1\n"
           << "255\n"
           << "255 255 255 \n";
  ostringstream actual;
  Image_print(img, actual);

  ASSERT_EQUAL(expected.str(), actual.str());

  delete img;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here

