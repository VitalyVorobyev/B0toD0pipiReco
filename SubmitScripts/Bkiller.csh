#!/bin/csh -f

@ job = 0
@ Njobs = 100
while($job < $Njobs)
 bkill -q $1
end 

