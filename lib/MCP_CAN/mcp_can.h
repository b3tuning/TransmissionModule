//
// Created by Bucky Fellini on 2/28/20.
//

#ifndef TRANSCONTROLLER_MCP_CAN_H
#define TRANSCONTROLLER_MCP_CAN_H

#include "mcp_can_dfs.h"

#define MAX_CHAR_IN_MESSAGE 8

class MCP_CAN {
	INT8U  m_nExtFlg; // Identifier Type
	// Extended (29 bit) or Standard (11 bit)
	INT32U m_nID;     // CAN ID
	INT8U  m_nDlc;    // Data Length Code
	INT8U  m_nDta[MAX_CHAR_IN_MESSAGE]; // Data array
	INT8U  m_nRtr;    // Remote request flag
	INT8U  m_nfilhit; // The number of the filter that matched the message
	INT8U  MCPCS;     // Chip Select pin number
	INT8U  mcpMode;   // Mode to return to after configurations are performed.


/*****************************************************************************************
 *  mcp2515 driver function
 ****************************************************************************************/
private:

	// Soft Reset MCP2515
	void mcp2515_reset(void) const;

	// Read MCP2515 register
	INT8U mcp2515_readRegister(INT8U address) const;

	// Read MCP2515 successive registers
	void mcp2515_readRegisterS(INT8U address, INT8U values[], INT8U n) const;

	// Set MCP2515 register
	void mcp2515_setRegister(INT8U address, INT8U value) const;

	// Set MCP2515 successive registers
	void mcp2515_setRegisterS(INT8U address, const INT8U values[], INT8U n) const;

	void mcp2515_initCANBuffers(void);

	// Set specific bit(s) of a register
	void mcp2515_modifyRegister(INT8U address, INT8U mask, INT8U data) const;

	// Read MCP2515 Status
	INT8U mcp2515_readStatus(void) const;

	// Set mode
	INT8U mcp2515_setCANCTRL_Mode(INT8U newMode);

	// Set baud rate
	INT8U mcp2515_configRate(INT8U canSpeed, INT8U canClock);

	// Initialize Controller
	INT8U mcp2515_init(INT8U canIDMode, INT8U canSpeed, INT8U canClock);

	// Write CAN Mask or Filter
	void mcp2515_write_mf(INT8U mcp_addr, INT8U ext, INT32U id);

	// Write CAN ID
	void mcp2515_write_id(INT8U mcp_addr, INT8U ext, INT32U id);

	// Read CAN ID
	void mcp2515_read_id(INT8U mcp_addr, INT8U* ext, INT32U* id);

	// Write CAN message
	void mcp2515_write_canMsg(INT8U buffer_sidh_addr);

	// Read CAN message
	void mcp2515_read_canMsg(INT8U buffer_sidh_addr);

	// Find empty transmit buffer
	INT8U mcp2515_getNextFreeTXBuf(INT8U* txBuf_n);

/*****************************************************************************************
 *  CAN operator function
 ****************************************************************************************/

	// Set message
	INT8U setMsg(INT32U id, INT8U rtr, INT8U ext, INT8U len, INT8U* pData);

	// Clear all message to zero
	INT8U clearMsg();

	// Read message
	INT8U readMsg();

	// Send message
	INT8U sendMsg();

public:
	MCP_CAN(INT8U _CS);

	// Initialize controller parameters
	INT8U begin(INT8U idModeSet, INT8U speedSet, INT8U clockSet);

	// Initialize Mask(s)
	INT8U init_Mask(INT8U num, INT8U ext, INT32U ulData);

	// Initialize Mask(s)
	INT8U init_Mask(INT8U num, INT32U ulData);

	// Initialize Filter(s)
	INT8U init_Filt(INT8U num, INT8U ext, INT32U ulData);

	// Initialize Filter(s)
	INT8U init_Filt(INT8U num, INT32U ulData);

	// Set operational mode
	INT8U setMode(INT8U opMode);

	// Send message to transmit buffer
	INT8U sendMsgBuf(INT32U id, INT8U ext, INT8U len, INT8U* buf);

	// Send message to transmit buffer
	INT8U sendMsgBuf(INT32U id, INT8U len, INT8U* buf);

	// Read message from receive buffer
	INT8U readMsgBuf(INT32U* id, INT8U* ext, INT8U* len, INT8U* buf);

	// Read message from receive buffer
	INT8U readMsgBuf(INT32U* id, INT8U* len, INT8U* buf);

	// Check for received data
	INT8U checkReceive(void);

	// Check for errors
	INT8U checkError(void);

	// Check for errors
	INT8U getError(void);

	// Get error count
	INT8U errorCountRX(void);

	// Get error count
	INT8U errorCountTX(void);

	// Enable one-shot transmission
	INT8U enOneShotTX(void);

	// Disable one-shot transmission
	INT8U disOneShotTX(void);

	// Abort queued transmission(s)
	INT8U abortTX(void);

	// Sets GPO
	INT8U setGPO(INT8U data);

	// Reads GPI
	INT8U getGPI(void);
};

#endif //TRANSCONTROLLER_MCP_CAN_H
