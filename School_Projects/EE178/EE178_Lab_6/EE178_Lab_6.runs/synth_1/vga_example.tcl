# 
# Synthesis run script generated by Vivado
# 

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
create_project -in_memory -part xc7a35tcpg236-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.cache/wt} [current_project]
set_property parent.project_path {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.xpr} [current_project]
set_property XPM_LIBRARIES XPM_MEMORY [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
add_files -quiet {{c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.srcs/sources_1/ip/framebuffer/framebuffer.dcp}}
set_property used_in_implementation false [get_files {{c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.srcs/sources_1/ip/framebuffer/framebuffer.dcp}}]
read_verilog -library xil_defaultlib {
  {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.srcs/sources_1/imports/Lab #6 Files/vga_timing.v}
  {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.srcs/sources_1/imports/Lab #6 Files/linedraw.v}
  {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.srcs/sources_1/imports/Lab #6 Files/vga_example.v}
}
foreach dcp [get_files -quiet -all *.dcp] {
  set_property used_in_implementation false $dcp
}
read_xdc {{C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.srcs/constrs_1/imports/Lab #6 Files/vga_example.xdc}}
set_property used_in_implementation false [get_files {{C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.srcs/constrs_1/imports/Lab #6 Files/vga_example.xdc}}]


synth_design -top vga_example -part xc7a35tcpg236-1


write_checkpoint -force -noxdef vga_example.dcp

catch { report_utilization -file vga_example_utilization_synth.rpt -pb vga_example_utilization_synth.pb }
