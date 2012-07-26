
#ifndef _IMP_TRACKER_H_
#define _IMP_TRACKER_H_


#include "imp_pea_common.h"


#ifdef __cplusplus
extern "C"
{
#endif

//�㷨���ò���
typedef struct impTrackerPara_S
{
	IMP_S32 s32S; //amount of subsampling, default value:2
}IMP_TrackerPara_S;


/***************************************************
name:IMP_GetMemSizeTracker
do:�õ��㷨����Ҫ���ڴ��С
input:
	pstResult:ϵͳ��������
output:�㷨��Ҫ���ڴ��С
history:
****************************************************/
IMP_S32 IMP_GetMemSizeTracker( PEA_RESULT_S *pstResult );


/***************************************************
name:IMP_CreateTracker
do:�����㷨�ڴ沢ʼ���㷨����
input:
	pstResult:ϵͳ��������
	pHwResource:ϵͳӲ����Դ
output:
	0:ʧ��
	��0:���
history:
****************************************************/
IMP_MODULE_HANDLE IMP_CreateTracker( PEA_RESULT_S *pstResult, GA_HARDWARE_RS_S *pstHwResource );


/***************************************************
name:IMP_ReleaseTracker
do:�ͷ��㷨�ڴ�
input:
	hModule:�㷨ģ����
output:
	0:�ɹ�
	��0:ʧ��
history:
****************************************************/
IMP_S32 IMP_ReleaseTracker( IMP_MODULE_HANDLE hModule );


/***************************************************
name:IMP_ConfigTracker
do:�����㷨����
input:
	hModule:�㷨ģ����
	pstPara:�������ýṹ��
output:
	0:�ɹ�
	��0:ʧ��
history:
****************************************************/
IMP_S32 IMP_ConfigTracker( IMP_MODULE_HANDLE hModule, IMP_TrackerPara_S *pstPara );


/***************************************************
name:IMP_ProcessTracker
do:�㷨������
input:
	hModule:�㷨ģ����
output:
	0:�ɹ�
	��0:ʧ��
history:
****************************************************/
IMP_S32 IMP_ProcessTracker( IMP_MODULE_HANDLE hModule );


#ifdef __cplusplus
}
#endif

#endif



