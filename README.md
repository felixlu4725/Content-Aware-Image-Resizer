Content-Aware Image Resizer
===========================
An advanced content-aware, image resizing program utilizing seam carving algorithm in C++ that allows image to be scaled without losing/distorting meaningful image landmarks. This is implemented according to the seam carving algorithm described in [Avidan & Shamir, 2007](http://graphics.cs.cmu.edu/courses/15-463/2007_fall/hw/proj2/imret.pdf) which finds the path of least energy density for removal by computing a energy matrix mapping to the image.

## Demo
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg)](https://youtu.be/6NcIJXTlugc?si=uzvCckZjN1mEtiLQ)

## Features

- **Seam Carving Algorithm**: Intelligently resizes images by removing or adding seams based on content importance.
- **Customizable Energy Functions**: Utilizes Sobel filtering for edge detection; easily extendable for custom energy functions.
- **Command-Line Interface**: Provides flexibility for batch processing and integration into workflows.
- **Visualization of Seam Removal**: Optionally displays the seam removal process for better understanding.

## Installation

### Prerequisites

- C++ compiler supporting C++11 standard
- openCV

### Building the Project

1. **Clone the repository**:

   ```bash
   git clone https://github.com/felixlu4725/Content-Aware-Image-Resizer.git
   cd Content-Aware-Image-Resizer
   ```

2. **Compile the code**:

   ```bash
   g++ -std=c++11 -o seam_carving main.cpp -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
   ```

   Ensure that OpenCV is correctly installed and linked.

## Usage

```bash
./seam_carving <input_image> <output_image> <new_width> <new_height> [display]
```

- `<input_image>`: Path to the input image file.
- `<output_image>`: Path to save the resized image.
- `<new_width>`: Desired width of the output image.
- `<new_height>`: Desired height of the output image.
- `[display]` (optional): Set to `1` to display the seam removal process; defaults to `0`.

### Example

```bash
./seam_carving input.jpg output.jpg 800 600 1
```

This command resizes `input.jpg` to 800x600 pixels and displays the seam removal process.

## How It Works

1. **Compute Energy Map**: Calculates the energy of each pixel using the Sobel operator to detect edges.
2. **Find Optimal Seams**: Applies dynamic programming to identify the seams with the lowest energy.
3. **Remove or Insert Seams**: Adjusts the image dimensions by removing or inserting seams based on the desired size.
4. **Output Processed Image**: Saves and optionally displays the resized image.





By Felix Lu <felixlu@umich.edu>
