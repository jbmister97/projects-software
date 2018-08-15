`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:05:29 09/17/2015 
// Design Name: 
// Module Name:    Lab_A_Exercise1 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module Lab_A_Exercise1(Y,A,B,C);

	output Y;
	input A,B,C;
	
	assign Y = (A&B) + (B&C) + (C&A);

endmodule
