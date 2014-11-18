#!/bin/sh
export PATH=$PATH:/Users/GwonHyeok/Documents/android-ndk-r10c/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin
cd src
make clean
make
