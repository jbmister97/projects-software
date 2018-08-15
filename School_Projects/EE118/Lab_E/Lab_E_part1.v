`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:01:00 10/06/2015 
// Design Name: 
// Module Name:    Lab_E_part1 
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
module Lab_E_part1(
    input A,
    input B,
    input Ci,
    output Sum,
    output Co
    );
	
	xor (w1, A, B);
	xor (Sum, w1, Ci);
	and (w2, w1, Ci);
	and (w3, A, B);
	or (Co, w2, w3);

endmodule
