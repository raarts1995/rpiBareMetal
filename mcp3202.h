#ifndef MCP3202_H
#define MCP3202_H

#define MCP3202_MAX 4095 //12 bit

#define MCP3202_DIFF_MODE 0x0
#define MCP3202_SGL_MODE  0x1 //single mode

typedef struct mcp3202{
	int cs, mode;
} MCP3202;

extern MCP3202 mcp3202;

void mcp3202_init(int cs);
void mcp3202_mode(int mode);
int mcp3202_read(int ch);
void mcp3202_read_int(int ch);
int mcp3202_rdy_int();

#endif