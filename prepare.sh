#!/bin/sh

if [ ! -e systems ];
then
    wget http://www.cs.cmu.edu/~ckaestne/tmp/includes-redhat.tar.bz2
    mkdir -p systems/redhat
    tar xjf includes-redhat.tar.bz2 -C ./systems/redhat
    mv includes-redhat.tar.bz2 systems
fi
