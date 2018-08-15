`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:11:36 09/17/2015 
// Design Name: 
// Module Name:    Lab_A_Exercise2 
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
module Lab_A_Exercise2(Y,A,B,C);

	output Y;
	input A,B,C;
	
	assign Y = A*B*(~C) + (~C)*(~A)*(~B);

endmodule
