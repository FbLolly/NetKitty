#!/bin/bash

cat $1 | nc $2 6942 -q 0
