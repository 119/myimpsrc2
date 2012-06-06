/**
* \defgroup VFD
* IMPOWER VFD����㷨
* @author �������ټ���
* @version 1.0
* @data 2009-1010
*/
/*@{*/

#ifndef _IMP_VFD_TYPE_H
#define _IMP_VFD_TYPE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "imp_vfd_matrix.h"

/** smallest such that 1.0+DBL_EPSILON != 1.0 */
#define IMP_DBL_EPSILON     2.2204460492503131e-016 
/** min & max without jumps */
#define  IMP_IMIN(a, b)  ((a) ^ (((a)^(b)) & (((a) < (b)) - 1)))

#define  IMP_IMAX(a, b)  ((a) ^ (((a)^(b)) & (((a) > (b)) - 1)))

/** these settings affect the quality of detection: change with care */
#define IMP_ADJUST_FEATURES 1
#define IMP_ADJUST_WEIGHTS  0

#define IMP_HAAR_MAGIC_VAL    0x42500000
#define IMP_TYPE_NAME_HAAR    "haar-classifier"

#define IMP_IS_HAAR_CLASSIFIER( haar )                                                    \
    ((haar) != NULL &&                                                                   \
(((const IMP_HaarClassifierCascade*)(haar))->flags & IMP_MAGIC_MASK)==IMP_HAAR_MAGIC_VAL)

#define IMP_HAAR_FEATURE_MAX  3



typedef int sumtype;
typedef double sqsumtype;

/** ��haar����*/
typedef struct IMP_HidHaarFeature
{
	/** rect�������� */
    struct
    {
        sumtype *p0, *p1, *p2, *p3;
        float weight;
    }rect[IMP_HAAR_FEATURE_MAX];  
}
IMP_HidHaarFeature;

/** ��haar���ڵ� */
typedef struct IMP_HidHaarTreeNode
{
    IMP_HidHaarFeature feature;   /**< ���� */
    float threshold;              /**< ��ֵ */
    int left;                     /**< ��ڵ� */
    int right;                    /**< �ҽڵ� */
}IMP_HidHaarTreeNode;

/** ��haar������ */
typedef struct IMP_HidHaarClassifier
{
    int count;                    /**< ��Ŀ */
    IMP_HidHaarTreeNode* node;    /**< �ڵ� */
    float* alpha;                 /**< ϵ�� */
}IMP_HidHaarClassifier;

/** ��haar stage������ */
typedef struct IMP_HidHaarStageClassifier
{
    int  count;                                /**< ��Ŀ */
    float threshold;                           /**< ��ֵ */         
    IMP_HidHaarClassifier* classifier;         /**< �������� */
    int two_rects;                             /**< rect */
    
    struct IMP_HidHaarStageClassifier* next;   /**< ��һ���ڵ� */
    struct IMP_HidHaarStageClassifier* child;  /**< �ӽڵ� */
    struct IMP_HidHaarStageClassifier* parent; /**< ���ڵ� */
}IMP_HidHaarStageClassifier;

/** ��haar���������� */
struct IMP_HidHaarClassifierCascade
{
    int  count;                                  /**< ��Ŀ */
    int  is_stump_based;                         /**< ���ձ�� */
    int  has_tilted_features;                    /**< ����ת����ͼ���� */
    int  is_tree;                                /**< ����� */
    double inv_window_area;                      /**< �������� */
    IMP_Mat sum, sqsum, tilted;                  /**< ����ͼ��ƽ������ͼ����ת����ͼ */
    IMP_HidHaarStageClassifier* stage_classifier;/**< ������ */
    sqsumtype *pq0, *pq1, *pq2, *pq3;            /**< ƽ������ͼָ�� */
    sumtype *p0, *p1, *p2, *p3;                  /**< ����ͼָ�� */
	
    void** ipp_stages;                           /**< stagesָ�� */
};


/** haar���������� */
typedef struct IMP_HaarFeature
{
    int  tilted;                     /**< ��ת */
	/** rect */
    struct
    {
        Imp_Rect r;
        float weight;
    } rect[IMP_HAAR_FEATURE_MAX];
}IMP_HaarFeature;

/** haar������ */
typedef struct IMP_HaarClassifier
{
    int count;                      /**< ��Ŀ */
    IMP_HaarFeature* haar_feature;  /**< ���� */  
    float* threshold;               /**< ��ֵ */  
    int* left;                      /**< ��ڵ� */  
    int* right;                     /**< �ҽڵ� */  
    float* alpha;                   /**< ϵ�� */  
}IMP_HaarClassifier;

/** stage haar������ */
typedef struct IMP_HaarStageClassifier
{
    int  count;                     /**< ��Ŀ */
    float threshold;                /**< ��ֵ */  
    IMP_HaarClassifier* classifier; /**< ������ */  
	
    int next;                       /**< ��һ���ڵ���Ŀ */
    int child;                      /**< �ӽڵ���Ŀ */
    int parent;                     /**< ���ڵ���Ŀ */
}IMP_HaarStageClassifier;

typedef struct IMP_HidHaarClassifierCascade IMP_HidHaarClassifierCascade;

/** haar���������� */
typedef struct IMP_HaarClassifierCascade
{
    int  flags;                                /**< ��� */
    int  count;                                /**< ��Ŀ */
    Imp_Size orig_window_size;                 /**< ԭʼ���ߴ� */
    Imp_Size real_window_size;                 /**< ʵ�ʴ��ߴ� */
    double scale;                              /**< ����ϵ�� */
    IMP_HaarStageClassifier* stage_classifier; /**< stage���� */
    IMP_HidHaarClassifierCascade* hid_cascade; /**< ������������ */
}IMP_HaarClassifierCascade;

typedef struct IMP_AvgComp
{
    Imp_Rect rect; /**< bounding rectangle for the object (average rectangle of a group) */
    int neighbors; /**< number of neighbor rectangles in the group */
}IMP_AvgComp;

#ifdef __cplusplus
}
#endif

#endif /*_IMP_VFD_TYPE_H*/
/*@}*/