----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    22:59:31 09/16/2015 
-- Design Name: 
-- Module Name:    Lab_A_Verilog - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
module Lab_A_Verilog(Y,A,B,C);
output Y;
input A,B,C;

assign Y = (A&(~B)) + (B&C);

endmodule

