
//////////////////////////////////////////////////////////////////////////
///    COPYRIGHT NOTICE
///    Copyright (c) 2010, �������ټ������޹�˾
///    All rights reserved.
///
/// @file avd_ptz.c
/// @brief AVDϵ�� - PTZʧ�ؼ��ģ�飨����
///
/// AVD PTZʧ�ؼ�⺯���������
///
/// @version 1.0
/// @author ���ټ���
/// @date 2010.12.23
///
///
///    �޶�˵��������汾
//////////////////////////////////////////////////////////////////////////

#include "imp_avd_ptz.h"



void AVD_ptzAnalysis( AVD_MODULE* avdModule, IMP_U32 u32ExtScnChg)
{
	IMP_S32 ratio = 0;
 	IMP_S32 flag_change = avdModule->flag_change;
 	static IMP_S32 chgCnt = 0;
    static IMP_S32 cnt = 0;
    static IMP_S32 s32AlarmDelay = 10;
    static u32ExtScnChgFlag = 0;
	IMP_S32 level = avdModule->Para.stPtzLoseCtlPara.u32AlarmLevel;


    if(u32ExtScnChg)
    {
        u32ExtScnChgFlag = 0;
        chgCnt = 0;
        cnt = 0;
        ratio = 0;
        avdModule->ptzValue = ratio;
        return;
    }


	if ( flag_change )
		chgCnt++;			   // �����任����

	cnt++;

	if(cnt >= AVD_PTZ_CNT_HIGH*level)
    {
        chgCnt = 0;
        cnt = 0;
        ratio = 0;
    }


    if(chgCnt >= AVD_PTZ_CHG_CNT && cnt >= AVD_PTZ_CNT_LOW)
    {
		ratio = 100;
    }
    else
    {
        ratio = 0;
    }

    if(ratio == 100)
    {
		chgCnt = 0;
        cnt = 0;
        u32ExtScnChgFlag = 1;
    }


	avdModule->ptzValue = ratio;

	return;
}
