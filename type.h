#pragma once

#include <stdint.h>
#include <chrono>
#include <map>

using namespace std;


typedef uint64_t TimeInt;
typedef uint64_t      AddrInt;
typedef uint32_t NodeType;
typedef pair<NodeType, NodeType> LinkType;
typedef uint64_t ScoreType;
typedef map<unsigned, NodeType> DomainMap;
typedef uint32_t ScopeType;
typedef pair<AddrInt, AddrInt> RangeType;
const TimeInt TimeMax = UINT64_MAX >> 1;
const NodeType NodeINF = UINT32_MAX >> 1;
const ScoreType ScoreMAX = INT64_MAX >> 1;
const ScoreType ScoreMIN = INT64_MIN >> 1;
const bool MEMREAD = false;
const bool MEMWRITE = true;
const int NOTFOUND = -1;
#define UNUSED_VAR(x) (void)(x)
const int SUBLOG_BITS = 3;
#define MAX_WINDOW      ((65-SUBLOG_BITS)*(1<<SUBLOG_BITS))
typedef chrono::time_point<chrono::high_resolution_clock> TP;
