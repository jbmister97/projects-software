# 
# Synthesis run script generated by Vivado
# 

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
create_project -in_memory -part xc7a35tcpg236-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.cache/wt} [current_project]
set_property parent.project_path {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.xpr} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
read_ip -quiet {{c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.srcs/sources_1/ip/framebuffer/framebuffer.xci}}
set_property is_locked true [get_files {{c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.srcs/sources_1/ip/framebuffer/framebuffer.xci}}]

foreach dcp [get_files -quiet -all *.dcp] {
  set_property used_in_implementation false $dcp
}
read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]

synth_design -top framebuffer -part xc7a35tcpg236-1 -mode out_of_context

rename_ref -prefix_all framebuffer_

write_checkpoint -force -noxdef framebuffer.dcp

catch { report_utilization -file framebuffer_utilization_synth.rpt -pb framebuffer_utilization_synth.pb }

if { [catch {
  file copy -force {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.runs/framebuffer_synth_1/framebuffer.dcp} {c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.srcs/sources_1/ip/framebuffer/framebuffer.dcp}
} _RESULT ] } { 
  send_msg_id runtcl-3 error "ERROR: Unable to successfully create or copy the sub-design checkpoint file."
  error "ERROR: Unable to successfully create or copy the sub-design checkpoint file."
}

if { [catch {
  write_verilog -force -mode synth_stub {c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.srcs/sources_1/ip/framebuffer/framebuffer_stub.v}
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create a Verilog synthesis stub for the sub-design. This may lead to errors in top level synthesis of the design. Error reported: $_RESULT"
}

if { [catch {
  write_vhdl -force -mode synth_stub {c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.srcs/sources_1/ip/framebuffer/framebuffer_stub.vhdl}
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create a VHDL synthesis stub for the sub-design. This may lead to errors in top level synthesis of the design. Error reported: $_RESULT"
}

if { [catch {
  write_verilog -force -mode funcsim {c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.srcs/sources_1/ip/framebuffer/framebuffer_sim_netlist.v}
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create the Verilog functional simulation sub-design file. Post-Synthesis Functional Simulation with this file may not be possible or may give incorrect results. Error reported: $_RESULT"
}

if { [catch {
  write_vhdl -force -mode funcsim {c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.srcs/sources_1/ip/framebuffer/framebuffer_sim_netlist.vhdl}
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create the VHDL functional simulation sub-design file. Post-Synthesis Functional Simulation with this file may not be possible or may give incorrect results. Error reported: $_RESULT"
}

if {[file isdir {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.ip_user_files/ip/framebuffer}]} {
  catch { 
    file copy -force {{c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.srcs/sources_1/ip/framebuffer/framebuffer_stub.v}} {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.ip_user_files/ip/framebuffer}
  }
}

if {[file isdir {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.ip_user_files/ip/framebuffer}]} {
  catch { 
    file copy -force {{c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.srcs/sources_1/ip/framebuffer/framebuffer_stub.vhdl}} {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_8/EE178_Lab_8.ip_user_files/ip/framebuffer}
  }
}
