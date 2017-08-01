#!/bin/bash
#
# run test examples
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
echo ./ImageAnalysisService AeolusTestImages/test1.png 58 147 $*
./ImageAnalysisService AeolusTestImages/test1.png 58 147 $*
echo ./ImageAnalysisService AeolusTestImages/test1.png 19 33 $*
./ImageAnalysisService AeolusTestImages/test1.png 19 33 $*
echo ./ImageAnalysisService AeolusTestImages/test1.png 58 100 $*
./ImageAnalysisService AeolusTestImages/test1.png 58 100 $*
echo ./ImageAnalysisService AeolusTestImages/test1.png 100 100 $*
./ImageAnalysisService AeolusTestImages/test1.png 100 100 $*
echo ./ImageAnalysisService AeolusTestImages/test1.png 122 60 $*
./ImageAnalysisService AeolusTestImages/test1.png 122 60 $*

echo ./ImageAnalysisService AeolusTestImages/test2.png 90 140 $*
./ImageAnalysisService AeolusTestImages/test2.png 90 140 $*
echo ./ImageAnalysisService AeolusTestImages/test2.png 58 100 $*
./ImageAnalysisService AeolusTestImages/test2.png 58 100 $*
echo ./ImageAnalysisService AeolusTestImages/test2.png 100 100 $*
./ImageAnalysisService AeolusTestImages/test2.png 100 100 $*
echo ./ImageAnalysisService AeolusTestImages/test2.png 164 72 $*
./ImageAnalysisService AeolusTestImages/test2.png 164 72 $*
echo ./ImageAnalysisService AeolusTestImages/test2.png 122 98 $*
./ImageAnalysisService AeolusTestImages/test2.png 122 98 $*

echo ./ImageAnalysisService AeolusTestImages/test3.png 58 100 $*
./ImageAnalysisService AeolusTestImages/test3.png 58 100 $*
echo ./ImageAnalysisService AeolusTestImages/test3.png 100 100 $*
./ImageAnalysisService AeolusTestImages/test3.png 100 100 $*
echo ./ImageAnalysisService AeolusTestImages/test3.png 156 103 $*
./ImageAnalysisService AeolusTestImages/test3.png 156 103 $*

echo ./ImageAnalysisService AeolusTestImages/test4.jpg 416 486 $*
./ImageAnalysisService AeolusTestImages/test4.jpg 416 486 $*
echo ./ImageAnalysisService AeolusTestImages/test4.jpg 1510 640 $*
./ImageAnalysisService AeolusTestImages/test4.jpg 1510 640 $*
echo ./ImageAnalysisService AeolusTestImages/test4.jpg 1590 1940 $*
./ImageAnalysisService AeolusTestImages/test4.jpg 1590 1940 $*
echo ./ImageAnalysisService AeolusTestImages/test4.jpg 2200 600 $*
./ImageAnalysisService AeolusTestImages/test4.jpg 2200 600 $*
echo ./ImageAnalysisService AeolusTestImages/test4.jpg 3300 1420 $*
./ImageAnalysisService AeolusTestImages/test4.jpg 3300 1420 $*



