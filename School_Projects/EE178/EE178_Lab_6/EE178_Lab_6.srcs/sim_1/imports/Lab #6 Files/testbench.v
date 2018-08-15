// File: testbench.v
// This is a top level testbench for the
// vga_example design, which is part of
// the EE178 Lab #6 assignment.

// The `timescale directive specifies what the
// simulation time units are (1 ns here) and what
// the simulator time step should be (1 ps here).

`timescale 1 ns / 1 ps

module testbench;

  // Declare some local parameters for easier
  // readability of testbench task invocation.

  localparam [2:0] REG_ADDR_STAX = 3'd0;
  localparam [2:0] REG_ADDR_STAY = 3'd1;
  localparam [2:0] REG_ADDR_ENDX = 3'd2;
  localparam [2:0] REG_ADDR_ENDY = 3'd3;
  localparam [2:0] REG_ADDR_BUSY = 3'd4;
  localparam [2:0] REG_ADDR_BEAM = 3'd5;
  localparam [2:0] REG_ADDR_MODE = 3'd6;
  localparam [2:0] REG_ADDR_PRNG = 3'd7;

  localparam [7:0] REG_DATA_BUSY_GO = 8'h01;
  localparam [7:0] REG_DATA_BEAM_HI = 8'h0f;
  localparam [7:0] REG_DATA_BEAM_MD = 8'h07;
  localparam [7:0] REG_DATA_BEAM_LO = 8'h03;
  localparam [7:0] REG_DATA_MODE_HLD = 8'h00;
  localparam [7:0] REG_DATA_MODE_CLR = 8'h01;
  localparam [7:0] REG_DATA_MODE_LIN = 8'h02;
  localparam [7:0] REG_DATA_MODE_EXP = 8'h03;
  
  localparam [7:0] REG_DATA_BEAM_INI = 8'hAf;

  // Declare wires to be driven by the outputs
  // of the design, and regs to drive the inputs.
  // The testbench will be in control of inputs
  // to the design, and will check the outputs.
  // Then, instantiate the design to be tested.

  reg clk;
  wire pclk_mirror;
  wire vs, hs;
  wire [3:0] r, g, b;
  reg [7:0] write_data;
  wire [7:0] read_data;
  reg [2:0] address;
  reg write;
  wire irq;
  
  // Instantiate the vga_example module.
  
  vga_example my_example (
    .clk(clk),
    .vs(vs),
    .hs(hs),
    .r(r),
    .g(g),
    .b(b),
    .pclk_mirror(pclk_mirror),
    .write_data(write_data),
    .read_data(read_data),
    .address(address),
    .write(write),
    .irq(irq)
  );

  // Instantiate the tiff_writer module.

  tiff_writer my_writer (
    .pclk_mirror(pclk_mirror),
    .r({r,r}), // fabricate an 8-bit value
    .g({g,g}), // fabricate an 8-bit value
    .b({b,b}), // fabricate an 8-bit value
    .go(irq),
    .xdim(16'd1056),
    .ydim(16'd628)
  );

  // Describe a process that generates a clock
  // signal. The clock is 100 MHz.

  always
  begin
    clk = 1'b0;
    #5;
    clk = 1'b1;
    #5;
  end

  // Describe a process that initializes all
  // other registers that should start off at
  // specific values.

  reg [7:0] result;
  
  initial
  begin
    result = 8'bx;
    write_data = 8'bx;
    address = 3'bx;
    write = 1'b0;
  end
  
  // Describe a task that will select a register
  // and write it with data.

  task WRITE_REGISTER;
    // This task is using the negative edge
    // of the pclock to apply the inputs to
    // the register interface centered over
    // the positive edge of the pclock.
    input [2:0] addr;
    input [7:0] data;
  begin
    @(negedge pclk_mirror);
    write_data <= data;
    address <= addr;
    write <= 1'b0;
    @(negedge pclk_mirror);
    write <= 1'b1;
    @(posedge pclk_mirror) if (write) $display("Info: wrote register %d with data %h",address,write_data);
    @(negedge pclk_mirror);
    write_data <= 8'bx;
    address <= 3'bx;
    write <= 1'b0;
  end
  endtask

  // Describe a task that will select a register
  // and read out the data.  The value is stored
  // for later use if needed.

  task READ_REGISTER;
    // This task is using the negative edge
    // of the pclock to apply the inputs to
    // the register interface centered over
    // the positive edge of the pclock.
    input [2:0] addr;
  begin
    @(negedge pclk_mirror);
    address <= addr;
    @(negedge pclk_mirror);
    @(posedge pclk_mirror)
    begin
      result <= read_data;
      $display("Info: read register %d with data %h",address,read_data);
    end
    @(negedge pclk_mirror);
    address <= 3'bx;
  end
  endtask

  // Describe a task that will pulse the
  // go bit and wait for not busy status.

  task SET_GO_POLL_BUSY;
    // This task uses the other tasks for
    // writing and reading registers.
  begin
    result = REG_DATA_BUSY_GO;
    WRITE_REGISTER (REG_ADDR_BUSY,result);
    while (result == REG_DATA_BUSY_GO)
    begin
      $display("Info: it is busy, waiting...");
      READ_REGISTER (REG_ADDR_BUSY);
    end
  end
  endtask

  // Assign values to the input signals and
  // check the output results. This template
  // is meant to get you started, you can modify
  // it as you see fit. If you simply run it as
  // provided, you will need to visually inspect
  // the output waveforms to see if they make
  // sense...

  initial
  begin
    $display("If simulation ends before the testbench");
    $display("completes, use the menu option to run all.");
    $display("Prepare to wait a long time...");
    @(posedge irq) $display("Info: vertical blank interrupt at %t",$time);
    // Put it into exponential decay mode
    WRITE_REGISTER (REG_ADDR_MODE,REG_DATA_MODE_EXP);
    // Draw with a high intensity
    WRITE_REGISTER (REG_ADDR_BEAM,REG_DATA_BEAM_HI);
    // Draw horizontal and vertical crosshairs 1 of 4
    WRITE_REGISTER (REG_ADDR_STAX,128);
    WRITE_REGISTER (REG_ADDR_STAY,126);
    WRITE_REGISTER (REG_ADDR_ENDX,128);
    WRITE_REGISTER (REG_ADDR_ENDY,100);
    SET_GO_POLL_BUSY;
    // Draw horizontal and vertical crosshairs 2 of 4
    WRITE_REGISTER (REG_ADDR_STAX,128);
    WRITE_REGISTER (REG_ADDR_STAY,130);
    WRITE_REGISTER (REG_ADDR_ENDX,128);
    WRITE_REGISTER (REG_ADDR_ENDY,156);
    SET_GO_POLL_BUSY;
    // Draw horizontal and vertical crossharis 3 of 4
    WRITE_REGISTER (REG_ADDR_STAX,126);
    WRITE_REGISTER (REG_ADDR_STAY,128);
    WRITE_REGISTER (REG_ADDR_ENDX,100);
    WRITE_REGISTER (REG_ADDR_ENDY,128);
    SET_GO_POLL_BUSY;
    // Draw horizontal and veritcal crosshairs 4 of 4
    WRITE_REGISTER (REG_ADDR_STAX,130);
    WRITE_REGISTER (REG_ADDR_STAY,128);
    WRITE_REGISTER (REG_ADDR_ENDX,156);
    WRITE_REGISTER (REG_ADDR_ENDY,128);
    SET_GO_POLL_BUSY;
    // Draw with a medium intensity
    WRITE_REGISTER (REG_ADDR_BEAM,REG_DATA_BEAM_MD);
    // Draw diagonal crosshairs 1 of 4
    WRITE_REGISTER (REG_ADDR_STAX,126);
    WRITE_REGISTER (REG_ADDR_STAY,126);
    WRITE_REGISTER (REG_ADDR_ENDX,100);
    WRITE_REGISTER (REG_ADDR_ENDY,100);
    SET_GO_POLL_BUSY;
    // Draw diagonal crosshairs 2 of 4
    WRITE_REGISTER (REG_ADDR_STAX,130);
    WRITE_REGISTER (REG_ADDR_STAY,126);
    WRITE_REGISTER (REG_ADDR_ENDX,156);
    WRITE_REGISTER (REG_ADDR_ENDY,100);
    SET_GO_POLL_BUSY;
    // Draw diagonal crossharis 3 of 4
    WRITE_REGISTER (REG_ADDR_STAX,126);
    WRITE_REGISTER (REG_ADDR_STAY,130);
    WRITE_REGISTER (REG_ADDR_ENDX,100);
    WRITE_REGISTER (REG_ADDR_ENDY,156);
    SET_GO_POLL_BUSY;
    // Draw diagonal crosshairs 4 of 4
    WRITE_REGISTER (REG_ADDR_STAX,130);
    WRITE_REGISTER (REG_ADDR_STAY,130);
    WRITE_REGISTER (REG_ADDR_ENDX,156);
    WRITE_REGISTER (REG_ADDR_ENDY,156);
    SET_GO_POLL_BUSY;
    // Draw with a low intensity
    WRITE_REGISTER (REG_ADDR_BEAM,REG_DATA_BEAM_LO);
    // Draw octant crosshairs 1 of 8
    WRITE_REGISTER (REG_ADDR_STAX,125);
    WRITE_REGISTER (REG_ADDR_STAY,127);
    WRITE_REGISTER (REG_ADDR_ENDX,100);
    WRITE_REGISTER (REG_ADDR_ENDY,114);
    SET_GO_POLL_BUSY;
    // Draw octant crosshairs 2 of 8
    WRITE_REGISTER (REG_ADDR_STAX,127);
    WRITE_REGISTER (REG_ADDR_STAY,125);
    WRITE_REGISTER (REG_ADDR_ENDX,114);
    WRITE_REGISTER (REG_ADDR_ENDY,100);
    SET_GO_POLL_BUSY;
    // Draw octant crossharis 3 of 8
    WRITE_REGISTER (REG_ADDR_STAX,129);
    WRITE_REGISTER (REG_ADDR_STAY,125);
    WRITE_REGISTER (REG_ADDR_ENDX,142);
    WRITE_REGISTER (REG_ADDR_ENDY,100);
    SET_GO_POLL_BUSY;
    // Draw octant crosshairs 4 of 8
    WRITE_REGISTER (REG_ADDR_STAX,131);
    WRITE_REGISTER (REG_ADDR_STAY,127);
    WRITE_REGISTER (REG_ADDR_ENDX,156);
    WRITE_REGISTER (REG_ADDR_ENDY,114);
    SET_GO_POLL_BUSY;
    // Draw octant crosshairs 5 of 8
    WRITE_REGISTER (REG_ADDR_STAX,125);
    WRITE_REGISTER (REG_ADDR_STAY,129);
    WRITE_REGISTER (REG_ADDR_ENDX,100);
    WRITE_REGISTER (REG_ADDR_ENDY,142);
    SET_GO_POLL_BUSY;
    // Draw octant crosshairs 6 of 8
    WRITE_REGISTER (REG_ADDR_STAX,127);
    WRITE_REGISTER (REG_ADDR_STAY,131);
    WRITE_REGISTER (REG_ADDR_ENDX,114);
    WRITE_REGISTER (REG_ADDR_ENDY,156);
    SET_GO_POLL_BUSY;
    // Draw octant crossharis 7 of 8
    WRITE_REGISTER (REG_ADDR_STAX,129);
    WRITE_REGISTER (REG_ADDR_STAY,131);
    WRITE_REGISTER (REG_ADDR_ENDX,142);
    WRITE_REGISTER (REG_ADDR_ENDY,156);
    SET_GO_POLL_BUSY;
    // Draw octant crosshairs 8 of 8
    WRITE_REGISTER (REG_ADDR_STAX,131);
    WRITE_REGISTER (REG_ADDR_STAY,129);
    WRITE_REGISTER (REG_ADDR_ENDX,156);
    WRITE_REGISTER (REG_ADDR_ENDY,142);
    SET_GO_POLL_BUSY;
    //Change color
    WRITE_REGISTER (REG_ADDR_BEAM,REG_DATA_BEAM_INI);
    //Letter J
    //J Piece 1
    WRITE_REGISTER (REG_ADDR_STAX,80);
    WRITE_REGISTER (REG_ADDR_STAY,90);
    WRITE_REGISTER (REG_ADDR_ENDX,80);
    WRITE_REGISTER (REG_ADDR_ENDY,145);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,72);
    WRITE_REGISTER (REG_ADDR_STAY,90);
    WRITE_REGISTER (REG_ADDR_ENDX,72);
    WRITE_REGISTER (REG_ADDR_ENDY,137);
    SET_GO_POLL_BUSY;
    //J Piece 2
    WRITE_REGISTER (REG_ADDR_STAX,80);
    WRITE_REGISTER (REG_ADDR_STAY,145);
    WRITE_REGISTER (REG_ADDR_ENDX,70);
    WRITE_REGISTER (REG_ADDR_ENDY,156);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,72);
    WRITE_REGISTER (REG_ADDR_STAY,137);
    WRITE_REGISTER (REG_ADDR_ENDX,65);
    WRITE_REGISTER (REG_ADDR_ENDY,148);
    //J Bottom Piece
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,70);
    WRITE_REGISTER (REG_ADDR_STAY,156);
    WRITE_REGISTER (REG_ADDR_ENDX,45);
    WRITE_REGISTER (REG_ADDR_ENDY,156);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,65);
    WRITE_REGISTER (REG_ADDR_STAY,148);
    WRITE_REGISTER (REG_ADDR_ENDX,50);
    WRITE_REGISTER (REG_ADDR_ENDY,148);
    SET_GO_POLL_BUSY;
    //J Piece 3
    WRITE_REGISTER (REG_ADDR_STAX,45);
    WRITE_REGISTER (REG_ADDR_STAY,156);
    WRITE_REGISTER (REG_ADDR_ENDX,30);
    WRITE_REGISTER (REG_ADDR_ENDY,145);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,50);
    WRITE_REGISTER (REG_ADDR_STAY,148);
    WRITE_REGISTER (REG_ADDR_ENDX,38);
    WRITE_REGISTER (REG_ADDR_ENDY,140);
    SET_GO_POLL_BUSY;
    //J Piece 4
    WRITE_REGISTER (REG_ADDR_STAX,30);
    WRITE_REGISTER (REG_ADDR_STAY,145);
    WRITE_REGISTER (REG_ADDR_ENDX,30);
    WRITE_REGISTER (REG_ADDR_ENDY,132);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,38);
    WRITE_REGISTER (REG_ADDR_STAY,140);
    WRITE_REGISTER (REG_ADDR_ENDX,38);
    WRITE_REGISTER (REG_ADDR_ENDY,132);
    SET_GO_POLL_BUSY;
    //J Piece 5
    WRITE_REGISTER (REG_ADDR_STAX,72);
    WRITE_REGISTER (REG_ADDR_STAY,90);
    WRITE_REGISTER (REG_ADDR_ENDX,80);
    WRITE_REGISTER (REG_ADDR_ENDY,90);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,30);
    WRITE_REGISTER (REG_ADDR_STAY,132);
    WRITE_REGISTER (REG_ADDR_ENDX,38);
    WRITE_REGISTER (REG_ADDR_ENDY,132);
    SET_GO_POLL_BUSY;
    //Letter B
    //B Piece 1
    WRITE_REGISTER (REG_ADDR_STAX,176);
    WRITE_REGISTER (REG_ADDR_STAY,90);
    WRITE_REGISTER (REG_ADDR_ENDX,176);
    WRITE_REGISTER (REG_ADDR_ENDY,156);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,184);
    WRITE_REGISTER (REG_ADDR_STAY,98);
    WRITE_REGISTER (REG_ADDR_ENDX,184);
    WRITE_REGISTER (REG_ADDR_ENDY,148);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,176);
    WRITE_REGISTER (REG_ADDR_STAY,90);
    WRITE_REGISTER (REG_ADDR_ENDX,201);
    WRITE_REGISTER (REG_ADDR_ENDY,90);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,184);
    WRITE_REGISTER (REG_ADDR_STAY,98);
    WRITE_REGISTER (REG_ADDR_ENDX,196);
    WRITE_REGISTER (REG_ADDR_ENDY,98);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,176);
    WRITE_REGISTER (REG_ADDR_STAY,156);
    WRITE_REGISTER (REG_ADDR_ENDX,201);
    WRITE_REGISTER (REG_ADDR_ENDY,156);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,184);
    WRITE_REGISTER (REG_ADDR_STAY,148);
    WRITE_REGISTER (REG_ADDR_ENDX,196);
    WRITE_REGISTER (REG_ADDR_ENDY,148);
    SET_GO_POLL_BUSY;
    //B Middle Part
    WRITE_REGISTER (REG_ADDR_STAX,184);
    WRITE_REGISTER (REG_ADDR_STAY,119);
    WRITE_REGISTER (REG_ADDR_ENDX,196);
    WRITE_REGISTER (REG_ADDR_ENDY,119);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,184);
    WRITE_REGISTER (REG_ADDR_STAY,127);
    WRITE_REGISTER (REG_ADDR_ENDX,196);
    WRITE_REGISTER (REG_ADDR_ENDY,127);
    SET_GO_POLL_BUSY;
    //B Inner Curved Parts Top Half
    WRITE_REGISTER (REG_ADDR_STAX,196);
    WRITE_REGISTER (REG_ADDR_STAY,98);
    WRITE_REGISTER (REG_ADDR_ENDX,204);
    WRITE_REGISTER (REG_ADDR_ENDY,104);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,204);
    WRITE_REGISTER (REG_ADDR_STAY,104);
    WRITE_REGISTER (REG_ADDR_ENDX,206);
    WRITE_REGISTER (REG_ADDR_ENDY,110);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,206);
    WRITE_REGISTER (REG_ADDR_STAY,110);
    WRITE_REGISTER (REG_ADDR_ENDX,204);
    WRITE_REGISTER (REG_ADDR_ENDY,116);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,204);
    WRITE_REGISTER (REG_ADDR_STAY,116);
    WRITE_REGISTER (REG_ADDR_ENDX,196);
    WRITE_REGISTER (REG_ADDR_ENDY,119);
    SET_GO_POLL_BUSY;
    //B Inner Curved Parts Bottom Half
    WRITE_REGISTER (REG_ADDR_STAX,196);
    WRITE_REGISTER (REG_ADDR_STAY,127);
    WRITE_REGISTER (REG_ADDR_ENDX,204);
    WRITE_REGISTER (REG_ADDR_ENDY,130);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,204);
    WRITE_REGISTER (REG_ADDR_STAY,130);
    WRITE_REGISTER (REG_ADDR_ENDX,206);
    WRITE_REGISTER (REG_ADDR_ENDY,136);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,206);
    WRITE_REGISTER (REG_ADDR_STAY,136);
    WRITE_REGISTER (REG_ADDR_ENDX,204);
    WRITE_REGISTER (REG_ADDR_ENDY,142);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,204);
    WRITE_REGISTER (REG_ADDR_STAY,142);
    WRITE_REGISTER (REG_ADDR_ENDX,196);
    WRITE_REGISTER (REG_ADDR_ENDY,148);
    SET_GO_POLL_BUSY;
    //B Outer Curved Parts Top Half
    WRITE_REGISTER (REG_ADDR_STAX,201);
    WRITE_REGISTER (REG_ADDR_STAY,90);
    WRITE_REGISTER (REG_ADDR_ENDX,209);
    WRITE_REGISTER (REG_ADDR_ENDY,98);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,209);
    WRITE_REGISTER (REG_ADDR_STAY,98);
    WRITE_REGISTER (REG_ADDR_ENDX,213);
    WRITE_REGISTER (REG_ADDR_ENDY,106);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,213);
    WRITE_REGISTER (REG_ADDR_STAY,106);
    WRITE_REGISTER (REG_ADDR_ENDX,212);
    WRITE_REGISTER (REG_ADDR_ENDY,116);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,212);
    WRITE_REGISTER (REG_ADDR_STAY,116);
    WRITE_REGISTER (REG_ADDR_ENDX,201);
    WRITE_REGISTER (REG_ADDR_ENDY,123);
    SET_GO_POLL_BUSY;
    //B Outer Curved Parts Bottom Half
    WRITE_REGISTER (REG_ADDR_STAX,201);
    WRITE_REGISTER (REG_ADDR_STAY,123);
    WRITE_REGISTER (REG_ADDR_ENDX,209);
    WRITE_REGISTER (REG_ADDR_ENDY,130);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,209);
    WRITE_REGISTER (REG_ADDR_STAY,130);
    WRITE_REGISTER (REG_ADDR_ENDX,213);
    WRITE_REGISTER (REG_ADDR_ENDY,140);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,213);
    WRITE_REGISTER (REG_ADDR_STAY,140);
    WRITE_REGISTER (REG_ADDR_ENDX,212);
    WRITE_REGISTER (REG_ADDR_ENDY,148);
    SET_GO_POLL_BUSY;
    WRITE_REGISTER (REG_ADDR_STAX,212);
    WRITE_REGISTER (REG_ADDR_STAY,148);
    WRITE_REGISTER (REG_ADDR_ENDX,201);
    WRITE_REGISTER (REG_ADDR_ENDY,156);
    SET_GO_POLL_BUSY;

    
    @(posedge irq) $display("Info: vertical blank interrupt at %t",$time);
    @(posedge irq) $display("Info: vertical blank interrupt at %t",$time);
    @(posedge irq) $display("Info: vertical blank interrupt at %t",$time);
    @(posedge irq) $display("Info: vertical blank interrupt at %t",$time);
    @(posedge irq) $display("Info: vertical blank interrupt at %t",$time);
    // End the simulation.
    $display("Simulation is over, check the waveforms.");
    $stop;
  end

endmodule
