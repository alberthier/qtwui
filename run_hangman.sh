#!/bin/sh
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./bin ./bin/hangman -p 8888 &
sleep 2
firefox http://localhost:8888
