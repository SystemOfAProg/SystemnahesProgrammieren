#!/usr/bin/env bash

cp ../../../cmake-build-debug/Parser/bin/Parser ./Parser

echo "======================================================================================";
echo "Parse every sourcefile located in ./src/ into ./bin/ as machine code";
echo "======================================================================================";
echo;

for src in ./src/*.txt; do
dst=${src%.txt};
dst=${dst:6};
echo "======================================================================================";
echo "Parse $src into ./bin/${dst}.code";
echo "======================================================================================";
./Parser "$src" "./bin/${dst}.code" ;
done

echo "======================================================================================";
echo "DONE";
echo "======================================================================================";

rm ./Parser