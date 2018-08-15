// Verilog test fixture created from schematic C:\Users\Justin\Lab_B\Lab_B_Schematic.sch - Tue Sep 22 15:11:59 2015

`timescale 1ns / 1ps

module Lab_B_Schematic_Lab_B_Schematic_sch_tb();

// Inputs
   reg A;
   reg B;
   reg C;

// Output
   wire Y;

// Bidirs

// Instantiate the UUT
   Lab_B_Schematic UUT (
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
