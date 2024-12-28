rm -rf res/resources.o res/resources.h out/*
# make
# ./blastem/blastem out.bin
#dgen out.bin
docker run --rm -v $PWD:/m68k -t registry.gitlab.com/doragasu/docker-sgdk:v2.00
/Applications/Genesis\ Plus.app/Contents/MacOS/Genesis\ Plus out/rom.bin