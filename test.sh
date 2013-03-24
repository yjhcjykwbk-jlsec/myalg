#!/bin/sh
./gendata > 1.in
cat 1.in
cat 1.in | ./wrong 
cat 1.in | ./mubang
