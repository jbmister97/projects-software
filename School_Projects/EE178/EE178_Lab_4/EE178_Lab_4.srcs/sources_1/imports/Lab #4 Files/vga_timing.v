// File: vga_timing.v
// This is the vga timing design for EE178 Lab #4.

// The `timescale directive specifies what the
// simulation time units are (1 ns here) and what
// the simulator time step should be (1 ps here).

`timescale 1 ns / 1 ps

// Declare the module and its ports. This is
// using Verilog-2001 syntax.

module vga_timing (
  output reg [10:0] vcount = 0,
  output wire vsync,
  output wire vblnk,
  output reg [10:0] hcount = 0,
  output wire hsync,
  output wire hblnk,
  input wire pclk
  );

  // Describe the actual circuit for the assignment.
  // Video timing controller set for 800x600@60fps
  // using a 40 MHz pixel clock per VESA spec.

always@(posedge pclk)
    begin
        if(hcount == 1055)
            begin 
            hcount <= 0;
            vcount <= vcount + 1;
            end
        else hcount <= hcount + 1;
        if(vcount == 627) vcount <= 0;
    end
assign hblnk = (hcount >= 800) && (hcount <= 1055);
assign vblnk = (vcount >= 600) && (vcount <= 627);       
assign hsync = (hcount >= 839) && (hcount <= 967);
assign vsync = (vcount >= 601) && (vcount <= 605);

endmodule
