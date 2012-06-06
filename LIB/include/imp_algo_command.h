/** 
* \defgroup �ӿ�
* �ӿ�
* @author �������ټ���
* @version 2.0
* @data 2009-2010
*/
/*@{*/

/** 
* \defgroup ���������������
* ���������������
* @author �������ټ���
* @version 2.0
* @data 2009-2010
*/
/*@{*/

#ifndef _IMP_ALGO_COMMAND_H_
#define _IMP_ALGO_COMMAND_H_

#include "imp_algo_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** ���������� */
#define IMP_MAX_CMD_CNT			4

typedef enum impCMD_TYPE_E
{
	IMP_CMD_TYPE_UNKNOWN	= 0x00000000	/**< δ֪���� */
}CMD_TYPE_E;

/** �������� */
#define IMP_BUFLEN_CMD_ITEM		64
/** ��������ݳ��� */
#define IMP_BUFLEN_CMD_DATA		(IMP_BUFLEN_CMD_ITEM-sizeof(IMP_U32) * 1)

/** ������ṹ */
typedef struct impCMD_ITEM_S
{
	IMP_U32	u32Type;						/**< �������� */
	IMP_U8	au8Data[IMP_BUFLEN_CMD_DATA];	/**< ��������*/
} CMD_ITEM_S;

/** ����ṹ */
typedef struct impCMD_SET_S 
{
	IMP_S32	    s32CmdNum;					/**< ������Ŀ */
	CMD_ITEM_S	astCmds[IMP_MAX_CMD_CNT];	/**< �������� */
} CMD_SET_S;

#ifdef __cplusplus
}
#endif


#endif /*_IMP_ALGO_COMMAND_H_*/
/*@}*/

/*@}*/