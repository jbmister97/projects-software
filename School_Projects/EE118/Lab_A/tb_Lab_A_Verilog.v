`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   00:01:14 09/17/2015
// Design Name:   Lab_A_Verilog
// Module Name:   C:/Users/Justin/Lab_A/tb_Lab_A_Verilog.v
// Project Name:  Lab_A
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Lab_A_Verilog
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_Lab_A_Verilog;

	// Inputs
	reg A;
	reg B;
	reg C;

	// Outputs
	wire Y;

	// Instantiate the Unit Under Test (UUT)
	Lab_A_Verilog uut (
		.Y(Y), 
		.A(A), 
		.B(B), 
		.C(C)
	);

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

