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

ThirdOrder::ThirdOrder() {
  total_fee = 0;
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

void ThirdOrder::PlaceOrderSign() {
  std::stringstream ss;
  std::string req_url = THIRD_URL;
  ss << req_url;
  ss <<  "&amount" << total_fee
      << "&callbackURL=" << notify_url
      << "&content=" << content 
	<< "&merchantNo=" << mch_id;

  ss << "&outTradeNo=" << out_trade_no 
      << "&payType=" << pay_type
//<< "&spbill_create_ip="
//     << spbill_create_ip 
     << "&key=" << key;

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

std::string ThirdOrder::PostFiled() {
  base_logic::DictionaryValue dic;
/*
  dic.SetString(L"appid", appid);
  dic.SetString(L"body", body);
  dic.SetString(L"mch_id", mch_id);
  dic.SetString(L"nonce_str", nonce_str);
  dic.SetString(L"notify_url", notify_url);
  dic.SetString(L"out_trade_no", out_trade_no);
  dic.SetString(L"spbill_create_ip", spbill_create_ip);
  dic.SetBigInteger(L"total_fee", total_fee);
  dic.SetString(L"trade_type", trade_type);
  dic.SetString(L"sign", sign);
  if (!open_id.empty())
    dic.SetString(L"openid", open_id);
*/
  dic.SetString(L"merchantNo", mch_id);
  dic.SetString(L"outTradeNo", out_trade_no);
  dic.SetString(L"notify_url", notify_url);
  dic.SetBigInteger(L"amount", total_fee);
  dic.SetString(L"content", content);
  dic.SetString(L"payType", pay_type);

  std::string filed = "";
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_XML, &filed);
  serializer->Serialize(dic);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_XML,
                                                serializer);
  return filed;
}

std::string ThirdOrder::PlaceOrder(const std::string& id, 
                                const std::string& pay_type,
                                const std::string& content) {
  InitWxVerify(id, pay_type, content);
  //PlaceOrderSign(id, m_id, trade_type, k_key, ptype, open_id);
  PlaceOrderSign();
  http::HttpMethodPost hmp(THIRD_URL);
  //std::string headers = "Content-Type: text/xml";
  std::string headers = "x-oapi-pv: 0.0.1";
  //std::string headers = "com.opentech.cloud.easypay.trade.create: 0.0.1";
  hmp.SetHeaders(headers); //api version
  headers = "x-oapi-sdkv: 0.0.1"; 
  hmp.SetHeaders(headers);	  //sdk version

  headers = "x-oapi-sk: 2017042116284843001";	  //证书key
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

