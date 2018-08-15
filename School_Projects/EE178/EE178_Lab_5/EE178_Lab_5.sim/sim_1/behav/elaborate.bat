@echo off
set xv_path=F:\\Xilinx\\Vivado\\2016.2\\bin
call %xv_path%/xelab  -wto d26b6cff47584c8cb9a573d51f41dce1 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot bubblesort_testbench_behav xil_defaultlib.bubblesort_testbench xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0