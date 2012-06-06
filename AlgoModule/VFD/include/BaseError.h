/*****************************************************************************/
/** @file
 * 1D LUT�任��
 * @date        2003/03/10
 * Copyright (C) 2004 WISEBIRD CO.,  All rights reserved.
******************************************************************************/


#ifndef BASE_ERROR_H
#define BASE_ERROR_H


typedef enum {
    kBaseErr_Success            = 0,    /**< �ɹ� */
    kBaseErr_Pending            = 1,    /**< �������� */
    kBaseErr_NoSupportProcess   = 2,    /**< δ֧�ֵĴ��� */
    kBaseErr_InvalidParam       = 3,    /**< �Ƿ����� */
    kBaseErr_ImgSizeError       = 10,   /**< ͼ���С���� */
    kBaseErr_ImgIOtypeError     = 11,   /**< ���롢���ͼ�����Ͳ�ƥ�� */
    kBaseErr_ImgDepthError      = 12,   /**< �����ͼ��λ�� */
    kBaseErr_ImgChannelError    = 13,   /**< �����ͼ��ͨ���� */
    kBaseErr_ImgColorError      = 14,   /**< �����ͼ����ɫ��ʽ��ʾ */
    kBaseErr_ImgOrderError      = 15,   /**< �����ͼ�����и�ʽ���㡢�ߡ��棩 */
    kBaseErr_ImgAlignError      = 16,   /**< �����ͼ����� */
    kBaseErr_ImgOrientError     = 17,   /**< �����ͼ��ʼ���� */
    kBaseErr_LUTError           = 30,   /**< �����LUT */
    kBaseErr_MagRateError       = 31,   /**< �����ʴ��� */
    kBaseErr_MallocError        = 100,  /**< �ڴ������� */
    kBaseErr_Arithmetic         = 101   /**< �������   */
} BASE_ERROR_CODE;


#endif /* BASE_ERROR_H */

