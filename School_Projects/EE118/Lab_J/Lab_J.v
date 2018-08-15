`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:39:32 11/17/2015 
// Design Name: 
// Module Name:    Lab_J 
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
module Lab_J(clk,rst,x0,x1,r0,y0,g0,r1,y1,g1);
	input clk,rst,x0,x1;
	output r0,y0,g0,r1,y1,g1;
	reg [1:0] st,nx_st;
	reg [4:0] count,upd_count;
	reg r0_0,y0_0,g0_0,r1_1,y1_1,g1_1;
	always@(posedge clk or posedge rst)
		begin
			if (rst)
				begin
				st <= 2'b00;
				count <= 5'd0;
				end
			else
				begin
				st <= nx_st;
				count <= upd_count;
				end
		end
	always@(*)
		begin
			upd_count = 5'd0;
			case(st)
				2'b00: begin
							if(x1)
								nx_st = 2'b01;
							else
								nx_st = 2'b00;
						 end
				2'b01: begin
							if(count >= 25)
								begin
									upd_count = 5'd0;
									nx_st = 2'b10;
								end
							else
								begin
									upd_count = count + 5'd1;
									nx_st = 2'b01;
								end
						 end
				2'b10: begin
							if(x0)
								nx_st = 2'b11;
							else
								nx_st = 2'b10;
						 end
				2'b11: begin
							if(count >= 25)
								begin
									upd_count = 5'd0;
									nx_st = 2'b00;
								end
							else
								begin
									upd_count = count + 5'd1;
									nx_st = 2'b11;
								end
							end
						endcase
				case(st)
					2'b00: begin
								g0_0 = 1'b1;
								y0_0 = 1'b0;
								r0_0 = 1'b0;
								g1_1 = 1'b0;
								y1_1 = 1'b0;
								r1_1 = 1'b1;
							 end
					2'b01: begin
								g0_0 = 1'b0;
								y0_0 = 1'b1;
								r0_0 = 1'b0;
								g1_1 = 1'b0;
								y1_1 = 1'b0;
								r1_1 = 1'b1;
							 end
					2'b10: begin
								g0_0 = 1'b0;
								y0_0 = 1'b0;
								r0_0 = 1'b1;
								g1_1 = 1'b1;
								y1_1 = 1'b0;
								r1_1 = 1'b0;
							 end
					2'b11: begin
								g0_0 = 1'b0;
								y0_0 = 1'b0;
								r0_0 = 1'b1;
								g1_1 = 1'b0;
								y1_1 = 1'b1;
								r1_1 = 1'b0;
							 end
					endcase
				end
		assign r0 = r0_0;
		assign y0 = y0_0;
		assign g0 = g0_0;
		assign r1 = r1_1;
		assign y1 = y1_1;
		assign g1 = g1_1;

endmodule
