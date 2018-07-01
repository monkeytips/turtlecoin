<<<<<<< HEAD
// Copyright (c) 2018, The TurtleCoin Developers
// 
// Please see the included LICENSE file for more information.

#include <algorithm>

#include "Difficulty.h"

#include <config/CryptoNoteConfig.h>

// LWMA-2 difficulty algorithm 
// Copyright (c) 2017-2018 Zawy, MIT License
// https://github.com/zawy12/difficulty-algorithms/issues/3
uint64_t nextDifficultyV5(std::vector<uint64_t> timestamps, std::vector<uint64_t> cumulativeDifficulties)
{
    int64_t T = CryptoNote::parameters::DIFFICULTY_TARGET;
    int64_t N = CryptoNote::parameters::DIFFICULTY_WINDOW_V3;
    int64_t L(0), ST, sum_3_ST(0), next_D, prev_D;

    /* If we are starting up, returning a difficulty guess. If you are a
       new coin, you might want to set this to a decent estimate of your
       hashrate */
    if (timestamps.size() < static_cast<uint64_t>(N+1))
    {
        return 10000;
    }

    for (int64_t i = 1; i <= N; i++)
    {  
        ST = static_cast<int64_t>(timestamps[i]) - static_cast<int64_t>(timestamps[i-1]);

        ST = std::max(-4 * T, std::min(ST, 6 * T));

        L +=  ST * i; 

        if (i > N-3)
        {
            sum_3_ST += ST;
        } 
    }

    next_D = (static_cast<int64_t>(cumulativeDifficulties[N] - cumulativeDifficulties[0]) * T * (N+1) * 99) / (100 * 2 * L);

    prev_D = cumulativeDifficulties[N] - cumulativeDifficulties[N-1];

    next_D = std::max((prev_D * 67) / 100, std::min(next_D, (prev_D * 150) / 100));

    if (sum_3_ST < (8 * T) / 10)
    {  
        next_D = std::max(next_D, (prev_D * 108) / 100);
    }

    return static_cast<uint64_t>(next_D);
}

// LWMA-2 difficulty algorithm 
// Copyright (c) 2017-2018 Zawy, MIT License
// https://github.com/zawy12/difficulty-algorithms/issues/3
uint64_t nextDifficultyV4(std::vector<uint64_t> timestamps, std::vector<uint64_t> cumulativeDifficulties)
{
    int64_t T = CryptoNote::parameters::DIFFICULTY_TARGET;
    int64_t N = CryptoNote::parameters::DIFFICULTY_WINDOW_V3;
    int64_t L(0), ST, sum_3_ST(0), next_D, prev_D;

    if (timestamps.size() <= static_cast<uint64_t>(N))
    {
        return 1000;
    }

    for (int64_t i = 1; i <= N; i++)
    {  
        ST = clamp(-6 * T, static_cast<int64_t>(timestamps[i]) - static_cast<int64_t>(timestamps[i-1]), 6 * T);

        L +=  ST * i; 

        if (i > N-3)
        {
            sum_3_ST += ST;
        } 
    }

    next_D = (static_cast<int64_t>(cumulativeDifficulties[N] - cumulativeDifficulties[0]) * T * (N+1) * 99) / (100 * 2 * L);
    prev_D = cumulativeDifficulties[N] - cumulativeDifficulties[N-1];

    /* Make sure we don't divide by zero if 50x attacker (thanks fireice) */
    next_D = std::max((prev_D*67)/100, std::min(next_D, (prev_D*150)/100));

    if (sum_3_ST < (8 * T) / 10)
    {  
        next_D = std::max(next_D, (prev_D * 110) / 100);
    }

    return static_cast<uint64_t>(next_D);
}

// LWMA-2 difficulty algorithm 
// Copyright (c) 2017-2018 Zawy, MIT License
// https://github.com/zawy12/difficulty-algorithms/issues/3
uint64_t nextDifficultyV3(std::vector<uint64_t> timestamps, std::vector<uint64_t> cumulativeDifficulties)
{
    int64_t T = CryptoNote::parameters::DIFFICULTY_TARGET;
    int64_t N = CryptoNote::parameters::DIFFICULTY_WINDOW_V3;
    int64_t FTL = CryptoNote::parameters::CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT_V3;
    int64_t L(0), ST, sum_3_ST(0), next_D, prev_D;

    if (timestamps.size() <= static_cast<uint64_t>(N))
    {
        return 1000;
    }

    for (int64_t i = 1; i <= N; i++)
    {  
        ST = std::max(-FTL, std::min(static_cast<int64_t>(timestamps[i]) - static_cast<int64_t>(timestamps[i-1]), 6 * T));

        L +=  ST * i; 

        if (i > N-3)
        {
            sum_3_ST += ST;
        } 
    }

    next_D = (static_cast<int64_t>(cumulativeDifficulties[N] - cumulativeDifficulties[0]) * T * (N+1) * 99) / (100 * 2 * L);
    prev_D = cumulativeDifficulties[N] - cumulativeDifficulties[N-1];

    /* Make sure we don't divide by zero if 50x attacker (thanks fireice) */
    next_D = std::max((prev_D*70)/100, std::min(next_D, (prev_D*107)/100));

    if (sum_3_ST < (8 * T) / 10)
    {  
        next_D = (prev_D * 110) / 100;
    }

    return static_cast<uint64_t>(next_D);
=======
// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
//
// This file is part of Bytecoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "Common/int-util.h"
#include "crypto/hash.h"
#include "CryptoNoteConfig.h"
#include "Difficulty.h"

namespace CryptoNote {

  using std::uint64_t;
  using std::vector;

#if defined(__SIZEOF_INT128__)

  static inline void mul(uint64_t a, uint64_t b, uint64_t &low, uint64_t &high) {
    typedef unsigned __int128 uint128_t;
    uint128_t res = (uint128_t) a * (uint128_t) b;
    low = (uint64_t) res;
    high = (uint64_t) (res >> 64);
  }

#else

  static inline void mul(uint64_t a, uint64_t b, uint64_t &low, uint64_t &high) {
    low = mul128(a, b, &high);
  }

#endif

  static inline bool cadd(uint64_t a, uint64_t b) {
    return a + b < a;
  }

  static inline bool cadc(uint64_t a, uint64_t b, bool c) {
    return a + b < a || (c && a + b == (uint64_t) -1);
  }

  bool check_hash(const Crypto::Hash &hash, Difficulty difficulty) {
    uint64_t low, high, top, cur;
    // First check the highest word, this will most likely fail for a random hash.
    mul(swap64le(((const uint64_t *) &hash)[3]), difficulty, top, high);
    if (high != 0) {
      return false;
    }
    mul(swap64le(((const uint64_t *) &hash)[0]), difficulty, low, cur);
    mul(swap64le(((const uint64_t *) &hash)[1]), difficulty, low, high);
    bool carry = cadd(cur, low);
    cur = high;
    mul(swap64le(((const uint64_t *) &hash)[2]), difficulty, low, high);
    carry = cadc(cur, low, carry);
    carry = cadc(high, top, carry);
    return !carry;
  }
>>>>>>> blood in blood out
}
