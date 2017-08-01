##!/bin/bash 
##
## run test examples
#
#* test1.png
#* (58,147)
#* (19,33)
#* (58,100)
#* (100,100)
#* (122,60)
#*
#* test2.png
#* (90,140)
#* (58,100)
#* (100,100)
#* (164,72)
#* (122,98)
#*
#* test3.png
#* (58,100)
#* (100,100)
#* (156,103)
#*
#* test4.jpg pick your own points but, suggested interesting points:
#* (416,486)
#* (1510,640)
#* (1590,1940)
#* (2200,600)
#* (3300,1420) 
#
echo ./ImageAnalysisService AeolusTestImages/test1.png 58 147 $1
./ImageAnalysisService AeolusTestImages/test1.png 58 147 $1
echo ./ImageAnalysisService AeolusTestImages/test1.png 19 33 $1
./ImageAnalysisService AeolusTestImages/test1.png 19 33 $1
echo ./ImageAnalysisService AeolusTestImages/test1.png 58 100 $1
./ImageAnalysisService AeolusTestImages/test1.png 58 100 $1
echo ./ImageAnalysisService AeolusTestImages/test1.png 100 100 $1
./ImageAnalysisService AeolusTestImages/test1.png 100 100 $1
echo ./ImageAnalysisService AeolusTestImages/test1.png 122 60 $1
./ImageAnalysisService AeolusTestImages/test1.png 122 60 $1

echo ./ImageAnalysisService AeolusTestImages/test2.png 90 140 $1
./ImageAnalysisService AeolusTestImages/test2.png 90 140 $1
echo ./ImageAnalysisService AeolusTestImages/test2.png 58 100 $1
./ImageAnalysisService AeolusTestImages/test2.png 58 100 $1
echo ./ImageAnalysisService AeolusTestImages/test2.png 100 100 $1
./ImageAnalysisService AeolusTestImages/test2.png 100 100 $1
echo ./ImageAnalysisService AeolusTestImages/test2.png 164 72 $1
./ImageAnalysisService AeolusTestImages/test2.png 164 72 $1
echo ./ImageAnalysisService AeolusTestImages/test2.png 122 98 $1
./ImageAnalysisService AeolusTestImages/test2.png 122 98 $1

echo ./ImageAnalysisService AeolusTestImages/test3.png 58 100 $1
./ImageAnalysisService AeolusTestImages/test3.png 58 100 $1
echo ./ImageAnalysisService AeolusTestImages/test3.png 100 100 $1
./ImageAnalysisService AeolusTestImages/test3.png 100 100 $1
echo ./ImageAnalysisService AeolusTestImages/test3.png 156 103 $1
./ImageAnalysisService AeolusTestImages/test3.png 156 103 $1

echo ./ImageAnalysisService AeolusTestImages/test4.jpg 416 486 $1
./ImageAnalysisService AeolusTestImages/test4.jpg 416 486 $1
echo ./ImageAnalysisService AeolusTestImages/test4.jpg 1510 640 $1
./ImageAnalysisService AeolusTestImages/test4.jpg 1510 640 $1
echo ./ImageAnalysisService AeolusTestImages/test4.jpg 1590 1940 $1
./ImageAnalysisService AeolusTestImages/test4.jpg 1590 1940 $1
echo ./ImageAnalysisService AeolusTestImages/test4.jpg 2200 600 $1
./ImageAnalysisService AeolusTestImages/test4.jpg 2200 600 $1
echo ./ImageAnalysisService AeolusTestImages/test4.jpg 3300 1420 $1
./ImageAnalysisService AeolusTestImages/test4.jpg 3300 1420 $1



