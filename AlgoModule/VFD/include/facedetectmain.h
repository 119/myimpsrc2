/** 
 * @brief���������SDK�ı�׼ģ��
 * @date	2008/07/22
 * Copyright (C) 2004 WISEBIRD CO.,  All rights reserved.
 *
 *----------------------------------------------------------------------
 */
#ifndef __FACEDETECT_H__
#define __FACEDETECT_H__

#include <stdio.h>
#include "FaceDetectDef.h"

#define LIB_API

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------------------
  public function
----------------------------------------------------------------------*/
/**
 *
 * ��ʼ��
 * Initialize
 *
 * @param	io_pInstance        
 * [in/out] ʵ�����
 *          Handle of instance
 *
 * @return	IFACE_ERR_SUCCESS_ID    :��������
 *									 Normal end
 *          IFACE_ERR_INVALID_PARAM :��������ȷ
 *									 Invalid parameter
 *
 */
LIB_API IFACE_ERROR_CODE Initialize( 
			FaceRecognitionHandle* io_pInstance
			);

/**
 *
 * �������������
 * Setting face detect parameters
 *
 * @param	in_pInstance			
 * [in/out] ʵ�����
 *          handle of instance
 * @param	in_FaceSize     		
 * [in]	 �������ҷ������С������Ĵ�С
 *		 the least size of detected face for up-down-left-right four direction
 *		 ȱʡֵ����			0.1
 *		 default����		0.1
 * @param	in_FaceSize30     		
 * [in]	 ����30�ȷ������С�������С
 *		 the least size of detected face for vertical 30 grade direction
 *       ȱʡֵ����			0.2
 *		 default����		0.2
 * @param	in_InPlane     			
 * [in]	 ������ƽ������ת
 *		 search for in plane rotation
 *		 SEARCH_INPLANE_000��	������������
 *								stand direction only
 *		 SEARCH_INPLANE_ALL��	12������ÿ��������30��
 *								inclreasing 30 grade for 12 direction
 *		 ȱʡֵ��				SEARCH_INPLANE_000��
 *		 default����			SEARCH_INPLANE_000
 * @param	in_OutPlane     		
 * [in]	 ������ƽ��Ĵ�ֱ������ת
 *		 search for out plane rotation
 *		 FRONT����			��	������������
 *								front face only
 *		 PROFILE��			��	����
 *								profile
 *		 SEARCH_OUTPLANE_ALL��	���з���
 *								all direction
 *		 ȱʡֵ����			FRONT
 *		 default����			FRONT
 * @param	in_LockRotate90    		
 * [in]	 �ҵ���ʱ���·���Ĺ̶����
 *		 direction fixed flag when a face is found 
 *		 LOCK_ROT90_ON����		�̶�
 *								lock
 *		 LOCK_ROT90_OFF��		���̶�
 *								don't lock
 *		 ȱʡֵ��			LOCK_ROT90_ON
 *		 default����			LOCK_ROT90_ON
 * @param	in_LockLarge     		
 * [in]	 �ҵ���ʱС�ߴ����Ƿ������ı�־
 *		 smaller face detect flag when a face is found 
 *		 LOCK_LARGE_ON����		������
 *								don't detect
 *		 LOCK_LARGE_OFF��		����
 *								detect
 *		 ȱʡֵ��			LOCK_LARGE_ON
 *		 default����			LOCK_LARGE_ON
 * @param	in_DetectMode  			
 * [in]	 ��������ȷ�ʽ
 *		 priority mode for face detect
 *		 MODE_NORMAL��			ͨ��
 *								normal
 *		 MODE_TP������			TP����
 *								TP has a high priority
 *		 MODE_SPEED��			�ٶ�����
 *								detect speed has a high priority
 *		 ȱʡֵ��			MODE_NORMAL
 *		 default����			MODE_NORMAL
 * @param	in_FaceDetectThreshold  
 * [in]	 ��������õķ�ֵ����
 *		 threshold for face detect score
 *		 ��Χ��					0-1000
 *		 range:					0-1000
 *		 ȱʡֵ��			100
 *		 default����			100
 * @param	in_FaceCropThreshold    
 * [in]	 �г����ķ�ֵ����
 *		 threshold for face crop score
 *		 ��Χ��					0-100
 *		 range:					0-100
 *		 ȱʡֵ��			100
 *		 default����			100
 *
 * @return	IFACE_ERR_SUCCESS_ID    :��������
 *									 Normal End
 *          IFACE_ERR_WRONG_SEQUENCE:˳�����
 *									 Wrong Sequence
 *          IFACE_ERR_INVALID_PARAM :�Ƿ�����
 *									 Invalid Parameter
 */
LIB_API IFACE_ERROR_CODE SetFaceDetectParameters(
		FaceRecognitionHandle*	in_pInstance,
		const short in_FaceSize,
 		const short in_FaceSize30,
 		const SearchInplaneMode in_InPlane,
 		const SearchOutplaneMode in_OutPlane,
 		const LockRotation90Mode in_LockRotate90,
 		const LockSearchLarge in_LockLarge,
 		const SearchMode in_DetectMode,
 		const short in_FaceDetectThreshold,
		const short in_FaceCropThreshold);

/* 
 * �����
 * face detect
 *
 * @param	io_pInstance			
 * [in/out] ʵ�����
 *          handle of instance
 * @param in_pImage
 * [in]ͼ������
 *	   image data
 * @param in_Width
 * [in]ͼ���
 *	   image width
 * @param in_Height
 * [in]ͼ���
 *	   image height
 * @param io_FaceNo
 * [io]�������������ѡ�������룩
 *	   the most detected face candidate number (input)
 *     ������������������
 *	   detected face candidate number (output)
 * @param io_pFace
 * [io]������������ꡢ�÷ֵȵĽṹ����
 *	   detected face coordinates, score struct list
 * @return	IFACE_ERR_SUCCESS_ID    :		��������
 *											Normal End
 *          IFACE_ERR_WRONG_SEQUENCE:		˳�����
 *											Wrong Sequence
 *          IFACE_ERR_INVALID_PARAM :		�Ƿ�����
 *											Invalid Parameter
 *			IFACE_ERR_NO_ENOUGH_MEMORY	:	�ڴ����ʧ��
 *											no enough memory
 *			IFACE_ERR_NO_FACE_FOUND		:	û�м쵽��
 *											no face detected
 */
LIB_API IFACE_ERROR_CODE  DetectFaces(
				FaceRecognitionHandle* in_pInstance, 
				const unsigned char *in_pImage,
                const long in_Width,
                const long in_Height,
				short *io_FaceNo,
				FACEINFO *io_pFace );


/**
 *
 * ��������
 * Uninitialize
 *
 * @param	in_pInstance			[in]	Handle of instance
 *
 * @return	IFACE_ERR_SUCCESS_ID    :��������
 *									 Normal End
 *          IFACE_ERR_WRONG_SEQUENCE:˳�����
 *									 Wrong Sequence
 *          IFACE_ERR_INVALID_PARAM :�Ƿ�����
 *									 Invalid Parameter
 */
LIB_API IFACE_ERROR_CODE Uninitialize(
				FaceRecognitionHandle*	in_pInstance
				);

#ifdef __cplusplus
}
#endif

#endif	/* __FACEDETECT_H__ */