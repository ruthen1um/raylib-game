#!/usr/bin/env sh
make game CXXFLAGS="-Wall" LDFLAGS="-L/home/ruthen1um/repo/quasi-msys2/root/ucrt64/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -static"
