/*
*********************************************************************************************************
*                                              HT6XXXX
*                                           Library Function
*
*                                   Copyright 2013, Hi-Trend Tech, Corp.
*                                        All Rights Reserved
*
*
* Project      : HT6xxx
* File         : ht501x_keyscan.c
* By           : Hitrendtech_SocTeam
* Version      : V1.0.1
* Description  : Only support HT501x and HT502x
*********************************************************************************************************
*/

#define  __HT511X_KEYSCAN_C

#include "ht501x_keyscan.h"

#if defined  HT501x  ||  defined  HT502x                    /* This File Only support HT501x and HT502x */

/*
*********************************************************************************************************
*                                           本地宏/结构体
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                             本地变量
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           本地函数申明
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                   GET KEY SCAN STATUS
*
* 函数说明: 获取KEY扫描状态
*
* 入口参数: 无
*
* 返回参数: KEYSTA   ：按键扫描状态
*
* 特殊说明: 无
*********************************************************************************************************
*/
uint32_t HT_KEY_ScanStatusGet()
{
    /*  assert_param  */

    return (HT_KEY->KEYSTA);
}

/*
*********************************************************************************************************
*                                   CLEAR KEY SCAN STATUS
*
* 函数说明: 清除KEY扫描状态
*
* 入口参数: 无
*
* 返回参数: 无
*
* 特殊说明: 无
*********************************************************************************************************
*/
void HT_KEY_ClearScanStatus()
{
    /*  assert_param  */

    HT_KEY->KEYSTA = 0;
}



/*
*********************************************************************************************************
*                            GET SPECIFIED KEY INTERRUPT FLAG STATUS
*
* 函数说明: 获取相应KEY中断标志状态
*
* 入口参数: ITFlag     想要检查的某个KEY扫描中断，可以为以下参数:
                       @arg KEY_KEYIF
*
* 返回参数: ITStatus    = SET：  相应中断标志产生
*                       = RESET：相应中断标志未产生
*
* 特殊说明: 无
*********************************************************************************************************
*/
ITStatus HT_KEY_ITFlagStatusGet(uint8_t ITFlag)
{
    /*  assert_param  */

    if (HT_KEY->KEYIF & ITFlag)
    {
        return SET;                                  /*!< Interrupt Flag is set      */
    }
    else
    {
        return RESET;                                /*!< Interrupt Flag is reset    */
    }
}

/*
*********************************************************************************************************
*                                   CLEAR KEY SCAN INTERRUPT FLAG
*
* 函数说明: 清除KEY扫描中断标志
*
* 入口参数: ITFlag     想要清除的某个KEY中断标志，可以为以下参数或其组合:
*                        @arg KEY_KEYIF
*
* 返回参数: 无
*
* 特殊说明: 无
*********************************************************************************************************
*/
void HT_KEY_ClearITPendingBit(uint8_t ITFlag)
{
    /*  assert_param  */


    HT_KEY->KEYIF  &= ~((uint32_t)ITFlag);           /*!< Clear  Interrupt Flag       */

}

#endif                                               /* This File Only support HT501x */
