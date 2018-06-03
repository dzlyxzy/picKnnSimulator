// picKnnSimulator.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



typedef unsigned char BYTE;
typedef unsigned int WORD;
#define rowLen 25
#define colLen 5

    const WORD knnSample[rowLen][colLen]={
    {1,0x14,0x54,0x177,0x133},{1,0x65f,0x46,0x13c,0x133},{1,0x1a1b,0x85,0x16d,0xe6},{1,0x68e,0x64,0x12a,0xed},{1,0x630,0x91,0x10a,0xcd},{1,0x3e8,0x64,0x102,0xa7},{1,0x55c,0xc1,0x1a5,0x0c},{1,0x4c7,0x61,0x122,0x133},{1,0x4c7,0x7d,0x1078,0xc7},
    {2,0x289,0x18e,0x1a5,0xd9},{2,0x37b,0xfb,0x102,0xd9},{2,0x4c7,0x145,0x177,0x0e},{2,0x55c,0x199,0x13c,0x4a},{2,0x5ad,0x145,0x102,0x199},{2,0x462,0xd3,0x119,0x10a},{2,0x395,0xdf,0xed,0x12a},{2,0x3cb,0x10a,0xf4,0x177},
    {3,0x584,0xed,0x95,0x66},{3,0x75b,0xc1,0x95,0x66},{3,0x20dd,0x111,0xc7,0x64},{3,0x943,0x0c,0x95,0xac},{3,0x630,0x199,0x89,0xac},{3,0x630,0x0c,0x76,0xac},{3,0x8be,0x1078,0x44,0xe6},{3,0x8be,0x162,0xcd,0x119}
    };

    WORD fingerPrint[colLen];



    long long getDistance(const WORD *d1, const WORD *d2)
	{
/***************output test*************/
	   // printf("*d1= %x %x %x %x , *d2= %d %d %d %d , ",*(d1+1),*(d1+2),*(d1+3),*(d1+4),*(d2+1),*(d2+2),*(d2+3),*(d2+4));
/***************output test*************/
		long long sum = 0;
        int i=1;

		for(i;i<=colLen;i++)
		{
            sum += (long long)pow((float)(abs((int)(*(d1+i)-*(d2+i)))),2);
/***************output test*************/
  //      printf("cha= %d , ",(*(d1+i)-*(d2+i)));
  //      //printf("pow= %d , ",(long long)pow((*(d1+i)-*(d2+i)),2));
		//printf("pow= %f , ",pow(fabs((float)(*(d1+i)-*(d2+i))),2));
  //      printf("sum is %d , ",sum);
/***************output test*************/
		}
		return sum;
	}

	void getAllDistance(void)
	{
		long long distance;
		//WORD min=0xffff;
		long long min=0xffffffff;
		BYTE label=0;
        int i=0;
		for(i;i<rowLen;i++)
		{
			distance = getDistance(&knnSample[i][0],&fingerPrint[0]);
/***************output test*************/
            printf("MIN is %u  ",min );//此处不用%d，位数不够会输出-1
            printf("this knnSample is  ");
			for(int j=0;j<colLen;j++)
            {
                printf("%d ",knnSample[i][j]);
            }
            printf("the distance is %d \n",distance);
/***************output test*************/
			if(distance<min)
			{
				min = distance;
				fingerPrint[0] = knnSample[i][0];
			}
	//		mapIndexDistance[i] = distance;

		}
		printf("the label fingerPring[0] = %d \n",fingerPrint[0]);

	}


	WORD findMin(WORD *array)
	{
		WORD min=0xffff;
        int i=0;
		for(i;i<rowLen;i++)
		{
			if (array[i]<min)
				min = i;
		}
		return min;
	}

/***********************************************************/
	int main()
{
/***************output test*************/
//    printf("the sizeof int is %d \n",sizeof(int));
//    printf("the sizeof float is %d \n",sizeof(float));
//    printf("the sizeof long is %d \n",sizeof(long));
//    printf("the sizeof long long is %d \n",sizeof(long long));
//    printf("the sizeof double is %d \n",sizeof(double));
/***************output test*************/
    int i=0;
    BYTE anchorNodes=10;
    WORD *pfingerPrint=NULL;
	WORD *temp=NULL;


    while(1)
    {
        printf("please input the number of the Anchor Nodes: \n");
        scanf("%d",&anchorNodes);

		temp=(WORD *)malloc(anchorNodes*sizeof(WORD));

        pfingerPrint=(WORD *)malloc(anchorNodes*sizeof(WORD));

        if(pfingerPrint == NULL)
        {
            printf("Error,unable to allocate required memory \n");
        }
        else
        {

            printf("Memory allocated succeeded,please input the fingerPrint: \n");
            for(int i = 0;i<anchorNodes;i++)
            {
                scanf("%d",&pfingerPrint[i]);
            }
            printf("which Anchor did you chose?(please input the sequence number of the anchor nodes)\n");

            for(int i=0;i<anchorNodes;i++)
            {
                scanf("%d",&temp[i]);
                while(temp[i]<1 || temp[i]>colLen)
                {
                    printf("error input ,please re-input %dth fingerprint:\n",i);
                    scanf("%d",&temp[i]);
                }
                fingerPrint[temp[i]]=*(pfingerPrint+i);
                fingerPrint[temp[i]]=pfingerPrint[i];
            }
        }

        for(int i=0;i<anchorNodes;i++)
        {
            printf("the pfingerPrint[%d]=%d\n",i,pfingerPrint[i]);
        }
        for(int i=0;i<anchorNodes;i++)
        {
            printf("the *(pfingerPrint+%d)=%d\n",i,*(pfingerPrint+i));
        }
        for(int i=0;i<colLen;i++)
        {
            printf("the fingerPrint[%d]=%d\n",i,fingerPrint[i]);
        }

        printf("i=%d\n",i++);

        getAllDistance();

        printf("Enter to QUIT or OTHERS to continue \n ");
        char c;

        scanf("%c",&c);
        switch(c)
        {
        case 'q':
            return 0;
        default:
            continue;
        }

        free(pfingerPrint);
    }

    return 0;



}



//#include <stdio.h>
//#include <stdlib.h>
//
//
//typedef unsigned char BYTE;
//typedef unsigned int WORD;
//#define rowLen 25
//#define colLen 5
//
//    WORD knnSample[rowLen][colLen]={
//    {1,0x14,0x54,0x177,0x133},{1,0x65f,0x46,0x13c,0x133},{1,0x1a1b,0x85,0x16d,0xe6},{1,0x68e,0x64,0x12a,0xed},{1,0x630,0x91,0x10a,0xcd},{1,0x3e8,0x64,0x102,0xa7},{1,0x55c,0xc1,0x1a5,0x0c},{1,0x4c7,0x61,0x122,0x133},{1,0x4c7,0x7d,0x1078,0xc7},
//    {2,0x289,0x18e,0x1a5,0xd9},{2,0x37b,0xfb,0x102,0xd9},{2,0x4c7,0x145,0x177,0x0e},{2,0x55c,0x199,0x13c,0x4a},{2,0x5ad,0x145,0x102,0x199},{2,0x462,0xd3,0x119,0x10a},{2,0x395,0xdf,0xed,0x12a},{2,0x3cb,0x10a,0xf4,0x177},
//    {3,0x584,0xed,0x95,0x66},{3,0x75b,0xc1,0x95,0x66},{3,0x20dd,0x111,0xc7,0x64},{3,0x943,0x0c,0x95,0xac},{3,0x630,0x199,0x89,0xac},{3,0x630,0x0c,0x76,0xac},{3,0x8be,0x1078,0x44,0xe6},{3,0x8be,0x162,0xcd,0x119}
//    };
//
//    WORD fingerPrint[colLen];
//
//    long long getDistance(WORD *d1,WORD *d2)
//	{
///***************output test*************/
//	   // printf("*d1= %x %x %x %x , *d2= %d %d %d %d , ",*(d1+1),*(d1+2),*(d1+3),*(d1+4),*(d2+1),*(d2+2),*(d2+3),*(d2+4));
///***************output test*************/
//		long long sum = 0;
//
////        int i=1;
////		for(i;i<=colLen;i++)
////		{
////            sum += (long long)pow((*(d1+i)-*(d2+i)),2);
/////***************output test*************/
//////        printf("cha= %d , ",(*(d1+i)-*(d2+i)));
//////        printf("pow= %d , ",(long long)pow((*(d1+i)-*(d2+i)),2));
//////        printf("sum is %d , ",sum);
/////***************output test*************/
////		}
//
//		sum += (long long)pow(abs((*(d1+2)-*(d2+2))),2);
/////***************output test*************/
//        printf("cha= %d , ",abs(*(d1+2)-*(d2+2)));
//        printf("pow= %d , ",(long long)pow((abs(*(d1+2)-*(d2+2))),2));
//        printf("sum is %d , ",sum);
/////***************output test*************/
//		printf("\n");
//		return sum;
//	}
//	void getAllDistance(void)
//	{
//		long long distance;
//		//WORD min=0xffff;
//		long long min=0xffffffff;
//		BYTE label=0;
//        int i=0;
//		for(i;i<rowLen;i++)
//		{
//			distance = getDistance(&knnSample[i][0],&fingerPrint[0]);
/////***************output test*************/
////            printf("MIN is %x  ",min );
////            printf("this knnSample is  ");
////			for(int j=0;j<colLen;j++)
////            {
////                printf("%d ",knnSample[i][j]);
////            }
////            printf("the distance is %d \n",distance);
/////***************output test*************/
//			if(distance<min)
//			{
//				min = distance;
//				fingerPrint[0] = knnSample[i][0];
//			}
//	//		mapIndexDistance[i] = distance;
//
//		}
//		printf("the label fingerPring[0] = %d \n",fingerPrint[0]);
//
//	}
//
//
//	WORD findMin(WORD *array)
//	{
//		WORD min=0xffff;
//        int i=0;
//		for(i;i<rowLen;i++)
//		{
//			if (array[i]<min)
//				min = i;
//		}
//		return min;
//	}
//
///***********************************************************/
//	int main()
//{
///***************output test*************/
////    printf("the sizeof int is %d \n",sizeof(int));
////    printf("the sizeof float is %d \n",sizeof(float));
////    printf("the sizeof long is %d \n",sizeof(long));
////    printf("the sizeof long long is %d \n",sizeof(long long));
////    printf("the sizeof double is %d \n",sizeof(double));
///***************output test*************/
//    for(int i=0;i<rowLen;i++)
//    {
//        fingerPrint[2]=knnSample[i][2];
//        fingerPrint[2]=0x03cb;
//        printf("fingerPrint[2]=%d",fingerPrint[2]);
//
////        printf("please input the KNN testdata \n");
////        for(int i=0;i<colLen;i++)
////        {
////            scanf("%d",&fingerPrint[i]);
////        }
////        for(int i=0;i<colLen;i++)
////        {
////            printf("the fingerPrint fingerPrint[i]=%d\n",fingerPrint[i]);
////        }
//
//
////        printf("%d",i);
////        i++;
////        printf("Enter to QUIT or OTHERS to continue ");
////        char c;
////        scanf("%c",&c);
////        switch(c)
////        {
////        case 'q':
////            return 0;
////        default:
////            continue;
////        }
//        getAllDistance();
//
//    }
//    getchar();
//    //getAllDistance();
//    return 0;
//}
