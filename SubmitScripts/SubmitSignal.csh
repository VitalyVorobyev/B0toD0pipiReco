#!/bin/csh -f
set INDEX = 0
set EXP = $1
set MYPATH = $2

echo $2evtgen_exp_$1_b0tod0pipi-${INDEX}.mdst
while(-e $2evtgen_exp_$1_b0tod0pipi-${INDEX}.mdst)
  /gpfs/home/belle/vitaly/work/B0toD0pipi/SubmitScripts/SigMC.csh $EXP $MYPATH $INDEX > scripts/Sig$EXP-$INDEX.csh
  chmod 755 scripts/Sig$EXP-${INDEX}.csh
  bsub -q s scripts/Sig$EXP-${INDEX}.csh
  @ INDEX = $INDEX + 1
end

