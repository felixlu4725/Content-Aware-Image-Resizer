#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include "Matrix.h"

// Struct representing an RGB pixel with red, green, and blue components.
struct Pixel {
  int r;
  int g;
  int b;
};

const int MAX_INTENSITY = 255;

// Struct representing a 2D RGB image with three color matrices.
struct Image {
  int width;
  int height;
  Matrix red_channel;
  Matrix green_channel;
  Matrix blue_channel;
};

// REQUIREMENTS: 'img' is a valid pointer to an Image
//               Dimensions must be within allowed range
// MODIFIES: Image object referenced by 'img'
// PURPOSE:  Initializes an Image with the given dimensions.
void Image_init(Image* img, int width, int height);

// REQUIREMENTS: 'img' points to a valid Image
//               'is' is an input stream containing a PPM image (without comments)
// MODIFIES: Image object referenced by 'img'
// PURPOSE:  Reads a PPM image from the input stream and initializes 'img'.
void Image_init(Image* img, std::istream& is);

// REQUIREMENTS: 'img' points to a valid Image
// MODIFIES: The provided output stream
// PURPOSE:  Outputs the Image as a PPM-formatted stream with required spacing.
void Image_print(const Image* img, std::ostream& os);

// REQUIREMENTS: 'img' is a valid Image instance
// PURPOSE:  Retrieves the width of the Image.
int Image_width(const Image* img);

// REQUIREMENTS: 'img' is a valid Image instance
// PURPOSE:  Retrieves the height of the Image.
int Image_height(const Image* img);

// REQUIREMENTS: 'img' is a valid Image instance
//               'row' and 'column' are within bounds
// PURPOSE:  Retrieves the pixel at the specified position.
Pixel Image_get_pixel(const Image* img, int row, int column);

// REQUIREMENTS: 'img' is a valid Image instance
//               'row' and 'column' are within bounds
// MODIFIES: The specified pixel in the Image
// PURPOSE:  Updates the pixel at the given position.
void Image_set_pixel(Image* img, int row, int column, Pixel color);

// REQUIREMENTS: 'img' is a valid Image instance
// MODIFIES: Entire Image
// PURPOSE:  Fills the Image with the specified color.
void Image_fill(Image* img, Pixel color);

#endif // IMAGE_H
