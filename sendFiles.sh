#!/bin/bash

cat $1 | netcat $2 6942 -q 0
