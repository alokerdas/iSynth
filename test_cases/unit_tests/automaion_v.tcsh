#!/usr/bin/tcsh -f

set script_dir = "$PWD"
set gatesToCheck = "$*"
if ($#gatesToCheck < 1) then
  echo "Usage ./automaion_v.tcsh gate_*"
  echo "Usage ./automaion_v.tcsh gate_11*"
  echo "Usage ./automaion_v.tcsh gate_123*"
  echo "Usage ./automaion_v.tcsh gate_1311"
  echo "Use * to run similar directories. For example gate_1* will run all the directories starting with gate_1"
  exit (1)
endif

set path=($HOME/projects/install/iverilog/bin $path)
set local_cmd = "./runme"
set default_cmd = "iverilog -S -tsynth *.v"
set synthlog = "synth.log"
set synthgold = "$synthlog.gold"
set fullog = "$script_dir/detailed.log"
set faillog = "$script_dir/fail.log"
set paslog = "$script_dir/pas.log"
rm -f $fullog $faillog $paslog

foreach gate ($gatesToCheck)
  if (-d $gate ) then
    cd $gate
    rm -f $synthlog
    echo "Running $gate..."
    echo "Running $gate..." >>& $fullog
    if (-e $local_cmd) then
      $local_cmd >>& $fullog
    else
      $default_cmd >>& $fullog
    endif
    if (-e $synthlog) then
      if (-z $synthlog) then
        echo "$gate did not run properly"
        echo "$gate did not run properly" >> $fullog
      else
        # iverilog ran correctly
        if (-e $synthgold) then
          diff $synthgold $synthlog >>& $fullog
          if ($status) then
            echo $gate FAIL
            echo $gate FAIL >> $faillog
          else
            echo $gate PASS
            echo $gate PASS >> $paslog
            rm -f $synthlog
          endif
        else
          # copy synth log to synth golden log
          mv $synthlog $synthgold
        endif
      endif
    else
      echo "$gate did not run properly"
      echo "$gate did not run properly" >> $fullog
      echo "$gate did not run properly" >> $faillog
    endif
    cd ..
  else
    echo "No directory, Skipping the $gate"
    echo "No directory, Skipping the $gate" >> $fullog
    echo "No directory, Skipping the $gate" >> $faillog
  endif
end
