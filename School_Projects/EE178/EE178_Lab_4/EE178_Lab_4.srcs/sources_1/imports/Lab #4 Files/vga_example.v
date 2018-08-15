// File: vga_example.v
// This is the top level design for EE178 Lab #4.

// The `timescale directive specifies what the
// simulation time units are (1 ns here) and what
// the simulator time step should be (1 ps here).

`timescale 1 ns / 1 ps

// Declare the module and its ports. This is
// using Verilog-2001 syntax.

module vga_example (
  input wire clk,
  output reg vs,
  output reg hs,
  output reg [3:0] r,
  output reg [3:0] g,
  output reg [3:0] b,
  output wire pclk_mirror
  );

  // Converts 100 MHz clk into 40 MHz pclk.
  // This uses a vendor specific primitive
  // called MMCME2, for frequency synthesis.

  wire clk_in;
  wire locked;
  wire clk_fb;
  wire clk_ss;
  wire clk_out;
  wire pclk;
  (* KEEP = "TRUE" *) 
  (* ASYNC_REG = "TRUE" *)
  reg [7:0] safe_start = 0;

  IBUF clk_ibuf (.I(clk),.O(clk_in));

  MMCME2_BASE #(
    .CLKIN1_PERIOD(10.000),
    .CLKFBOUT_MULT_F(10.000),
    .CLKOUT0_DIVIDE_F(25.000))
  clk_in_mmcme2 (
    .CLKIN1(clk_in),
    .CLKOUT0(clk_out),
    .CLKOUT0B(),
    .CLKOUT1(),
    .CLKOUT1B(),
    .CLKOUT2(),
    .CLKOUT2B(),
    .CLKOUT3(),
    .CLKOUT3B(),
    .CLKOUT4(),
    .CLKOUT5(),
    .CLKOUT6(),
    .CLKFBOUT(clkfb),
    .CLKFBOUTB(),
    .CLKFBIN(clkfb),
    .LOCKED(locked),
    .PWRDWN(1'b0),
    .RST(1'b0)
  );

  BUFH clk_out_bufh (.I(clk_out),.O(clk_ss));
  always @(posedge clk_ss) safe_start<= {safe_start[6:0],locked};

  BUFGCE clk_out_bufgce (.I(clk_out),.CE(safe_start[7]),.O(pclk));

  // Mirrors pclk on a pin for use by the testbench;
  // not functionally required for this design to work.

  ODDR pclk_oddr (
    .Q(pclk_mirror),
    .C(pclk),
    .CE(1'b1),
    .D1(1'b1),
    .D2(1'b0),
    .R(1'b0),
    .S(1'b0)
  );

  // Instantiate the vga_timing module, which is
  // the module you are designing for this lab.

  wire [10:0] vcount, hcount;
  wire vsync, hsync;
  wire vblnk, hblnk;

  vga_timing my_timing (
    .vcount(vcount),
    .vsync(vsync),
    .vblnk(vblnk),
    .hcount(hcount),
    .hsync(hsync),
    .hblnk(hblnk),
    .pclk(pclk)
  );

  // This is a simple test pattern generator.
  reg JH1, JH2, JH3, JH4, JH5;
  reg JV1, JV2, JV3, JV4, JV5;
  reg BH1, BH2, BH3, BH4, BH5, BH6, BH7, BH8, BH9;
  reg BV1, BV2, BV3, BV4, BV5, BV6, BV7, BV8, BV9;
  
  always @(posedge pclk)
  begin
    // Just pass these through.
    hs <= hsync;
    vs <= vsync;
    //For letter J
    JH1 = (hcount >= 360) && (hcount <= 372); //J piece 1
    JV1 = (vcount >= 220) && (vcount <= 290);
    JH2 = (hcount >= 320) && (hcount <= 370); //J piece 2
    JV2 = (vcount >= 291) && (vcount <= 297);
    JH3 = (hcount >= 330) && (hcount <= 360); //J piece 3
    JV3 = (vcount >= 302) && (vcount <= 304);
    JH4 = (hcount >= 320) && (hcount <= 332); //J piece 4
    JV4 = (vcount >= 280) && (vcount <= 290);
    JH5 = (hcount >= 325) && (hcount <= 365); //J piece 5
    JV5 = (vcount >= 298) && (vcount <= 301);
    //For letter B
    BH1 = (hcount >= 394) && (hcount <= 426); //B piece 1
    BV1 = (vcount >= 220) && (vcount <= 227);
    BH2 = (hcount >= 394) && (hcount <= 406); //B piece 2
    BV2 = (vcount >= 228) && (vcount <= 296);
    BH3 = (hcount >= 394) && (hcount <= 426); //B piece 3
    BV3 = (vcount >= 297) && (vcount <= 304);
    BH4 = (hcount >= 407) && (hcount <= 420); //B piece 4
    BV4 = (vcount >= 255) && (vcount <= 265);
    BH5 = (hcount >= 421) && (hcount <= 426); //B piece 5
    BV5 = ((vcount >= 253) && (vcount <= 258)) || ((vcount >= 262) && (vcount <= 267));
    BH6 = (hcount >= 427) && (hcount <= 431); //B piece 6
    BV6 = ((vcount >= 251) && (vcount <= 256)) || ((vcount >= 264) && (vcount <= 269));
    BH7 = (hcount >= 432) && (hcount <= 435); //B piece 7
    BV7 = ((vcount >= 225) && (vcount <= 253)) || ((vcount >= 267) && (vcount <= 296));
    BH8 = (hcount >= 427) && (hcount <= 431); //B piece 8
    BV8 = ((vcount >= 222) && (vcount <= 227)) || ((vcount >= 294) && (vcount <= 299));
    BH9 = (hcount >= 435) && (hcount <= 438); //B piece 9
    BV9 = ((vcount >= 229) && (vcount <= 249)) || ((vcount >= 271) && (vcount <= 292));
    // During blanking, make it it black.
    if (vblnk || hblnk) {r,g,b} <= 12'h0_0_0; 
    else
    begin
      // Active display, top edge, make a yellow line.
      if (vcount == 1) {r,g,b} <= 12'hf_f_0;
      // Active display, bottom edge, make a red line.
      else if ((vcount == 0) || (hcount == 799)) {r,g,b} <= 12'h0_0_0;
      else if (vcount == 599) {r,g,b} <= 12'hf_0_0;
      // Active display, left edge, make a green line.
      else if (hcount == 0) {r,g,b} <= 12'h0_f_0;
      // Active display, right edge, make a blue line.
      else if (hcount == 798) {r,g,b} <= 12'h0_0_f;
      // Display the letter J
      else if ((JH1 && JV1) || (JH2 && JV2) || (JH3 && JV3) || (JH4 && JV4) || (JH5 && JV5)) {r,g,b} <= 12'hE_5_A;
      // Display the letter B
      else if ((BH1 && BV1) || (BH2 && BV2) || (BH3 && BV3) || (BH4 && BV4) || (BH5 && BV5) || (BH6 && BV6) || (BH7 && BV7) || (BH8 && BV8) || (BH9 && BV9)) {r,g,b} <= 12'hE_5_A;
      // Active display, interior, fill with gray.
      // You will replace this with your own test.
      else {r,g,b} <= 12'h8_8_8;    
    end
  end

endmodule
