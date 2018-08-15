
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name Lab_F -dir "C:/Users/Justin/Lab_F/planAhead_run_3" -part xc7a100tcsg324-3
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "Lab_F_Comp4.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {Lab_F_Comp4.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set_property top Lab_F_Comp4 $srcset
add_files [list {Lab_F_Comp4.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc7a100tcsg324-3
