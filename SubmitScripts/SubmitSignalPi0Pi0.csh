#!/bin/csh -f
set INDEX = 0
set EXP = $1
set MYPATH = $2

echo $2evtgen_exp_$1_b0tod0pi0pi0-${INDEX}.mdst
while(-e $2evtgen_exp_$1_b0tod0pi0pi0-${INDEX}.mdst)
  ./SigMCPi0Pi0.csh $EXP $MYPATH $INDEX > scripts/SigPi0Pi0$EXP-$INDEX.csh
  chmod 755 scripts/SigPi0Pi0$EXP-${INDEX}.csh
  bsub -q s scripts/SigPi0Pi0$EXP-${INDEX}.csh
  @ INDEX = $INDEX + 1
end

