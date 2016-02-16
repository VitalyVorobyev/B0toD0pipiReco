#!/bin/csh -f

set EXP = $1
set NRUNS = $2
set STEP = $3

set RS = 0
set RF = $STEP
@ RF = $RF - 1
while($RS < $NRUNS)
if($RS == 0) then
  set CSHFILE = 'scripts/DataNT_'$EXP'_1_'$RF'.csh'
  ./DataNT.csh $EXP 1 $RF > $CSHFILE
else
  set CSHFILE = 'scripts/DataNT_'$EXP'_'$RS'_'$RF'.csh'
  ./DataNT.csh $EXP $RS $RF > $CSHFILE
endif

chmod 755 $CSHFILE
bsub -q l './'$CSHFILE

@ RS = $RS + $STEP
@ RF = $RF + $STEP

end

