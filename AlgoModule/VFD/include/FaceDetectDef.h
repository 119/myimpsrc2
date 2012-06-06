/*****************************************************************************/
/** @file ����ṹ��������
 * 
 * @date	2008/07/22 
 * Copyright (C) 2004 WISEBIRD CO.,  All rights reserved.      
******************************************************************************/

#ifndef IFACE_FACEDETECT_H
#define IFACE_FACEDETECT_H

typedef struct {
	long rightEyeX;			/* ���۵ı�׼λ��X */
							/* Standard position of right eye's X-axis */ 
	long rightEyeY;			/* ���۵ı�׼λ��Y */
							/* Standard position of right eye's Y-axis */ 
	long leftEyeX;			/* ���۵ı�׼λ��X */
							/* Standard position of left eye's X-axis */ 
	long leftEyeY;			/* ���۵ı�׼λ��Y */
							/* Standard position of left eye's Y-axis */ 
	long centerX;			/* ��׼������λ��X */
							/* Standard center position of face's X-axis */ 
	long centerY;			/* ��׼������λ��Y */
							/* Standard center position of face's Y-axis */ 
    long faceSize;			/* ��׼����С�����ε�һ���߳��� */
							/* Standard size of face(one side's length of rectangle) */
	short angleInPlane;		/* inplane����ת�Ƕ� */
							/* angle of inplane */
	short angleOutPlane;	/* outplane����ת�Ƕ� */
							/* angle of outplane */
	long faceScore;         /* ���÷� */
							/* face score */
	long serialNumber;		/* ���к� */
							/* serial number */
	long shapeScore;		/* ��״�÷� */
							/* shape score */
} FACEINFO;

/* Inplane����ģʽ */
/* Inplane search mode */
typedef enum {
     Search_Inplane_All = -1,    /* ���з��� */
								 /* All Direction */
     Search_Inplane_000 = 0,     /* ֻ��0�ȷ��� */
								 /* 0�� only */
     Search_Inplane_090 = 90,    /* ֻ��90�ȷ��� */
								 /* 90�� only */
     Search_Inplane_180 = 180,   /* ֻ��180�ȷ��� */
								 /* 180�� only */
     Search_Inplane_270 = 270    /* ֻ��270�ȷ��� */
								 /* 9270�� only */
} SearchInplaneMode;


/* Outplane����ģʽ */
/* Outplane search mode */
typedef enum {
     FRONT = 1,                 /* ���� */
								/* Front */
     PROFILE = 2,               /* ���� */
								/* Profile */
     HALFPROFILE = 4,           /* ����� */
								/* Half Profile */
     SEARCH_OUTPLANE_ALL = -1   /* ���з��� */
								/* All Direction */
} SearchOutplaneMode;

/* LockRotation90ģʽ */
/* LockRotation90 mode */
typedef enum {
     LOCK_ROT90_ON = 1,         /* ���� */
								/* lock */
     LOCK_ROT90_OFF = 0         /* ������ */
								/* no lock */
} LockRotation90Mode;


/* LockSearchLargeģʽ */
/* LockSearchLarge mode */
typedef enum {
     LOCK_LARGE_ON = 1,         /* ���� */
								/* lock */
     LOCK_LARGE_OFF = 0         /* ������ */
								/* no lock */
} LockSearchLarge;


/* Searchģʽ */
/* Search mode */
typedef enum {
     MODE_NORMAL = 0,       /* ͨ��ģʽ */
							/* Normal */
     MODE_TP = 1,           /* TP���� */
							/* TP High Priority */
     MODE_SPEED = -1        /* �ٶ����� */
							/* Speed Mode */
} SearchMode;

/** ������
 *  Error ID of library
 */
typedef enum {
	/** iFACE library common*/

    IFACE_ERR_SUCCESS_ID                    = 0,        /**< ����ɹ�   */
		                                                /**< Processing success */
    IFACE_ERR_WRONG_SEQUENCE                = 1,        /**< ����˳����� */
                                                        /**< Calling sequence wrong */
    IFACE_ERR_INVALID_PARAM                 = 2,        /**< �Ƿ����� */
	                                                    /**< Injustice of argument */
    IFACE_ERR_NO_ENOUGH_MEMORY              = 3,        /**< �ڴ治�� */
                                                        /**< Memory shortage */
    IFACE_ERR_NO_FACE_FOUND                 = 4,		/**< ͼ����û�з������� */
	                                                    /**< The face was not able to be discovered in the image */
	IFACE_ERR_NO_FACE_CROP                  = 5,		/**< �����г�ͼ�������� */
	                                                    /**< Face could not be cropped in the image */ 
    IFACE_ERR_FILE_OPEN                     = 6,        /**< �ļ��򿪴��� */
	                                                    /**< File opening error */ 
    IFACE_ERR_FILE_READ                     = 7,        /**< ���ļ����� */
														/**< File reading error */
	IFACE_ERR_TOO_MANY_CANDIDATES           = 8			/**< ̫��ĺ�ѡ������ */
														/**< Too many candidates error */

} IFACE_ERROR_ID;

#define	SEARCH_INPLANE_ALL  Search_Inplane_All 
#define	SEARCH_INPLANE_000  Search_Inplane_000	
#define SEARCH_INPLANE_090  Search_Inplane_090
#define SEARCH_INPLANE_180  Search_Inplane_180
#define SEARCH_INPLANE_270  Search_Inplane_270
typedef unsigned char ubyte;

typedef void* FaceRecognitionHandle;
typedef unsigned long   IFACE_ERROR_CODE;

#define MAXINT	0x7fffff00
#define PI		3.1415926535f		/* Բ���� */
									/* pi     */

//<<<--- 2009-12-28 �޸�Ϊshort
/*! Header of structure array */
//typedef struct {
//    long flag;
//} CandidateHeader;
//
///*! Structure array */
//typedef struct {
//    void* pTop;
//    long unitLength;
//    long maxNumber;
//    long number;
//} CandidatesList;

typedef struct {
	short flag;
} CandidateHeader;

/*! Structure array */
typedef struct {
	void* pTop;
	short unitLength;
	short maxNumber;
	short number;
} CandidatesList;
//--->>>

/* ==== ����С ==== */
#define FACE_DETECT_UNIT    32
#define FEATURE_DETECT_UNIT 24

/* ==== ����/����/���۵�ʶ���� ==== */
#define EYE_RIGHT 0
#define EYE_LEFT  1

#ifndef __T_FACECANDIDATESNEW__
#define __T_FACECANDIDATESNEW__
/* ��ѡ����Ϣ */
//<<<--- 2009-12-28 �޸�Ϊshort
//typedef struct {
//	CandidateHeader header;
//    long centerHeight;            /* ������λ���ε����ĵ�Y���꣨FXP_UNIT_POS�ı�ֵ�� */
//    long centerWidth;             /* ������λ���ε����ĵ�X���꣨FXP_UNIT_POS�ı�ֵ�� */
//    long aCanonicalEyeHeight[2];  /* �涨���۾���Y���꣨FXP_UNIT_POS�ı�ֵ�� */
//    long aCanonicalEyeWidth[2];   /* �涨���۾���X���꣨FXP_UNIT_POS�ı�ֵ�� */
//    short angle;                  /* ���ʱ�ĽǶ� */
//    short angleOutPlane;
//	short direction;
//    short scale;                  /* ���ʱʹ�õı�����FXP_UNIT_SCALE�ı�ֵ�� */
//    long score;                  /* ���ʱ�ĵ÷� */
//    long scoreNeighbor;
//    long score2;
//    long score2Neighbor;
//} FaceCandidatesNew;

typedef struct {
	CandidateHeader header;
	short centerHeight;            /* ������λ���ε����ĵ�Y���꣨FXP_UNIT_POS�ı�ֵ�� */
	short centerWidth;             /* ������λ���ε����ĵ�X���꣨FXP_UNIT_POS�ı�ֵ�� */
	short aCanonicalEyeHeight[2];  /* �涨���۾���Y���꣨FXP_UNIT_POS�ı�ֵ�� */
	short aCanonicalEyeWidth[2];   /* �涨���۾���X���꣨FXP_UNIT_POS�ı�ֵ�� */
	short angle;                  /* ���ʱ�ĽǶ� */
	short angleOutPlane;
	short direction;
	short scale;                  /* ���ʱʹ�õı�����FXP_UNIT_SCALE�ı�ֵ�� */
	short score;                  /* ���ʱ�ĵ÷� */
	short scoreNeighbor;
	short score2;
	short score2Neighbor;
} FaceCandidatesNew;

//--->>>

#endif

#ifndef __T_IJINDEXNEW__
#define __T_IJINDEXNEW__
/* ������������Ϣ */

typedef struct {
	short x;
	short y;
	short score;
	short score2;
	short type;
} IJIndexNew;
#endif

#ifndef __T_IJINDEXNEWLIST__
#define __T_IJINDEXNEWLIST__
/* �����������б� */

//<<<--- 2009-12-28 �޸�Ϊshort
//typedef struct {
//    IJIndexNew* list;
//    long length;
//    long lengthMax;
//} IJIndexNewList;

typedef struct {
	IJIndexNew* list;
	short length;
	long lengthMax;
} IJIndexNewList;
//--->>>
#endif

#ifndef __T_DETECTPARAM__
#define __T_DETECTPARAM__
typedef struct {
	short faceSize;			/* �������ҷ�������С�������С */
	/* The least size of detected face for up-down-left-right four direction */
	short faceSize30;		/* ����30�ȷ������С�������С */
	/* The least size of detected face for vertical 30 grade direction */
	short inPlane;			/* ������ƽ������ת */
	/* Search for in plane rotation  */
	short outPlane;			/* ������ƽ��Ĵ�ֱ������ת */
	/* Search for out plane rotation */
	short lockRotate90;		/* �ҵ���ʱ���·���Ĺ̶���� */
	/* Direction fixed flag when a face is found */
	short lockLarge;		/* �ҵ���ʱС�ߴ����Ƿ������ı�־ */
	/* Smaller face detect flag when a face is found. */
	short detectMode;		/* ��������ȷ�ʽ */
	/* Priority mode for face detect */
	short faceDetectThreshold;/* ��������õķ�ֵ���� */
	/* Threshold for face detect score */
	short faceCropThreshold;/* �г����ķ�ֵ���� */
	/* Threshold for face crop score */
} DetectParam;
#endif

#endif /* IFACE_FACEDETECT_H */
