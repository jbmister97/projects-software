@echo off
set xv_path=F:\\Xilinx\\Vivado\\2016.2\\bin
call %xv_path%/xsim bubblesort_testbench_behav -key {Behavioral:sim_1:Functional:bubblesort_testbench} -tclbatch bubblesort_testbench.tcl -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0