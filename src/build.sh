#!/bin/sh
export PATH=$PATH:/Users/GwonHyeok/Desktop/android-ndk-r9d/toolchains/arm-linux-androideabi-4.8/prebuilt/darwin-x86_64/bin
make clean
make
adb wait
adb root
adb push ../bin/bnchat /data/data/com.hyeok.m16_chat_pt.app/files/
adb shell chmod 755 /data/data/com.hyeok.m16_chat_pt.app/files/bnchat
