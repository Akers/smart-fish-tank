#ifndef __SFT_SHTC3_UTIL
#define __SFT_SHTC3_UTIL
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

SHTC3VAL read_shtc3() {
  if (shtc3_sencer_inited != 1) {
    #ifdef SHTC3_I2C_SDA_PIN
    Wire.begin(SHTC3_I2C_SDA_PIN, SHTC3_I2C_SCL_PIN);
    #else
    Wire.begin();
    #endif
    shtc3_sencer_inited = 1;
  }
  SHTC3_Status_TypeDef result = mySHTC3.update();
  if(mySHTC3.lastStatus == SHTC3_Status_Nominal) {
    //判断SHTC3状态是否正常
    lastShtc3Val.RH = mySHTC3.toPercent();   //读取湿度数据
    lastShtc3Val.T = mySHTC3.toDegC();       //读取温度数据
    return lastShtc3Val;
  } else {
    Serial.print("Update failed, error: ");
    shtc3ErrorDecoder(mySHTC3.lastStatus); //输出错误原因
    Serial.println();
  }
  lastShtc3Val.RH = -99;
  lastShtc3Val.T = -99;
  return lastShtc3Val;
}

void shtc3ErrorDecoder(SHTC3_Status_TypeDef message) // The errorDecoder function prints "SHTC3_Status_TypeDef" resultsin a human-friendly way
{
  switch(message) {
    case SHTC3_Status_Nominal : Serial.print("Nominal"); break;
    case SHTC3_Status_Error : Serial.print("Error"); break;
    case SHTC3_Status_CRC_Fail : Serial.print("CRC Fail"); break;
    default : Serial.print("Unknown return code"); break;
  }
}

#endif