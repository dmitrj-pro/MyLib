#pragma once

#include <list>
#include <DPLib.conf.h>

using std::list;
using __DP_LIB_NAMESPACE__::String;

list <String> GetFiles(const String & filder);

list<String> SetFilter(const list<String> & data, const String& filter = "${name}.ovpn");
