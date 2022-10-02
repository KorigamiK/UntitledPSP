#!/bin/bash

mkdir -p build/psp &&
cd build/psp &&
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$PSPDEV/psp/share/pspdev.cmake -S ../../ -B . &&
make &&

if [[ $1 == "--package" ]]; then
    mkdir -p dist &&
    cp EBOOT.PBP dist/ &&
    cp -r res dist/ &&
    cp ../../README.md dist/ &&
    cp ../../LICENSE dist/ &&
    cp ../../CHANGELOG.md dist/ &&
    cd dist &&
    zip -r ../UNTITLED.$(date +%s).zip . &&
    cd .. &&
    rm -rf dist
fi
