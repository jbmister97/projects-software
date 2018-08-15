// Verilog test fixture created from schematic C:\Users\Justin\Lab_A\Lab_Aschematic.sch - Wed Sep 16 23:18:57 2015

`timescale 1ns / 1ps

module Lab_Aschematic_Lab_Aschematic_sch_tb();

// Inputs
   reg A;
   reg B;
   reg C;

// Output
   wire Y;

// Bidirs

// Instantiate the UUT
   Lab_Aschematic UUT (
		.A(A), 
		.B(B), 
		.C(C), 
		.Y(Y)
   );
// Initialize Inputs
		initial begin
		
			A = 0;B = 0;C = 0;
		#5 A = 0;B = 0;C = 1;
		#5 A = 0;B = 1;C = 0;
		#5 A = 0;B = 1;C = 1;
		#5 A = 1;B = 0;C = 0;
		#5 A = 1;B = 0;C = 1;
		#5 A = 1;B = 1;C = 0;
		#5 A = 1;B = 1;C = 1;
		end
endmodule
