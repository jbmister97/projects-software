`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   15:09:37 11/17/2015
// Design Name:   Lab_J
// Module Name:   C:/Users/Justin/Lab_J/tb_Lab_J.v
// Project Name:  Lab_J
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Lab_J
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_Lab_J;

	// Inputs
	reg clk;
	reg rst;
	reg x0;
	reg x1;

	// Outputs
	wire r0;
	wire y0;
	wire g0;
	wire r1;
	wire y1;
	wire g1;

	// Instantiate the Unit Under Test (UUT)
	Lab_J uut (
		.clk(clk), 
		.rst(rst), 
		.x0(x0), 
		.x1(x1), 
		.r0(r0), 
		.y0(y0), 
		.g0(g0), 
		.r1(r1), 
		.y1(y1), 
		.g1(g1)
	);

	initial begin
		#1 clk = 0;
	forever begin
		 #10 clk = ~clk;
		 end
	end


	initial begin
		// Initialize Inputs
		rst = 0;
		#20 rst = 1;
		#5 rst = 0;
		#100 x0 = 0;x1 = 0;
		#100 x0 = 0;x1 = 1;
		#100 x0 = 1;x1 = 0;
		#100 x0 = 1;x1 = 1;

	end
      
endmodule

