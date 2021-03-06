#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>

#include "hi_tde_api.h"
#include "hi_tde_type.h"
#include "hi_tde_errcode.h"
#include "hifb.h"
#include "vo_open.h"

#include "imp_algo_type.h"
#include "imp_algo_urp_param.h"
extern RESULT_S gstPeaResult;;
//#define IMAGE_WIDTH     640
//#define IMAGE_HEIGHT    352
//#define IMAGE_SIZE      (640*352*2)
#define IMAGE_WIDTH     1280
#define IMAGE_HEIGHT    1024
#define IMAGE_SIZE      (1280*1024*2)
#define IMAGE_NUM       14
#define IMAGE_PATH		"./res/%d.bits"
#define PEA_IMAGE_PATH1		"./res/background.bits"
#define PEA_IMAGE_PATH2		"./res/pea2.bits"
#define PEA_IMAGE_PATH3		"./res/pea3.bits"
#define PEA_IMAGE_PATH4		"./res/pea4.bits"
#define PEA_IMAGE_PATH5		"./res/pea5.bits"
#define PEA_IMAGE_PATH6		"./res/pea6.bits"
//#define VIR_SCREEN_WIDTH	640					/*virtual screen width*/
//#define VIR_SCREEN_HEIGHT	IMAGE_HEIGHT*2		/*virtual screen height*/
#define VIR_SCREEN_WIDTH	1280					/*virtual screen width*/
#define VIR_SCREEN_HEIGHT	IMAGE_HEIGHT*2		/*virtual screen height*/



static struct fb_bitfield g_r16 = {10, 5, 0};
static struct fb_bitfield g_g16 = {5, 5, 0};
static struct fb_bitfield g_b16 = {0, 5, 0};
static struct fb_bitfield g_a16 = {15, 1, 0};

#define PIXFMT  TDE2_COLOR_FMT_ARGB1555

//#define printf(...)

HI_S32 SetTrasValueBydevPath(int fd)
{

	HIFB_ALPHA_S stAlpha;
//	const char* file = pszDevPath;


	int ret;
    HIFB_COLORKEY_S CKey;

//	tellme_out("blair:u8Alpha0\n");
    if (ioctl(fd, FBIOGET_ALPHA_HIFB, &stAlpha) < 0)
    {
        fprintf (stderr, "Couldn't set alpha\n");
        ret = -1;
    }

	stAlpha.bAlphaEnable=HI_TRUE;
	stAlpha.bAlphaChannel=HI_FALSE;
	stAlpha.u8Alpha0 = 0xC0;
	//stAlpha.u8Alpha0 = 0x70;
    stAlpha.u8Alpha1 = 0xff;
    //stAlpha.u8GlobalAlpha = 0xff;
    ret = ioctl(fd, FBIOPUT_ALPHA_HIFB, &stAlpha);
    if (ret < 0)
    {
        fprintf (stderr, "Couldn't set alpha\n");
        ret = -1;
    }

	//getchar();
	ret = ioctl(fd, FBIOGET_COLORKEY_HIFB, &CKey);
    if (ret < 0)
    {
        fprintf (stderr, "Couldn't get colorkey\n");
        return -1;
    }
    CKey.bKeyEnable = HI_TRUE;
    CKey.u32Key = 0x00000000;
   // CKey.u32Key = 0x000000FF;
    if (ioctl(fd, FBIOPUT_COLORKEY_HIFB, &CKey) < 0)
    {
        fprintf (stderr, "Couldn't put colorkey\n");
        return -1;
    }

    return ret;
}

extern URP_PARA_S stURPpara;
void TDE_OUTPUT_PEA_RESULT(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstDst,RESULT_S *result)//,TDE2_IMP_RECT_S *pstDstRect)
{
    TDE2_RECT_S pstDstRect;
    HI_U32 u32FillData = 0x7c00;
    HI_U32 u32PEAData = 0x3e0;
    HI_U32 u32TWData = 0x3e0;
    HI_U32 u32GrayData = 0x6318;
    HI_U32 u32WihteData = 0;
    TGT_SET_S	*target_set = &result->stTargetSet;
    EVT_SET_S *event_set = &result->stEventSet;
    int target_num = target_set->s32TargetNum;
    int zone = 0;
    TGT_ITEM_S *target;
    IMP_RECT_S *rc;
    IMP_RECT_S rc1;
    float scale_x = (IMAGE_WIDTH/(176*2.0));
    float scale_y = (IMAGE_HEIGHT/(144*2.0));
    int i = 0;
    int j = 0;
    int pixWidth = 4;
    int peaPixWidth = 4;
    int twPixWidth = 4;
    int s32Ret = 0;
    short cr;
    TDE2_FILLCOLOR_S pstFillColor;
    TDE2_FILLCOLOR_S pstFillColor_PEA;
    TDE2_OPT_S pstOpt;
    pstFillColor.enColorFmt = TDE2_COLOR_FMT_ARGB1555;
    pstFillColor.u32FillColor = 0x7c00;

    pstFillColor_PEA.enColorFmt = TDE2_COLOR_FMT_ARGB1555;
    pstFillColor_PEA.u32FillColor =u32WihteData;

    memset(&pstOpt,0,sizeof(pstOpt));
    pstOpt.bDeflicker = HI_TRUE;
 //   IP_PIXVAL *cr = &cr_tbl[0];
  //  int i = 0;
#if 1
    pstDstRect.s32Xpos =0;
    pstDstRect.s32Ypos =(IMAGE_HEIGHT>>1)-peaPixWidth/2-1;
    pstDstRect.u32Width = IMAGE_WIDTH;
    pstDstRect.u32Height = peaPixWidth;
    pstFillColor.u32FillColor = u32GrayData;
    HI_TDE2_SolidDraw( s32Handle,NULL,NULL,pstDst,&pstDstRect,&pstFillColor,&pstOpt);

    pstDstRect.s32Xpos =(IMAGE_WIDTH>>1)-peaPixWidth/2-1;
    pstDstRect.s32Ypos =0;
    pstDstRect.u32Width = peaPixWidth;
    pstDstRect.u32Height = IMAGE_HEIGHT;
    pstFillColor.u32FillColor = u32GrayData;
 //   printf("s32Xpos:%d,s32Ypos:%d,u32Width:%d,u32Height:%d\n",pstDstRect.s32Xpos,pstDstRect.s32Ypos,pstDstRect.u32Width,pstDstRect.u32Height);
    HI_TDE2_SolidDraw( s32Handle,NULL,NULL,pstDst,&pstDstRect,&pstFillColor,&pstOpt);
#endif
    for(i=0;i<event_set->s32EventNum;i++)
    {
        if(event_set->astEvents[i].u32Status==IMP_EVT_STATUS_START || event_set->astEvents[i].u32Status== IMP_EVT_STATUS_PROCEDURE)
        {
            if(event_set->astEvents[i].u32Type==IMP_EVT_TYPE_AlarmPerimeter)
            {
                zone=event_set->astEvents[i].u32Zone;
                if(zone == 0)
                {
                    u32PEAData = 0x7c00;
                }
                /*else if(zone == 2)
                {
                    u32PEAData = 0x7c00;
                }*/
            }
            if(event_set->astEvents[i].u32Type==IMP_EVT_TYPE_AlarmTripwire)
            {
                zone=event_set->astEvents[i].u32Zone;
                u32TWData = 0x7c00;
            }
        }
    }
    rc1.s16X1 = stURPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.astBoundaryPts[0].s16X;
	rc1.s16Y1 = stURPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.astBoundaryPts[0].s16Y;
	rc1.s16X2 = stURPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.astBoundaryPts[2].s16X;
	rc1.s16Y2 = stURPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.astBoundaryPts[2].s16Y;

    rc1.s16X1 = (short)((rc1.s16X1)*scale_x);
    rc1.s16Y1 = (short)((rc1.s16Y1)*scale_y);
    rc1.s16X2 = (short)((rc1.s16X2)*scale_x);
    rc1.s16Y2 = (short)((rc1.s16Y2)*scale_y);
    pstFillColor.u32FillColor = u32PEAData;
    for( j = 0; j < 4;j++)
    {
        if(j == 0)
        {
            pstDstRect.s32Xpos = rc1.s16X1;
            pstDstRect.s32Ypos =rc1.s16Y1;
            pstDstRect.u32Width = peaPixWidth;
            pstDstRect.u32Height = rc1.s16Y2 - rc1.s16Y1;
        }
        else if(j == 1)
        {
            pstDstRect.s32Xpos = rc1.s16X1;
            pstDstRect.s32Ypos =rc1.s16Y1;
            pstDstRect.u32Width = rc1.s16X2 - rc1.s16X1;
            pstDstRect.u32Height = peaPixWidth;
        }
        else if(j == 2)
        {
            pstDstRect.s32Xpos = rc1.s16X1;
            pstDstRect.s32Ypos =rc1.s16Y2;
            pstDstRect.u32Width = rc1.s16X2 - rc1.s16X1;
            pstDstRect.u32Height = peaPixWidth;
        }
        else if(j == 3)
        {
            pstDstRect.s32Xpos = rc1.s16X2;
            pstDstRect.s32Ypos =rc1.s16Y1;
            pstDstRect.u32Width = peaPixWidth;
            pstDstRect.u32Height = rc1.s16Y2 - rc1.s16Y1+peaPixWidth;
        }
        //printf("s32Xpos:%d,s32Ypos:%d,u32Width:%d,u32Height:%d\n",pstDstRect.s32Xpos,pstDstRect.s32Ypos,pstDstRect.u32Width,pstDstRect.u32Height);

        HI_TDE2_SolidDraw( s32Handle,NULL,NULL,pstDst,&pstDstRect,&pstFillColor,&pstOpt);
    }

#if 1
    pstDstRect.s32Xpos =stURPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLines[0].stLine.stStartPt.s16X*scale_x + (IMAGE_WIDTH>>1);
    pstDstRect.s32Ypos =stURPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLines[0].stLine.stStartPt.s16Y*scale_y;
    pstDstRect.u32Width = twPixWidth;
    pstDstRect.u32Height = (stURPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLines[0].stLine.stEndPt.s16Y - stURPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLines[0].stLine.stStartPt.s16Y)*scale_y;
    pstFillColor.u32FillColor = u32TWData;
 //   printf("s32Xpos:%d,s32Ypos:%d,u32Width:%d,u32Height:%d\n",pstDstRect.s32Xpos,pstDstRect.s32Ypos,pstDstRect.u32Width,pstDstRect.u32Height);
    HI_TDE2_SolidDraw( s32Handle,NULL,NULL,pstDst,&pstDstRect,&pstFillColor,&pstOpt);
#endif
 //   if(target_num > 2)
 //       printf("target_num:%d\n",target_num);
    for( i = 0;i < target_num;i++)
    {
        target = &target_set->astTargets[i];
        if((target->u32Event &IMP_TGT_EVENT_PERIMETER )|| ( target->u32Event&IMP_TGT_EVENT_TRIPWIRE ) )
        {
            cr = 0x7c00;
            u32FillData = 0x7c00;
        }
        else
        {
            cr = 0x3e0;
            u32FillData = 0x3e0;
        }
        pstFillColor.u32FillColor = u32FillData;
        {
           /* IP_TGT_ITEM_NICE *item_data = (IP_TGT_ITEM_NICE*)(target->data);
            IP_TGT_TRAJECT *traject = &item_data->traject;
            int num = 0;
            int k = 0;
            //short cr = 0x7c00;

            IP_POINT *pt1,*pt2;
            IP_POINT pt3,pt4;
            num = traject->length;
            pt1 = &traject->points[0];
            for( k=1; k<num; k++ )
            {
                pt2 = &traject->points[k];
                pt3.x = pt1->x * scale_x;
                pt3.y = pt1->y * scale_y;
                pt4.x = pt2->x * scale_x;
                pt4.y = pt2->y * scale_y;
                FB_DrawLine( pVBuf,stride, &pt3, &pt4,&cr );
                pt1 = pt2;
            }*/
            rc = &target->stRect;
            if(target->u32Event&IMP_TGT_EVENT_PERIMETER)
            {
                rc1.s16X1 = (short)((rc->s16X1)*scale_x);
                rc1.s16Y1 = (short)((rc->s16Y1)*scale_y);
                rc1.s16X2 = (short)((rc->s16X2)*scale_x);
                rc1.s16Y2 = (short)((rc->s16Y2)*scale_y);

                for( j = 0; j < 4;j++)
                {
                    if(j == 0)
                    {
                        pstDstRect.s32Xpos = rc1.s16X1;
                        pstDstRect.s32Ypos =rc1.s16Y1;
                        pstDstRect.u32Width = pixWidth;
                        pstDstRect.u32Height = rc1.s16Y2 - rc1.s16Y1;
                    }
                    else if(j == 1)
                    {
                        pstDstRect.s32Xpos = rc1.s16X1;
                        pstDstRect.s32Ypos =rc1.s16Y1;
                        pstDstRect.u32Width = rc1.s16X2 - rc1.s16X1;
                        pstDstRect.u32Height = pixWidth;
                    }
                    else if(j == 2)
                    {
                        pstDstRect.s32Xpos = rc1.s16X1;
                        pstDstRect.s32Ypos =rc1.s16Y2;
                        pstDstRect.u32Width = rc1.s16X2 - rc1.s16X1;
                        pstDstRect.u32Height = pixWidth;
                    }
                    else if(j == 3)
                    {
                        pstDstRect.s32Xpos = rc1.s16X2;
                        pstDstRect.s32Ypos =rc1.s16Y1;
                        pstDstRect.u32Width = pixWidth;
                        pstDstRect.u32Height = rc1.s16Y2 - rc1.s16Y1+pixWidth;
                    }
                    pstFillColor_PEA.u32FillColor  = u32PEAData;
                  //  printf("s32Xpos:%d,s32Ypos:%d,u32Width:%d,u32Height:%d\n",pstDstRect.s32Xpos,pstDstRect.s32Ypos,pstDstRect.u32Width,pstDstRect.u32Height);
                    HI_TDE2_SolidDraw( s32Handle,NULL,NULL,pstDst,&pstDstRect,&pstFillColor_PEA,&pstOpt);
                }

            }
            if(target->u32Event&IMP_TGT_EVENT_TRIPWIRE)
            {
               /* rc1.s16X1 = (short)((rc->lb_x)*scale_x)+(IMAGE_WIDTH>>1);
                rc1.s16Y1 = (short)((rc->lb_y)*scale_y);
                rc1.s16X2 = (short)((rc->ru_x)*scale_x)+(IMAGE_WIDTH>>1);
                rc1.s16Y2 = (short)((rc->ru_y)*scale_y);*/
                rc1.s16X1 = (short)((rc->s16X1)*scale_x)+(IMAGE_WIDTH>>1);
                rc1.s16Y1 = (short)((rc->s16Y1)*scale_y);
                rc1.s16X2 = (short)((rc->s16X2)*scale_x)+(IMAGE_WIDTH>>1);
                rc1.s16Y2 = (short)((rc->s16Y2)*scale_y);
                for( j = 0; j < 4;j++)
                {
                    if(j == 0)
                    {
                        pstDstRect.s32Xpos = rc1.s16X1;
                        pstDstRect.s32Ypos =rc1.s16Y1;
                        pstDstRect.u32Width = pixWidth;
                        pstDstRect.u32Height = rc1.s16Y2 - rc1.s16Y1;
                    }
                    else if(j == 1)
                    {
                        pstDstRect.s32Xpos = rc1.s16X1;
                        pstDstRect.s32Ypos =rc1.s16Y1;
                        pstDstRect.u32Width = rc1.s16X2 - rc1.s16X1;
                        pstDstRect.u32Height = pixWidth;
                    }
                    else if(j == 2)
                    {
                        pstDstRect.s32Xpos = rc1.s16X1;
                        pstDstRect.s32Ypos =rc1.s16Y2;
                        pstDstRect.u32Width = rc1.s16X2 - rc1.s16X1;
                        pstDstRect.u32Height = pixWidth;
                    }
                    else if(j == 3)
                    {
                        pstDstRect.s32Xpos = rc1.s16X2;
                        pstDstRect.s32Ypos =rc1.s16Y1;
                        pstDstRect.u32Width = pixWidth;
                        pstDstRect.u32Height = rc1.s16Y2 - rc1.s16Y1+pixWidth;
                    }
                  //  printf("s32Xpos:%d,s32Ypos:%d,u32Width:%d,u32Height:%d\n",pstDstRect.s32Xpos,pstDstRect.s32Ypos,pstDstRect.u32Width,pstDstRect.u32Height);
                    HI_TDE2_SolidDraw( s32Handle,NULL,NULL,pstDst,&pstDstRect,&pstFillColor,&pstOpt);
                }

            }
            if(target->u32Event&IMP_TGT_EVENT_PERIMETER)
            {
                rc1.s16X1 = (short)((rc->s16X1)*scale_x);
                rc1.s16Y1 = (short)((rc->s16Y1)*scale_y)+(IMAGE_HEIGHT>>1);
                rc1.s16X2 = (short)((rc->s16X2)*scale_x);
                rc1.s16Y2 = (short)((rc->s16Y2)*scale_y)+(IMAGE_HEIGHT>>1);

                for( j = 0; j < 4;j++)
                {
                    if(j == 0)
                    {
                        pstDstRect.s32Xpos = rc1.s16X1;
                        pstDstRect.s32Ypos =rc1.s16Y1;
                        pstDstRect.u32Width = pixWidth;
                        pstDstRect.u32Height = rc1.s16Y2 - rc1.s16Y1;
                    }
                    else if(j == 1)
                    {
                        pstDstRect.s32Xpos = rc1.s16X1;
                        pstDstRect.s32Ypos =rc1.s16Y1;
                        pstDstRect.u32Width = rc1.s16X2 - rc1.s16X1;
                        pstDstRect.u32Height = pixWidth;
                    }
                    else if(j == 2)
                    {
                        pstDstRect.s32Xpos = rc1.s16X1;
                        pstDstRect.s32Ypos =rc1.s16Y2;
                        pstDstRect.u32Width = rc1.s16X2 - rc1.s16X1;
                        pstDstRect.u32Height = pixWidth;
                    }
                    else if(j == 3)
                    {
                        pstDstRect.s32Xpos = rc1.s16X2;
                        pstDstRect.s32Ypos =rc1.s16Y1;
                        pstDstRect.u32Width = pixWidth;
                        pstDstRect.u32Height = rc1.s16Y2 - rc1.s16Y1+pixWidth;
                    }
                  //  printf("s32Xpos:%d,s32Ypos:%d,u32Width:%d,u32Height:%d\n",pstDstRect.s32Xpos,pstDstRect.s32Ypos,pstDstRect.u32Width,pstDstRect.u32Height);
                    HI_TDE2_SolidDraw( s32Handle,NULL,NULL,pstDst,&pstDstRect,&pstFillColor,&pstOpt);
                }

            }
            /*pstDstRect.s32Xpos = rc1.s16X1;
            pstDstRect.s32Ypos =rc1.s16Y1;
            pstDstRect.u32Width = rc1.s16X2 - rc1.s16X1;
            pstDstRect.u32Height = rc1.s16Y2 - rc1.s16Y1;
            HI_TDE2_SolidDraw( s32Handle,NULL,NULL,pstDst,&pstDstRect,&pstFillColor,&pstOpt);*/
        }

    }
}

static TDE2_SURFACE_S g_stScreen[2];
static TDE2_SURFACE_S* g_pstBackGround = NULL;
static TDE2_SURFACE_S g_stScreen_pic[2];
static TDE2_SURFACE_S g_stBackGround0;
static TDE2_SURFACE_S g_stBackGround1;
static TDE2_SURFACE_S g_stBackGround2;
static TDE2_SURFACE_S g_stBackGround3;
static TDE2_SURFACE_S g_stBackGround4;
static TDE2_SURFACE_S g_stBackGround5;
static TDE2_SURFACE_S g_stPingBuf;
static TDE2_SURFACE_S g_stPangBuf;
static HI_S32 TDE_CreateSurfaceByFile(const HI_CHAR *pszFileName, TDE2_SURFACE_S *pstSurface, HI_U8 *pu8Virt)
{
    FILE *fp;
    HI_U32 colorfmt, w, h, stride;

    if((NULL == pszFileName) || (NULL == pstSurface))
    {
        printf("%s, LINE %d, NULL ptr!\n", __FUNCTION__, __LINE__);
        return -1;
    }

    fp = fopen(pszFileName, "rb");
    if(NULL == fp)
    {
        printf("error when open pszFileName %s, line:%d\n", pszFileName, __LINE__);
        return -1;
    }

    fread(&colorfmt, 1, 4, fp);
    fread(&w, 1, 4, fp);
    fread(&h, 1, 4, fp);
    fread(&stride, 1, 4, fp);

    pstSurface->enColorFmt = colorfmt;
    pstSurface->u32Width = w;
    pstSurface->u32Height = h;
    pstSurface->u32Stride = stride;
    pstSurface->u8Alpha0 = 0;
    pstSurface->u8Alpha1 = 0xff;
    pstSurface->bAlphaMax255 = HI_TRUE;

    fread(pu8Virt, 1, stride*h, fp);

    fclose(fp);

    return 0;
}
int RunHiFBTde(int layer)
{
    int fd;
    int i;
	int j;
    struct fb_fix_screeninfo fix;
    struct fb_var_screeninfo var;
    HIFB_CAPABILITY_S cap;
	HI_U32 u32FixScreenStride = 0;
    unsigned char *pShowScreen;
    unsigned char *pHideScreen;
	HIFB_ALPHA_S stAlpha;
    HIFB_POINT_S stPoint = {0, 0};
    FILE *fp;
    char file[12] = "/dev/fb0";
    char image_name[128];
	HI_CHAR *pDst = NULL;

    HI_U32 u32PhyAddr;
    HI_U32 u32Size;
    HI_U32 u32CurOnShow = 0;
    HI_U32 u32NextOnShow = 1;
    /* 1. open tde device */

    HI_TDE2_Open();

    /* 1. open framebuffer device overlay 0 */
    //fd = open(file, O_RDWR, 0);
    /* 2. framebuffer operation */
    fd = open("/dev/fb0", O_RDWR);
    if(fd < 0)
    {
        printf("open %s failed!\n",file);
        return -1;
    }

    /* 2. set the screen original position */
    if (ioctl(fd, FBIOPUT_SCREEN_ORIGIN_HIFB, &stPoint) < 0)
    {
        printf("set screen original show position failed!\n");
        close(fd);
        return -1;
    }
#if 1
	SetTrasValueBydevPath(fd);
#else
	/* 3.set alpha */
	stAlpha.bAlphaEnable = HI_FALSE;
	stAlpha.bAlphaChannel = HI_FALSE;
	stAlpha.u8Alpha0 = 0xff;
	stAlpha.u8Alpha1 = 0x8f;
    stAlpha.u8GlobalAlpha = 0x80;

	if (ioctl(fd, FBIOPUT_ALPHA_HIFB,  &stAlpha) < 0)
	{
	    printf("Set alpha failed!\n");
        close(fd);
        return -1;
	}

#endif
    /* 4. get the variable screen info */
    if (ioctl(fd, FBIOGET_VSCREENINFO, &var) < 0)
    {
   	    printf("Get variable screen info failed!\n");
        close(fd);
        return -1;
    }

    /* 5. modify the variable screen info
          the screen size: IMAGE_WIDTH*IMAGE_HEIGHT
          the virtual screen size: VIR_SCREEN_WIDTH*VIR_SCREEN_HEIGHT
          (which equals to VIR_SCREEN_WIDTH*(IMAGE_HEIGHT*2))
          the pixel format: ARGB1555
    */

    var.xres_virtual = VIR_SCREEN_WIDTH;
	var.yres_virtual = VIR_SCREEN_HEIGHT;
	var.xres = IMAGE_WIDTH;
    var.yres = IMAGE_HEIGHT;

    var.transp= g_a16;
    var.red = g_r16;
    var.green = g_g16;
    var.blue = g_b16;
    var.bits_per_pixel = 16;
    var.activate = FB_ACTIVATE_FORCE;
    /* 6. set the variable screeninfo */
    if (ioctl(fd, FBIOPUT_VSCREENINFO, &var) < 0)
    {
   	    printf("Put variable screen info failed!\n");
        close(fd);
        return -1;
    }

    /* 7. get the fix screen info */
    if (ioctl(fd, FBIOGET_FSCREENINFO, &fix) < 0)
    {
   	    printf("Get fix screen info failed!\n");
        close(fd);
        return -1;
    }
	u32FixScreenStride = fix.line_length;	/*fix screen stride*/

    /* 8. map the physical video memory for user use */
    u32Size 	= fix.smem_len;
    u32PhyAddr  = fix.smem_start;
    pShowScreen = mmap(NULL, fix.smem_len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(MAP_FAILED == pShowScreen)
    {
   	    printf("mmap framebuffer failed!\n");
        close(fd);
        return -1;
    }

    pHideScreen = pShowScreen + u32FixScreenStride*IMAGE_HEIGHT;
    memset(pShowScreen, 0x0000, u32FixScreenStride*IMAGE_HEIGHT);

    /* 9. create surface */
    g_stScreen[0].enColorFmt = PIXFMT;
    g_stScreen[0].u32PhyAddr = u32PhyAddr;
    g_stScreen[0].u32Width = VIR_SCREEN_WIDTH;
    g_stScreen[0].u32Height = IMAGE_HEIGHT;
    g_stScreen[0].u32Stride = fix.line_length;
    g_stScreen[0].bAlphaMax255 = HI_TRUE;
    g_stScreen[1] = g_stScreen[0];
    g_stScreen[1].u32PhyAddr = g_stScreen[0].u32PhyAddr + g_stScreen[0].u32Stride * g_stScreen[0].u32Height;

    //g_stBackGround = g_stScreen[0];
   // g_stBackGround.u32PhyAddr = g_stScreen[1].u32PhyAddr + g_stScreen[1].u32Stride * g_stScreen[1].u32Height;
    //TDE_CreateSurfaceByFile(PEA_IMAGE_PATH1, &g_stBackGround, pShowScreen + ((HI_U32)g_stBackGround.u32PhyAddr - u32PhyAddr));


    g_stPingBuf = g_stScreen[0];
    g_stPangBuf = g_stScreen[1];
    //g_stBackGround.u32PhyAddr = g_stScreen[1].u32PhyAddr + g_stScreen[1].u32Stride * g_stScreen[1].u32Height;

        // var.yoffset = (i%2)?0:1024;
         //var.yoffset = 0;
        /*set frame buffer start position*/

    i = 0;
    while(1)
    {
        int target_num = 0;
        i++;
        u32CurOnShow = i%2;
        u32NextOnShow = !u32CurOnShow;
        if(u32CurOnShow == 1)
        {
            g_pstBackGround = &g_stPingBuf;
        }
        else
        {
            g_pstBackGround = &g_stPangBuf;
        }
        TDE_HANDLE s32Handle;
        TDE2_OPT_S stOpt = {0};
        HI_FLOAT eXMid, eYMid;
        HI_FLOAT eRadius;
        HI_U32 i;
        HI_FLOAT f;
        HI_U32 u32NextOnShow;
        TDE2_RECT_S stSrcRect;
        TDE2_RECT_S stDstRect;
        HI_S32 s32Ret;
        HI_U32 u32FillData = 0x8010;

        target_num = gstPeaResult.stTargetSet.s32TargetNum;

        if(target_num >= 0)
        {printf("TDE2_BeginJob!\n");
        /* 1. start job */
        s32Handle = HI_TDE2_BeginJob();
        if(HI_ERR_TDE_INVALID_HANDLE == s32Handle)
        {
        //    TDE_PRINT("start job failed!\n");
            printf("start job failed!\n");
            return ;
        }

        //memset(pShowScreen, 0x0000, u32FixScreenStride*IMAGE_HEIGHT);
        stDstRect.s32Xpos = 0;
        stDstRect.s32Ypos = 0;
        stDstRect.u32Width = VIR_SCREEN_WIDTH;
        stDstRect.u32Height = IMAGE_HEIGHT;
        s32Ret = HI_TDE2_QuickFill( s32Handle, g_pstBackGround,&stDstRect, 0);

      /*  stSrcRect.s32Xpos = 0;
        stSrcRect.s32Ypos = 0;
        stSrcRect.u32Width = g_stBackGround.u32Width;
        stSrcRect.u32Height = g_stBackGround.u32Height;*/
        /* 2. bitblt background to screen */
        //s32Ret = HI_TDE2_QuickCopy(s32Handle, &g_stBackGround, &stSrcRect, g_pstBackGround, &stSrcRect);
        printf("TDE2_BeginJob2!\n");
        stDstRect.s32Xpos = 0;
        stDstRect.s32Ypos = 0;
        stDstRect.u32Width = 120;
        stDstRect.u32Height = 120;
        stSrcRect.s32Xpos = 0;
        stSrcRect.s32Ypos = 0;
        stSrcRect.u32Width = g_pstBackGround->u32Width;
        stSrcRect.u32Height = g_pstBackGround->u32Height;


        TDE_OUTPUT_PEA_RESULT(s32Handle, g_pstBackGround,&gstPeaResult);//,&stDstRect);

       /* TDE_CreateSurfaceByFile(PEA_IMAGE_PATH1, g_pstBackGround, pShowScreen + ((HI_U32)g_pstBackGround->u32PhyAddr - u32PhyAddr));
        stDstRect.s32Xpos = 0;
        stDstRect.s32Ypos = 0;
        stDstRect.u32Width = 50;
        stDstRect.u32Height = 50;
        s32Ret = HI_TDE2_QuickCopy(s32Handle, g_pstBackGround, &stDstRect, g_pstBackGround, &stDstRect);*/
        //printf("(%d,%d,%d,%d)\n",stDstRect.s32Xpos,stDstRect.s32Ypos,stDstRect.u32Width,stDstRect.u32Height);
        //IP_TGT_SET	*target_set = g_IP_Result.target_set;
        //target_num = g_IP_Result.target_set.target_num;
        //printf("TDE target_num :%d\n",target_num);
      //  if(target_num > 0)
        //s32Ret = HI_TDE2_QuickFill( s32Handle, &g_stBackGround,&stDstRect, u32FillData);
  /*      else
        {
            s32Ret = HI_TDE2_QuickFill( s32Handle, &g_stBackGround,&stDstRect, 0);
        }*/
      /*  HI_TDE2_SolidDraw( s32Handle,NULL,NULL,&g_stBackGround,&stDstRect
TDE2_SURFACE_S *pstDst,
TDE2_IMP_RECT_S *pstDstRect,
TDE2_FILLCOLOR_S *pstFillColor,
TDE2_OPT_S *pstOpt);*/

        if(s32Ret < 0)
        {
            printf("Line:%d,HI_TDE2_QuickFill failed,ret=0x%x!\n", __LINE__, s32Ret);
            return ;
        }
         printf("TDE2_BeginJob3!\n");
#if 0
        /* 2. bitblt background to screen */
        s32Ret = HI_TDE2_QuickCopy(s32Handle, &g_stBackGround, &stSrcRect, &g_stScreen[u32NextOnShow], &stSrcRect);

        if(s32Ret < 0)
        {
            printf("Line:%d,HI_TDE2_QuickCopy failed,ret=0x%x!\n", __LINE__, s32Ret);
            HI_TDE2_CancelJob(s32Handle);
            return ;
        }
        printf("TDE2_BeginJob4!\n");
#endif
        /* 5. submit job */
        s32Ret = HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 10);
        if(s32Ret < 0)
        {
          //  TDE_PRINT("Line:%d,HI_TDE2_EndJob failed,ret=0x%x!\n", __LINE__, s32Ret);
            HI_TDE2_CancelJob(s32Handle);
            return ;
        }
        printf("TDE2_EndJob5!\n");
        }
        var.yoffset = (u32CurOnShow==1) ? 0 : IMAGE_HEIGHT;
        if (ioctl(fd, FBIOPAN_DISPLAY, &var) < 0)
        {
             //TDE_PRINT("process frame buffer device error\n");
             printf("process frame buffer device error\n");
             //goto FB_PROCESS_ERROR1;
        }
        usleep(1000);
    }


    printf("Enter to quit!\n");
    getchar();

    /* 10.unmap the physical memory */
    munmap(pShowScreen, fix.smem_len);

    /* 11. close the framebuffer device */
    close(fd);

    HI_TDE2_Close();
    return 0;
}

int ProcessHiFbTde()
{
	HI_S32 s32Ret = 0;
    VOU_DEV_E VoDev = HD;
    int layer = 0;
    //return -1;
   // sleep(2);
	/*2 run hifbTde*/
	s32Ret = RunHiFBTde(layer);
	if(s32Ret != HI_SUCCESS)
	{
		goto err;
	}

	err:
	DisableVoDev(HD);
	DisableVoDev(SD);
	MppSysExit();

	return 0;

}


#define PIC_IMAGE_WIDTH     1280
#define PIC_IMAGE_HEIGHT    1024
#define PIC_IMAGE_SIZE      (1280*1024*2)
#define PIC_IMAGE_NUM       14
#define PIC_IMAGE_PATH		"./res/%d.bits"
#define PIC_PEA_IMAGE_PATH1		"./res/pea1.bits"
#define PIC_PEA_IMAGE_PATH2		"./res/pea2.bits"
#define PIC_PEA_IMAGE_PATH3		"./res/pea3.bits"
#define PIC_PEA_IMAGE_PATH4		"./res/pea4.bits"
#define PIC_PEA_IMAGE_PATH5		"./res/pea5.bits"
#define PIC_PEA_IMAGE_PATH6		"./res/pea6.bits"
//#define VIR_SCREEN_WIDTH	640					/*virtual screen width*/
//#define VIR_SCREEN_HEIGHT	IMAGE_HEIGHT*2		/*virtual screen height*/
#define PIC_VIR_SCREEN_WIDTH	1280					/*virtual screen width*/
#define PIC_VIR_SCREEN_HEIGHT	PIC_IMAGE_HEIGHT*2		/*virtual screen height*/


#define NEW_PIC_IMAGE_WIDTH     79
#define NEW_PIC_IMAGE_HEIGHT    24
#define NEW_PIC_IMAGE_SIZE      (79*24*2)
#define NEW_PIC_IMAGE_NUM       14
#define NEW_PIC_IMAGE_PATH		"./res/%d.bits"
#define NEW_PIC_PEA_IMAGE_PATH1		"./res/pea1.bits"
#define NEW_PIC_PEA_IMAGE_PATH2		"./res/pea2.bits"
#define NEW_PIC_PEA_IMAGE_PATH3		"./res/pea3.bits"
#define NEW_PIC_PEA_IMAGE_PATH4		"./res/pea4.bits"

#define NEW_PIC_VIR_SCREEN_WIDTH	79					/*virtual screen width*/
#define NEW_PIC_VIR_SCREEN_HEIGHT	PIC_IMAGE_HEIGHT*2		/*virtual screen height*/
int RunHiFBTde_PIC(int layer)
{
    int fd;
    int i;
	int j;
    struct fb_fix_screeninfo fix;
    struct fb_var_screeninfo var;
    HIFB_CAPABILITY_S cap;
	HI_U32 u32FixScreenStride = 0;
    unsigned char *pShowScreen;
    unsigned char *pHideScreen;
	HIFB_ALPHA_S stAlpha;
    HIFB_POINT_S stPoint = {10, 10};
    FILE *fp;
    char file[12] = "/dev/fb1";
    char image_name[128];
	HI_CHAR *pDst = NULL;
    //int i = 0;
    HI_U32 u32PhyAddr;
    HI_U32 u32Size;
    HI_U32 u32CurOnShow = 0;
    HI_U32 u32NextOnShow = 1;
    //sleep(5);
    /* 1. open tde device */
   //printf("11111111\n");
    HI_TDE2_Open();

    /* 1. open framebuffer device overlay 0 */
    //fd = open(file, O_RDWR, 0);
    /* 2. framebuffer operation */
    fd = open("/dev/fb1", O_RDWR);
    if(fd < 0)
    {
        printf("open %s failed!\n",file);
        return -1;
    }

    if (ioctl(fd, FBIOPUT_VSCREENINFO, &stPoint) < 0)
    {
        printf("set screen original show position failed!\n");
        close(fd);
        return -1;
    }
    /* 2. set the screen original position */
    if (ioctl(fd, FBIOPUT_SCREEN_ORIGIN_HIFB, &stPoint) < 0)
    {
        printf("set screen original show position failed!\n");
        close(fd);
        return -1;
    }
#if 1
	SetTrasValueBydevPath(fd);
#else
	/* 3.set alpha */
	stAlpha.bAlphaEnable = HI_FALSE;
	stAlpha.bAlphaChannel = HI_FALSE;
	stAlpha.u8Alpha0 = 0xff;
	stAlpha.u8Alpha1 = 0x8f;
    stAlpha.u8GlobalAlpha = 0x80;

	if (ioctl(fd, FBIOPUT_ALPHA_HIFB,  &stAlpha) < 0)
	{
	    printf("Set alpha failed!\n");
        close(fd);
        return -1;
	}

#endif
    /* 4. get the variable screen info */
    if (ioctl(fd, FBIOGET_VSCREENINFO, &var) < 0)
    {
   	    printf("Get variable screen info failed!\n");
        close(fd);
        return -1;
    }

    /* 5. modify the variable screen info
          the screen size: IMAGE_WIDTH*IMAGE_HEIGHT
          the virtual screen size: VIR_SCREEN_WIDTH*VIR_SCREEN_HEIGHT
          (which equals to VIR_SCREEN_WIDTH*(IMAGE_HEIGHT*2))
          the pixel format: ARGB1555
    */

    var.xres_virtual = PIC_VIR_SCREEN_WIDTH;
	var.yres_virtual = PIC_VIR_SCREEN_HEIGHT;
	var.xres = PIC_IMAGE_WIDTH;
    var.yres = PIC_IMAGE_HEIGHT;

    var.transp= g_a16;
    var.red = g_r16;
    var.green = g_g16;
    var.blue = g_b16;
    var.bits_per_pixel = 16;
    var.activate = FB_ACTIVATE_FORCE;
    /* 6. set the variable screeninfo */
    if (ioctl(fd, FBIOPUT_VSCREENINFO, &var) < 0)
    {
   	    printf("Put variable screen info failed!\n");
        close(fd);
        return -1;
    }

    /* 7. get the fix screen info */
    if (ioctl(fd, FBIOGET_FSCREENINFO, &fix) < 0)
    {
   	    printf("Get fix screen info failed!\n");
        close(fd);
        return -1;
    }
	u32FixScreenStride = fix.line_length;	/*fix screen stride*/

    /* 8. map the physical video memory for user use */
    u32Size 	= fix.smem_len;
    u32PhyAddr  = fix.smem_start;
    pShowScreen = mmap(NULL, fix.smem_len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(MAP_FAILED == pShowScreen)
    {
   	    printf("mmap framebuffer failed!\n");
        close(fd);
        return -1;
    }

    pHideScreen = pShowScreen + u32FixScreenStride*PIC_IMAGE_HEIGHT;
    memset(pShowScreen, 0x0000, u32FixScreenStride*PIC_IMAGE_HEIGHT);

    /* 9. create surface */
    g_stScreen_pic[0].enColorFmt = PIXFMT;
    g_stScreen_pic[0].u32PhyAddr = u32PhyAddr;
    g_stScreen_pic[0].u32Width = PIC_VIR_SCREEN_WIDTH;
    g_stScreen_pic[0].u32Height = PIC_IMAGE_HEIGHT;
    g_stScreen_pic[0].u32Stride = fix.line_length;
    g_stScreen_pic[0].bAlphaMax255 = HI_TRUE;

    g_stBackGround0 = g_stScreen_pic[0];
    g_stBackGround0.enColorFmt = PIXFMT;
    g_stBackGround0.u32PhyAddr = u32PhyAddr;
    g_stBackGround0.u32Width = NEW_PIC_VIR_SCREEN_WIDTH;
    g_stBackGround0.u32Height = NEW_PIC_IMAGE_HEIGHT;
    g_stBackGround0.u32Stride = NEW_PIC_VIR_SCREEN_WIDTH;
    g_stBackGround0.bAlphaMax255 = HI_TRUE;
    g_stBackGround0.u32PhyAddr = g_stScreen_pic[0].u32PhyAddr + g_stScreen_pic[0].u32Stride * g_stScreen_pic[0].u32Height;
    g_stBackGround1 = g_stBackGround0;
    g_stBackGround1.u32PhyAddr = g_stBackGround0.u32PhyAddr + g_stBackGround0.u32Stride * g_stBackGround0.u32Height;

    g_stBackGround2 = g_stBackGround1;
    g_stBackGround2.u32PhyAddr = g_stBackGround1.u32PhyAddr + g_stBackGround1.u32Stride * g_stBackGround1.u32Height;

    g_stBackGround3 = g_stBackGround2;
    g_stBackGround3.u32PhyAddr = g_stBackGround2.u32PhyAddr + g_stBackGround2.u32Stride * g_stBackGround2.u32Height;

    //g_stBackGround4 = g_stBackGround3;
    g_stBackGround4.enColorFmt = PIXFMT;
    //g_stBackGround0.u32PhyAddr = u32PhyAddr;
    g_stBackGround4.u32Width = 71;
    g_stBackGround4.u32Height = 167;
    g_stBackGround4.u32Stride = 71;
    g_stBackGround4.bAlphaMax255 = HI_TRUE;
    g_stBackGround4.u32PhyAddr = g_stBackGround3.u32PhyAddr + g_stBackGround3.u32Stride * g_stBackGround3.u32Height;

    //g_stBackGround1 = g_stBackGround0;
    //g_stBackGround1.u32PhyAddr = g_stBackGround0.u32PhyAddr + g_stBackGround0.u32Stride * g_stBackGround0.u32Height;
  //  g_stBackGround1 = g_stScreen_pic[0];
  //  g_stBackGround2 = g_stScreen_pic[0];
  //  g_stBackGround3 = g_stScreen_pic[0];
    //g_stBackGround.u32PhyAddr = g_stScreen_pic[0].u32PhyAddr + g_stScreen_pic[0].u32Stride * g_stScreen_pic[0].u32Height;

    i = 0;
    while(1)
    {

        TDE_HANDLE s32Handle;
        TDE2_OPT_S stOpt = {0};
        HI_FLOAT eXMid, eYMid;
        HI_FLOAT eRadius;
        //HI_U32 i;
        HI_FLOAT f;
        HI_U32 u32NextOnShow;
        TDE2_RECT_S stSrcRect;
        TDE2_RECT_S stDstRect;
        HI_S32 s32Ret;
        HI_U32 u32FillData = 0x8010;

        /* 1. start job */
        s32Handle = HI_TDE2_BeginJob();
        if(HI_ERR_TDE_INVALID_HANDLE == s32Handle)
        {
        //    TDE_PRINT("start job failed!\n");
            printf("start job failed!\n");
            return ;
        }

        //memset(pShowScreen, 0x0000, u32FixScreenStride*IMAGE_HEIGHT);
        /*stDstRect.s32Xpos = 0;
        stDstRect.s32Ypos = 0;
        stDstRect.u32Width = PIC_VIR_SCREEN_WIDTH;
        stDstRect.u32Height = PIC_IMAGE_HEIGHT;*/
        i++;
        //if(i == 3)
         //   i = 0;

        stDstRect.s32Xpos = 0;
        stDstRect.s32Ypos = 0;
        stDstRect.u32Width = g_stBackGround0.u32Width;
        stDstRect.u32Height = g_stBackGround0.u32Height;

        stSrcRect.s32Xpos = 0;
        stSrcRect.s32Ypos = 0;
        stSrcRect.u32Width = g_stBackGround0.u32Width;
        stSrcRect.u32Height = g_stBackGround0.u32Height;
        //stSrcRect.u32Width = g_stBackGround0.u32Width;
        //stSrcRect.u32Height = g_stBackGround0.u32Height;
        printf("i = %d\n",i);
        if(i%5==0)
        {
            TDE_CreateSurfaceByFile(PIC_PEA_IMAGE_PATH1, &g_stBackGround0, pShowScreen + ((HI_U32)g_stBackGround0.u32PhyAddr - u32PhyAddr));
            HI_TDE2_QuickCopy(s32Handle, &g_stBackGround0, &stSrcRect, &g_stScreen_pic[0], &stDstRect);
        }
        else if(i%5==1)
        {
            TDE_CreateSurfaceByFile(PIC_PEA_IMAGE_PATH4, &g_stBackGround3, pShowScreen + ((HI_U32)g_stBackGround3.u32PhyAddr - u32PhyAddr));
            stDstRect.s32Xpos = (IMAGE_WIDTH>>1)+2;
            stDstRect.s32Ypos = (IMAGE_HEIGHT>>1)+2;
            stDstRect.u32Width = g_stBackGround3.u32Width;
            stDstRect.u32Height = g_stBackGround3.u32Height;

            s32Ret = HI_TDE2_QuickCopy(s32Handle, &g_stBackGround3, &stSrcRect, &g_stScreen_pic[0], &stDstRect);
            if(s32Ret < 0)
            {
                printf("Line:%d,HI_TDE2_QuickCopy failed,ret=0x%x!\n", __LINE__, s32Ret);
                return ;
            }
        }
        else if(i%5==2)
        {
            printf("TDE_CreateSurfaceByFile\n");
            TDE_CreateSurfaceByFile(PIC_PEA_IMAGE_PATH2, &g_stBackGround1, pShowScreen + ((HI_U32)g_stBackGround1.u32PhyAddr - u32PhyAddr));
            stSrcRect.s32Xpos = 0;
            stSrcRect.s32Ypos = 0;
            stSrcRect.u32Width = g_stBackGround1.u32Width;
            stSrcRect.u32Height = g_stBackGround1.u32Height;

            stDstRect.s32Xpos =(IMAGE_WIDTH>>1)+2;
            stDstRect.s32Ypos = 0;
            stDstRect.u32Width = g_stBackGround1.u32Width;
            stDstRect.u32Height = g_stBackGround1.u32Height;
            s32Ret = HI_TDE2_QuickCopy(s32Handle, &g_stBackGround1, &stSrcRect, &g_stScreen_pic[0], &stDstRect);
            if(s32Ret < 0)
            {
                printf("Line:%d,HI_TDE2_QuickCopy failed,ret=0x%x!\n", __LINE__, s32Ret);
                return ;
            }
        }
        else if(i%5==3)
         {
            TDE_CreateSurfaceByFile(PIC_PEA_IMAGE_PATH3, &g_stBackGround2, pShowScreen + ((HI_U32)g_stBackGround2.u32PhyAddr - u32PhyAddr));
            stDstRect.s32Xpos =0;
            stDstRect.s32Ypos = (IMAGE_HEIGHT>>1)+2;
            stDstRect.u32Width = g_stBackGround2.u32Width;
            stDstRect.u32Height = g_stBackGround2.u32Height;
            s32Ret = HI_TDE2_QuickCopy(s32Handle, &g_stBackGround2, &stSrcRect, &g_stScreen_pic[0], &stDstRect);
        }
        else if(i%5==4)
        {
            TDE_CreateSurfaceByFile(PIC_PEA_IMAGE_PATH6, &g_stBackGround4, pShowScreen + ((HI_U32)g_stBackGround4.u32PhyAddr - u32PhyAddr));
            stSrcRect.s32Xpos = 0;
            stSrcRect.s32Ypos = 0;
            stSrcRect.u32Width = 79;
            stSrcRect.u32Height = g_stBackGround4.u32Height;
            stDstRect.s32Xpos = (IMAGE_WIDTH>>1)+2;
            stDstRect.s32Ypos = (IMAGE_HEIGHT>>1)+35;
            stDstRect.u32Width = 79;
            stDstRect.u32Height = g_stBackGround4.u32Height;
            s32Ret = HI_TDE2_QuickCopy(s32Handle, &g_stBackGround4, &stSrcRect, &g_stScreen_pic[0], &stDstRect);
        }
        //printf("g_stBackGround1.u32Width:%d,g_stBackGround1.u32Height:%d\n",g_stBackGround1.u32Width,g_stBackGround1.u32Height);
/*

*/


   /*
*/
        /* 5. submit job */
        s32Ret = HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 10);
        if(s32Ret < 0)
        {
          //  TDE_PRINT("Line:%d,HI_TDE2_EndJob failed,ret=0x%x!\n", __LINE__, s32Ret);
            HI_TDE2_CancelJob(s32Handle);
            return ;
        }
        printf("TDE2_PIC_EndJob5!\n");

        var.yoffset = 0;
        if (ioctl(fd, FBIOPAN_DISPLAY, &var) < 0)
        {
             //TDE_PRINT("process frame buffer device error\n");
             printf("process frame buffer device error\n");
             //goto FB_PROCESS_ERROR1;
        }
        usleep(2000000);
    }
     /* 2. bitblt background to screen */
   // HI_TDE2_QuickCopy(s32Handle, &g_stBackGround, &stSrcRect, &g_stScreen_pic[0], &stSrcRect);


    /* 10.unmap the physical memory */
    munmap(pShowScreen, fix.smem_len);

    /* 11. close the framebuffer device */
    close(fd);

    HI_TDE2_Close();
    return 0;
}

int ProcessHiFbTde_PIC()
{
	HI_S32 s32Ret = 0;
    VOU_DEV_E VoDev = HD;
    int layer = 0;
    //return -1;
 //   sleep(1);
	/*2 run hifbTde*/
	s32Ret = RunHiFBTde_PIC(layer);
	if(s32Ret != HI_SUCCESS)
	{
		goto err;
	}

	err:
	DisableVoDev(HD);
	DisableVoDev(SD);
	MppSysExit();

	return 0;

}
