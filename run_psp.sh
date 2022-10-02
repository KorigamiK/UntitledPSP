mkdir -p ./build/psp && \
cp -r ./res ./build/psp && \
cd ./build/psp && \
psp-cmake -DVERBOSE=1 -S ../.. -B . && \
make && \
PPSSPPSDL ./EBOOT.PBP && \
cd ../.. 