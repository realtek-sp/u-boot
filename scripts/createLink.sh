#!/bin/sh
rm -rf ./board/realtek/rlxboard
rm -rf ./ram_init/*
rm -f ./include/configs/rlxboard.h
rm -f ./include/configs/bspchip.h

ln -s -r ./board/realtek/rts3917 ./board/realtek/rlxboard

ln -s -r ./board/realtek/rlxboard/rlxboard.h ./include/configs/rlxboard.h
ln -s -r ./board/realtek/rlxboard/bspchip.h ./include/configs/bspchip.h

