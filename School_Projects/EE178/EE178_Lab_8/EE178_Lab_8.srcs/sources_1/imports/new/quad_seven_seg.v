// File: quad_seven_seg.v
// This is the top level design for EE178 Lab #2.
// The `timescale directive specifies what the
// simulation time units are (1 ns here) and what
// the simulator time step should be (1 ps here).
`timescale 1 ns / 1 ps
// Declare the module and its ports. This is
// using Verilog-2001 syntax.
module quad_seven_seg (
input wire clk,
input wire [3:0] val3,
input wire dot3,
input wire [3:0] val2,
input wire dot2,
input wire [3:0] val1,
input wire dot1,
input wire [3:0] val0,
input wire dot0,
output reg an3,
output reg an2,
output reg an1,
output reg an0,
output reg ca,
output reg cb,
output reg cc,
output reg cd,
output reg ce,
output reg cf,
output reg cg,
output reg dp
);
// Describe the actual circuit for the assignment.
reg [3:0] dummy;
reg [14:0] count;
reg [1:0] count2;
initial count = 0;
initial count2 = 0;

always@(posedge clk)
    begin
        if(count == 20000) 
            begin
            count <= 15'd0; // reset count
            count2 <= count2 + 2'd1; // add to count2 after 20000 cycles
            end
        else
            begin
            count <= count + 15'd1; // countinuously count
            end
        if(count2 > 3) // reset count2
            count2 <= 2'd0;
    end
    
always@(*)
    begin        
        case(count2) // 2-to-4 decoder
            2'd0: {an3, an2, an1, an0} = 4'b1110;
            2'd1: {an3, an2, an1, an0} = 4'b1101;
            2'd2: {an3, an2, an1, an0} = 4'b1011;
            2'd3: {an3, an2, an1, an0} = 4'b0111;
            default: {an3, an2, an1, an0} = 4'bxxxx;
        endcase     
        case(count2) // 4-to-1 mux
            2'd0: dp = ~dot0;
            2'd1: dp = ~dot1;
            2'd2: dp = ~dot2;
            2'd3: dp = ~dot3;
            default: dp = 4'bxxxx;
        endcase
        case(count2) // 2-to-4 decoder
            2'd0: dummy = val0;
            2'd1: dummy = val1;
            2'd2: dummy = val2;
            2'd3: dummy = val3;
            default: dummy = 4'bxxxx;
        endcase
        case(dummy) // 4-to-7 decoder
            4'h0: {cg, cf, ce, cd, cc, cb, ca} = ~7'b0111111;
            4'h1: {cg, cf, ce, cd, cc, cb, ca} = ~7'b0000110;
            4'h2: {cg, cf, ce, cd, cc, cb, ca} = ~7'b1011011;
            4'h3: {cg, cf, ce, cd, cc, cb, ca} = ~7'b1001111;
            4'h4: {cg, cf, ce, cd, cc, cb, ca} = ~7'b1100110;
            4'h5: {cg, cf, ce, cd, cc, cb, ca} = ~7'b1101101;
            4'h6: {cg, cf, ce, cd, cc, cb, ca} = ~7'b1111101;
            4'h7: {cg, cf, ce, cd, cc, cb, ca} = ~7'b0000111;
            4'h8: {cg, cf, ce, cd, cc, cb, ca} = ~7'b1111111;
            4'h9: {cg, cf, ce, cd, cc, cb, ca} = ~7'b1100111;
            4'hA: {cg, cf, ce, cd, cc, cb, ca} = ~7'b1110111;
            4'hB: {cg, cf, ce, cd, cc, cb, ca} = ~7'b1111100;
            4'hC: {cg, cf, ce, cd, cc, cb, ca} = ~7'b0111001;
            4'hD: {cg, cf, ce, cd, cc, cb, ca} = ~7'b1011110;
            4'hE: {cg, cf, ce, cd, cc, cb, ca} = ~7'b1111001;
            4'hF: {cg, cf, ce, cd, cc, cb, ca} = ~7'b1110001;
            default: {cg, cf, ce, cd, cc, cb, ca} = ~7'bxxxxxxx;
        endcase   
    end
endmodule
