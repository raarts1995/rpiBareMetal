#include "mcp3202.h"

MCP3202 mcp3202;

void mcp3202_init(int cs) {
	mcp3202.mode = MCP3202_SGL_MODE;
	mcp3202.cs = cs;
}

void mcp3202_mode(int mode) {
	if (mode > MCP3202_SGL_MODE)
		return;
	mcp3202.mode = mode;
}

int mcp3202_read(int ch) {
	if (ch > 1)
		return;
	
	spi_set_cpol(0);
	spi_set_cpha(0);
	spi_set_cs(mcp3202.cs);
	spi_set_cspol(mcp3202.cs, 0);

	unsigned char data[3] = {0x01, 0x20 | (mcp3202.mode << 7) | (ch << 6), 0x00};
	spi_transfer(data, 3);
	return ((data[1] & 0xf) << 8) | data[2];
}

void mcp3202_read_int(int ch) {
	if (ch > 1)
		return;
	
	spi_set_cpol(0);
	spi_set_cpha(0);
	spi_set_cs(mcp3202.cs);
	spi_set_cspol(mcp3202.cs, 0);

	unsigned char data[3] = {0x01, 0x20 | (mcp3202.mode << 7) | (ch << 6), 0x00};
	spi_write_int(data, 3);
}

//data ready -> parse data
int mcp3202_rdy_int() {
	unsigned char data[3];
	spi_read_int(data, 3);
	return ((data[1] & 0xf) << 8) | data[2];
}