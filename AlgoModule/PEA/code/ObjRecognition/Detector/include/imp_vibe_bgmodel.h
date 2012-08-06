
#ifndef _IMP_VIBE_BG_MODEL_H_
#define _IMP_VIBE_BG_MODEL_H_


#include "imp_pea_common.h"


#ifdef __cplusplus
extern "C"
{
#endif

//�㷨���ò���
typedef struct impViBePara_S
{
	IMP_S32 s32BkgUR; //���������ٶ�1~120
}IMP_ViBePara_S;



PEA_RESULT_S *pstResult;


/***************************************************
name:IMP_GetMemSizeViBe
do:�õ��㷨����Ҫ���ڴ��С
input:
	pstResult:ϵͳ��������
output:�㷨��Ҫ���ڴ��С
history:
****************************************************/
IMP_S32 IMP_GetMemSizeViBe(IMP_S32 s32Width, IMP_S32 s32Height);


/***************************************************
name:IMP_CreateViBe
do:�����㷨�ڴ沢ʼ���㷨����
input:
	pstResult:ϵͳ��������
	pHwResource:ϵͳӲ����Դ
output:
	0:ʧ��
	��0:���
history:
****************************************************/
IMP_MODULE_HANDLE IMP_CreateViBe( PEA_RESULT_S *pstResult, GA_HARDWARE_RS_S *pstHwResource );


/***************************************************
name:IMP_ReleaseViBe
do:�ͷ��㷨�ڴ�
input:
	hModule:�㷨ģ����
output:
	0:�ɹ�
	��0:ʧ��
history:
****************************************************/
IMP_S32 IMP_ReleaseViBe( IMP_MODULE_HANDLE hModule );


/***************************************************
name:IMP_ConfigViBe
do:�����㷨����
input:
	hModule:�㷨ģ����
	pstPara:�������ýṹ��
output:
	0:�ɹ�
	��0:ʧ��
history:
****************************************************/
IMP_S32 IMP_ConfigViBeModel( IMP_MODULE_HANDLE hModule, IMP_ViBePara_S *pstPara );


/***************************************************
name:IMP_ProcessViBe
do:�㷨������
input:
	hModule:�㷨ģ����
output:
	0:�ɹ�
	��0:ʧ��
history:
****************************************************/
IMP_S32 IMP_ProcessViBe( IMP_MODULE_HANDLE hModule );


#ifdef __cplusplus
}
#endif

#endif



