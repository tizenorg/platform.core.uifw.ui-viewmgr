#!/bin/bash

patch_cpp=`dirname $0`/cpplint_tizen_160520.py

# check rule to cpp
for i in `find $1 -name "*.cpp"`
do
python $patch_cpp $i
done

# check rule to header
for i in `find $1 -name "*.h"`
do
python $patch_cpp $i
done
