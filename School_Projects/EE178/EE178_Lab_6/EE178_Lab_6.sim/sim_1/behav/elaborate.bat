@echo off
set xv_path=F:\\Xilinx\\Vivado\\2016.2\\bin
call %xv_path%/xelab  -wto 6b2b52a0fb714914b684a508b73e0404 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L xpm -L blk_mem_gen_v8_3_3 -L unisims_ver -L unimacro_ver -L secureip --snapshot testbench_behav xil_defaultlib.testbench xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
