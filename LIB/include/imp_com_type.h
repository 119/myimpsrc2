
#ifndef _IMP_COM_TYPE_H_
#define _IMP_COM_TYPE_H_

#include "imp_algo_type.h"


#ifdef __cplusplus
extern "C"
{
#endif


#define IMP_BUF_SIZE_CONTROL	(64-32)
#define IMP_BUF_SIZE_EVENT		(64-32)
#define IMP_BUF_SIZE_VPRO		(16*1024-32)
#define IMP_BUF_SIZE_CONFIG		(128*1024-32)

#define IMP_BUFLEN_PACKET	(1024*512)

#define IMP_EVENT_ID_SLAVE_MIN	0x00000000
#define IMP_EVENT_ID_SLAVE_MAX	0xFFFFFFFF

// ״̬��
typedef enum _STATUS_E
{
	IMP_STATUS_SUCCESS				= 0x00000000,
	IMP_STATUS_COMMAND				= 0x00010000,
	IMP_STATUS_ERROR				= 0x00080000,
	IMP_STATUS_ERROR_NOT_FOUND		= 0x00080001,
	IMP_STATUS_ERROR_NOT_SUPPORTED	= 0x00080002
} IMP_STATUS_E;

// ����ͨ������
typedef struct impOPER_DATA_S
{
	IMP_U32	u32Size;							// ���ݰ�����
	IMP_U32	u32Type;							// ����
	IMP_U32	u32Status;						// ״̬
	IMP_U32	u32Channel;						// ͨ����
	IMP_U32	u32Time;							// ʱ��
	IMP_U32	u32Date;							// ����
	IMP_U32	u32Id;								// ��ʶ
	IMP_U32	u32Level;							// ��������
} IMP_OPER_DATA_S;


///////////////////////////////////////////////////////////////////////////////////////////////////
// ���������������

// ��������
typedef enum impCONTROL_TYPE_E
{
	IMP_CONTROL_TYPE_BASE = 0x1000,

	IMP_CONTROL_TYPE_VDR_Arm					= 0x1000,			// ��������
	IMP_CONTROL_TYPE_VDR_Arm_Rsp				= 0x1001,			// ��������Ӧ��

	IMP_CONTROL_TYPE_VDR_Disarm					= 0x1002,			// �������
	IMP_CONTROL_TYPE_VDR_Disarm_Rsp			    = 0x1003,			// �������Ӧ��

	IMP_CONTROL_TYPE_VDR_ClearAlarm			    = 0x1004,			// �������
	IMP_CONTROL_TYPE_VDR_ClearAlarm_Rsp     	= 0x1005,			// �������Ӧ��

	IMP_CONTROL_TYPE_END
} IMP_CONTROL_TYPE_E;

typedef struct
{
	IMP_U32 u32AlgoModule;
}CONTROL_DATA_S;

typedef union impCONTROL_DATA_INTERNAL_U
{
	IMP_U8 au8Buffer[IMP_BUF_SIZE_CONTROL];
	CONTROL_DATA_S stControlData;
} IMP_CONTROL_DATA_INTERNAL_U;

typedef struct impIMP_CONTROL_DATA_S
{
	IMP_OPER_DATA_S stHead;						// ����ͷ
	IMP_CONTROL_DATA_INTERNAL_U unData;			// ��������
} IMP_CONTROL_DATA_S;

// ���Ʋ��������������
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// �¼������������

// �¼����ݸ�ʽ

typedef enum impEVENT_TYPE_E
{
	IMP_EVENT_TYPE_BASE = 0x2000,

	IMP_EVENT_TYPE_PEA_EVENT	= 0x2001,		// PEA�¼�����
	IMP_EVENT_TYPE_AVD_EVENT	= 0x2002,		// AVD�¼�����
	IMP_EVENT_TYPE_VFD_EVENT	= 0x2004,		// VFD�¼�����
    IMP_EVENT_TYPE_AAI_EVENT	= 0x2008,		// VFD�¼�����

	IMP_EVENT_TYPE_END
} IMP_EVENT_TYPE_E;

typedef union impEVENT_DATA_INTERNAL_U
{
	IMP_U8 au8Buffer[IMP_BUF_SIZE_EVENT];
	EVT_ITEM_S	stDataEvent;						// �¼�
} IMP_EVENT_DATA_INTERNAL_U;

typedef struct impEVENT_DATA_S
{
	IMP_OPER_DATA_S stHead;						// ����ͷ
	IMP_EVENT_DATA_INTERNAL_U unData;				// �¼�����
} IMP_EVENT_DATA_S;

// �¼������������
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ƶ���������������

// ��Ƶ��������
typedef enum impVPRO_TYPE_E
{
	IMP_VPRO_TYPE_BASE = 0x3000,

	IMP_VPRO_TYPE_PEA_TARGET_SET	= 0x3001,		// ��Ƶ����Ŀ��
	IMP_VPRO_TYPE_AVD_TARGET_SET	= 0x3002,		// ��Ƶ����Ŀ��
	IMP_VPRO_TYPE_VFD_TARGET_SET	= 0x3004,		// ��Ƶ����Ŀ��
    IMP_VPRO_TYPE_AAI_TARGET_SET	= 0x3005,

	IMP_VPRO_TYPE_END
} IMP_VPRO_TYPE_E;

// ��Ƶ�������ݸ�ʽ

typedef union impVPRO_DATA_INTERNAL_U
{
	IMP_U8 au8Buffer[IMP_BUF_SIZE_VPRO];
	TGT_SET_S	stTargetSet;					// Ŀ�꼯��
} IMP_VPRO_DATA_INTERNAL_U;

typedef struct impVPRO_DATA_S
{
	IMP_OPER_DATA_S stHead;						// ����ͷ
	IMP_VPRO_DATA_INTERNAL_U unData;				// ��Ƶ��������
} IMP_VPRO_DATA_S;

// ��Ƶ���������������
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// ���������������

typedef enum impCONFIG_TYPE_E
{
	IMP_CONFIG_TYPE_BASE = 0x4000,

	IMP_CONFIG_TYPE_SetAlgoModule								= 0x4000,		// �����㷨ģ��
	IMP_CONFIG_TYPE_GetAlgoModule								= 0x4001,		// ��ȡ�㷨ģ��

	IMP_CONFIG_TYPE_SetVideoSourceMode					= 0x4100,		// ������Ƶ������ʽ
	IMP_CONFIG_TYPE_GetVideoSourceMode					= 0x4101,		// ��ȡ��Ƶ������ʽ
	IMP_CONFIG_TYPE_SetSysTime									= 0x4102,		// ����ϵͳʱ��
	IMP_CONFIG_TYPE_GetSysTime									= 0x4103,		// ��ȡϵͳʱ��
	IMP_CONFIG_TYPE_SetSecretCode								= 0x4104,		// ����ϵͳ�ļ���оƬֵ
	IMP_CONFIG_TYPE_GetSecretCode								= 0x4105,		// ��ȡϵͳ�ļ���оƬֵ

	IMP_CONFIG_TYPE_SetAlgoLibInfo							= 0x4200,		// �����㷨����Ϣ
	IMP_CONFIG_TYPE_GetAlgoLibInfo							= 0x4201,		// ��ȡ�㷨����Ϣ

	IMP_CONFIG_TYPE_SetPeaRulePara							= 0x4300,		// ����PEA��Ƶ��������
	IMP_CONFIG_TYPE_GetPeaRulePara							= 0x4301, 	// ��ȡPEA��Ƶ��������
	IMP_CONFIG_TYPE_SetAvdRulePara							= 0x4302,		// ����AVD��Ƶ��������
	IMP_CONFIG_TYPE_GetAvdRulePara							= 0x4303, 	// ��ȡAVD��Ƶ��������
	IMP_CONFIG_TYPE_SetVfdRulePara							= 0x4304,		// ����VFD��Ƶ��������
	IMP_CONFIG_TYPE_GetVfdRulePara							= 0x4305, 	// ��ȡVFD��Ƶ��������
    IMP_CONFIG_TYPE_SetAaiRulePara							= 0x4306,		// ����VFD��Ƶ��������
	IMP_CONFIG_TYPE_GetAaiRulePara							= 0x4307,

	IMP_CONFIG_TYPE_SetPeaAdvancePara						= 0x4400,		// ����PEA��Ƶ�����߼�����
	IMP_CONFIG_TYPE_GetPeaAdvancePara						= 0x4401, 	// ��ȡPEA��Ƶ�����߼�����
	IMP_CONFIG_TYPE_SetAvdAdvancePara						= 0x4402,		// ����AVD��Ƶ�����߼�����
	IMP_CONFIG_TYPE_GetAvdAdvancePara						= 0x4403, 	// ��ȡAVD��Ƶ�����߼�����
	IMP_CONFIG_TYPE_SetVfdAdvancePara						= 0x4404,		// ����VFD��Ƶ�����߼�����
	IMP_CONFIG_TYPE_GetVfdAdvancePara						= 0x4405, 	// ��ȡVFD��Ƶ�����߼�����
    IMP_CONFIG_TYPE_SetAaiAdvancePara						= 0x4406,		// ����VFD��Ƶ�����߼�����
	IMP_CONFIG_TYPE_GetAaiAdvancePara						= 0x4407, 	// ��ȡVFD��Ƶ�����߼�����

	IMP_CONFIG_TYPE_END
} IMP_CONFIG_TYPE_E;

// �������ݸ�ʽ

typedef union
{
	IMP_U8 au8Buffer[IMP_BUF_SIZE_CONFIG];
} IMP_CONFIG_DATA_INTERNAL_U;

typedef struct  impCONFIG_DATA_S
{
	IMP_OPER_DATA_S stHead;				// ����ͷ
	IMP_CONFIG_DATA_INTERNAL_U unData;		// ��������
} IMP_CONFIG_DATA_S;

typedef enum impVIDEO_STREAM_E
{
	IMP_VIDEO_STREAM_TYPE_BASE = 0x5000,

	IMP_VIDEO_STREAM_TYPE_VENC_H264									= 0x5000,		//
	IMP_VIDEO_STREAM_TYPE_VENC_MJPEG								= 0x5001,		//
	IMP_VIDEO_STREAM_TYPE_VENC_MPEG2								= 0x5002,		//
	IMP_VIDEO_STREAM_TYPE_VENC_MPEG4								= 0x5003		//

}IMP_VIDEO_STREAM_E;


#ifdef __cplusplus
}
#endif


#endif


