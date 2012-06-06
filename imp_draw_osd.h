/**
* \defgroup �ṹ���Ͷ���
* �㷨�������Ͷ���
* @author �������ټ���
* @version 2.0
* @data 2009-2010
*/
/*@{*/
#ifndef _IMP_DRAW_OSD_H_
#define _IMP_DRAW_OSD_H_
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "hi_tde_api.h"
#include "hi_tde_type.h"
#include "hi_tde_errcode.h"

#include "hi_comm_video.h"
#include "imp_algo_type.h"
#include "imp_algo_urp_param.h"


#define TBL_YUV(y,u,v) {y,u,v}
/** YUVͼ�������� 0��,1��,2��*/
static PIXEL_S cr_tbl[] =
{
	TBL_YUV(81,90,240),
	TBL_YUV(144,54,34),
	TBL_YUV(29,121,102),
	TBL_YUV(255,0,128),
	TBL_YUV(0,255,128),
	TBL_YUV(128,255,128),
	TBL_YUV(128,255,0),
	TBL_YUV(255,128,0),
	TBL_YUV(0,255,128),
	TBL_YUV(255,128,0),
	TBL_YUV(128,0,255),
	TBL_YUV(128,255,0),
	TBL_YUV(0,0,255)
};
#define IMP_IMAGE_WIDTH 704
#define IMP_IMAGE_HEIGHT 576

static IMP_U32 color_tbl[] =
{
	0x3e0,              /**< blue */
	0x7c00,             /**< red */
};
typedef enum impVIDEO_FORMAT_E
{
    IMP_QCIF,
    IMP_CIF,
    IMP_D1,
	IMP_HD1
}VIDEO_FORMAT_E;

#ifdef __cplusplus
extern "C"
{
#endif
/**
* �ں�˹����ͼ�����PEA���OSD��Ϣ
* @param pVBuf ��˹����ͼ������
* @param pstResult PEA�㷨���
* @param enFormatSrc ��˹��ƵVI���õķֱ���
* @param enFormatAlgo PEA�㷨����ķֱ���
* @return IMP_VOID   ���ؿ�
*/
IMP_VOID IMP_DrawPeaResult(VIDEO_FRAME_S *pVBuf, RESULT_S *pstResult,VIDEO_FORMAT_E enFormatSrc,VIDEO_FORMAT_E enFormatAlgo);
IMP_VOID IMP_TDE_DrawPeaResult( TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstYSurface,TDE2_SURFACE_S* pstUVSurface, RESULT_S *result,VIDEO_FORMAT_E enFormatSrc,VIDEO_FORMAT_E enFormatAlgo );
IMP_VOID IMP_DrawVfdResult(VIDEO_FRAME_S *pVBuf, VFD_RESULT_S *pVfdResult,VIDEO_FORMAT_E enFormatSrc,VIDEO_FORMAT_E enFormatAlgo);
IMP_VOID IMP_DrawPeaRule( VIDEO_FRAME_S *pVBuf, URP_PARA_S *pstURPpara );
IMP_VOID IMP_DrawOSCResult(VIDEO_FRAME_S *pVBuf, RESULT_S *pstResult,VIDEO_FORMAT_E enFormatSrc,VIDEO_FORMAT_E enFormatAlgo);
#ifdef __cplusplus
}
#endif



#endif /*_IMP_DRAW_OSD_H_*/

/*@}*/


