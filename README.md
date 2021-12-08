# CSE701 Final Project: Generating world most expensive mosaic NFTs

## 1. Introduction
As Elon Musk recently on twitter said: "NFTs are jpeging the dollar." Then I thought, instead of jpeging the dollars, jepging the world most expensive painting in a flexible manner may be a good ideas to catch the NFT trend. So pictures look like this: ![](/supplementary_readme/Elon_Musk.jpg) can be transform to mosaic art by stacking the worlds most expensive paintings together: ![](/supplementary_readme/Elon_Musk_mosaic.jpg) where each of the small tile on the mosaic canvas is a compressed image of one of the world's most expensive painting. Not only Elon Musk, every single person can have a picture and transform it into the a mosaic based on the worlds most expensive paintings. ![](/supplementary_readme/other_mosaics.png)

This project is to generate such mosaic images for a pool of source input images and from the tile images, which are the jpeg pictures of the worlds most expensive painting. The data preprocessing part of the project as well as the visualization of the mosaic images are handled by [R](https://www.r-project.org/) in R Mark down (.rmd) files. The key computational part of matching tile image to the right spot of the source image is handle by C++.

## Program Structure

This programs contains 3 parts: 
- data preprocessing to LUV color space(handled by R)
- data processing and computation of the mosaic matching(handled by C++), 
- data visualization of mosaic image (handled by R)

This project is using [LUV color space](https://en.wikipedia.org/wiki/CIELUV) for color processing. The reason is discussed in [this thread](https://photo.stackexchange.com/questions/67933/when-to-use-luv-and-not-rgb-colourspaces). Basically LUV color space fully separate the greyscale, which is a good fit for matching mosaic since the grey scale could be different but the Euclidean distance based on color space in RGB maybe close. Therefore LUV color space is the best fit for mosaic image matching.

### Data preprocessing (User can Ignore this, just for preparing the data not run every time for the program)

For data preprocessing, when running the program, the **user can ignore this part** since it is preparing the some input for the program and need to be run only once. But basically, This part take care of transforming the source images in jpeg files in to C++ readable csv files by calculating the average color space in LUV color space format with files containing the color format information. For example, source image *[Barak Shoshany.jpg]* is transform to color space readable jpeg to *[Barak Shoshany_l.csv]*, *[Barak Shoshany_u.csv]*, and *[Barak Shoshany_v.csv]* and store in the folder *[sourceImage]*. For this project, for fairness, we are using a fixed sized 50x50 tile for processing the mosaic so that every image has the same number of tiles, which is fair for mosaic value comparison by adding all the values of the tile painting together as the value of the mosaic. Also for the input images, since the size of images are big, if using the original files to run the program, it will take too long to generate the final image in data visualization part (not necessary the C++ program, but the visualization of the mosaic will run for too long). Therefore, in the data preprocessing part, we resize the images all to 5x5 and put all the resized tile images in the folder *[paintings/tileimage_resize]*. It will not affect too much the file representation of mosaic and will decrease the time for visualizing the mosaic handled by R in the final part of the project(not C++)

### Computational part

For the C++ computation of the mosaic project, the program reads from the LUV color space file prepared by the data preprocessing part from source images and the LUV color space from the tile image in *[paintings_avg_color.csv]* for matching the mosaic and *[paintings.csv]* for getting other information of the tile images. The program uses points object for color space, [kd-tree](https://en.wikipedia.org/wiki/K-d_tree) object to hold for all the tile image for best computation search purpose. Algorithms like recursions on trees, quick select, and more are applied to change increase the computational performance of matching the best tile images. The output of all the mosaic information is in the folder *[outputImageCSV]*, where each of the file in the folder is a 50x50 table with each entry corresponds to the name of the painting. For visualizing the output CSV file based the order to stuck the tile images together and form the mosaic picture, the user should run the *[visualizing_output.rmd]* discussed in the next part.

### Visualization the mosaic

The final part of the project is visualization of the project, which is handle by *[visualizing_output.rmd]*. The R code uses some outsourced library to generate the jpeg for the mosaic in the *[outputImageCSV]*. The user should run the rmd file from start to end. The R will automatically delete all the previous files inside the folder and generate new jpg files based on the output from C++ program. 


## Input and Output


### Input

The user input of this program is in *[input.txt]*, where the user put the name of picture of the person in the file line by line. Due to the data is preprocess, **the user can only choose the names from preprocessed color spaces data in source images**. The input set contains **only 12** possible inputs (because the program pre-load color space information for 12 pictures):
```
Barak Shoshany
Bill Gates
Elon Musk
Haibo Gao
Jack Dorsey
Jack Ma
Jeff Bezos
Larry Ellison
Steve Jobs
Warren Buffett
Yao Ming
Yunfei Ma
```

otherwise, the program will through an error saying the input image does not exist.

The input from the programs are the csv files in *[sourceimage]* folder, *[paintings.csv]*, and *[paintings_avg_color.csv]*.

The files in folder *[paintings]* are used for visualizing the mosaic in part 3 by  *[visualizing_output.rmd]*. 

### Output

The output is in the folder *[outputImageCSV]*, where the csv files are storing 50x50 table of tile image names as the sequence of the mosaic images. For example:
```
Suprematist Composition,Suprematist Composition,Suprematist Composition,Suprematist Composition,.....
Suprematist Composition,Suprematist Composition,Suprematist Composition,Suprematist Composition,.....
.
.
.
.
```
(a 50x50 table)

For visualizing the output, run *[visualizing_output.rmd]* and the images of the mosaic in jpg format will be in folder *[outputImages]*.

## Sample Input and output


Sample input in *[input.txt]*:
```
Jack Ma
```

Sample output *[outputImageCSV/Jack Ma.csv]*:
```
Woman III,Suprematist Composition,Suprematist Composition,Suprematist Composition,......
Woman III,Suprematist Composition,Suprematist Composition,Suprematist Composition,......
.
.
.
.

```
(a 50x50 table)

Sample output visualization: ![](/supplementary_readme/Jack_Ma.jpg)

