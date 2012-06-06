
//////////////////////////////////////////////////////////////////////////
///    COPYRIGHT NOTICE
///    Copyright (c) 2010, �������ټ������޹�˾
///    All rights reserved.
///
/// @file avd_conf.h
/// @brief AVDϵ�� - ����ģ�飨������
///
/// AVD�ź�ȱʧ��⺯���������
///
/// @version 1.0
/// @author ���ټ���
/// @date 2010.12.26
///
///
///    �޶�˵��������汾
//////////////////////////////////////////////////////////////////////////
#include "imp_avd_para.h"

#ifndef _IMP_AVD_CONF_H_
#define _IMP_AVD_CONF_H_

typedef struct impAVD_ADVAN_PARA_S
{
	IMP_U8 u8NoiseThrd[MODE_CNT][LEVEL_CNT+1][THRSHLD_CNT];		///< �������˫��ֵ
	IMP_U8 u8BrightHThrd[MODE_CNT][LEVEL_CNT+1][THRSHLD_CNT];	///< �������˫��ֵ
	IMP_U8 u8BrightLThrd[MODE_CNT][LEVEL_CNT+1][THRSHLD_CNT];	///< �������˫��ֵ
	IMP_U8 u8ClarityThrd[MODE_CNT][LEVEL_CNT+1][THRSHLD_CNT];	///< �����ȼ��˫��ֵ
	IMP_U8 u8ColorThrd[MODE_CNT][LEVEL_CNT+1][THRSHLD_CNT];		///< ƫɫ���˫��ֵ
	
	IMP_U8 u8FreezePara[MODE_CNT][LEVEL_CNT+1][PARA_CNT];		///< ���涳����߼�����
	IMP_U8 u8NosignalPara[MODE_CNT][LEVEL_CNT+1][PARA_CNT];		///< �ź�ȱʧ���߼�����
	IMP_U8 u8ChangePara[MODE_CNT][LEVEL_CNT+1][PARA_CNT];		///< �����任���߼�����
	IMP_U8 u8InterferePara[MODE_CNT][LEVEL_CNT+1][PARA_CNT];	///< ��Ϊ���ż��߼�����
	IMP_U8 u8PtzLoseCtlPara[MODE_CNT][LEVEL_CNT+1][PARA_CNT];	///< PTZʧ�ؼ��߼�����
}
IMP_AVD_ADVAN_PARA_S;

void AVD_setDefaultUserParameter( IMP_AVD_PARA_S* pstUsrPara );
void AVD_checkUserParameter( IMP_AVD_PARA_S* pstUsrPara );
void AVD_setAdvancedParameter( IMP_AVD_PARA_S* pstUsrPara, IMP_AVD_ADVAN_PARA_S* pstAdvPara );

#endif /*_IMP_AVD_CONF_H_*/
