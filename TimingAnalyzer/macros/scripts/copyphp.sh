#!/bin/bash

dir=${1}

#echo is safegaurd check
#find ${dir} -mindepth 1 -type d -exec echo cp index.php {} \;

#cp index into all subs
find ${dir} -mindepth 0 -type d -exec cp index.php {} \;

#ln soft php into all subs
#find ${dir} -mindepth 1 -type d -exec ln -s index.php {} \;
