/** 
 * @brief	         �������SDK�ı�׼ģ��	
 * @date	2008/07/22
 * Copyright (C) 2004 WISEBIRD CO.,  All rights reserved.
 *
 *----------------------------------------------------------------------
 */

#include <stdlib.h>
#include <math.h>
#include <memory.h>

#include "FaceDetectMain.h"
#include "DetectFaceOnly.h"
#include "IO.h"
#include "FixedPoint.h"
#include "detectimage.h"

/**
 *
 * ��ʼ��
 * Initialize
 *
 * @param	io_pInstance        
 * [in/out] ʵ�����
 *          Handle of instance
 * @param	in_pBinPath     	
 * [in]		ѧϰ���ݵĴ��·��
 *			Path of study data
 * @param	out_pModelSize      
 * [out]    ģ�����ݵĴ�С
 *			Size of model data
 * @param	out_pHeight         
 * [out]    ��һ��ͼ��ĸ�
 *			Height of regularized face image
 * @param	out_pWidth          
 * [out]    ��һ��ͼ��Ŀ�
 *			Width of regularized face image
 *
 * @return	IFACE_ERR_SUCCESS_ID    :��������
 *									 Normal end
 *          IFACE_ERR_INVALID_PARAM :��������ȷ
 *									 Invalid parameter
 *          IFACE_ERR_FILE_OPEN		:�ļ���ʧ��
 *									 File Open Failed
 *          IFACE_ERR_FILE_READ		:�ļ�����ʧ��
 *									 File Read Failed
 *
 */
IFACE_ERROR_CODE Initialize( 
			FaceRecognitionHandle* io_pInstance
			)

{
	IFACE_ERROR_CODE resultCode = IFACE_ERR_SUCCESS_ID;
	/* Parameter check */
	FACEHANDLE * ptr;


	if( io_pInstance == NULL) {
		return IFACE_ERR_INVALID_PARAM;
	}
	if( *io_pInstance == NULL){
		*io_pInstance = calloc(sizeof(FACEHANDLE), 1);
		ptr = (FACEHANDLE *)*io_pInstance;
	}else{
		return IFACE_ERR_INVALID_PARAM;
	}


	if(ptr->initFlag != 1){

		/* �趨������ȱʡֵ */
		/* Setting the default value to the parameter.  */
		resultCode = SetFaceDetectParameters(io_pInstance, 5, 5,
			SEARCH_INPLANE_000,
			FRONT,LOCK_ROT90_ON,
			LOCK_LARGE_ON,
			MODE_NORMAL, 100, 50);
		if( resultCode != IFACE_ERR_SUCCESS_ID) {
			return resultCode;
		}
		ptr->initFlag = 1;
	}

	return resultCode;
}


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
IFACE_ERROR_CODE SetFaceDetectParameters(
		FaceRecognitionHandle*	in_pInstance,
		const short in_FaceSize,
 		const short in_FaceSize30,
 		const SearchInplaneMode in_InPlane,
 		const SearchOutplaneMode in_OutPlane,
 		const LockRotation90Mode in_LockRotate90,
 		const LockSearchLarge in_LockLarge,
 		const SearchMode in_DetectMode,
 		const short in_FaceDetectThreshold,
		const short in_FaceCropThreshold ) {

	IFACE_ERROR_CODE resultCode = IFACE_ERR_SUCCESS_ID;		
	FACEHANDLE* ptr = NULL;
	DetectParam* pDetectParam = NULL;

	/* Parameter check */
	if( in_pInstance == NULL){
		resultCode = IFACE_ERR_INVALID_PARAM;
		return resultCode;
	}
	if( *in_pInstance == NULL){
		resultCode = IFACE_ERR_WRONG_SEQUENCE;
		return resultCode;
	}
		
	if( in_FaceSize<=1 || in_FaceSize>100
		|| in_FaceSize30<=1 || in_FaceSize30>100 ||
		( in_InPlane != SEARCH_INPLANE_000 && in_InPlane != SEARCH_INPLANE_ALL ) || 
		( in_OutPlane != FRONT && in_OutPlane != PROFILE && in_OutPlane != SEARCH_OUTPLANE_ALL ) ||
		( in_LockRotate90 != LOCK_ROT90_ON && in_LockRotate90 != LOCK_ROT90_OFF ) ||
		( in_LockLarge != LOCK_LARGE_ON && in_LockLarge != LOCK_LARGE_OFF ) ||
		( in_DetectMode != MODE_NORMAL && in_DetectMode != MODE_TP && in_DetectMode != MODE_SPEED ) ||
		//( in_FaceDetectThreshold < 0 || in_FaceDetectThreshold > 100 ) || //2008-07-14 �޸�
		( in_FaceDetectThreshold < 0 || in_FaceDetectThreshold > 1000 ) ||
		( in_FaceCropThreshold < 0 || in_FaceCropThreshold > 100) ) {

		resultCode = IFACE_ERR_INVALID_PARAM;
		return resultCode;
	}

	/* �Ӿ����ȡ�ýṹ����	*/
	/* Get the structure for parameter from handle */
	ptr = ((FACEHANDLE*)*in_pInstance);
	pDetectParam = &ptr->detectParam;
	if( pDetectParam == NULL) {
		resultCode = IFACE_ERR_WRONG_SEQUENCE;
		
		return resultCode;
	}

	/* Setting the least size of detected face for up-down-left-right four direction */
	pDetectParam->faceSize = in_FaceSize;
	/* Setting the least size of detected face for vertical 30 grade direction */
	pDetectParam->faceSize30 = in_FaceSize30;	
	/* Setting Search for in plane rotation */
	pDetectParam->inPlane = in_InPlane;
	/* Setting search for out plane rotation */	
	pDetectParam->outPlane = in_OutPlane;
	/* Setting direction fixed flag when a face is found  */
	pDetectParam->lockRotate90 = in_LockRotate90;
	/* Setting smaller face detect flag when a face is found */
	pDetectParam->lockLarge = in_LockLarge;
	/* Setting priority mode for face detect */
	pDetectParam->detectMode = in_DetectMode;	
	/* Setting threshold for face crop score */
	pDetectParam->faceDetectThreshold = in_FaceDetectThreshold;
	pDetectParam->faceCropThreshold = in_FaceCropThreshold;

	return IFACE_ERR_SUCCESS_ID;
}

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
IFACE_ERROR_CODE  DetectFaces(
				FaceRecognitionHandle* in_pInstance, 
				const unsigned char* in_pImage,
                const long in_Width,
                const long in_Height,
				short* io_pFaceNo,
				FACEINFO* io_pFace ) {

	IFACE_ERROR_CODE resultCode = IFACE_ERR_SUCCESS_ID;
	unsigned char* pYImage;

	FACEHANDLE * ptr;

	/* Parameter check */
	if( in_pInstance == NULL){
		resultCode = IFACE_ERR_INVALID_PARAM;
		return resultCode;
	}
	if( *in_pInstance == NULL){
		resultCode = IFACE_ERR_WRONG_SEQUENCE;
		return resultCode;
	}
	if( in_pImage == NULL || in_Width <= 0 ||
		in_Height <= 0 || io_pFaceNo == NULL || io_pFace == NULL ) {
		resultCode = IFACE_ERR_INVALID_PARAM;
		
		return resultCode;
	}

    /******************************
     * RGB->Y                     *
     ******************************/
	pYImage = ( unsigned char * ) malloc( in_Width * in_Height );
	if( pYImage==NULL )	{
		resultCode = IFACE_ERR_NO_ENOUGH_MEMORY;
		return resultCode;
	}

    resultCode = ConvertRGBtoY( in_pInstance, in_pImage, in_Width, in_Height, pYImage );
	if( resultCode != IFACE_ERR_SUCCESS_ID ) {
		if( pYImage!=NULL ) {
			if( pYImage != NULL ) {
				free( pYImage );
				pYImage = NULL;
			}
		}
		return resultCode;
	}

    /********************************
	 * Face detection
     ********************************/
    resultCode = DetectFaces2( in_pInstance, pYImage, in_Width, in_Height, io_pFaceNo, io_pFace );


	if( resultCode != IFACE_ERR_SUCCESS_ID )
	{
		
		if( pYImage!=NULL ) {
			if( pYImage != NULL ) {
				free( pYImage );
				pYImage = NULL;
			}
		}
		return resultCode;
	}

	if( pYImage != NULL ) {
		free( pYImage );
		pYImage = NULL;
	}

    return resultCode;
}


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
IFACE_ERROR_CODE Uninitialize(
				FaceRecognitionHandle*	in_pInstance)
{
	IFACE_ERROR_CODE	ret = IFACE_ERR_SUCCESS_ID;
	FACEHANDLE *ptr;

	if( in_pInstance == NULL){
		ret = IFACE_ERR_INVALID_PARAM;
		return ret;
	}
	if( *in_pInstance == NULL){
		ret = IFACE_ERR_WRONG_SEQUENCE;
		return ret;
	} else{
		ptr = (FACEHANDLE *)*in_pInstance;
		
		ptr->initFlag = 0;
		free(ptr);
		ptr = NULL;

		return IFACE_ERR_SUCCESS_ID;
	}
}

