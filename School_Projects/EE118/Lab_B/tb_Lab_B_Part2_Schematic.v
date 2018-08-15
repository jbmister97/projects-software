// Verilog test fixture created from schematic C:\Users\Justin\Lab_B\Lab_B_Part2_Schematic.sch - Mon Sep 28 21:55:54 2015

`timescale 1ns / 1ps

module Lab_B_Part2_Schematic_Lab_B_Part2_Schematic_sch_tb();

// Inputs
   reg A;
   reg B;
   reg C;
   reg D;

// Output
   wire M;
   wire U;
   wire T;

// Bidirs

// Instantiate the UUT
   Lab_B_Part2_Schematic UUT (
		.A(A), 
		.B(B), 
		.C(C), 
		.D(D), 
		.M(M), 
		.U(U), 
		.T(T)
   );
// Initialize Inputs
       initial begin
		A = 0;B = 0;C = 0;D = 0;
		#5 A = 0;B = 0;C = 0;D = 1;
		#5 A = 0;B = 0;C = 1;D = 0;
		#5 A = 0;B = 0;C = 1;D = 1;
		#5 A = 0;B = 1;C = 0;D = 0;
		#5 A = 0;B = 1;C = 0;D = 1;
		#5 A = 0;B = 1;C = 1;D = 0;
		#5 A = 0;B = 1;C = 1;D = 1;
		#5 A = 1;B = 0;C = 0;D = 0;
		#5 A = 1;B = 0;C = 0;D = 1;
		#5 A = 1;B = 0;C = 1;D = 0;
		#5 A = 1;B = 0;C = 1;D = 1;
		#5 A = 1;B = 1;C = 0;D = 0;
		#5 A = 1;B = 1;C = 0;D = 1;
		#5 A = 1;B = 1;C = 1;D = 0;
		#5 A = 1;B = 1;C = 1;D = 1;
		
		
   end
endmodule
