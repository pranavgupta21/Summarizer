#!/bin/bash

make txsm_clean
make txsm_install
./textrank < input
