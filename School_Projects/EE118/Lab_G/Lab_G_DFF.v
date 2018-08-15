`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:26:33 10/27/2015 
// Design Name: 
// Module Name:    Lab_G_DFF 
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
module Lab_G_DFF(clk,D,Q);
	input D,clk;
	output Q;
	reg Q_;
	assign Q = Q_;
	always@(posedge clk)
	begin
	Q_ <= D; // Q_ gets the value of D (non-blocking)
	end


endmodule
