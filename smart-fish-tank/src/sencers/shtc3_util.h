#include <Wire.h>
#include <SparkFun_SHTC3.h>
#include <SmartFishTankConfig.h>

struct SHTC3VAL
{
    /* data */
    float RH;
    float T;
};

static int shtc3_sencer_inited = 0;
SHTC3 mySHTC3;
SHTC3VAL lastShtc3Val;



/**
 * 读取shtc3传感器
*/
SHTC3VAL read_shtc3();

/**
 * shtc3错误消息处理
*/
void shtc3ErrorDecoder(SHTC3_Status_TypeDef message);