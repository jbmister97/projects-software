`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   14:18:16 10/06/2015
// Design Name:   Lab_E_part1
// Module Name:   C:/Users/Justin/Lab_E/tb_Lab_E_part1.v
// Project Name:  Lab_E
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Lab_E_part1
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_Lab_E_part1;

	// Inputs
	reg A;
	reg B;
	reg Ci;

	// Outputs
	wire Sum;
	wire Co;

	// Instantiate the Unit Under Test (UUT)
	Lab_E_part1 uut (
		.A(A), 
		.B(B), 
		.Ci(Ci), 
		.Sum(Sum), 
		.Co(Co)
	);

	initial begin
		// Initialize Inputs
		A=1'b0; B=1'b0; Ci=1'b0;
		#10 A=1'b0; B=1'b0; Ci=1'b1;
		#10 A=1'b0; B=1'b1; Ci=1'b0;
		#10 A=1'b0; B=1'b1; Ci=1'b1;
		#10 A=1'b1; B=1'b0; Ci=1'b0;
		#10 A=1'b1; B=1'b0; Ci=1'b1;
		#10 A=1'b1; B=1'b1; Ci=1'b0;
		#10 A=1'b1; B=1'b1; Ci=1'b1;
		
		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
      
endmodule

