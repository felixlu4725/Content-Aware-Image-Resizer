#include <cassert>
#include "Image.h"
#include <string>

// REQUIREMENTS: Pointer 'img' must reference a valid Image object
//              Dimensions must be within predefined bounds
// MODIFIES: The Image object referenced by 'img'
// PURPOSE:  Configures the Image with specified width and height.
// NOTE:     No dynamic memory allocation (new/delete) should be used.
void Image_init(Image* img, int width, int height) {
  assert(width > 0 && width <= MAX_MATRIX_WIDTH);
  assert(height > 0 && height <= MAX_MATRIX_HEIGHT);
  img->width = width;
  img->height = height;
  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->green_channel, width, height);
  Matrix_init(&img->blue_channel, width, height);
}

// REQUIREMENTS: 'img' points to an Image
//               'is' provides a valid PPM image stream (no comments)
// MODIFIES: The Image object referenced by 'img'
// PURPOSE:  Reads a PPM image from the input stream and initializes 'img'
void Image_init(Image* img, std::istream& is) {
  std::string format;
  int width, height, max_value;
  is >> format >> width >> height >> max_value;
  Image_init(img, width, height);
  
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      is >> *Matrix_at(&img->red_channel, r, c)
         >> *Matrix_at(&img->green_channel, r, c)
         >> *Matrix_at(&img->blue_channel, r, c);
    }
  }
}

// REQUIREMENTS: 'img' is a properly initialized Image
// PURPOSE:  Outputs the Image to the given stream in PPM format
//           Uses required whitespace formatting.
void Image_print(const Image* img, std::ostream& os) {
  os << "P3\n";
  os << img->width << " " << img->height << "\n255\n";
  
  for (int r = 0; r < img->height; ++r) {
    for (int c = 0; c < img->width; ++c) {
      Pixel px = Image_get_pixel(img, r, c);
      os << px.r << " " << px.g << " " << px.b << " ";
    }
    os << "\n";
  }
}

// REQUIREMENTS: 'img' is a valid Image instance
// PURPOSE:  Retrieves the width of the Image.
int Image_width(const Image* img) {
  return img->width;
}

// REQUIREMENTS: 'img' is a valid Image instance
// PURPOSE:  Retrieves the height of the Image.
int Image_height(const Image* img) {
  return img->height;
}

// REQUIREMENTS: 'img' points to an initialized Image
//               'row' and 'column' are within valid bounds
// PURPOSE:  Returns the pixel at the specified position.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  assert(row >= 0 && row < img->height);
  assert(column >= 0 && column < img->width);
  
  return {
    *Matrix_at(&img->red_channel, row, column),
    *Matrix_at(&img->green_channel, row, column),
    *Matrix_at(&img->blue_channel, row, column)
  };
}

// REQUIREMENTS: 'img' is a valid Image instance
//               'row' and 'column' are within valid bounds
// MODIFIES: The Image at the specified location
// PURPOSE:  Updates the pixel at the given position.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  assert(row >= 0 && row < img->height);
  assert(column >= 0 && column < img->width);

  *Matrix_at(&img->red_channel, row, column) = color.r;
  *Matrix_at(&img->green_channel, row, column) = color.g;
  *Matrix_at(&img->blue_channel, row, column) = color.b;
}

// REQUIREMENTS: 'img' is a valid Image instance
// MODIFIES: Entire Image
// PURPOSE:  Fills the Image with the specified color.
void Image_fill(Image* img, Pixel color) {
  for (int r = 0; r < img->height; ++r) {
    for (int c = 0; c < img->width; ++c) {
      Image_set_pixel(img, r, c, color);
    }
  }
}
