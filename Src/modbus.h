#include "PubDef.h"
#ifdef Valve_NWK_ENABLE

#include "main.h"

#ifndef _MODBUS_H
#define _MODBUS_H

#define MODBUS_DATA_MAX    80

// MODBUS������
#define MODBUS_CMD_READ_MULTI		0x03	// ������Ĵ���
#define MODBUS_CMD_WRITE_SINGLE		0x06	// д�����Ĵ���
#define MODBUS_CMD_WRITE_MULTI		0x10	// д����Ĵ���

// MODBUS��ַ��
#define MODBUS_ADDR	0xFF

typedef enum _ModbusRet{
    MODBUS_OK = 0,
	MODBUS_ERR_INVALID_CMD,		 // δ֪������
    MODBUS_ERR_CRC16,			 // У��ʹ���
    MODBUS_ERR_LESS_MEMORY,      // �ڴ治��
    MODBUS_ERR_ADDR,             // ��ַ��ƥ��
	MODBUS_ERR_LENGTH			 // ���ȴ���
}ModbusRet;

// ModbusЭ��֡����
typedef struct _ModbusPkg{
    u8  addr;		// �Ǳ��ַ
    u8  cmd;		// ������
    u8*  data;	    // ����
    u8  data_len;	// ���ݳ���
}modbus_pkg;

extern modbus_pkg g_modbus_pkg;

u8 modbus_read_multi_request_unpack(u8 *data_field, u8 data_field_len, u16 *reg_val, u16 *reg_cnt);
u8 modbus_write_single_request_unpack(u8 *data_field, u8 data_field_len, u16 *reg_addr, u16 *reg_val);
u8 modbus_write_multi_request_unpack(u8 *data_field, u8 data_field_len, u16 *reg_addr_st, u16 *reg_val, u8 *reg_cnt);
u8 modbus_pack(u8 *package, u8 *size, u8 addr, u8 cmd, u8 *dat, u8 len);
u8 modbus_unpack(u8 *package, u8 size, u8 *addr, u8 *cmd, u8 **dat, u8 *len);




#endif
#endif

