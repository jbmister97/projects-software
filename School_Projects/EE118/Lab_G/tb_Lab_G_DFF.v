`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   15:40:09 10/27/2015
// Design Name:   Lab_G_DFF
// Module Name:   C:/Users/Justin/Lab_G/tb_Lab_G_DFF.v
// Project Name:  Lab_G
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Lab_G_DFF
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_Lab_G_DFF;

	// Inputs
	reg clk;
	reg D;

	// Outputs
	wire Q;

	// Instantiate the Unit Under Test (UUT)
	Lab_G_DFF uut (
		.clk(clk), 
		.D(D), 
		.Q(Q)
	);

	initial begin
		// Initialize Inputs
		forever begin
		#5 clk = ~clk;
		end
	end
	initial begin
		clk = 0;
		#12 D = 0;
		#10 D = 1;
		#12 D = 0;
		#10 D = 1;
		#12 D = 0;
		#10 D = 1;
		#12 D = 0;
		#10 D = 1;

	end
	
      
endmodule

