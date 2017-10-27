#include "TypeE2p.h"
#include "TypeRAM.h"
#include "ht6xxx_lib.h"
#include "DLT698.h"					
#include "Measure.h"
#include "Port.h"
#include "TypeFlash.h"
#include "Data.h"
#include "General.h"
#include "Mem.h"

#include "RsComm.h"
#include "interrupt.h"
#include "Mem.h"
#include "Time.h"
#include "Power.h"
#if ( MEASCHIP == ADE7878 )	
#include "AD7878.h"
#endif
#include "Initial.h"
//#include "Produce.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char ActionFileTransferClassData( unsigned short COM_No, unsigned char* Dest, unsigned char* Source, unsigned short DataLen, unsigned short* ItemLen, unsigned short* BackLen ) 
{
	unsigned char ErrorByte=0;

	RAM_Write( Dest, Source, 4 );

	ErrorByte = ActionFileTransferClassDataTab( COM_No, Dest+4, Source, DataLen, ItemLen, BackLen  );
	return ErrorByte;		

}	

unsigned char ActionFileTransferClassDataTab( unsigned short COM_No, unsigned char* Dest, unsigned char* Source, unsigned short DataLen, unsigned short* ItemLen, unsigned short* BackLen ) 
{
	unsigned char Buff[4];
//	short i,j;
//	unsigned char* Addr;
	unsigned char ErrorByte=object_class_inconsistent;
//	short Len;
//	unsigned short OICode;
//	short Temp;
//	unsigned short GetLen;
//	short Start,End;
//	unsigned char Attribute;
//	unsigned char Feature;
//	unsigned char Index;
//	unsigned char DataType;
//	unsigned char Element_Len;			
	unsigned char* Ptr;
	unsigned char* OMD;
//	unsigned char* WriteBufAds;
	unsigned char Method;
//	Len = -1;
	unsigned short* ComBTime;

	OMD = Source;
//	WriteBufAds = Source+4;
//	OICode = SwapCharToShort( OMD );
	Method = *(OMD+2);
	ComBTime = CommPara[COM_No].BTime;
	Ptr = Buff;
	
	switch( Method )
	{
		case 10:										//�����ȶ�
			if( Judge_operating_authority( COM_No, OMD, 0x8220, active_authority ) != 0 ) return read_write_denied;	
			
			
			break;
		default:
			break;	
	}	
	return ErrorByte;
}




//��ȡ����ȶ�����
//Source:�ӽṹ��ʼ�������ṹ�ַ�����
unsigned short GetProgramCompareData( unsigned char* Dest, unsigned char* Source )				//�¹���
{
	unsigned long FactorAddr;
	unsigned long DataAddr;
	unsigned char KeyIndex;
	unsigned char Buff[256];
	unsigned char Buff2[16];
	unsigned char* Ptr;
	unsigned char* Point;
  	unsigned short Err_Byte=0;
	unsignedshort Length;
	unsigned short DataLen;
	short i;
		
	Ptr = Buff;
	Point = Buff2;
	
	if( *(Source+3) != 0 ) 
	{
		Err_Byte = 0x01;
		return Err_Byte;				//����CPU���
	}
	
	KeyIndex = *(Source+5);
	FactorAddr = SwapCharToLong( Source+7 );
	DataAddr = SwapCharToLong( Source+12 );
	DataLen = SwapCharToShort( Source+17 );
	
	if(( FactorAddr >= 0x40000 )||( DataAddr >= 0x40000 ))		//��ʼ����HT602X��Χ	
	{
		Err_Byte = 0x80;				//��ַ����	
		return Err_Byte;				
	}

	RAM_Fill( Point, 16);
	if( (FactorAddr+16) > 0x40000 )		
	{
		Length = 0x40000 - 	FactorAddr;	
		*(Point+Length) = 0x80;										//���㲿�ֵ�һ�ֽڲ�x80,���00	
	}
	else Length = 16;
	
	RAM_Write( Point, (unsigned char*)FactorAddr, Length );
	
//	for( i=0;i<8;i++ )
//	{
//		*(Point+i) ^= *(Point+8+i);									//�ȶ�����
//	}	
//	if( DisperseAuthenticationCardNo( KeyIndex, Point ) != 0 )		//��ȡ�ȶ���Կ
//	{
//		Err_Byte = 0x01;				//��������
//		return Err_Byte;				
//	}	
	
	RAM_Fill( Ptr, 256);
	if( (DataAddr+256) > 0x40000 )		
	{
		Length = 0x40000 - 	DataAddr;	
		*(Ptr+Length) = 0x80;										//���㲿�ֵ�һ�ֽڲ�x80,���00	
	}
	else Length = 256;
	
	RAM_Write( Ptr, (unsigned char*)DataAddr, Length );

//	for( i=0;i<64;i++ )
//	{
//		*(Ptr+i) ^= *(Ptr+64+i);									//����	
//		*(Ptr+i) ^= *(Ptr+128+i);									
//		*(Ptr+i) ^= *(Ptr+192+i);		
//	}	
//	
//	if( CompareEncrypt( Dest+2, Ptr, 64 ) != 0 )
//	{
//		Err_Byte = 0x01;				//��������
//		return Err_Byte;					
//	}	
//	SwapData( Dest+2, 64 );				//����

	*Dest = D_OctetStr;
	*(Dest+1) = 64;
	
	return Err_Byte;
}	















	
	
	
	
	
	