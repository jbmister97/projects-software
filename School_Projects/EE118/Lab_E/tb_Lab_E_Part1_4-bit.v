`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   15:00:27 10/06/2015
// Design Name:   Lab_E_Part1_4
// Module Name:   C:/Users/Justin/Lab_E/tb_Lab_E_Part1_4-bit.v
// Project Name:  Lab_E
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Lab_E_Part1_4
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_Lab_E_Part1_4;

	// Inputs
	reg [3:0] A;
	reg [3:0] B;
	reg [0:0] Ci;

	// Outputs
	wire [3:0] Sum;
	wire Co;

	// Instantiate the Unit Under Test (UUT)
	Lab_E_Part1_4 uut (
		.A(A), 
		.B(B), 
		.Ci(Ci), 
		.Sum(Sum), 
		.Co(Co)
	);

	initial begin
		// Initialize Inputs
		A=4'd3;B=4'd6;Ci=1'b0;
		#10 A=4'd3;B=4'd5;Ci=1'b0;
		#10 A=4'd8;B=4'd8;Ci=1'b1;
		#10 A=4'd11;B=4'd7;Ci=1'b0;
		#10 A=4'd2;B=4'd9;Ci=1'b1;
		#10 A=4'd4;B=4'd1;Ci=1'b1;
		#10 A=4'd9;B=4'd5;Ci=1'b0;
		#10 A=4'd1;B=4'd6;Ci=1'b0;
		#10 A=4'd13;B=4'd14;Ci=1'b1;
		#10 A=4'd11;B=4'd12;Ci=1'b0;
		

		
		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
      
endmodule

