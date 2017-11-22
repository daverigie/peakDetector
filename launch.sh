#!/usr/bin/env sh
docker run --rm -w "/home/" -v $PWD:/home/ -it "alpine-gxx" /bin/sh 