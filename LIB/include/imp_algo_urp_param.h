/**
* \defgroup �ӿ�
* �ӿ�
* @author �������ټ���
* @version 2.0
* @data 2009-2010
*/
/*@{*/

/**
* \defgroup �û�����Э�飨URP��
* �����弰����
* @author �������ټ���
* @version 2.0
* @data 2009-2010
*/
/*@{*/

#ifndef _IMP_ALGO_URP_PARAM_H_
#define _IMP_ALGO_URP_PARAM_H_


#ifdef __cplusplus
extern "C"
{
#endif


/** �������� */
typedef enum impURP_SCENE_TYPE_E
{
	IMP_URP_INDOOR = 0,					/**< ���ڳ��� */
	IMP_URP_OUTDOOR						/**< ���ⳡ�� */
} URP_SCENE_TYPE_E;

//�������
typedef enum impURP_CAMERA_TYPE_E
{
	IMP_URP_COMMON_CAMERA = 0,
	IMP_URP_PINHOLE_CAMERA
} URP_CAMERA_TYPE_E;

/** �ܽ���ģʽ */
typedef enum impURP_PERIMETER_MODE_E
{
	IMP_URP_PMODE_INTRUSION = 0,/**< ���� */
	IMP_URP_PMODE_ENTER,		/**< ���� */
	IMP_URP_PMODE_EXIT			/**< �뿪 */
} URP_PERIMETER_MODE_E;

/** ���߽���� */
#define IMP_MAX_BOUNDARY_POINT_NUM 8

//Added by mzhang 2011-11-14 14:02:48
#define IMP_MAX_POINT_NUM 4
#define IMP_NAME_BUF_SIZE 16

/** ����� */
typedef struct impURP_IMP_POINT_S
{
	IMP_S16 s16X;        /**< x */
	IMP_S16 s16Y;        /**< y */
}URP_IMP_POINT_S;

/** �߽ṹ */
typedef struct impURP_LINE_S
{
	URP_IMP_POINT_S stStartPt;	/**< �߶���� */
	URP_IMP_POINT_S stEndPt;	/**< �߶��յ� */
}URP_LINE_S;

//added by mzhang 2011-11-14 14:00:14
typedef struct impURP_POLYGON_REGION_S
{
	IMP_S32 s32Valid;
	IMP_S32 s32PointNum;
	URP_IMP_POINT_S astPoint[IMP_MAX_BOUNDARY_POINT_NUM];
} URP_POLYGON_REGION_S;

/** URP�ܽ���߽�� */
typedef struct impURP_PERIMETER_LIMIT_BOUNDARY_S
{
	IMP_S32       s32BoundaryPtNum;								    /**< �߽����Ŀ */
	URP_IMP_POINT_S   astBoundaryPts[IMP_MAX_BOUNDARY_POINT_NUM];	/**< �߽�㼯�� */
}URP_PERIMETER_LIMIT_BOUNDARY_S;

/** URP�ܽ������Ʋ��� */
typedef struct impURP_PERIMETER_LIMIT_PARA_S
{
	IMP_S32 s32MinDist;							    /**< ��С���ؾ��� */
	IMP_S32 s32MinTime;							    /**< ���ʱ�� */
	IMP_S32	s32DirectionLimit;						/**< �Ƿ����������� */
	IMP_S32 s32ForbiddenDirection;					/**< ��ֹ����Ƕ�(��λ: �Ƕ�) */
	URP_PERIMETER_LIMIT_BOUNDARY_S stBoundary;		/**< �ܽ�߽����� */
}URP_PERIMETER_LIMIT_PARA_S;

/** URP�ܽ��������� */
typedef struct impURP_PERIMETER_RULE_PARA_S
{
	IMP_S32 s32TypeLimit;							/**< Ŀ���������� */
	IMP_S32 s32TypeHuman;							/**< Ŀ�������(�޶�����ʱʹ��) */
	IMP_S32 s32TypeVehicle;						    /**< Ŀ����𣺳� */
	IMP_S32 s32Mode;								/**< �ܽ�ģʽ */
	URP_PERIMETER_LIMIT_PARA_S stLimitPara;		/**< �ܽ����Ʋ��� */
} URP_PERIMETER_RULE_PARA_S;

//��Ʒ����-begin
#define IMP_MAX_OSC_NUM 4
typedef struct impURP_OSC_SPECL_REGIONS_S
{
	IMP_S32 s32Valid; //�Ƿ���Ч
	IMP_S8 as8Name[IMP_NAME_BUF_SIZE]; //��������
	URP_POLYGON_REGION_S stOscRg; //Ҫ���������
	URP_POLYGON_REGION_S astSubRgA; //��������е���Ч������
	URP_POLYGON_REGION_S astSubRgB; //��������е���Ч������
	URP_POLYGON_REGION_S astSubRgC; //��������е���Ч������
} URP_OSC_SPECL_REGIONS_S;

typedef struct impURP_OSC_LMT_PARA_S
{
	IMP_S32 s32TimeMin; //ʱ��Լ��
	IMP_S32 s32SizeMin; //��С�ߴ�
	IMP_S32 s32SizeMax; //���ߴ�
} URP_OSC_LMT_PARA_S;

typedef struct impURP_OSC_RULE_PARA_S
{
	IMP_S32 s32SceneType; //��������
	IMP_S32 s32CameraType; //�������
	URP_OSC_SPECL_REGIONS_S astSpclRgs[IMP_MAX_OSC_NUM]; //Ҫ������������
	URP_OSC_LMT_PARA_S stOscPara; //һЩԼ��
} URP_OSC_RULE_PARA_S;
//��Ʒ����-end

/** URP������������� */
#define IMP_URP_MAX_TRIPWIRE_CNT 8

/** URP�����߽ṹ */
typedef struct impURP_TRIPWIRE_S
{
	IMP_S32     s32Valid;							/**< �Ƿ���Ч */
	IMP_S32     s32IsDoubleDirection;			    /**< ��ʾ�ð����Ƿ�Ϊ˫�����(0: ��, 1: ��) */
	IMP_S32     s32ForbiddenDirection;	            /**< �����߽�ֹ����Ƕ�(��λ: ��) */
	URP_LINE_S	stLine;				          	    /**< ������λ�� */
}URP_TRIPWIRE_S;

/** URP���������Ʋ��� */
typedef struct impURP_TRIPWIRE_LIMIT_PARA_S
{
	IMP_S32 s32MinDist;			/**< ��С���ؾ��� */
	IMP_S32 s32MinTime;			/**< ���ʱ�� */
}URP_TRIPWIRE_LIMIT_PARA_S;

/** URP�����߹������ */
typedef struct impURP_TRIPWIRE_RULE_PARA_S
{
	IMP_S32 s32TypeLimit;							    /**< Ŀ���������� */
	IMP_S32 s32TypeHuman;							    /**< Ŀ�������(�޶�����ʱʹ��) */
	IMP_S32 s32TypeVehicle;							    /**< Ŀ����𣺳� */
	URP_TRIPWIRE_S astLines[IMP_URP_MAX_TRIPWIRE_CNT];	/**< ������ */
	URP_TRIPWIRE_LIMIT_PARA_S stLimitPara;			    /**< ���������Ʋ��� */
} URP_TRIPWIRE_RULE_PARA_S;

/** URP˫����������� */
#define IMP_URP_MAX_MTRIPWIRE_CNT 4

/** URP˫�����߽ṹ���� */
typedef struct impURP_MTRIPWIRE_S
{
	IMP_S32 s32Valid;					/**< �Ƿ���Ч*/
	IMP_S32 s32TimeMin;					/**< ��Խ�����ߵ����ʱ����(unit: s)*/
	IMP_S32 s32TimeMax;					/**< ��Խ�����ߵ��ʱ����(unit: s)*/
	IMP_S32 as32AbnmlAngle[2];			/**< ˫�����߽�ֹ����Ƕ�(unit: degree)*/
	URP_LINE_S	astLine[2];				/**< ˫������λ��(unit: pixel)*/
} URP_MTRIPWIRE_S;

/** URP˫���������Ʋ������� */
typedef struct impURP_MTRIPWIRE_LMT_PARA_S
{
	IMP_S32 s32DistMin;                /**< ��С���� */
	IMP_S32 s32TimeMin;                /**< ��Сʱ�� */
} URP_MTRIPWIRE_LMT_PARA_S;

/** URP˫�����߹������ */
typedef struct impURP_MTRIPWIRE_RULE_PARA_S
{
	IMP_S32 s32TypeLimit;						    /**< Ŀ���������� */
	IMP_S32 s32TypeHuman;							    /**< Ŀ�������(�޶�����ʱʹ��) */
	IMP_S32 s32TypeVehicle;						        /**< Ŀ����𣺳� */
	URP_MTRIPWIRE_S astLines[IMP_URP_MAX_MTRIPWIRE_CNT];	/**< ˫������ */
	URP_MTRIPWIRE_LMT_PARA_S stLimitPara;                   /**< ���Ʋ��� */
} URP_MTRIPWIRE_RULE_PARA_S;

/** URP�ǻ�������� */
typedef struct impURP_LOITER_RULE_PARA_S
{
	IMP_S32 s32TypeLimit;  	/**< Ŀ���������� */
	IMP_S32 s32TimeMin;			/**< �й����ʱ��(unit: s) */
} URP_LOITER_RULE_PARA_S;

/** ��Ʒ���� */
typedef struct impURP_RULE_PARA_ABANDUM_S
{
	IMP_S32 s32TimeMin;			/**< ��С����ʱ�� */
	IMP_S32 s32SizeMin;			/**< ��С���سߴ� */
	IMP_S32 s32SizeMax;			/**< ������سߴ� */
} URP_RULE_PARA_ABANDUM_S;

/** ��Ʒ���� */
typedef struct impURP_RULE_PARA_OBJ_STOLEN_S
{
	IMP_S32 s32TimeMin;			/**< ��С����ʱ�� */
	IMP_S32 s32SizeMin;			/**< ��С���سߴ� */
	IMP_S32 s32SizeMax;			/**< ������سߴ� */
} URP_RULE_PARA_OBJ_STOLEN_S;

/** �Ƿ�ͣ�� */
typedef struct impURP_RULE_PARA_NO_PARKING_S
{
	IMP_S32 s32TimeMin;			/**< ��С����ʱ�� */
} URP_RULE_PARA_NO_PARKING_S;

/** URP��ֹĿ���������� */
typedef struct impURP_STATIC_OBJ_DETECT_RULE_PARA_S
{
	URP_RULE_PARA_ABANDUM_S stObjAbandumRulePara;     /**< ��Ʒ�������� */
	URP_RULE_PARA_OBJ_STOLEN_S stObjStolenRulePara;   /**< ��Ʒ�������� */
	URP_RULE_PARA_NO_PARKING_S stNoParkingRulePara;   /**< �Ƿ�ͣ������ */
} URP_STATIC_OBJ_DETECT_RULE_PARA_S;


/** �û�����Э�飨URP������ */
typedef struct impURP_RULE_PARA_S
{
	URP_OSC_RULE_PARA_S     stOscRulePara;  //��Ʒ�������
	URP_PERIMETER_RULE_PARA_S	stPerimeterRulePara;	          /**< �ܽ��� */
	URP_TRIPWIRE_RULE_PARA_S	stTripwireRulePara;		          /**< �����߼�� */
	URP_MTRIPWIRE_RULE_PARA_S	stMTripwireRulePara;		      /**< ����߼�� */
	URP_LOITER_RULE_PARA_S      stLoiterRulePara;                 /**< �ǻ���� */
	URP_STATIC_OBJ_DETECT_RULE_PARA_S stStaticObjDetectRulePara;  /**< ������ */
}URP_RULE_PARA_S;

/** ��������Ŀ */
#define IMP_URP_MAX_NUM_RULE_NUM 8

/** ���������ֳ��� */
#define IMP_URP_NAME_BUF_SIZE 16

/** URP������ */
typedef enum impURP_FUNC_PERIMETER_E
{
	IMP_URP_FUNC_ABANDUM        = 0x00000002,	/**< �������� */
	IMP_URP_FUNC_OBJSTOLEN      = 0x00000004,	/**< �������� */
	IMP_URP_FUNC_NOPARKING      = 0x00000008,	/**< �Ƿ�ͣ����� */
	IMP_URP_FUNC_PERIMETER		= 0x00000010,	/**< �ܽ��� */
	IMP_URP_FUNC_TRIPWIRE		= 0x00000020,	/**< �����߼�� */
	IMP_URP_FUNC_MTRIPWIRE      = 0x00000040,	/**< ����� */
	IMP_URP_FUNC_ABNMLVEL       = 0x00000080,	/**< �������ٶ� */
	IMP_URP_FUNC_LOITER         = 0x00000100,	/**< �ǻ� */
	IMP_URP_FUNC_OSC            = 0X00000200    //object status change
}URP_FUNC_PERIMETER_E;

/** URP����ṹ���� */
typedef struct impURP_RULE_S
{
	IMP_S8  aName[IMP_URP_NAME_BUF_SIZE];		/**< �������� */
	IMP_U32 u32Valid;				 	        /**< �Ƿ���Ч */
	IMP_U32 u32Enable;			  	            /**< �Ƿ�ʹ�� */
	IMP_U32 u32Level;					        /**< ���伶�� */
	IMP_U32 u32Mode;					        /**< ����ģʽ�����õĹ��ܶ�Ӧ�����밴λ��� */
	URP_RULE_PARA_S stPara;				        /**< ������� */
}URP_RULE_S;

/** URP���򼯺� */
typedef struct impURP_RULE_SET_S
{
	URP_RULE_S astRule[IMP_URP_MAX_NUM_RULE_NUM];			/**< ���򼯺� */
}URP_RULE_SET_S;

/** D1ͼ���� */
#define IMP_D1_IMG_WIDTH 704
/** CIFͼ���� */
#define IMP_CIF_IMG_WIDTH 352
/** QCIFͼ���� */
#define IMP_QCIF_IMG_WIDTH 176
/** PAL D1ͼ��߶� */
#define IMP_D1_PAL_IMG_HEIGHT 576
/** PAL CIFͼ��߶� */
#define IMP_CIF_PAL_IMG_HEIGHT 288
/** PAL QCIFͼ��߶� */
#define IMP_QCIF_PAL_IMG_HEIGHT 144
/** NTSC D1ͼ��߶� */
#define IMP_D1_NTSC_IMG_HEIGHT 480
/** NTSC CIFͼ��߶� */
#define IMP_CIF_NTSC_IMG_HEIGHT 240
/** NTSC QCIFͼ��߶� */
#define IMP_QCIF_NTSC_IMG_HEIGHT 120

typedef enum impVIDEO_STANDARD_E
{
    IMP_NTSC,				/**< NTSC��ʽ */
    IMP_PAL				    /**< PAL��ʽ */
}VIDEO_STANDARD_E;
/** URP���ò��� */
typedef struct impURP_CONFIG_PARA_S
{
	IMP_S32 s32Version;									/**< �汾�� */
	IMP_S32 s32ImgW;									/**< ��������ƵԴ�Ŀ�� */
	IMP_S32 s32ImgH;									/**< ��������ƵԴ�ĸ߶� */
	VIDEO_STANDARD_E eVideoStandard;					/**< ��������ƵԴ����ʽ */
}URP_CONFIG_PARA_S;


/** URPĿ����������ȼ��� */
typedef enum impSENSITIVITY_LEVEL_E
{
	IMP_HIGH_LEVEL_SENSITIVITY,         /**< �������� */
	IMP_MIDDLE_LEVEL_SENSITIVITY,		/**< �������� */
	IMP_LOW_LEVEL_SENSITIVITY			/**< �������� */
}SENSITIVITY_LEVEL_E;

/** URP�߼����� */
typedef struct impURP_ADVANCE_PARA_S
{
	IMP_S32   s32AdvanceParaEnable;				/**< �Ƿ����ø߼�����(0:�� 1:��) */
	IMP_S32   s32TargetMinSize;					/**< Ŀ����С���سߴ�(-1Ϊ��������) */
	IMP_S32   s32TargetMaxSize;					/**< Ŀ��������سߴ�(-1Ϊ��������) */
	IMP_S32   s32TargetMinWidth;				/**< Ŀ����С���ؿ��(-1Ϊ��������) */
	IMP_S32   s32TargetMaxWidth;				/**< Ŀ��������ؿ��(-1Ϊ��������) */
	IMP_S32   s32TargetMinHeight;				/**< Ŀ����С���ظ߶�(-1Ϊ��������) */
	IMP_S32   s32TargetMaxHeight;				/**< Ŀ��������ظ߶�(-1Ϊ��������) */
	IMP_S32   s32TargetMinSpeed;				/**< Ŀ����С�����ٶ�(-1Ϊ��������) */
	IMP_S32   s32TargetMaxSpeed;				/**< Ŀ����������ٶ�(-1Ϊ��������) */
	IMP_S32   s32TargetOutputSensitivityLevel;	/**< Ŀ����������ȼ���(�ߡ��С���) */
}URP_ADVANCE_PARA_S;



#define IMP_URP_MAX_NUM_FDEPTH_LINE 3
/** �����߽ṹ */
typedef struct impURP_FDZ_LINE_S
{
	LINE_S stRefLine;			/**< ��ֱ�߶�����(unit: pixel) */
	IMP_S32 s32RefLen;			/**< �߶γ���(unit: cm) */
} URP_FDZ_LINE_S;

/** �����߽ṹ */
typedef struct impURP_FDZ_LINES_S
{
	IMP_U32    u32NumUsed;			               /**< ������Ŀ ���ڵ���2 */
	URP_FDZ_LINE_S stLines[IMP_URP_MAX_NUM_FDEPTH_LINE];   /**< ������Ŀ */
} URP_FDZ_LINES_S;

/** ��������ṹ */
typedef struct impURP_FDEPTH_MEASURE_S
{
	URP_FDZ_LINES_S stFdzLines;		/**< �궨���� */
} URP_FDEPTH_MEASURE_S;
/** �궨���� */
typedef struct impURP_FDEPTH_S
{
	IMP_U32 u32Enable;					/**< ���ñ�ʶ*/
	URP_FDEPTH_MEASURE_S stMeasure;			/**< �궨����*/
}URP_FDEPTH_S;


/** �������� */
typedef struct impURP_ENVIRONMENT_S
{
	IMP_U32 u32Enable;					/**< ���ñ�ʶ*/
	IMP_S32 s32SceneType;				/**< �������� */
} URP_ENVIRONMENT_S;

/** URP���� */
typedef struct impURP_PARA_S
{
	URP_CONFIG_PARA_S stConfigPara;				/**< ���ò��� */
	URP_RULE_SET_S    stRuleSet;				/**< ������� */
	URP_FDEPTH_S	stFdepth;					/**< �궨���� */
	URP_ENVIRONMENT_S stEnvironment;            /**< �������� */
	URP_ADVANCE_PARA_S  stAdvancePara;			/**< �߼����� */
}URP_PARA_S;

#ifdef __cplusplus
}
#endif


#endif
/*@}*/

/*@}*/
