// Project UID af1f95f547e44c8ea88730dfb185559dmake

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "processing.h"

using namespace std;

int main(int argc, char *argv[]) {

    string input = argv[1];
    ifstream fin(input);
    if (!fin.is_open()) {
        cout << "ERROR: UNABLE TO OPEN FILE";
        return 1;
    }

    string output = argv[2];
    ofstream fout(output);

    int newWidth = atoi(argv[3]);
    
    Image *img = new Image;
    Image_init(img, fin);
    
    if (argc == 5) {
        int newHeight = atoi(argv[4]);
        if (!(newWidth > 0 && newWidth <= Image_width(img))
            || !(newHeight > 0 && newHeight <= Image_height(img))) {
            cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original" << endl;
            return 1;
        }
        seam_carve(img, newWidth, newHeight);
        Image_print(img, fout);
    }

    else if (argc == 4) {
        if (!(newWidth > 0 && newWidth <= Image_width(img))) {
            cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original" << endl;
            return 1;
        }
        seam_carve(img, newWidth, Image_height(img));
        Image_print(img, fout);
    }
    
    else    {
        cout << "ERROR: COMMAND LINE";
        return 1;
    }

    delete img;
    fin.close();
    return 0;
}
