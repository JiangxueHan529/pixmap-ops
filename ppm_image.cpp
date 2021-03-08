#include "ppm_image.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace agl;
using namespace std;

ppm_image::ppm_image() 
{
    wid = 0;
    hgt = 0;
    img = new ppm_pixel[0];
}

ppm_image::ppm_image(int w, int h) 
{
    wid = w;
    hgt = h;
    int total = w * h;
    img = new ppm_pixel[total];

}
//copy constructor 
ppm_image::ppm_image(const ppm_image& orig)
{
    wid = orig.wid;
    hgt = orig.hgt;
    int total = wid * hgt;
    img = new ppm_pixel[total];
    for (int i = 0; i < total;i++) {
        img[i] = orig.img[i];
    }
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{
   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }
   delete[] img;
   wid = orig.wid;
   hgt = orig.hgt;
   int total = wid * hgt;
   img = new ppm_pixel[total];
   for (int i = 0; i < total;i++) {
       img[i] = orig.img[i];
   }

   return *this;   
}

//destructor
ppm_image::~ppm_image()
{
    delete[] img;
}

bool ppm_image::load(const std::string& filename)
{
    ifstream file(filename.c_str());
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
    int total = row * col;
    delete[] img;
    ppm_pixel* imgArr = new ppm_pixel[total];
    for (int i = 0; i < total; i++) {
        int v; 
        file >> v;
        imgArr[i].r = (unsigned char)v;
        file >> v;
        imgArr[i].g = (unsigned char)v;
        file >> v;
        imgArr[i].b = (unsigned char)v;
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
    int total = wid * hgt;
    for (int i = 0;i < total; i++) {
        file << (int)img[i].r << " " << (int)img[i].g << " " << (int)img[i].b << " ";
    }
    file.close();
    return true;
}

 ppm_image ppm_image::resize(int w, int h) const
 {
     ppm_image result = ppm_image(w,h);
     for (int i = 0; i < h; i++) {
         for (int j = 0; j < w; j++) {
             result.img[i * w + j] = img[(int)(((float)i / (float)(h - 1)) * (hgt - 1)) * wid + (int)(((float)j / (float)(w - 1)) * (wid - 1))];
         }
     }
     return result;
}

ppm_image ppm_image::flip_horizontal() const
{
    ppm_image result = ppm_image(wid,hgt);
    for (int i = 0;i < hgt; i++) {
        for (int j = 0; j < wid;j++) {
            result.img[i * wid + j] = img[i * wid + (wid - j - 1)];
        }
    }
    return result;
}

ppm_image ppm_image::subimage(int startx, int starty, int w, int h) const
{
    ppm_image result = ppm_image(w,h);;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            result.img[i * w + j] = img[(starty + i) * wid + j + startx];
        }
    }
    return result;
}

void ppm_image::replace(const ppm_image& image, int startx, int starty)
{
    for (int i = starty; i < starty + image.hgt; i++) {
        for (int j = startx; j < startx + image.wid;j++) {
            img[i * wid + j] = image.img[(i - starty) * image.wid + j -startx];
        }
    }
}

ppm_image ppm_image::alpha_blend(const ppm_image& other, float alpha) const
{
   ppm_image result = ppm_image(wid,hgt);
   int total = wid * hgt;
   for (int i = 0; i < total;i++) {
       result.img[i].r = img[i].r * (1.0f - alpha) + other.img[i].r * alpha;
       result.img[i].g = img[i].g * (1.0f - alpha) + other.img[i].g * alpha;
       result.img[i].b = img[i].b * (1.0f - alpha) + other.img[i].b * alpha;
   }
   return result;
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
   ppm_image result = ppm_image(wid,hgt);
   int total = wid * hgt;
   for (int i = 0; i < total; i++) {
       result.img[i].r = (unsigned char)255*pow((float)img[i].r/255.0,  1.0/gamma);
       result.img[i].g = (unsigned char)255*pow((float)img[i].g/255.0, 1.0/gamma);
       result.img[i].b = (unsigned char)255*pow((float)img[i].b/255.0, 1.0/gamma);
   }
   return result;
}

ppm_image ppm_image::grayscale() const
{
    ppm_image result = ppm_image(wid, hgt);
    int total = wid * hgt;
    for (int i = 0; i < total; i++) {
        int answer = (int)((img[i].r * 0.3) + (img[i].g * 0.59) + (img[i].b * 0.11));
        result.img[i].r = (unsigned char)answer;
        result.img[i].g = (unsigned char)answer;
        result.img[i].b = (unsigned char)answer;
    }
   return result;
}

ppm_image ppm_image::swirl_color() const
{
    ppm_image result = ppm_image(wid, hgt);
    int total = wid * hgt;
    for (int i = 0; i < total;i++) {
        result.img[i].r = img[i].g;
        result.img[i].g = img[i].b;
        result.img[i].b = img[i].r;
    }
    return result;
}
ppm_image ppm_image::invert_color() const
{
    ppm_image result = ppm_image(wid, hgt);
    int total = wid * hgt;
    for (int i = 0; i < total;i++) {
        result.img[i].r = 255 - img[i].r;
        result.img[i].g = 255 - img[i].g;
        result.img[i].b = 255 - img[i].b;
    }
    return result;
}

ppm_image ppm_image::extract_green() const
{
    ppm_image result = ppm_image(wid, hgt);
    int total = wid * hgt;
    for (int i = 0; i < total;i++) {
        result.img[i].r = 0;
        result.img[i].g = img[i].g;
        result.img[i].b = 0;
    }
    return result;
}

ppm_image ppm_image::darkest(ppm_image other) const
{   
    ppm_image result = ppm_image(wid, hgt);
    int total = wid * hgt;
    for (int i = 0; i < total;i++) {
        result.img[i].r = min(img[i].r, other.img[i].r);
        result.img[i].g = min(img[i].g, other.img[i].g);
        result.img[i].b = min(img[i].b, other.img[i].b);
    }
    return result;

}

ppm_image ppm_image::lightest(ppm_image other) const
{
    ppm_image result = ppm_image(wid, hgt);
    int total = wid * hgt;
    for (int i = 0; i < total;i++) {
        result.img[i].r = max(img[i].r, other.img[i].r);
        result.img[i].g = max(img[i].g, other.img[i].g);
        result.img[i].b = max(img[i].b, other.img[i].b);
    }
    return result;
}

ppm_image ppm_image::blur() const
{
    ppm_image result = ppm_image(wid, hgt);
    for (int i = 0; i < hgt; i++) {
        for (int j = 0; j < wid; j++) {
            if (i == 0 || j == 0 || i == hgt - 1 || j == wid -1 ) {
                result.img[i * wid + j] = img[i * wid + j];
            }
            else {
                result.img[i*wid+j].r = (int)(img[i*wid+j].r+ img[i*wid + j+1].r + img[(i + 1)*wid +j].r + img[(i + 1) * wid + j + 1].r +
                    img[i * wid + j - 1].r + img[(i + 1) * wid + j - 1].r + img[(i-1)*wid + j].r + img[(i-1)*wid + j - 1].r + img[(i-1)*wid + j + 1].r) / 9;
                result.img[i * wid + j].g = (int)(img[i * wid + j].g + img[i * wid + j + 1].g + img[(i + 1) * wid + j].g + img[(i + 1) * wid + j + 1].g +
                    img[i * wid + j - 1].g + img[(i + 1) * wid + j - 1].g + img[(i - 1) * wid + j].g + img[(i - 1) * wid + j - 1].g + img[(i - 1) * wid + j + 1].g) / 9;
                result.img[i * wid + j].b = (int)(img[i * wid + j].b + img[i * wid + j + 1].b + img[(i + 1) * wid + j].b + img[(i + 1) * wid + j + 1].b +
                    img[i * wid + j - 1].b + img[(i + 1) * wid + j - 1].b + img[(i - 1) * wid + j].b + img[(i - 1) * wid + j - 1].b + img[(i - 1) * wid + j + 1].b) / 9;
            }
            }
    }
    return result;
}

ppm_pixel ppm_image::get(int row, int col) const
{
    if (row == 0) {
        return img[col];
    }
    return img[(row - 1)*wid + col];
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
    if (row == 0) {
        img[col] = c;
    }
    img[(row - 1) * wid + col] = c;
}

int ppm_image::height() const
{
   return hgt;
}

int ppm_image::width() const
{
   return wid;
}
