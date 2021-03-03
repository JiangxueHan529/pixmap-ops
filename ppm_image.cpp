#include "ppm_image.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace agl;
using namespace std;

ppm_image::ppm_image() 
{
}

ppm_image::ppm_image(int w, int h) 
{
    wid = w;
    hgt = h;

}
//copy constructor 
ppm_image::ppm_image(const ppm_image& orig)
{
    wid = orig.wid;
    hgt = orig.hgt;
    img = orig.img;
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{
   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }

   wid = orig.wid;
   hgt = orig.hgt;
   img = orig.img;

   return *this;   
}

//destructor
ppm_image::~ppm_image()
{
    delete img;
}

bool ppm_image::load(const std::string& filename)
{
    ifstream file(filename);
    if (!file) // true if the file is valid
    {
        cout << "Cannot load file: " << filename << endl;
        return false;
    }
    string imgtype;
    int col;
    int row;
    int max;
    file >> imgtype;
    file >> col;
    file >> row;
    file >> max;
    wid = col;
    hgt = row;
    ppm_pixel* imgArr = new ppm_pixel[row*col];
    for (int i = 0; i < row * col; i++) {
        unsigned char r, g, b;
        file >> r;
        file >> g;
        file >> b;
        imgArr[i] = ppm_pixel{ r,g,b };
    }
    img = imgArr;
    file.close();
    return true;
}

bool ppm_image::save(const std::string& filename) const
{
    ofstream file(filename);
    if (!file) // true if the file is valid
    {
        cout << "Cannot open file: " << filename << endl;
        return false;
    }
    file << "P3" << endl;
    file << wid << " " << hgt << endl;
    file << "255" << endl;
    for (int i = 0;i < wid * hgt; i++) {
        file << img[i].r << " " << img[i].g << " " << img[i].b << " ";
    }
    file.close();
    return true;
}

 ppm_image ppm_image::resize(int w, int h) const
{
    ppm_image result;
    return result;
}

ppm_image ppm_image::flip_horizontal() const
{
    ppm_image result;
    return result;
}

ppm_image ppm_image::subimage(int startx, int starty, int w, int h) const
{
    ppm_image result;
    return result;
}

void ppm_image::replace(const ppm_image& image, int startx, int starty)
{
}

ppm_image ppm_image::alpha_blend(const ppm_image& other, float alpha) const
{
   ppm_image result;
   return result;
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
   ppm_image result;
   return result;
}

ppm_image ppm_image::grayscale() const
{
   ppm_image result;
   return result;
}

ppm_pixel ppm_image::get(int row, int col) const
{
   return ppm_pixel{ 0,0,0 };
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
}

int ppm_image::height() const
{
   return hgt;
}

int ppm_image::width() const
{
   return wid;
}
