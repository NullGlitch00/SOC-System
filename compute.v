module compute (
    input iClk,
    input iReset_n,
    input iChipSelect_n,
    input iWrite_n,
    input iRead_n,
    input [3:0] iAddress,
    input [31:0] iData,
    output reg [31:0] oData
);
    reg [31:0] values[0:7];
    integer i;
    reg [31:0] sum;

    always @(posedge iClk or negedge iReset_n) begin
        if (~iReset_n) begin
            for (i = 0; i < 8; i = i + 1)
                values[i] <= 0;
            sum <= 0;
            oData <= 0;
        end else begin
            if (~iChipSelect_n && ~iWrite_n) begin
                if (iAddress < 8)
                    values[iAddress] <= iData;
            end
            if (~iChipSelect_n && ~iRead_n) begin
                case(iAddress)
                    4'd8: begin
                        sum = 0;
                        for (i = 0; i < 8; i = i + 1)
                            sum = sum + values[i];
                        oData <= sum;
                    end
                    4'd9: begin
                        oData <= (sum % 2 == 0) ? 1 : 0; // chan = 1, le = 0
                    end
                    default: oData <= values[iAddress];
                endcase
            end
        end
    end
endmodule