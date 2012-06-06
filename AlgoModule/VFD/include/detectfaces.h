/*****************************************************************************
 ** 
 * �ļ�˵�������õ��������ģ��
 * @brief		��: Face detection wrapper module for openning
 * @date           2004/12/15
 * history:
 * @date           2005/12/05 ���������ʶ��ģ��ĺϲ����׼��
 * Copyright (C) 2004 WISEBIRD CO., LTD. All rights reserved.
 *****************************************************************************/

#ifndef __DETECTFACES_H__
#define __DETECTFACES_H__

/*---------------------------------------------------------
 * Private parameter
 *---------------------------------------------------------*/

//<<<--- 2008-01-05
//#define	HALFPROFILE					4
//--->>>

/*---------------------------------------------------------
 * Type definition
 *---------------------------------------------------------*/

#include "FaceDetectDef.h"

/*---------------------------------------------------------
 * Function definition
 *---------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------------------------*/
/** DetectFaces2 : �������
 *                 Face detection wrapper
 * @param in_pInstance			
 * [in] ʵ�����
 *          handle of instance
 * @param in_pImage
 * [in]ͼ������
 *	   image data
 * @param in_Width
 * [in]ͼ����
 *	   image width
 * @param in_Height
 * [in]ͼ��߶�
 *	   image height
 * @param io_pFaceNo
 * [io]���ɼ����������ѡ�������룩
 *	   the most detected face candidate number (input)
 *     ʵ�ʼ�����������������
 *	   detected face candidate number (output)
 * @param io_pFace
 * [io]������������ꡢ�÷��б�
 *	   detected face coordinates, score struct list
 * @return	IFACE_ERR_SUCCESS_ID    :		��������
 *											Normal End
 *          IFACE_ERR_WRONG_SEQUENCE:		˳�����
 *											Wrong Sequence
 *          IFACE_ERR_INVALID_PARAM :		�Ƿ�����
 *											Invalid Parameter
 *			IFACE_ERR_NO_ENOUGH_MEMORY	:	�ڴ����ʧ��
 *											no enough memory
 *			IFACE_ERR_NO_FACE_FOUND		:	û�м������
 *											no face detected
/*----------------------------------------------------------------------------*/
//<<<--- 2009-12-30 ��long�����޸�Ϊshort
IFACE_ERROR_CODE DetectFaces2(
				FaceRecognitionHandle* in_pInstance, 
				const unsigned char* in_pImage,
                const short/*long*/ in_Width,
                const short/*long*/ in_Height,
				short/*long*/* io_pFaceNo,
				FACEINFO* io_pFace );




#ifdef __cplusplus
}
#endif


#endif /* __DETECTFACES_H__ */



/* End of file */
