
#include "imp_algo_type.h"
#include "imp_algo_interface.h"
#include "imp_algo_urp_param.h"


URP_PARA_S URPpara;
#define PAR_SRC_FILE 0
#define MAX_RULE_DATA_SIZE 64*1024


static void DEBUG_startArmNICE( IMP_MODULE_HANDLE hModule, IMP_S32 nImgW, IMP_S32 nImgH )
{
	EXTERNAL_PARA_S *vapara = IMP_PARA_Alloc( IMP_PARA_RULE_BUFLEN,
		IMP_PARA_ADVBUF_BUFCNT, IMP_PARA_ADVBUF_BUFLEN, NULL );
	
	memset(&URPpara,0,sizeof(URP_PARA_S));
	{
        URPpara.stConfigPara.s32ImgW = 352;
		URPpara.stConfigPara.s32ImgH = 288;
		URPpara.stRuleSet.astRule[0].u32Enable = 1;
		URPpara.stRuleSet.astRule[0].u32Valid = 1;
		URPpara.stRuleSet.astRule[0].u32Mode |= IMP_FUNC_PERIMETER;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.s32Mode = IMP_URP_PMODE_INTRUSION;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.s32TypeLimit = 0;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.s32TypeHuman = 1;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.s32TypeVehicle = 1;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.s32DirectionLimit = 0;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.s32ForbiddenDirection = 180;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.s32MinDist = 0;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.s32MinTime = 0;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.s32BoundaryPtNum = 4;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.astBoundaryPts[0].s16X = 10;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.astBoundaryPts[0].s16Y = 10;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.astBoundaryPts[1].s16X = 10;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.astBoundaryPts[1].s16Y = 270;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.astBoundaryPts[2].s16X = 340;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.astBoundaryPts[2].s16Y = 270;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.astBoundaryPts[3].s16X = 340;
		URPpara.stRuleSet.astRule[0].stPara.stPerimeterRulePara.strLimitPara.stBoundary.astBoundaryPts[3].s16Y = 10;
		
		URPpara.stRuleSet.astRule[1].u32Enable = 1;
		URPpara.stRuleSet.astRule[1].u32Valid = 1;
		URPpara.stRuleSet.astRule[1].u32Mode |= IMP_FUNC_TRIPWIRE;
		URPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.s32TypeLimit = 0;
		URPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.s32TypeHuman =1;
		URPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.s32TypeVehicle =1;
		URPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLimitPara.s32MinDist=0;
		URPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLimitPara.s32MinTime=0;
		URPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLines[0].s32ForbiddenDirection=0;
		URPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLines[0].s32IsDoubleDirection=1;
		URPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLines[0].s32Valid=1;
		URPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLines[0].stLine.stStartPt.s16X=232;
		URPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLines[0].stLine.stStartPt.s16Y=0;
		URPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLines[0].stLine.stEndPt.s16X=232;
		URPpara.stRuleSet.astRule[1].stPara.stTripwireRulePara.astLines[0].stLine.stEndPt.s16Y=270;
	}
	
    IMP_PARA_Init( vapara, NULL, NULL, nImgW, nImgH, NULL );	
    IMP_ConfigParameter( hModule, vapara );
    //IMP_ConfigArmPeaParameter( hModule, vapara ,&URPpara );
	IMP_PARA_Free( vapara, IMP_PARA_ADVBUF_BUFCNT, NULL );
}


static void IMP_Example()
{
	OBJ_S vao;
	IMP_HANDLE hva = &vao;
	IMP_U32 version;
	IMP_U32 funcode;
//	IMP_U32 enacode;
	MEM_SET_S vamems;
	EXTERNAL_PARA_S *vapara_e;
//	INNER_PARA_S *vapara_i;
	YUV_IMAGE422_S image;
	RESULT_S varesult;
	IMP_S32 cmd_cancel=1;
	IMP_S32 w, h;

	w = 352; h = 288;
	IMP_YUVImage422Create( &image, w, h, NULL );

	// ��ȡ�汾��Ϣ
	IMP_GetVersion( hva, &version );

	// ��ȡ������
	IMP_GetFuncode( hva, &funcode );

	// ��ȡ�ڴ�����
	vamems.u32ImgW = w;
	vamems.u32ImgH = h;
	IMP_GetMemReq( hva, &vamems );

	// ��ȡDMA����
	//IMP_GetDmaReq( hva, &idmachs );

	// ��ʼ��ģ��
	IMP_MemsAlloc( &vamems );
	if(	IMP_Initialize( hva, &vamems ) != IMP_STATUS_OK)
	   exit(0);

	// ����DMAͨ��
	// prepare idmachs...
	//IMP_InitIdmaChs( hva, &idmachs );

	// ���ò���
	//IMP_PARA_Init( vapara_e, NULL, NULL, w, h, NULL );
	IMP_ConfigParameter( hva, vapara_e );

	// ��ȡ����
	//IMP_GetParameter( hva, &vapara_i );

	// ��ȡʹ����
	//IMP_GetEnacode( hva, &enacode );

	// ����ģ��
	IMP_Start( hva );

	while( 1 )
	{
		// ����һ֡ͼ��
		// prepare image...
		IMP_ProcessImage( hva, &image );

		// ��ȡ�������
		IMP_GetResults( hva, &varesult );

		// �������
		//IMP_DoSpecial( hva, &vaop );

		// �ӵ��˳�����
		if( --cmd_cancel == 0 )
			break;
	}

	// ֹͣģ��
	IMP_Stop( hva, &varesult );

	// ��ֹģ��
	IMP_Terminate( hva );
	IMP_MemsFree( &vamems );
	IMP_YUVImage422Destroy( &image, NULL );
}


