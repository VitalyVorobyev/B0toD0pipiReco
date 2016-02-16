#!/bin/csh -f

set EXP = $1
set NRUNS = $2
set STEP = $3

set RS = 0
set RF = $STEP
@ RF = $RF - 1
while($RS < $NRUNS)
if($RS == 0) then
  set CSHFILE = 'scripts/Data_'$EXP'_1_'$RF'.csh'
  ./DataSkim.csh $EXP 1 $RF > $CSHFILE
else
  set CSHFILE = 'scripts/Data_'$EXP'_'$RS'_'$RF'.csh'
  ./DataSkim.csh $EXP $RS $RF > $CSHFILE
endif

chmod 755 $CSHFILE
bsub -q b_a './'$CSHFILE

@ RS = $RS + $STEP
@ RF = $RF + $STEP

end

