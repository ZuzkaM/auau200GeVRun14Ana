#!/bin/bash

outFile=${1:-bgSelected1stIter.root}
root -l -b -q bgSelector/macros/loadBgSelector.C 'bgSelector/macros/runBgSelector.C++("/global/project/projectdirs/star/pwg/starhf/simkomir/LambdaC/bgSelectedAllStat.root","secondarySelected","'$outFile'")'

