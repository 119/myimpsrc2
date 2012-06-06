/*****************************************************************************
 ** 
 * �ļ�˵������������
 * @brief
 * @date			 2005/10/31
 *
 * @date			 2003/12/02 �޸�����ʶ������ģ�����ݺϲ�����׼������
 *                     Update Face recognition and detect module merged and standardize
 * Copyright (C) 2004 WISEBIRD CO.,  All rights reserved.
 *----------------------------------------------------------------------
 */

#ifndef __DEFINES_H__
#define __DEFINES_H__


/*---------------------------------------------------------
 * ������Ϣ���ָ��
 *---------------------------------------------------------*/
/* ==== ����ʱ�� ==== */
/*#define DEBUG_PRINT_CALCULATION_TIME*/


/* ==== image.c ==== */
/*#define DEBUG_IMAGE_MULTIRESOLUTION*/
/*#define DEBUG_IMAGE_NORMALIZE*/


/*---------------------------------------------------------
 * ����
 *---------------------------------------------------------*/
/* ==== ���طֱ���ϵͳ���ֵ���� ==== */
#define MAX_MULTIRESOLUTION_LEVELS     10
#define MAX_MULTIRESOLUTION_SERIES     5


/* ==== ��ѡ�������ֵ ==== */
//<<<--- 2009-12-28 �������ֵ
//#define MAX_NUM_CANDIDATES_TEMP        100000
//#define MAX_NUM_CANDIDATES             1000
//#define MAX_NUM_CANDIDATES_FEATURE     100000

#define MAX_NUM_CANDIDATES_TEMP        20000
#define MAX_NUM_CANDIDATES             100
#define MAX_NUM_CANDIDATES_FEATURE     20000
//--->>>

/* ==== in-plane��ת ==== */
#ifndef __DEFINES_DETECT__
#define __DEFINES_DETECT__
/*
#define SEARCH_INPLANE_090          90
#define SEARCH_INPLANE_180          180
#define SEARCH_INPLANE_270          270
/* ==== out-plane��ת ==== */
/*#define FRONT						1
#define PROFILE						2
#define	HALFPROFILE					4
#define SEARCH_OUTPLANE_ALL         -1*/
/* ==== lock rot90 ==== */
//#define LOCK_ROT90_ON               1
//#define LOCK_ROT90_OFF              0
/* ==== lock large ==== */
//#define LOCK_LARGE_ON               1
//#define LOCK_LARGE_OFF              0
/* ==== mode ==== */
/*#define MODE_NORMAL                 0
#define MODE_TP                     1
#define MODE_SPEED                  -1*/
#endif


#endif /* __DEFINES_H__ */



/* End of file */
