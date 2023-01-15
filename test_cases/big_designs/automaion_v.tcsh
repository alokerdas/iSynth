#!/usr/bin/tcsh -f

set script_dir = "$PWD"
set rulesToCheck = "$*"
if ($#rulesToCheck < 1) then
  echo "Usage ./automaion_v.tcsh rule_*"
  echo "Usage ./automaion_v.tcsh rule_11*"
  echo "Usage ./automaion_v.tcsh rule_123*"
  echo "Usage ./automaion_v.tcsh rule_1311"
  echo "Use * to run similar directories. For example rule_1* will run all the directories starting with rule_1"
  exit (1)
endif

set path=($HOME/projects/install/iverilog/bin $path)
set local_cmd = "./runme"
set default_cmd = "iverilog -tlint *.v"
set lintlog = "lint.log"
set lintgold = "$lintlog.gold"
set fullog = "$script_dir/detailed.log"
set faillog = "$script_dir/fail.log"
set paslog = "$script_dir/pas.log"
rm -f $fullog $faillog $paslog

foreach rule ($rulesToCheck)
  if (-d $rule ) then
    cd $rule
    rm -f $lintlog
    echo "Running $rule..."
    echo "Running $rule..." >>& $fullog
    if (-e $local_cmd) then
      $local_cmd >>& $fullog
    else
      $default_cmd >>& $fullog
    endif
    if (-e $lintlog) then
      set var = `echo $rule | cut -d '_'  -f 2`
      set var = `echo $var | cut -d '/'  -f 1`
      grep "Violated $var" $lintlog >>& $fullog
      if ($status) then
        echo $rule FAIL FOR NO MESSAGE
        echo $rule FAIL FOR NO MESSAGE >> $faillog
      else
        if (-z $lintlog) then
          echo "$rule did not run properly"
          echo "$rule did not run properly" >> $fullog
        else
          # iverilog ran correctly
          if (-e $lintgold) then
            diff $lintgold $lintlog >>& $fullog
            if ($status) then
              echo $rule FAIL
              echo $rule FAIL >> $faillog
            else
              echo $rule PASS
              echo $rule PASS >> $paslog
              rm -f $lintlog
            endif
          else
            # copy lint log to lint golden log
            mv $lintlog $lintgold
          endif
        endif
      endif
    else
      echo "$rule did not run properly"
      echo "$rule did not run properly" >> $fullog
      echo "$rule did not run properly" >> $faillog
    endif
    cd ..
  else
    echo "No directory, Skipping the $rule"
    echo "No directory, Skipping the $rule" >> $fullog
    echo "No directory, Skipping the $rule" >> $faillog
  endif
end
