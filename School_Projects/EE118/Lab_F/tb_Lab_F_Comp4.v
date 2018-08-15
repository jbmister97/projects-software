`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   14:17:43 10/20/2015
// Design Name:   Lab_F_Comp4
// Module Name:   C:/Users/Justin/Lab_F/tb_Lab_F_Comp4.v
// Project Name:  Lab_F
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Lab_F_Comp4
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_Lab_F_Comp4;

	// Inputs
	reg [3:0] A;
	reg [3:0] B;

	// Outputs
	wire G;
	wire E;
	wire L;

	// Instantiate the Unit Under Test (UUT)
	Lab_F_Comp4 uut (
		.A(A), 
		.B(B), 
		.G(G), 
		.E(E), 
		.L(L)
	);

	initial begin
		// Initialize Inputs
		A = 4'd9;B = 4'd4;
		#10 A = 4'd11;B = 4'd7;
		#10 A = 4'd1;B = 4'd1;
		#10 A = 4'd13;B = 4'd14;
		#10 A = 4'd6;B = 4'd9;
		#10 A = 4'd1;B = 4'd2;
		#10 A = 4'd3;B = 4'd3;
		
		


	end
      
endmodule

