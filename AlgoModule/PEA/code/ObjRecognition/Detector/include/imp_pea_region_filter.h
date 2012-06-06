/** 
* \defgroup �������
* �������
* @ingroup ������ģ
* @author �������ټ���
* @version 1.0
* @data 2009-2010
*/
/*@{*/
#ifndef _IMP_PEA_REGION_FILTER_H_
#define _IMP_PEA_REGION_FILTER_H_

#include "imp_pea_common.h"

///<������˲���
typedef struct  
{
	IMP_S32 s32RgeFilterEnable;             /**< ����������� */
	IMP_S32 s32ThRgeFilterrMinEdge;         /**< ���������С�ݶ� */
	IMP_S32 s32ThRgeFilterMinWidth;         /**< ���������С��� */
	IMP_S32 s32ThRgeFilterMinHeight;        /**< ���������С�߶� */
	IMP_S32 s32ThRgeFilterMinAreaPixel;     /**< �������������������� */
} IpRGEFilterPara;

/**
* ���򼯺Ϲ��˼��
* @param pstPara ��Ӱ����
* @param pstRgs ����Ŀ�꼯��
* @param pstShadow ��Ӱͼ��
*/
IMP_VOID ipRegionSetFilterDetect( IpRGEFilterPara *pstPara, PEA_DETECTED_REGIONSET_S *pstRgs );

/**
* ������˼��
* @param pstPara ������˲���
* @param pstRgs �������򼯺�
* @param s32RegionIndex ��������
*/
static IMP_VOID ipRegionFilterDetect( IpRGEFilterPara *pstPara, PEA_DETECTED_REGIONSET_S *pstRgs, IMP_S32 s32RegionIndex );
#endif /*_IMP_PEA_SHADOW_MODLE_H_*/

/*@}*/
