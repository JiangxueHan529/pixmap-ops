# pixmap-ops

Image manipulation demos based on the PPM image format.

TODO: Add a representative image for your project here

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake -G "Visual Studio 16 2019" ..
pixmap-ops/build $ start Pixmap-Ops.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
pixmap-ops/build $ ../bin/Debug/pixmap_test
pixmap-ops/build $ ../bin/Debug/pixmap_art
```

*macOS*

Open terminal to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake ..
pixmap-ops/build $ make
```

To run each program from build, you would type

```
pixmap-ops/build $ ../bin/pixmap_test
pixmap-ops/build $ ../bin/pixmap_art
```

## Image operators
These are the additional methods I created for my ppm_image class: 

     //Return a copy of this image with swirled color
     ppm_image swirl_color() const;

     //Return a copy of this image with inverted color
     ppm_image invert_color() const;

     //Return a copy of image with extracted green channel
     ppm_image extract_green() const;


     //Get the lightest pixels from the two images
     ppm_image lightest(ppm_image other) const;

     //Get the darkest pixels from the two images
     ppm_image darkest(ppm_image other) const;

     //Return a copy of image blurred
     ppm_image blur() const;

## Results

https://github.com/JiangxueHan529/pixmap-ops/blob/main/unique_images/art-work-1.ppm

https://github.com/JiangxueHan529/pixmap-ops/blob/main/unique_images/art-work.ppm

https://github.com/JiangxueHan529/pixmap-ops/blob/main/unique_images/after-blur.ppm


