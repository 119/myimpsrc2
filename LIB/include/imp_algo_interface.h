/**
* \defgroup �ӿ�
* �ӿ�
* @author �������ټ���
* @version 2.1
* @data 2009-2012
*/
/*@{*/


/**
* \defgroup PEA�ӿ�
* PEA�ӿ�
* @ingroup �ӿ�
* @author �������ټ���
* @version 2.1
* @data 2009-2012
*/
/*@{*/
#ifndef _IMP_ALGO_INTERFACE_H_
#define _IMP_ALGO_INTERFACE_H_

#include "imp_algo_type.h"
#include "imp_algo_urp_param.h"
#ifdef __cplusplus
extern "C"
{
#endif

/**
* ��ȡ�汾�ź͹�����
* @param hModule ģ����
* @param pstLibInfo ���ؿ������Ϣ
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_GetAlgoLibInfo( IMP_HANDLE hModule, LIB_INFO_S *pstLibInfo );
/**
* �����ڴ�
* @param hModule ģ����
* @param pstMems ������ڴ�
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_GetMemReq( IMP_HANDLE hModule, MEM_SET_S *pstMems );

/**
* ��������ģ�鲢��ʼ��
* @param hModule ģ����
* @param pstMems ��ʼ�����ڴ�����
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_Create( IMP_HANDLE hModule, MEM_SET_S *pstMems );
/**
* ��ֹ����ģ�鲢�ͷ��ڴ�
* @param hModule ģ����
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_Release( IMP_HANDLE hModule );
/**
* ����Arm PEA�Ĳ���
* @param hModule ģ����
* @param pstParaE �ⲿ����
* @param pstParaURP �û��߼�����
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_ConfigArmPeaParameter( IMP_HANDLE hModule, EXTERNAL_PARA_S *pstParaE ,URP_PARA_S *pstParaURP);
/**
* ���ò���
* @param hModule ģ����
* @param pstParaE �ⲿ����
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_ConfigParameter( IMP_HANDLE hModule, EXTERNAL_PARA_S *pstParaE );
/**
* ��ʼִ���㷨
* @param hModule ģ����
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_Start( IMP_HANDLE hModule );
/**
* ִֹͣ���㷨
* @param hModule ģ����
* @param pstResult ������
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_Stop( IMP_HANDLE hModule, RESULT_S *pstResult );
/**
* ����һ��ͼ��
* @param hModule ģ����
* @param pstImage ͼ��ָ��
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_ProcessImage( IMP_HANDLE hModule, YUV_IMAGE422_S *pstImage );
/**
* ��ȡ������
* @param hModule ģ����
* @param pstResult ͼ��ָ��
* @return STATUS_E ������
*/
IMP_EXPORTS STATUS_E IMP_GetResults( IMP_HANDLE hModule, RESULT_S *pstResult );
/*@}*/


//OSC �ӿ�
/**
* ��������ģ�鲢��ʼ��
* @param hModule ģ����
* @param pstMems ��ʼ�����ڴ�����
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_OSC_Create( IMP_HANDLE hModule, MEM_SET_S *pstMems );
/**
* ��ֹ����ģ�鲢�ͷ��ڴ�
* @param hModule ģ����
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_OSC_Release( IMP_HANDLE hModule );
/**
* ����Arm PEA�Ĳ���
* @param hModule ģ����
* @param pstParaE �ⲿ����
* @param pstParaURP �û��߼�����
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_OSC_ConfigArmPeaParameter( IMP_HANDLE hModule, EXTERNAL_PARA_S *pstParaE ,URP_PARA_S *pstParaURP);
/**
* ���ò���
* @param hModule ģ����
* @param pstParaE �ⲿ����
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_OSC_ConfigParameter( IMP_HANDLE hModule, EXTERNAL_PARA_S *pstParaE );

/**
* ����һ��ͼ��
* @param hModule ģ����
* @param pstImage ͼ��ָ��
* @return STATUS_E ����״̬
*/
IMP_EXPORTS STATUS_E IMP_OSC_ProcessImage( IMP_HANDLE hModule, YUV_IMAGE422_S *pstImage );
/**
* ��ȡ������
* @param hModule ģ����
* @param pstResult ͼ��ָ��
* @return STATUS_E ������
*/
IMP_EXPORTS STATUS_E IMP_OSC_GetResults( IMP_HANDLE hModule, RESULT_S *pstResult );




/**
* \defgroup YUV422ͼ�����
* YUV422ͼ�����
* @ingroup �ӿ�
* @author �������ټ���
* @version 2.0
* @data 2009-2010
*/
/*@{*/
/**
* ����YUV422ͼ��
* @param pstImg YUV422ͼ��ָ��
* @param s32W ͼ����
* @param s32H ͼ��߶�
* @param pMmgr �ڴ������ָ��
*/
IMP_EXPORTS IMP_VOID IMP_YUVImage422Create( YUV_IMAGE422_S *pstImg, IMP_S32 s32W, IMP_S32 s32H, IMP_VOID *pMmgr );
/**
* ����YUV422ͼ��
* @param pstImg YUV422ͼ��ָ��
* @param pMmgr �ڴ������ָ��
*/
IMP_EXPORTS IMP_VOID IMP_YUVImage422Destroy( YUV_IMAGE422_S *pstImg, IMP_VOID *pMmgr );
/**
* ���YUV422ͼ��
* @param pstImg YUV422ͼ��ָ��
*/
IMP_EXPORTS IMP_VOID IMP_YUVImage422Clear( YUV_IMAGE422_S *pstImg );
/**
* ����YUV422ͼ��
* @param pstSrc ԴYUV422ͼ��ָ��
* @param pstDst Ŀ��YUV422ͼ��ָ��
*/
IMP_EXPORTS IMP_VOID IMP_YUVImage422Clone( YUV_IMAGE422_S *pstSrc, YUV_IMAGE422_S *pstDst );


/**
* ����YUV420ͼ��
* @param pstImg YUV420ͼ��ָ��
* @param s32W ͼ����
* @param s32H ͼ��߶�
* @param pMmgr �ڴ������ָ��
*/
IMP_EXPORTS IMP_VOID IMP_YUVImage420Create( YUV_IMAGE420_S *pstImg, IMP_S32 s32W, IMP_S32 s32H, IMP_VOID *pMmgr );
/**
* ����YUV420ͼ��
* @param pstImg YUV420ͼ��ָ��
* @param pMmgr �ڴ������ָ��
*/
IMP_EXPORTS IMP_VOID IMP_YUVImage420Destroy( YUV_IMAGE420_S *pstImg, IMP_VOID *pMmgr );
/**
* ���YUV420ͼ��
* @param pstImg YUV420ͼ��ָ��
*/
IMP_EXPORTS IMP_VOID IMP_YUVImage420Clear( YUV_IMAGE420_S *pstImg );
/**
* ����YUV420ͼ��
* @param pstSrc ԴYUV420ͼ��ָ��
* @param pstDst Ŀ��YUV420ͼ��ָ��
*/
IMP_EXPORTS IMP_VOID IMP_YUVImage420Clone( YUV_IMAGE420_S *pstSrc, YUV_IMAGE422_S *pstDst );
/*@}*/

/**
* \defgroup �ڴ�������ͷ�
* �ڴ�������ͷ�
* @ingroup �ӿ�
* @author �������ټ���
* @version 2.0
* @data 2009-2010
*/
/*@{*/
/**
* �����ڴ�
* @param pstMems �ڴ�ָ��
*/
IMP_EXPORTS IMP_VOID IMP_MemsAlloc( MEM_SET_S *pstMems );
/**
* �ͷ��ڴ�
* @param pstMems �ڴ�ָ��
*/
IMP_EXPORTS IMP_VOID IMP_MemsFree( MEM_SET_S *pstMems );
/*@}*/


/**
* \defgroup �ⲿ��������
* �ⲿ��������
* @ingroup �ӿ�
* @author �������ټ���
* @version 2.0
* @data 2009-2010
*/
/*@{*/

/**
* �����ⲿ���ò���������
* @param s32VanaBufLen vana��������С
* @param s32AdvBufNum �߼���������
* @param s32AdvBufLen �߼�������������С
* @param pMmgr �ڴ�ָ��
* @return EXTERNAL_PARA_S �ⲿ����ָ��
*/
IMP_EXPORTS EXTERNAL_PARA_S* IMP_PARA_Alloc( IMP_S32 s32VanaBufLen,IMP_S32 s32AdvBufNum, IMP_S32 s32AdvBufLen, IMP_VOID *pMmgr );
/**
* �ͷ��ⲿ���ò���������
* @param pstPara �ⲿ����������ָ��
* @param s32AdvBufNum �߼���������
* @param s32AdvBufLen �߼�������������С
* @param pMmgr �ڴ�ָ��
*/
IMP_EXPORTS IMP_VOID IMP_PARA_Free( EXTERNAL_PARA_S *pstPara, IMP_S32 s32AdvBufNum, IMP_VOID *pMmgr );
/**
* ����ⲿ���ò���������
* @param pstPara �ⲿ����������ָ��
* @param s32AdvBufNum �߼���������
*/
IMP_EXPORTS IMP_VOID IMP_PARA_Clear( EXTERNAL_PARA_S *pstPara, IMP_S32 s32AdvBufNum );
/**
* ��ʼ��ͼ���������������ⲿ�ļ���ȡ����
* @param pstPara �ⲿ����
* @param pstScnFil �����ļ�
* @param pstAdvFil �߼������ļ�
* @param s32ImgW ͼ����
* @param s32ImgH ͼ��߶�
* @param pMmgr �ڴ�ָ��
*/
IMP_EXPORTS IMP_VOID IMP_PARA_Init( EXTERNAL_PARA_S *pstPara, STR_ARRAY_PARA_S *pstScnFil,
									  STR_ARRAY_PARA_S *pstAdvFil, IMP_S32 s32ImgW, IMP_S32 s32ImgH, IMP_VOID *pMmgr );

/*@}*/


#ifdef __cplusplus
}
#endif

#endif /*_IMP_ALGO_INTERFACE_H_*/



/*@}*/
