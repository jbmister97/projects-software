// File: tutorial.v
// This is the top level design for EE178 Lab #7.

// The `timescale directive specifies what the
// simulation time units are (1 ns here) and what
// the simulator time step should be (1 ps here).

`timescale 1 ns / 1 ps

// Declare the module and its ports. This is
// using Verilog-2001 syntax.

module tutorial (
  input wire clk,
  input wire [15:0] switches,
  output reg [15:0] leds,
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

  //******************************************************************//
  // Instantiate PicoBlaze and the Instruction ROM.                   //
  //******************************************************************//

  wire [11:0] address;
  wire [17:0] instruction;
  wire bram_enable;
  wire [7:0] port_id;
  wire [7:0] out_port;
  reg [7:0] in_port;
  wire write_strobe;
  wire k_write_strobe;
  wire read_strobe;
  wire interrupt_ack;

  kcpsm6 kcpsm6_inst (
    .address(address),
    .instruction(instruction),
    .bram_enable(bram_enable),
    .port_id(port_id),
    .write_strobe(write_strobe),
    .k_write_strobe(k_write_strobe),
    .out_port(out_port),
    .read_strobe(read_strobe),
    .in_port(in_port),
    .interrupt(1'b0),
    .interrupt_ack(interrupt_ack),
    .reset(1'b0),
    .sleep(1'b0),
    .clk(clk)
  ); 

  software software_inst (
    .address(address),
    .instruction(instruction),
    .bram_enable(bram_enable),
    .clk(clk)
  );

  //******************************************************************//
  // Implement output ports.                                          //
  //******************************************************************//

  always @(posedge clk)
    begin
    if (write_strobe)
    begin
      if (port_id == 8'h02) leds[7:0] <= out_port;
      if (port_id == 8'h03) leds[15:8] <= out_port;
    end
  end

  //******************************************************************//
  // Implement input ports.                                           //
  //******************************************************************//

  always @*
  begin
    case (port_id)
      8'h00: in_port = switches[7:0];
      8'h01: in_port = switches[15:8];
      default: in_port = 8'h00;
    endcase
  end

  //******************************************************************//
  // To control seven seven segment display                           //
  //******************************************************************//
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
          
          case(count2) // 2-to-4 decoder
              2'd0: dummy = leds[3:0];
              2'd1: dummy = leds[7:4];
              2'd2: dummy = leds[11:8];
              2'd3: dummy = leds[15:12];
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