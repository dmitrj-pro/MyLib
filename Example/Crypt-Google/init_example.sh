#!/bin/bash

export DPLibInclude=../..
export DPLibLib=$DPLibInclude/libdp.a
export make=make

$make -f Make $1
exit
