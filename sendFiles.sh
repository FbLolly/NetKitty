#!/bin/bash

cat $1 | netcat $2 6942069 -q 0
