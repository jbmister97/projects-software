proc start_step { step } {
  set stopFile ".stop.rst"
  if {[file isfile .stop.rst]} {
    puts ""
    puts "*** Halting run - EA reset detected ***"
    puts ""
    puts ""
    return -code error
  }
  set beginFile ".$step.begin.rst"
  set platform "$::tcl_platform(platform)"
  set user "$::tcl_platform(user)"
  set pid [pid]
  set host ""
  if { [string equal $platform unix] } {
    if { [info exist ::env(HOSTNAME)] } {
      set host $::env(HOSTNAME)
    }
  } else {
    if { [info exist ::env(COMPUTERNAME)] } {
      set host $::env(COMPUTERNAME)
    }
  }
  set ch [open $beginFile w]
  puts $ch "<?xml version=\"1.0\"?>"
  puts $ch "<ProcessHandle Version=\"1\" Minor=\"0\">"
  puts $ch "    <Process Command=\".planAhead.\" Owner=\"$user\" Host=\"$host\" Pid=\"$pid\">"
  puts $ch "    </Process>"
  puts $ch "</ProcessHandle>"
  close $ch
}

proc end_step { step } {
  set endFile ".$step.end.rst"
  set ch [open $endFile w]
  close $ch
}

proc step_failed { step } {
  set endFile ".$step.error.rst"
  set ch [open $endFile w]
  close $ch
}

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000

start_step init_design
set rc [catch {
  create_msg_db init_design.pb
  set_property design_mode GateLvl [current_fileset]
  set_param project.singleFileAddWarning.threshold 0
  set_property webtalk.parent_dir {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.cache/wt} [current_project]
  set_property parent.project_path {C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.xpr} [current_project]
  set_property ip_repo_paths {{c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.cache/ip}} [current_project]
  set_property ip_output_repo {{c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.cache/ip}} [current_project]
  set_property XPM_LIBRARIES XPM_MEMORY [current_project]
  add_files -quiet {{C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.runs/synth_1/vga_example.dcp}}
  add_files -quiet {{c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.srcs/sources_1/ip/framebuffer/framebuffer.dcp}}
  set_property netlist_only true [get_files {{c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.srcs/sources_1/ip/framebuffer/framebuffer.dcp}}]
  read_xdc -mode out_of_context -ref framebuffer -cells U0 {{c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.srcs/sources_1/ip/framebuffer/framebuffer_ooc.xdc}}
  set_property processing_order EARLY [get_files {{c:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.srcs/sources_1/ip/framebuffer/framebuffer_ooc.xdc}}]
  read_xdc {{C:/Users/Justin/Documents/4th School Year/Fall 2016 Semester/EE178/Vivado Projects/EE178_Lab_6/EE178_Lab_6.srcs/constrs_1/imports/Lab #6 Files/vga_example.xdc}}
  link_design -top vga_example -part xc7a35tcpg236-1
  write_hwdef -file vga_example.hwdef
  close_msg_db -file init_design.pb
} RESULT]
if {$rc} {
  step_failed init_design
  return -code error $RESULT
} else {
  end_step init_design
}

start_step opt_design
set rc [catch {
  create_msg_db opt_design.pb
  opt_design 
  write_checkpoint -force vga_example_opt.dcp
  report_drc -file vga_example_drc_opted.rpt
  close_msg_db -file opt_design.pb
} RESULT]
if {$rc} {
  step_failed opt_design
  return -code error $RESULT
} else {
  end_step opt_design
}

start_step place_design
set rc [catch {
  create_msg_db place_design.pb
  implement_debug_core 
  place_design 
  write_checkpoint -force vga_example_placed.dcp
  report_io -file vga_example_io_placed.rpt
  report_utilization -file vga_example_utilization_placed.rpt -pb vga_example_utilization_placed.pb
  report_control_sets -verbose -file vga_example_control_sets_placed.rpt
  close_msg_db -file place_design.pb
} RESULT]
if {$rc} {
  step_failed place_design
  return -code error $RESULT
} else {
  end_step place_design
}

start_step route_design
set rc [catch {
  create_msg_db route_design.pb
  route_design 
  write_checkpoint -force vga_example_routed.dcp
  report_drc -file vga_example_drc_routed.rpt -pb vga_example_drc_routed.pb
  report_timing_summary -warn_on_violation -max_paths 10 -file vga_example_timing_summary_routed.rpt -rpx vga_example_timing_summary_routed.rpx
  report_power -file vga_example_power_routed.rpt -pb vga_example_power_summary_routed.pb -rpx vga_example_power_routed.rpx
  report_route_status -file vga_example_route_status.rpt -pb vga_example_route_status.pb
  report_clock_utilization -file vga_example_clock_utilization_routed.rpt
  close_msg_db -file route_design.pb
} RESULT]
if {$rc} {
  step_failed route_design
  return -code error $RESULT
} else {
  end_step route_design
}

start_step write_bitstream
set rc [catch {
  create_msg_db write_bitstream.pb
  catch { write_mem_info -force vga_example.mmi }
  write_bitstream -force vga_example.bit 
  catch { write_sysdef -hwdef vga_example.hwdef -bitfile vga_example.bit -meminfo vga_example.mmi -file vga_example.sysdef }
  catch {write_debug_probes -quiet -force debug_nets}
  close_msg_db -file write_bitstream.pb
} RESULT]
if {$rc} {
  step_failed write_bitstream
  return -code error $RESULT
} else {
  end_step write_bitstream
}

