#!/bin/bash

# Forces a remake of assign4 executable
make -B 

# Run executable
assign4 500 >> REPORT.txt
assign4 1000 >> REPORT.txt
assign4 2000 >> REPORT.txt
