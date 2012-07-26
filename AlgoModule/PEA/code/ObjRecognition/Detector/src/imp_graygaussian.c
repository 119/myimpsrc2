#include "time.h"
#include "stdlib.h"
#include "imp_graygaussian.h"
#include "math.h"
#include "time.h"
#include "sys/time.h"

struct timeval start,end;
typedef struct impGrayGaussian_S
{
	GA_HARDWARE_RS_S  *pstHwResource;
    PEA_RESULT_S *pstResult;
    IMP_OutputGrayGaussian_S *pstOutput; 
	IMP_S32 *pstCod;
	GRAY_IMAGE_S stSub1;
	GRAY_IMAGE_S stSub2;
	GRAY_IMAGE_S stSub1_dilate;
	GRAY_IMAGE_S stSub2_dilate;	
	IMP_S32	s32H;
	IMP_S32 s32W;
	IMP_S32 s32Alpha;       //模型学习率
	IMP_S32 s32w_Alpha;     //权重学习率
}IMP_GrayGaussian_S;

IMP_S32 IMP_GetMemSizeGrayGaussian(PEA_RESULT_S *pstResult)
{
	IMP_S32 width = pstResult->s32Width;
	IMP_S32 height = pstResult->s32Height;
	IMP_S32 size = sizeof(IMP_GrayGaussian_S)+6*height*width; 	
	return size;
}

IMP_MODULE_HANDLE IMP_CreateGrayGaussian(PEA_RESULT_S *pstResult, GA_HARDWARE_RS_S *pstHwResource) //创建内存
{
	IMP_MODULE_HANDLE hModule = NULL;
	IMP_GrayGaussian_S *pstModule;  
	pstModule = (IMP_GrayGaussian_S*)IMP_MMAlloc( &pstHwResource->stMemMgr, IMP_MEMBLK_TYPE_SLOW, sizeof(IMP_GrayGaussian_S));	
	pstModule->pstHwResource = pstHwResource; 
	pstModule->pstResult = pstResult; 
	IMP_OutputGrayGaussian_S *pstOutput =&pstResult->stOutPutGG;
	pstModule->pstOutput = pstOutput;
    IMP_S32	s32H=pstResult->s32Height;
	IMP_S32 s32W=pstResult->s32Width;
	pstModule->s32Alpha=51;  //初始化模型学习率
	pstModule->s32w_Alpha=13; //初始化权重学习率
   	IMP_S32 s32row;
   	IMP_S32 s32col;
	pstModule->pstCod = (IMP_S32 *) IMP_MMAlloc( &pstHwResource->stMemMgr,IMP_MEMBLK_TYPE_SLOW,s32H*s32W*4);
	IMP_GrayImageCreate( &pstModule->stSub1, s32W, s32H, &pstHwResource->stMemMgr );
	IMP_GrayImageCreate( &pstModule->stSub2, s32W, s32H, &pstHwResource->stMemMgr );
	IMP_GrayImageCreate( &pstModule->stSub1_dilate, s32W, s32H, &pstHwResource->stMemMgr );
	IMP_GrayImageCreate( &pstModule->stSub2_dilate, s32W, s32H, &pstHwResource->stMemMgr );	
	IMP_GrayImageCreate( &pstOutput->stBkg, s32W, s32H, &pstHwResource->stMemMgr );
    IMP_GrayImageCreate( &pstOutput->stFilter, s32W, s32H, &pstHwResource->stMemMgr );
	hModule = (IMP_MODULE_HANDLE)pstModule;
	return hModule;
}
IMP_VOID filter(IMP_GrayGaussian_S *pstModule);
IMP_VOID SCAN( IMP_U8 *src,IMP_U8 *dst, IMP_U16 width, IMP_U16 height);
IMP_VOID norm_of_weight( IMP_S32 *ps32w1, IMP_S32 *ps32w2);
IMP_VOID DilateImage ( IMP_U8 *src,IMP_U8 *dst, IMP_U16 width, IMP_U16 height);

IMP_S32 IMP_ProcessGrayGaussian(IMP_MODULE_HANDLE hModule)
{
	gettimeofday(&start,NULL);
	IMP_GrayGaussian_S *pstModule;	
	pstModule = (IMP_GrayGaussian_S*)hModule;
	IMP_S32 s32row; //所在行位置
	IMP_S32 s32col; //所在列位置
	IMP_U8 u8Scenceval;
    IMP_S32 s32H = pstModule->pstResult->s32Height;
	IMP_S32 s32W = pstModule->pstResult->s32Width;
	IMP_S32 s32Alpha = pstModule->s32Alpha;
   	IMP_S32 s32w_Alpha = pstModule->s32w_Alpha;
	IMP_S32 *ps32tempval = pstModule->pstCod;
	IMP_U8 *pu8Scence = pstModule->pstResult->stImgInGray.pu8Data;
	IMP_U8 *pu8Bkg = pstModule->pstOutput->stBkg.pu8Data;
	IMP_U8 *pu8Sub1 = pstModule->stSub1.pu8Data;
	IMP_U8 *pu8Sub2 = pstModule->stSub2.pu8Data;
	IMP_U8 *pu8Sub1_dilate = pstModule->stSub1_dilate.pu8Data;
	IMP_U8 *pu8Sub2_dilate = pstModule->stSub2_dilate.pu8Data;
	IMP_S32 s32d = pstModule->pstResult->u32FrmTimeCur;  //帧号
	if(s32d-2<=0)                                       //取第一帧信息
	{
	   for(s32row=s32H-1;s32row>=0;s32row--)
		   for(s32col=s32W-1;s32col>=0;s32col--)
		   {
			u8Scenceval = (pu8Scence+s32row*s32W)[s32col];
			(ps32tempval+s32row*s32W)[s32col]= (127<<24)|(127<<16)|(u8Scenceval<<8)|(u8Scenceval);  //初始化
		   }
    }
    else
	{
		IMP_S32 s32weight1 ;  //当前模型1权重
		IMP_S32 s32weight2 ;  //当前模型2权重
		IMP_S32 s32model1 ;
		IMP_S32 s32model2 ;
		IMP_S32 s32Distance_model1 ;
		IMP_S32 s32Distance_model2 ;
		IMP_S32 s32weight;       
		IMP_U8 u8tmp;
		IMP_S32 s32sumval;
		IMP_U8 *ptr_sub1 = pu8Sub1;
		IMP_U8 *ptr_sub2 = pu8Sub2;
		IMP_S32 s32n=s32H;
		for(s32row=s32H-1;s32row>=0;s32row--)
		{
			IMP_S32 *ptr_tmp = (IMP_S32*)(ps32tempval+s32row*s32W);
			IMP_U8 *ptr_scence = (IMP_U8*)(pu8Scence+s32row*s32W);
			IMP_U8 *ptr_sub1 = (IMP_U8*)(pu8Sub1+s32row*s32W);
			IMP_U8 *ptr_sub2 = (IMP_U8*)(pu8Sub2+s32row*s32W);
			IMP_U8 *ptr_sub1_dilate = (IMP_U8*)(pu8Sub1_dilate+s32row*s32W);
			IMP_U8 *ptr_sub2_dilate = (IMP_U8*)(pu8Sub2_dilate+s32row*s32W);
			for(s32col=s32W-1;s32col>=0;s32col--)
			{
				ptr_sub1_dilate[s32col]=0;
				ptr_sub2_dilate[s32col]=0;
				s32sumval = ptr_tmp[s32col];
				s32model1 = (s32sumval&0xFF00)>>8;
				s32model2 = s32sumval&0x00FF;
				s32Distance_model1 = abs(s32model1-ptr_scence[s32col]);
				s32Distance_model2 = abs(s32model2-ptr_scence[s32col]);
				if(s32Distance_model1-10<0)
					ptr_sub1[s32col] = 0;
				else
					ptr_sub1[s32col] = 255;					
				if(s32Distance_model2-10<0)
					ptr_sub2[s32col] = 0;
				else
					ptr_sub2[s32col] = 255;				
			}	
		}
		ipShowGrayImage(s32W, s32H,  pu8Sub1, "fish1");
		SCAN( pu8Sub1, pu8Sub1_dilate, s32W, s32H);
		SCAN( pu8Sub2, pu8Sub2_dilate, s32W, s32H);
		ipShowGrayImage(s32W, s32H,  pu8Sub1_dilate, "fish2");
		memset(pu8Sub1, 0, s32W*s32H);
		memset(pu8Sub2, 0, s32W*s32H);
		DilateImage ( pu8Sub1_dilate, pu8Sub1, s32W, s32H);
		ipShowGrayImage(s32W, s32H,  pu8Sub1, "fish3");
		DilateImage ( pu8Sub2_dilate, pu8Sub2, s32W, s32H);
		//DilateImage ( pu8Sub1, pu8Sub1_dilate, s32W, s32H);
		//DilateImage ( pu8Sub2, pu8Sub2_dilate, s32W, s32H);
		//ipShowGrayImage(s32W, s32H, pu8Sub1, "sub1");
		/*printf("\n hello sub1:\n");
		for( s32row = 170; s32row <173; s32row++)
		{
			for( s32col=168; s32col<171; s32col++)
				{					
					printf("%d %d ----",(pu8Sub1+s32row*s32W)[s32col],(pu8Sub1_dilate+s32row*s32W)[s32col]);
				}
		}	
		printf("\n hello sub2:\n");
		for( s32row = 170; s32row <173; s32row++)
		{
			for( s32col=168; s32col<171; s32col++)
				{					
					printf("%d %d ----",(pu8Sub2+s32row*s32W)[s32col],(pu8Sub2_dilate+s32row*s32W)[s32col]);
				}
		}
		*/		
		for( s32row = s32H-1; s32row >= 0; s32row--)
		{
			IMP_U8 *ptr_sub1= (IMP_U8*)(pu8Sub1+s32row*s32W);
			IMP_U8 *ptr_sub2= (IMP_U8*)(pu8Sub2+s32row*s32W);
			IMP_S32 *ptr_tmp = (IMP_S32*)(ps32tempval+s32row*s32W);
			IMP_U8 *ptr_scence = (IMP_U8*)(pu8Scence+s32row*s32W);
			IMP_U8 *ptr_bkg = (IMP_U8*)(pu8Bkg+s32row*s32W);
			for( s32col=s32W-1; s32col>=0; s32col--)
			{	
				s32sumval = ptr_tmp[s32col];
				s32weight1 = (s32sumval&0xFF000000)>>24;
				s32weight2 = (s32sumval&0x00FF0000)>>16;
				s32model1 = (s32sumval&0xFF00)>>8;
				s32model2 =  s32sumval&0x00FF;		
				if(ptr_sub1[s32col]==0)
				{
					s32weight1 = ((128-s32w_Alpha)*s32weight1+(s32w_Alpha<<7))>>7;
					//if(s32weight1-255<0)
						//s32weight1++;			
					s32model1 = ((s32model1<<7)+s32Alpha*(ptr_scence[s32col]-s32model1) +64 )>>7;
				}
				//s32weight2 = 255-s32weight1;
				if(ptr_sub2[s32col]==0)
				{
					s32weight2 = ((128-s32w_Alpha)*s32weight2+(s32w_Alpha<<7))>>7;
					//if(s32weight2-255<0)
						//s32weight2++;
					s32model2=((s32model2<<7)+s32Alpha*(ptr_scence[s32col]-s32model2) +64 )>>7;
				}
				norm_of_weight(&s32weight1,&s32weight2);
				if(s32weight2-s32weight1>0)
				{
					s32weight = s32weight2;
					s32weight2 = s32weight1;
					s32weight1 = s32weight;
					u8tmp = s32model2;
					s32model2 = s32model1;
					s32model1 = u8tmp;
				}
				if((ptr_sub1[s32col]&ptr_sub2[s32col])==255)
				{
					s32weight2 = s32w_Alpha;
					norm_of_weight(&s32weight1,&s32weight2);
					//if(s32weight2>0)
						//s32weight2-- ;
					s32model2 = ptr_scence[s32col];
				}
				//s32weight1 = 255-s32weight2;	
				(ps32tempval+s32row*s32W)[s32col] = (((IMP_U8)s32weight1)<<24)|(((IMP_U8)s32weight2)<<16)|(((IMP_U8)s32model1)<<8)|((IMP_U8)s32model2); 
				ptr_bkg[s32col] = (IMP_U8)s32model1;					
			}
		}
		ipShowGrayImage(s32W, s32H, pu8Bkg, "hellotrl1");
		filter(pstModule);
		ipShowGrayImage(s32W, s32H, pstModule->pstOutput->stFilter.pu8Data, "hellofilter");
		//char c;
		//if(c=='u')
			//impSaveImage(pstModule->pstOutput->stFilter.pu8Data, s32W, s32H, "hellotrl1.bmp");
		//ipMorphDilateImage( pstModule->stFilter.pu8Data, s32W, pstModule->stFilter2.pu8Data, s32W, s32W, s32H,u8str);
		gettimeofday(&end,NULL);
		IMP_S32 timeuse = end.tv_usec - start.tv_usec; 
		printf("time %d\n", timeuse);
	}
}


IMP_S32 IMP_ReleaseGrayGaussian(IMP_MODULE_HANDLE hModule)
{
	IMP_GrayGaussian_S *pstModule;	
	pstModule = (IMP_GrayGaussian_S*)hModule;
	GA_HARDWARE_RS_S *pstHwResource; 
	IMP_GrayImageDestroy( &pstModule->pstOutput->stFilter, &pstHwResource->stMemMgr );   //释放内存
	IMP_GrayImageDestroy( &pstModule->pstOutput->stBkg, &pstHwResource->stMemMgr );
	IMP_GrayImageDestroy( &pstModule->stSub2_dilate, &pstHwResource->stMemMgr );
	IMP_GrayImageDestroy( &pstModule->stSub1_dilate, &pstHwResource->stMemMgr );
	IMP_GrayImageDestroy( &pstModule->stSub2, &pstHwResource->stMemMgr );
	IMP_GrayImageDestroy( &pstModule->stSub1, &pstHwResource->stMemMgr );
	IMP_MMFree(&pstHwResource->stMemMgr, IMP_MEMBLK_TYPE_SLOW, pstModule->pstCod);
    IMP_MMFree(&pstHwResource->stMemMgr, IMP_MEMBLK_TYPE_SLOW, pstModule);
}

IMP_VOID filter(IMP_GrayGaussian_S *pstModule)
{
	IMP_S32 s32W = pstModule->pstResult->s32Width;
	IMP_S32 s32H = pstModule->pstResult->s32Height;
	IMP_U8 *pu8Scence=pstModule->pstResult->stImgInGray.pu8Data;
	IMP_S32 s32threshold = 0;
	s32threshold = pstModule->pstResult->s32Noise;
	s32threshold = ((s32threshold<<1)+s32threshold)>>1;
	IMP_U8 *pu8Bkg = pstModule->pstOutput->stBkg.pu8Data;
	IMP_U8 *pu8Filter = pstModule->pstOutput->stFilter.pu8Data;
	IMP_S32 s32row;
	IMP_S32 s32col;
	IMP_S32 s32Intensity_sub;
	for(s32row=s32H-1;s32row>=0;s32row--)
	{
		IMP_U8 *ptr_scence = (IMP_U8*)(pu8Scence+s32row*s32W);
		IMP_U8 *ptr_bkg = (IMP_U8*)(pu8Bkg+s32row*s32W);
		IMP_U8 *ptr_filter = (IMP_U8*)(pu8Filter+s32row*s32W);
		for(s32col=s32W-1;s32col>=0;s32col--)
		{	
			s32Intensity_sub =abs(ptr_scence[s32col]-ptr_bkg[s32col]);
			if(s32Intensity_sub-s32threshold<0)
				ptr_filter[s32col]=0;
			else 
				ptr_filter[s32col]=255;			
		}
	}
}

IMP_VOID SCAN( IMP_U8 *src,IMP_U8 *dst, IMP_U16 width, IMP_U16 height)
{
	IMP_S32 x, y, result1;
	IMP_S32 widthM1 = width - 1;
	IMP_S32 heightM1 = height - 1;
	IMP_U8 *ps1, *ps2;
	ps1 = src;	// skip one stride
	ps2 = dst;
	ps1 +=width;	// for each line
	ps2 +=width;
	for ( y = 1; y < heightM1; y++ )
	{
		ps1 ++ ;
		ps2 ++;								
		for ( x = 1; x < widthM1; x++)
		{
			result1 = 0;
			if((*ps1)==255)
			{
			    //printf("catch the fish!");
				result1 |= *(ps1 - (width-1));
				result1 |= *(ps1 - (width<<1));
				result1 |= *(ps1 - (width+1));
				result1 |= *(ps1 - 2);
				result1 |= *(ps1 + 2);
				result1 |= *(ps1 + (width-1));
				result1 |= *(ps1 + (width<<1));
				result1 |= *(ps1 + (width+1));
				if(result1==255)
				(*ps2) = 255;
			}
			ps1 ++ ;	
			ps2 ++ ;	
		}
		ps1 ++ ;
		ps2 ++ ;
	}
}

IMP_VOID norm_of_weight( IMP_S32 *ps32w1, IMP_S32 *ps32w2)
{
	IMP_S32 s32w_sum = *ps32w1 + *ps32w2;
	*ps32w1 = (*ps32w1<<7)/s32w_sum;
	*ps32w2 = 128 - *ps32w1;
}

IMP_VOID DilateImage ( IMP_U8 *src,IMP_U8 *dst, IMP_U16 width, IMP_U16 height)
{
	IMP_S32 x, y, result ;

	IMP_S32 widthM1 = width - 1;
	IMP_S32 heightM1 = height - 1;
	IMP_U8 *ps1,*ps2;
	ps1 = src;	// skip one stride
	ps2 = dst;
	ps1 +=width;	// for each line
	ps2 +=width;
	for ( y = 1; y < heightM1; y++ )
	{
		ps1 ++ ;
		ps2 ++ ;								
		for ( x = 1; x < widthM1; x++)
		{
			result = 0;
			result |= *(ps1 - (width-1));
			result |= *(ps1 - width);
			result |= *(ps1 - (width+1));
			result |= *(ps1 - 1);
			result |= *(ps1);
			result |= *(ps1 + 1);
			result |= *(ps1 + (width-1));
			result |= *(ps1 + width);
			result |= *(ps1 + (width+1));
			(*ps2) = (result !=0? 255 : 0);			
			ps1 ++ ;
			ps2 ++ ;	
		}
		ps1 ++ ;
		ps2 ++ ;
	}
}


