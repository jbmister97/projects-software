`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:09:18 10/20/2015 
// Design Name: 
// Module Name:    Lab_F_Comp4 
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
module Lab_F_Comp4(A,B,G,E,L);

    input [3:0] A;
    input [3:0] B;
    output G;
    output E;
    output L;
	 
assign G = (A>B) ? 1'b1:1'b0;
assign L = (A<B) ? 1'b1:1'b0;
assign E = (A==B) ? 1'b1:1'b0;

endmodule
