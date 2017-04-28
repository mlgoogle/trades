//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年1月12日 Author: kerry

#ifndef PUB_PAY_THIRD_ORDER_H_
#define PUB_PAY_THIRD_ORDER_H_

#include <string>
#include "logic/base_values.h"
#include "http/http_method.h"


const std::string T_APPID = "th9dc39aec13ee3158";
const std::string T_MCH_ID = "MNYH54001EBOM"; //商户号

//const std::string T_MPID = "the9f0932fb23e8f8a";

const std::string T_APP_KEY = "2017042116284843001"; //证书编号
const std::string T_MD5_KEY = "RPOUDPWHNMJETKCJADHFYQBEMJRVDVHP"; //证书编号

const std::string T_APP_TRADE_TYPE = "APP";

//const std::string THIRD_URL = "https://gw.uqiantu.net/native/";
//const std::string THIRD_CASH_URL = "https://gw.uqiantu.net/native/";
const std::string THIRD_URL = "http://119.23.114.137/native/";
const std::string THIRD_CASH_URL = "http://119.23.114.137/native/";
const std::string THIRD_PACKAGE = "Sign=ThirdPay";
const std::string T_NOTIFY_URL =
    "http://139.224.34.22/cgi-bin/flight/pay/v1/third_callback.fcgi";
const std::string T_CASH_NOTIFY_URL =
    "http://139.224.34.22/cgi-bin/flight/pay/v1/third_cash_callback.fcgi";

/*
 */
namespace pay_logic {

class ThirdOrder {
 public:
  ThirdOrder();
  virtual ~ThirdOrder();

  //inline void set_body(std::string b) {
  //  body = b;
  //}
  inline void set_rec_bank_name(const std::string &value) {
    rec_bank_name = value;
  }
  inline void set_rec_branch_bank_name(const std::string &value) {
    rec_branch_bank_name = value;
  }
  inline void set_rec_card_no(const std::string &value) {
    rec_card_no = value;
  }
  inline void set_rec_account_name(const std::string &value) {
    rec_account_name = value;
  }
  inline void set_out_trade_no(std::string oid) {
    out_trade_no = oid;
  }
  inline void set_total_fee(int fee) {
    total_fee = fee;
  }
  inline void set_spbill_create_ip(std::string ip) {
    spbill_create_ip = ip;
  }
  inline void set_payment_info(const std::string &paymentinfo) {
    payment_info = paymentinfo;
  }
  inline void set_prepayid(std::string preid) {
    prepayid = preid;
  }
  //void PreSign();
  //void PreSerialize(base_logic::DictionaryValue* dic);
  //std::string PlaceOrder();
  std::string PlaceOrder(const std::string& id, const std::string& pay_type,const std::string &content);
  std::string CashPlaceOrder(const std::string& id);

  inline std::string get_appid() {
    return appid;
  }
  inline std::string get_partnerid() {
    return mch_id;
  }
  inline std::string get_payment_info() {
    return payment_info;
  }
  inline std::string get_prepayid() {
    return prepayid;
  }
  inline std::string get_package() {
    return package;
  }
  inline std::string get_nonce_str() {
    return nonce_str;
  }
  inline std::string get_timestamp() {
    return timestamp;
  }
/*
*/
 private:
  std::string PostFiled(bool iscash=false);
  //void InitWxVerify();
  void InitWxVerify(const std::string& id);
  void InitWxVerify(const std::string& id, 
                    const std::string& pay_type,
                    const std::string& content);

  void Set_Headers(http::HttpMethodPost &hmp);
  void PlaceOrderSign(const std::string &body, bool iscash = false);
 private:
  //随机字符串，不长于32位
  std::string nonce_str;
  //用户端实际ip
  std::string spbill_create_ip;
  //支付类型 固定 为 APP //类型 0 app  1.微信公众号
  std::string trade_type;
  //商户key 参与sign签名-不做其他用途
  std::string key;

  //下单成功

  //微信生成的预支付回话标识，用于后续接口调用中使用，该值有效期为2小时
  std::string prepayid;
  //用于客户端调支付
  std::string package;
  //时间戳
  std::string timestamp;
//充值----------------------------------------------------------------------------------------------------------------
  //商户系统内部的订单号,32个字符内、可包含字母
  std::string out_trade_no;
  
  int total_fee;	//订单总金额，单位为分
  
  std::string mch_id; //merchantNo//支付分配的商户号
  //平台审核通过的应用APPID
  std::string appid;

  //签名，详见函数说明
  std::string sign;
  //接收支付异步通知回调地址，通知url必须为直接可访问的url，不能携带参数。
  std::string notify_url;
  std::string pay_type;		//支付类型
  std::string content;		//交易描述
  std::string payment_info;
//提现----------------------------------------------------------------------------------------------------------------
//
  std::string rec_bank_name;
  std::string rec_branch_bank_name;
  std::string rec_card_no;
  std::string rec_account_name;
//ret
//
  int transfer_amount; //实际到账金额
  int fee; //代收手续费
  std::string pay_no;
  std::string status;
};
///
extern int32 GetThirdCashStatus(const std::string &status);
}

#endif  // PUB_PAY_WXPAY_WX_ORDER_H_
