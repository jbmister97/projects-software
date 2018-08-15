`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:59:32 10/06/2015 
// Design Name: 
// Module Name:    Lab_E_Part1_4-bit 
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
module Lab_E_Part1_4(
    input [3:0] A,
    input [3:0] B,
    input  [0:0] Ci,
    output [3:0] Sum,
    output [0:0] Co
    );

Lab_E_part1 uut0 (
		.A(A[0]), 
		.B(B[0]), 
		.Ci(Ci), 
		.Sum(Sum[0]), 
		.Co(w0)
	);

Lab_E_part1 uut1 (
		.A(A[1]), 
		.B(B[1]), 
		.Ci(w0), 
		.Sum(Sum[1]), 
		.Co(w1)
	);

Lab_E_part1 uut2 (
		.A(A[2]), 
		.B(B[2]), 
		.Ci(w1), 
		.Sum(Sum[2]), 
		.Co(w2)
	);

Lab_E_part1 uut3 (
		.A(A[3]), 
		.B(B[3]), 
		.Ci(w2), 
		.Sum(Sum[3]), 
		.Co(Co)
	);

endmodule
