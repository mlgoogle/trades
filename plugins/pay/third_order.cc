//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年1月12日 Author: kerry

#include "pay/third_order.h"

#include <iostream>
#include <sstream>
#include "basic/md5sum.h"
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
static std::string Upper(std::string &text) {
  for (unsigned int i = 0; i < text.length(); i ++)
  {
	if (text[i] >= 'a' && text[i] <= 'z')
		text[i] = text[i] - 32;
  }
return text;
}

void ThirdOrder::PlaceOrderSign(const std::string &body, bool iscash) {
  std::stringstream ss;
  //std::string req_url = THIRD_URL+"";
  std::string req_url = THIRD_URL + "com.opentech.cloud.easypay.trade.create/0.0.1";
  if (iscash)
    req_url = THIRD_CASH_URL + "com.opentech.cloud.easypay.balance.pay/0.0.1";
  ss << req_url;


  ss << "&x-oapi-pv=0.0.1"
   << "&x-oapi-sdkv=0.0.1/c" 
   << "&x-oapi-sk=" << T_APP_KEY	  //证书key
   << "&x-oapi-sm=MD5"
   << "&" << body;

  ss << "&" << T_MD5_KEY;

  LOG_DEBUG2("THIRD_ORDER_SIGN before: %s",ss.str().c_str());
  base::MD5Sum md5sum(ss.str());
  LOG_DEBUG2("THIRD_ORDER_SIGN_MD5 after: %s",md5sum.GetHash().c_str());
  sign = md5sum.GetHash();
  Upper(sign);
  LOG_DEBUG2("THIRD_ORDER_SIGN_MD5 after2___________: %s",md5sum.GetHash().c_str());
}

/*
*/

std::string ThirdOrder::PostFiled(bool iscash) {
  base_logic::DictionaryValue dic;

  dic.SetBigInteger(L"amount", total_fee);
  dic.SetString(L"callbackURL", notify_url);
  if (iscash)
  {
    dic.SetString(L"merchantNo", mch_id);
    dic.SetString(L"outPayNo", out_trade_no);
    dic.SetString(L"payPassword", PASSWORD);
    dic.SetString(L"receiverAccountName", rec_account_name);
    dic.SetString(L"receiverBankName", rec_bank_name);
    dic.SetString(L"receiverBranchBankName", rec_branch_bank_name);
    dic.SetString(L"receiverCardNo", rec_card_no);
  }
  else
  {
    dic.SetString(L"content", content);
    dic.SetString(L"merchantNo", mch_id);
    dic.SetString(L"outTradeNo", out_trade_no);
    dic.SetString(L"payType", pay_type);
  }

  std::string filed = "";
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &filed);
  serializer->Serialize(dic);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return filed;
}
void ThirdOrder::Set_Headers(http::HttpMethodPost &hmp)
{
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
//
  headers = "Accept: application/json";    
  hmp.SetHeaders(headers); 
  headers = "Content-Type: application/json";  
  hmp.SetHeaders(headers); 
  headers = "charsets: utf-8";     
  hmp.SetHeaders(headers); 
  headers = "User-Agent: easypay-api-sdk/c";     
  hmp.SetHeaders(headers); 
}

std::string ThirdOrder::CashPlaceOrder(const std::string& id) {
  InitWxVerify(id);
  std::string body = PostFiled();
  PlaceOrderSign(body ,true);

  std::string url = THIRD_CASH_URL + "com.opentech.cloud.easypay.balance.pay/0.0.1";
  http::HttpMethodPost hmp(url);
  Set_Headers(hmp);
///
  hmp.Post(body.c_str());
  std::string result;
  hmp.GetContent(result);
  //LOG(INFO)<< "http post result:" << result;
  LOG_DEBUG2("http post result: %s", result.c_str());
  return result;
}

std::string ThirdOrder::PlaceOrder(const std::string& id, 
                                const std::string& pay_type,
                                const std::string& content) {
  LOG_ERROR("PlaceOrder start..................\n"); //tw test
  std::string url = THIRD_URL + "com.opentech.cloud.easypay.trade.create/0.0.1";
  InitWxVerify(id, pay_type, content);
  std::string body = PostFiled();
  PlaceOrderSign(body);
  http::HttpMethodPost hmp(url);
  Set_Headers(hmp);
///
  //hmp.Post(PostFiled().c_str());
  hmp.Post(body.c_str());
  std::string result;
  hmp.GetContent(result);

////get header message
  std::string err_key = "x-oapi-error-code";
  MIG_VALUE err_value;
  
  hmp.GetHeader(err_key, err_value);
  MIG_VALUE::iterator iter;
  for (iter = err_value.begin(); iter != err_value.end(); iter++)
    LOG_DEBUG2("err_value_____[%s]", iter->c_str());

/////

  //LOG(INFO)<< "http post result:" << result;
  LOG_DEBUG2("http post result: %s", result.c_str());
  LOG_ERROR2("PlaceOrder end.......result[%s]...........\n", result.c_str()); //tw test
  LOG_ERROR("PlaceOrder end..................\n"); //tw test
  return result;
}

}//namespace pay_logic

