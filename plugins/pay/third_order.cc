//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年1月12日 Author: kerry

#include "pay/third_order.h"

#include <iostream>
#include <sstream>
#include "basic/md5sum.h"
#include "http/http_method.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"

namespace pay_logic {

const std::string PASSWORD = "password";
ThirdOrder::ThirdOrder() {
  total_fee = 0;
  fee = 0;
  transfer_amount = 0;  
}

ThirdOrder::~ThirdOrder() {
}

void ThirdOrder::InitWxVerify(const std::string& id, 
                           const std::string& p_type, 
                           const std::string& ctent) {
  appid = id;
  //mch_id = m_id;
  mch_id = T_MCH_ID;
  notify_url = T_NOTIFY_URL;
  pay_type = p_type;
  content = ctent;
//
  nonce_str = logic::SomeUtils::RandomString(32);
}

void ThirdOrder::InitWxVerify(const std::string& id) {
//cash use
  appid = id;
  mch_id = T_MCH_ID;
  notify_url = T_CASH_NOTIFY_URL;
}
void ThirdOrder::InitWxVerify() {
  appid = T_APPID;
  mch_id = T_MCH_ID;
  notify_url = T_NOTIFY_URL;
  trade_type = T_APP_TRADE_TYPE;
  package = THIRD_PACKAGE;
  key = T_APP_KEY;
  nonce_str = logic::SomeUtils::RandomString(32);
  //out_trade_no += logic::SomeUtils::RandomString(6);
}

void ThirdOrder::PlaceOrderSign(bool iscash) {
  std::stringstream ss;
  //std::string req_url = THIRD_URL+"";
  std::string req_url = THIRD_URL + "com.opentech.cloud.easypay.trade.create/ 0.0.1";
  if (iscash)
    req_url = THIRD_CASH_URL + "com.opentech.cloud.easypay.balance.pay/0.0.1";
    //req_url = THIRD_CASH_URL+"";
  ss << req_url;


  ss << "&x-oapi-pv=0.0.1"
   << "&x-oapi-sdkv=0.0.1/c" 
   << "&x-oapi-sk=" << T_APP_KEY	  //证书key
   << "&x-oapi-sm=MD5";

  ss << "&amount=" << total_fee
     << "&callbackURL=" << notify_url;
  if (iscash)
  {
     ss << "&merchantNo=" << mch_id
	<< "&outPayNo=" << out_trade_no 
        << "&payPassword=" << PASSWORD
        << "&receiverAccountName=" << rec_account_name
        << "&receiverBankName=" << rec_bank_name
        << "&receiverBranchBankName=" << rec_branch_bank_name
        << "&receiverCardNo=" << rec_card_no;
  }
  else
  {
     ss << "&content=" << content 
        << "&merchantNo=" << mch_id
        << "&outTradeNo=" << out_trade_no 
        << "&payType=" << pay_type;
  }
//<< "&spbill_create_ip="
//     << spbill_create_ip 
     ss << "&key=" << key;

  LOG_DEBUG2("THIRD_ORDER_SIGN before: %s",ss.str().c_str());
  base::MD5Sum md5sum(ss.str());
  LOG_DEBUG2("THIRD_ORDER_SIGN_MD5 after: %s",md5sum.GetHash().c_str());
  sign = md5sum.GetHash();
}

//APP充值
void ThirdOrder::PreSign() {
  //重新赋值 nonce_str
  nonce_str = logic::SomeUtils::RandomString(32);
  std::stringstream ss;
  ss << time(NULL);
  timestamp = ss.str();
  ss.str("");
  ss.clear();
  if (trade_type == T_APP_TRADE_TYPE) {
    ss << "appid=" << appid << "&noncestr=" << nonce_str << "&package=Sign=WXPay"
          << "&partnerid=" << mch_id << "&prepayid=" << prepayid << "&timestamp="
          << timestamp << "&key=" << key;
  } else {
    ss << "appId=" << appid << "&nonceStr=" << nonce_str << "&package="
        << "prepayid=" << prepayid << "&signType=MD5&timeStamp=" << timestamp
        << "&key=" << key;
  }
  //LOG(INFO)<< "WX_PRE_SIGN before:" << ss.str();
  LOG_DEBUG2("WX_ORDER_SIGN before: %s",ss.str().c_str());
  base::MD5Sum md5sum(ss.str());
  //LOG(INFO)<< "WX_PRE_SIGN_MD5 after:" << md5sum.GetHash();
  LOG_DEBUG2("WX_ORDER_SIGN_MD5 after: %s",md5sum.GetHash().c_str());
  prepaysign = md5sum.GetHash();
}

std::string ThirdOrder::PostFiled(bool iscash) {
  base_logic::DictionaryValue dic;

  dic.SetString(L"merchantNo", mch_id);
  dic.SetString(L"callbackURL", notify_url);
  dic.SetBigInteger(L"amount", total_fee);
  if (iscash)
  {
    dic.SetString(L"outPayNo", out_trade_no);
    dic.SetString(L"payPassword", PASSWORD);
    dic.SetString(L"receiverBankName", rec_bank_name);
    dic.SetString(L"receiverBranchBankName", rec_branch_bank_name);
    dic.SetString(L"receiverCardNo", rec_card_no);
    dic.SetString(L"receiverAccountName", rec_account_name);
  }
  else
  {
    dic.SetString(L"outTradeNo", out_trade_no);
    dic.SetString(L"content", content);
    dic.SetString(L"payType", pay_type);
  }

  std::string filed = "";
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_XML, &filed);
  serializer->Serialize(dic);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_XML,
                                                serializer);
  return filed;
}

std::string ThirdOrder::CashPlaceOrder(const std::string& id) {
  InitWxVerify(id);
  //PlaceOrderSign(id, m_id, trade_type, k_key, ptype, open_id);
  PlaceOrderSign(true);

  std::string url = THIRD_CASH_URL + "com.opentech.cloud.easypay.balance.pay/0.0.1";
  http::HttpMethodPost hmp(url);
  //http::HttpMethodPost hmp(THIRD_CASH_URL);
  //std::string headers = "Content-Type: text/xml";
  std::string headers = "x-oapi-pv: 0.0.1";
  //std::string headers = "com.opentech.cloud.easypay.balance.pay: 0.0.1";
  hmp.SetHeaders(headers); //api version
  headers = "x-oapi-sdkv: 0.0.1/c"; 
  hmp.SetHeaders(headers);	  //sdk version

  headers = "x-oapi-sk: " + T_APP_KEY;	  //证书key
  hmp.SetHeaders(headers);
  headers = "x-oapi-sm: MD5";
  hmp.SetHeaders(headers);
  headers = "x-oapi-sign: " + sign;
  hmp.SetHeaders(headers);
///
  hmp.Post(PostFiled().c_str());
  std::string result;
  hmp.GetContent(result);
  //LOG(INFO)<< "http post result:" << result;
  LOG_DEBUG2("http post result: %s", result.c_str());
  return result;
}

std::string ThirdOrder::PlaceOrder(const std::string& id, 
                                const std::string& pay_type,
                                const std::string& content) {
  printf("PlaceOrder start..................\n"); //tw test
  std::string url = THIRD_URL + "com.opentech.cloud.easypay.trade.create/ 0.0.1";
  InitWxVerify(id, pay_type, content);
  //PlaceOrderSign(id, m_id, trade_type, k_key, ptype, open_id);
  PlaceOrderSign();
  http::HttpMethodPost hmp(url);
  //std::string headers = "Content-Type: text/xml";
  std::string headers = "x-oapi-pv: 0.0.1";
  hmp.SetHeaders(headers); //api version
  headers = "x-oapi-sdkv: 0.0.1/c"; 
  hmp.SetHeaders(headers);	  //sdk version

  headers = "x-oapi-sk: " + T_APP_KEY;	  //证书key
  hmp.SetHeaders(headers);
  headers = "x-oapi-sm: MD5";
  hmp.SetHeaders(headers);
  headers = "x-oapi-sign: " + sign;
  hmp.SetHeaders(headers);
///
  hmp.Post(PostFiled().c_str());
  std::string result;
  hmp.GetContent(result);
  //LOG(INFO)<< "http post result:" << result;
  LOG_DEBUG2("http post result: %s", result.c_str());
  printf("PlaceOrder end.......result[%s]...........\n", result.c_str()); //tw test
  printf("PlaceOrder end..................\n"); //tw test
  return result;
}

std::string ThirdOrder::PlaceOrder() {
  InitWxVerify();
  PlaceOrderSign();
  http::HttpMethodPost hmp(THIRD_URL);
  std::string headers = "Content-Type: text/xml";
  hmp.SetHeaders(headers);
  hmp.Post(PostFiled().c_str());
  std::string result;
  hmp.GetContent(result);
  //LOG(INFO)<< "http post result:" << result;
  LOG_DEBUG2("http post result: %s", result.c_str());
  return result;
}

void ThirdOrder::PreSerialize(base_logic::DictionaryValue* dic) {
  if (dic != NULL) {
    dic->SetString(L"appid", appid);
    dic->SetString(L"partnerid", mch_id);
    dic->SetString(L"prepayid", prepayid);
    if (trade_type == "APP")
      dic->SetString(L"package", package);
    else {
      std::string str_package;
      str_package = "prepayid=" + prepayid;
      dic->SetString(L"package", str_package);
    }
    dic->SetString(L"noncestr", nonce_str);
    dic->SetString(L"timestamp", timestamp);
    dic->SetString(L"sign", prepaysign);
  }
}
}

