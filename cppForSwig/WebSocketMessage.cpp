////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Copyright (C) 2018, goatpig.                                              //
//  Distributed under the MIT license                                         //
//  See LICENSE-MIT or https://opensource.org/licenses/MIT                    //                                      
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "WebSocketMessage.h"

////////////////////////////////////////////////////////////////////////////////
BinaryData WebSocketMessage::serialize(uint64_t id, const string& msg)
{
   BinaryWriter bw;

   bw.put_uint32_t(0); //leading 4 bytes for lws
   bw.put_uint64_t(id);

   //TODO: fallback to raw binary messages once lws is standardized
   BinaryDataRef bdr((uint8_t*)msg.c_str(), msg.size());
   bw.put_BinaryDataRef(bdr);

   return bw.getData();
}

////////////////////////////////////////////////////////////////////////////////
uint64_t WebSocketMessage::deserialize(const BinaryData& data, string& msg)
{
   BinaryRefReader brr(data.getRef());

   auto id = brr.get_uint64_t();
   auto bdr = brr.get_BinaryDataRef(brr.getSizeRemaining());
   msg = string(bdr.toCharPtr(), bdr.getSize());
   
   return id;
}
