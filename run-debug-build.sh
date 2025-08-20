#! /bin/bash
WORKDIR=~/Tetris
cmake --build ${WORKDIR}/debug-build
cd ${WORKDIR}/debug-build/bin
./Tetris
cd -
