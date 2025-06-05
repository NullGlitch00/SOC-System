module top(
	 input CLOCK_50,
    input [3:0] SW,
    input [1:0] KEY,
    output [6:0] HEX0,
	 output [6:0] HEX1,
	 output [7:0] LEDR,
	 output [7:0] LEDG
	 
);

    system u0 (
        .clk_clk                         (CLOCK_50),                         //                      clk.clk
        .reset_reset_n                   (KEY[0]),                   //                    reset.reset_n
        .switches_0_conduit_end_export   (SW),   //   switches_0_conduit_end.export
        .green_leds_0_conduit_end_export (LEDG), // green_leds_0_conduit_end.export
        .red_leds_0_conduit_end_export   (LEDR),   //   red_leds_0_conduit_end.export
        .hex1_external_connection_export (HEX0), // hex1_external_connection.export
        .hex2_external_connection_export (HEX1), // hex2_external_connection.export
        .key_external_connection_export  (KEY[1])   //  key_external_connection.export
    );

endmodule