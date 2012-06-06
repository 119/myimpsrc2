/**
* \defgroup VFD
* IMPOWER VFD����㷨
* @author �������ټ���
* @version 1.0
* @data 2009-1010
*/
/*@{*/

#ifndef _IMP_VFD_HAAR_H_
#define _IMP_VFD_HAAR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include "imp_algo_type.h"
#include "imp_vfd_type.h"
#include "imp_vfd_xtype.h"
#include "imp_vfd_matrix.h"
#include "imp_vfd_para.h"

#define IMP_HAAR_MAGIC_VAL    0x42500000

/** ������ */
typedef struct impFUNC_TABLE_S
{
    void*   fn_2d[IMP_DEPTH_MAX]; /**< ������ */
}FUNC_TABLE_S;

/** compatible return codes */
typedef enum IMP_Status
{         
    IMP_BADMEMBLOCK_ERR          = -113,
	IMP_INPLACE_NOT_SUPPORTED_ERR= -112,
	IMP_UNMATCHED_ROI_ERR        = -111,
	IMP_NOTFOUND_ERR             = -110,
	IMP_BADCONVERGENCE_ERR       = -109,
	
	IMP_BADDEPTH_ERR             = -107,
	IMP_BADROI_ERR               = -106,
	IMP_BADHEADER_ERR            = -105,
	IMP_UNMATCHED_FORMATS_ERR    = -104,
	IMP_UNSUPPORTED_COI_ERR      = -103,
	IMP_UNSUPPORTED_CHANNELS_ERR = -102,
	IMP_UNSUPPORTED_DEPTH_ERR    = -101,
	IMP_UNSUPPORTED_FORMAT_ERR   = -100,
	
	IMP_BADARG_ERR      = -49,  
	IMP_NOTDEFINED_ERR  = -48,  
	
	IMP_BADCHANNELS_ERR = -47,  
	IMP_BADRANGE_ERR    = -44,  
	IMP_BADSTEP_ERR     = -29,  
		
	IMP_BADFLAG_ERR     =  -12,
	IMP_DIV_BY_ZERO_ERR =  -11, 
	IMP_BADCOEF_ERR     =  -10,
	
	IMP_BADFACTOR_ERR   =  -7,
	IMP_BADPOINT_ERR    =  -6,
	IMP_BADSCALE_ERR    =  -4,
	IMP_OUTOFMEM_ERR    =  -3,
	IMP_NULLPTR_ERR     =  -2,
	IMP_BADSIZE_ERR     =  -1,
	IMP_NO_ERR          =   0,
	IMP_OK              =   IMP_NO_ERR
}
IMP_Status;



IMP_API_EX( IMP_Status, icvIntegral_8u32s_C1R,
            "ippiIntegral_8u32s_C1R", IMP_PLUGINS1(IMP_PLUGIN_IPPCV),
            ( const unsigned char* pSrc, int srcStep, int* pDst, int dstStep,
              Imp_Size roiSize, int val ))

IMP_API_EX( IMP_Status, icvSqrIntegral_8u32s64f_C1R,
            "ippiSqrIntegral_8u32s64f_C1R", IMP_PLUGINS1(IMP_PLUGIN_IPPCV),
            ( const unsigned char* pSrc, int srcStep,
              int* pDst, int dstStep, double* pSqr, int sqrStep,
              Imp_Size roiSize, int val, double valSqr ))

IMP_API_EX( IMP_Status, icvRectStdDev_32s32f_C1R,
            "ippiRectStdDev_32s32f_C1R", IMP_PLUGINS1(IMP_PLUGIN_IPPCV),
            ( const int* pSrc, int srcStep,
              const double* pSqr, int sqrStep, float* pDst, int dstStep,
              Imp_Size roiSize, Imp_Rect rect ))

IMP_API_EX( IMP_Status, icvHaarClassifierInitAlloc_32f,
            "ippiHaarClassifierInitAlloc_32f", IMP_PLUGINS1(IMP_PLUGIN_IPPCV),
            ( void **pState, const Imp_Rect* pFeature, const float* pWeight,
              const float* pThreshold, const float* pVal1,
              const float* pVal2, const int* pNum, int length ))

IMP_API_EX( IMP_Status, icvHaarClassifierFree_32f,
            "ippiHaarClassifierFree_32f", IMP_PLUGINS1(IMP_PLUGIN_IPPCV),
            ( void *pState ))

IMP_API_EX( IMP_Status, icvApplyHaarClassifier_32s32f_C1R,
            "ippiApplyHaarClassifier_32s32f_C1R", IMP_PLUGINS1(IMP_PLUGIN_IPPCV),
            ( const int* pSrc, int srcStep, const float* pNorm,
              int normStep, unsigned char* pMask, int maskStep,
              Imp_Size roi, int *pPositive, float threshold,
              void *pState ))


/** canny���˱�� */
#define IMP_HAAR_DO_CANNY_PRUNING 1
/** ͼ������ */
#define IMP_HAAR_SCALE_IMAGE      2


/** �������ģ��ṹ */
typedef struct impVFD_HAAR_MODULE
{
	GRAY_IMAGE_S temp;                  /**< �ݴ�Ҷ�ͼ */
	IMP_U64 *integralImage;             /**< ����ͼ��(W+1)��(H+1), ��ͨ����64λ������ƽ������ͼ��ռ��0-35λ������ͼ��ռ��36-59λ */
	IMP_S32 *sumcanny;                  /**< cannyͼ��Ļ���ͼ */
	GRAY_IMAGE16_S stImgInEdgeGrad;		/**< �ݶ�ͼ */
	GRAY_IMAGE_S stImageEdgeMag;        /**< ����ͼ */
	
    IMP_Mat *sum;                       /**< ����ͼ */
	IMP_Mat *sum2;                      /**< ����ͼ */
	IMP_Mat *tilted;                    /**< ��ת����ͼ */
	IMP_Mat *sqsum;                     /**< ƽ������ͼ */
	IMP_Mat *norm_img;                  /**< �����ߴ��ͼ�� */
	IMP_Mat *img_small;                 /**< �任�ߴ��ͼ����С�� */
    IMP_Seq* seq;                       /**< ���� */
    IMP_Seq* seq2;                      /**< ���� */
    IMP_Seq* idx_seq;                   /**< ��Ŷ��� */
    IMP_Seq* result_seq;                /**< ����������� */
	IMP_S32 s32ImgW;                    /**< ͼ���� */
	IMP_S32 s32ImgH;                    /**< ͼ��߶� */
	
	IMP_MemStorage* storage;            /**< �洢�� */
	IMP_VFD_PARA_S m_stVfdPara;         /**< ���������� */
	VFD_RESULT_S m_stVfdResult;         /**< ������⴦��ӹ� */

	IMP_HaarClassifierCascade* Cascade; /**< ������ */

}VFD_HAAR_MODULE;

/**
* Haar�������
* @param module �������ģ����
* @param _img ����ͼ�� 
* @param cascade harr �������������ڲ���ʶ��ʽ 
* @param storage �����洢��⵽��һ���к�ѡĿ����ο���ڴ����� 
* @param scale_factor ��ǰ��������̵�ɨ���У��������ڵı���ϵ��������1.1ָ������������������10%��
* @param min_neighbors ���ɼ��Ŀ������ھ��ε���С����(ȱʡ��1)�������ɼ��Ŀ���С���εĸ�����С��min_neighbors-1 ���ᱻ�ų������min_neighbors Ϊ 0, ���������κβ����ͷ������еı����ѡ���ο������趨ֵһ�������û��Զ���Լ��������ϳ����ϡ� 
* @param flags ������ʽ����ǰΨһ���Զ���Ĳ�����ʽ�� IMP_HAAR_DO_CANNY_PRUNING��������趨����������Canny��Ե��������ų�һЩ��Ե���ٻ��ߺܶ��ͼ��������Ϊ����������һ�㲻������Ŀ�ꡣ���������ͨ���趨��ֵʹ�������ַ��������������˼���ٶȡ� 
* @param min_size ��ⴰ�ڵ���С�ߴ硣ȱʡ������±���Ϊ������ѵ��ʱ���õ������ߴ�(���������ȱʡ��С��~20��20)�� 
* @return ������λ�Ľ��
*/
IMP_EXPORTS IMP_Seq* IMP_HaarDetectObjects( VFD_HAAR_MODULE *module, const GRAY_IMAGE_S* _img,
										   IMP_HaarClassifierCascade* cascade,
										   IMP_MemStorage* storage, double scale_factor,
					                       int min_neighbors, int flags, Imp_Size min_size );

/**
* ��������������
* @param stage_count �������׶���
* @return ������
*/
IMP_EXPORTS IMP_HaarClassifierCascade* IMP_CreateHaarClassifierCascade( int stage_count );
/**
* �ͷ�����������
* @param cascade ������
*/
IMP_EXPORTS void IMP_ReleaseHaarClassifierCascade( IMP_HaarClassifierCascade** cascade );

/**
* ��������������
* @param pPathName �������ı��ļ�������
* @return ������
*/
IMP_EXPORTS IMP_HaarClassifierCascade* IMP_CreateHaarClassifier(char* pPathName);
/**
* �ͷ�����������
* @param cascade ������
*/
IMP_EXPORTS void IMP_ReleaseHaarClassifier(IMP_HaarClassifierCascade** _cascade);

/**
* ��ȡ����������
* @param pPathName �������ı��ļ�������
* @param cascade ������
*/
IMP_EXPORTS void IMP_ReadHaarClassifierCascade(char* pPathName,IMP_HaarClassifierCascade* cascade);
/**
* д������������
* @param cascade ������
* @param pPathName �������ı��ļ�������
*/
IMP_EXPORTS  void IMP_WriteHaarClassifierCascade(IMP_HaarClassifierCascade* cascade,char* pPathName);

/**
* ��������������
* @param module ������ģ����
* @param storage �洢��
* @param pPathName �������ı��ļ�������
* @return ������
*/
IMP_EXPORTS IMP_HaarClassifierCascade* IMP_CreateHaar(VFD_HAAR_MODULE *module, IMP_MemStorage* storage, char* pPathName);
/**
* �ͷ�����������
* @param module ������ģ����
* @param cascade ������
*/
IMP_EXPORTS void IMP_ReleaseHaar(VFD_HAAR_MODULE *module,IMP_HaarClassifierCascade** _cascade);

#ifdef __cplusplus
}
#endif

#endif
/*@}*/