
#include "imp_avd_change.h"


IMP_S32 AVD_changeAnalysis( AVD_MODULE* avdModule )
{
	AVD_HISTOGROUP * pHistGrayImgDiff = &avdModule->histGrayImgDiff;
	IMP_S32 val = pHistGrayImgDiff->histAll.bin[IP_HIST_LEVEL-1];  //��ֵͼ�����һ��bin���ڴ洢ǰ�����ص����
	IMP_S32 w = avdModule->YImg.s32W;
	IMP_S32 h = avdModule->YImg.s32H;
	IMP_S32 changeFrm = 0;
	IMP_S32 ratio = 0;

	if (avdModule->prcFrmCnt <= AVD_CHANGE_NO_PROCESS_FRM) //ǰN֡ ��������
	{
		ratio = 0;
		changeFrm = 0;
	}
	else
	{
		if (val * 100 > AVD_CHANGE_RATIO_TH * w * h  )
			changeFrm ++;				// �ۻ��䶯֡
		else
			changeFrm = 0;
	}

	if (changeFrm >= AVD_CHANGE_MIN_FRM)
		ratio = 100;					// ����
	else
		ratio = 0;					// �������

    //printf("val=%d,%d,%d,%d,%d\n",val,w,h,changeFrm,ratio);
	return ratio;
}


#define AVD_IR_NO_PROCESS_FRM 5
#define AVD_IR_MIN_FRM 20
IMP_BOOL AVD_irAnalysis( AVD_MODULE* avdModule )
{
	AVD_HISTOGROUP * pHistUImg = &avdModule->histUImg;
	AVD_HISTOGROUP * pHistVImg = &avdModule->histVImg;
	AVD_HISTOGROUP * pHistRImg = &avdModule->histRImg;
	AVD_HISTOGROUP * pHistGImg = &avdModule->histGImg;
	AVD_HISTOGROUP * pHistBImg = &avdModule->histBImg;

	IMP_S32 UMean = pHistUImg->meanAll;
	IMP_S32 VMean = pHistVImg->meanAll;

	IMP_S32 RMean = pHistRImg->meanAll;
	IMP_S32 GMean = pHistGImg->meanAll;
	IMP_S32 BMean = pHistBImg->meanAll;

	IMP_S32 w = avdModule->imgW;
	IMP_S32 h = avdModule->imgH;
	IMP_S32 diff1,diff2,diff3,i;
	IMP_S32 vr;
	static IMP_S32 irFrm = AVD_IR_MIN_FRM/2;
	IMP_S32 result;

	//R,G,B����ֵ�ͷ����������U,V�ľ�ֵ��128��������ֵ��3��bin����
	if (avdModule->prcFrmCnt <= AVD_IR_NO_PROCESS_FRM) //ǰN֡ ��������
	{
		result = 0;
//		irFrm = AVD_IR_MIN_FRM/2;
		diff1 = 0;
		diff2 = 0;
		diff3 = 0;
		vr = 0;
	}
	else
	{
		diff1 = abs(UMean-128)+abs(VMean-128);
		diff2 = abs(RMean-BMean)+abs(RMean-GMean)+abs(BMean-GMean);
		diff3 = 0;

		for (i=0;i<IP_HIST_LEVEL;i++)
		{
			diff3  = abs(pHistRImg->histAll.bin[i]-pHistGImg->histAll.bin[i]);
			diff3 += abs(pHistRImg->histAll.bin[i]-pHistBImg->histAll.bin[i]);
			diff3 += abs(pHistGImg->histAll.bin[i]-pHistBImg->histAll.bin[i]);
		}

		vr = pHistUImg->stdDevAll + pHistVImg->stdDevAll;

		if ( diff1<=3 && diff2<=14 && diff3<=200 && vr<=2)
		{
			irFrm ++;				// �ۻ��䶯֡
		}
		else
		{
			irFrm --;
		}

		if (irFrm > AVD_IR_MIN_FRM)
		{
			irFrm = AVD_IR_MIN_FRM;
		}
		if (irFrm < 0)
		{
			irFrm = 0;
		}
	}

	if (irFrm >= AVD_IR_MIN_FRM/2)
		result = IR_MODE;					// ����
	else
		result = NORMAL_MODE;				// �ɼ���

//    printf("IR=%d irFrm=%d diff1=%d diff2=%d diff3=%d vr=%d\n",result,irFrm,diff1,diff2,diff3,vr);
	return result;
}
