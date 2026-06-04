#!/bin/sh

set -e

./Gauss_main AB.csv > result.csv
cmp result.csv expected.csv
echo "Integration test passed"
