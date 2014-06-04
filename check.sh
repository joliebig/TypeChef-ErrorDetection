#!/bin/bash

cfile=$1
dbgfile=`basename $cfile .c`.dbg

../TypeChef/typechef.sh --bdd -x CONFIG_ --writePI -A deadstore -A cfginnonvoidfunction -A doublefree -A xfree -A casetermination \
                        -A danglingswitchcode -A checkstdlibfuncreturn -A uninitializedmemory -c redhat.properties $cfile >> $dbgfile 2>&1
