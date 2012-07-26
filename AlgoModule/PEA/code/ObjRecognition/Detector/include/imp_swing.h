
#ifndef _IMP_SWING_MODEL_H_
#define _IMP_SWING_MODEL_H_


#include "imp_pea_common.h"


#ifdef __cplusplus
extern "C"
{
#endif

//�㷨���ò���
typedef struct impSwingPara_S
{
	IMP_S32 s32Tmp; 
}IMP_SwingPara_S;


typedef struct impswing_S
{
	GA_HARDWARE_RS_S  *pstHwResource;
	PEA_RESULT_S *pstResult; 

	IMP_UCHAR * p00;
	IMP_UCHAR * p01;
	IMP_UCHAR * p02;
	IMP_UCHAR * p10;
	IMP_UCHAR * p11;
	IMP_UCHAR * p12;
	IMP_UCHAR * p20;
	IMP_UCHAR * p21;
	IMP_UCHAR * p22;
	//IMP_UCHAR * Img[9];
	IMP_UCHAR * zSadmin;
	IMP_UCHAR * vSadmin;
	IMP_UCHAR * inMask;
	IMP_UCHAR * swImg;

}IMP_Swing_S;

IMP_S32 IMP_ShowImg(IMP_UCHAR*srcGray,IMP_S32 Height,IMP_S32 Width,IMP_UCHAR*widoName);

IMP_S32 IMP_BinaryImg(IMP_UCHAR *srcGray,IMP_UCHAR *BinMask,IMP_S32 val,IMP_S32 Lenght);
/*/�õ�srcGray�Ķ�ֵͼ,������val�ĸ�ֵΪ255�������ĸ�ֵΪ0��������BinMask�У�Length��ͼ��ġ���X��/*/

IMP_S32 IMP_StatiPix(IMP_UCHAR*srcGray,IMP_UCHAR*statiImg,IMP_S32 ImgH,IMP_S32 ImgW);
/*/�õ�srcGray���ۼ�ͼ��/*/
/*/�ò���֮ǰ��Ҫ��statiImgͼ����й���/*/
/*/srcGrayͼ��������ֵ����0����statiImg��Ӧλ��Ӧ��+1/*/
/*/srcGrayͼ��������ֵΪ0����statiImg��Ӧλ��Ӧ��-1/*/
/*/����ֵ����255ʱ��statiImg��ֵΪ255/*/
/*/����ֵС��0��statiImg��ֵΪ0/*/

IMP_S32 IMP_Proporte(IMP_UCHAR*backGray,IMP_UCHAR*srcGray,IMP_UCHAR*proMat1,IMP_UCHAR*proMat2,IMP_S32 Length);
/*/�õ�ͼ������ֵ�ı�ֵͼ��Length��ͼ�������ڴ���ܳ���/*/

IMP_S32 IMP_RectSum(IMP_UCHAR*srcGray,IMP_RECT_S widow,IMP_S32 Height,IMP_S32 Width);
/*/ͼ��srcGray�ھ��ο�widow�е������ܺ�/*/

IMP_S32 IMP_GetSadImg(IMP_Swing_S*PsModel);
/*/�õ�����������SAD��ͼ�񣬷ֱ���������ָ���Ӧ��zSadMin��vSadMin��/*/

IMP_S32 IMP_GetMemSizeSwingModel( PEA_RESULT_S *pstResult);
/*/�õ����㷨������Ҫ�ڴ��ܺ�,�Ѿ��������ڲ������ͼ���ڴ�/*/

IMP_MODULE_HANDLE IMP_CreateSwing(PEA_RESULT_S *pstResult, GA_HARDWARE_RS_S *pstHwResource);
/*/�㷨�ڲ���Ҫ�����в����Ľ������ڴ������Ľ���/*/

IMP_S32 IMP_ProcessSwing(IMP_MODULE_HANDLE hModule);
/*/�㷨�Ĵ������,�㷨�ĺ��ģ���װ�ڴ�/*/

IMP_S32 IMP_ReleaseSwing(IMP_MODULE_HANDLE hModule);
/*/�ͷ��㷨���ڴ�/*/



#ifdef __cplusplus
}
#endif

#endif

