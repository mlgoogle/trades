//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年1月12日 Author: kerry

#ifndef PUB_HISTORY_SHFJ_ORDER_H_
#define PUB_HISTORY_SHFJ_ORDER_H_

#include <string>
#include "logic/base_values.h"
#include "http/http_method.h"

const std::string T_MCH_ID = "MNYH54001EBOM"; //商户号
const std::string T_APP_KEY = "2017042116284843001"; //证书编号
const std::string T_MD5_KEY = "RPOUDPWHNMJETKCJADHFYQBEMJRVDVHP"; //证书编号

const std::string THIRD_URL = "https://gw.xzlpay.com/native/";
const std::string THIRD_CASH_URL = "https://gw.xzlpay.com/native/";

/*
 */
namespace history_logic {

class SHFJOrder {
 public:
  SHFJOrder();
  virtual ~SHFJOrder();

  inline void set_out_trade_no(std::string oid) {
    out_trade_no = oid;
  }
  inline void set_spbill_create_ip(std::string ip) {
    spbill_create_ip = ip;
  }

  std::string PlaceOrder(const std::string& id, 
  		const std::string& pay_type, const std::string &content);
  std::string TradeQry(std::string& id); //充值记录查询
//---------------------------------------------------------------------------------
/*
*/
 private:
  std::string QryPostFiled(std::string &date);

  void InitWxVerify();

  void Set_Headers(http::HttpMethodPost &hmp);
  void PlaceOrderSign(const std::string &body,const std::string &req_url, bool iscash = false);
 private:
  //用户端实际ip
  std::string spbill_create_ip;
  //支付类型 固定 为 APP //类型 0 app  1.微信公众号
 // std::string key;

//充值----------------------------------------------------------------------------------------------------------------
  //商户系统内部的订单号,32个字符内、可包含字母
  std::string out_trade_no;
  
  std::string mch_id; //merchantNo//支付分配的商户号
  //签名，详见函数说明
  std::string sign;
};
///
extern int32 GetSHFJCashStatus(const std::string &status);
}

#endif  // PUB_PAY_WXPAY_WX_ORDER_H_
