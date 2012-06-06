/**
* \defgroup �ṹ���Ͷ���
* VFD�㷨���ò�������
* @author �������ټ���
* @version 2.0
* @data 2009-2011
*/
/*@{*/
#ifndef _IMP_VFD_PARA_H_
#define _IMP_VFD_PARA_H_

#include "imp_algo_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct impVFD_FACE_CAPTURE_PARA_S
{
	IMP_U32 u32Enable;			///< ����ץ�Ĺ��ܿ��أ�0Ϊ�رգ�1Ϊ����
	IMP_U32 u32AlarmTime;		///< ����ץ�ı���ʱ�䣬��0-20�룩����ֵԽ����Ҫ�ı���ʱ��Խ��
}IMP_VFD_FACE_CAPTURE_PARA_S;

typedef struct impVFD_FACE_CAMOUFLAGE_PARA_S
{
	IMP_U32 u32Enable;			///< ����αװ���ܿ��أ�0Ϊ�رգ�1Ϊ����
	IMP_U32 u32AlarmLevel;		///< ����αװ���������ȣ�1-5������ֵԽ��Խ����Խ�ױ���
	IMP_U32 u32AlarmTime;		///< ����αװ����ʱ�䣬��0-20�룩����ֵԽ����Ҫ�ı���ʱ��Խ��
}IMP_VFD_FACE_CAMOUFLAGE_PARA_S;

typedef struct impVFD_PASSWORD_PEEP_PARA_S
{
	IMP_U32 u32Enable;			///< ����͵�����ܿ��أ�0Ϊ�رգ�1Ϊ����
	IMP_U32 u32AlarmLevel;		///< ����͵�����������ȣ�1-5������ֵԽ��Խ����Խ�ױ���
	IMP_U32 u32AlarmTime;		///< ����͵������ʱ�䣬��0-20�룩����ֵԽ����Ҫ�ı���ʱ��Խ��
}IMP_VFD_PASSWORD_PEEP_PARA_S;

typedef struct impVFD_SCENE_MODE_PARA_S
{
	IMP_U32 IR_mode;				///< ģʽ�л���0Ϊ�ɼ���ģʽ��1Ϊ����ģʽ
}IMP_VFD_SCENE_MODE_PARA_S;

typedef struct impVFD_PARA_S
{
	IMP_VFD_SCENE_MODE_PARA_S stTrigModePara;				///< ����ģʽ����
	IMP_VFD_FACE_CAPTURE_PARA_S stFaceCapturePara;			///< ����ץ�Ĳ���
	IMP_VFD_FACE_CAMOUFLAGE_PARA_S stFaceCamouflagePara;	///< ����αװ����
	IMP_VFD_PASSWORD_PEEP_PARA_S stPasswordPeepPara;		///< ����͵������
}IMP_VFD_PARA_S;

#ifdef __cplusplus
}
#endif

#endif /*_IMP_VFD_PARA_H_*/

/*@}*/
