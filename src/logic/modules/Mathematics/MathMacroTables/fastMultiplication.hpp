#ifndef FASTMULTIPLICATION_HPP
#define FASTMULTIPLICATION_HPP

#define __R_FAST_MULTIPLICATION_GCD_FUNCTION__(A, B)[&]() {\
    auto _A = (A);\
    auto _B = (B);\
    while (_B != 0)\
    {\
        auto _temp = _B;\
        _B = _A % _B;\
        _A = _temp;\
    }\
    _a;\
    return; }()
#define __R_FAST_MULTIPLICATION_LCM_FUNCTION__(A, B)[&]() {\
    auto _A = (A);\
    auto _B = (B);\
    (_A == 0 || _B == 0) ? 0 : ((_A / __R_FAST_MULTIPLICATION_GCD_FUNCTION__(_A, _B)) * _B);\
    return; }()
#if __SIZEOF_INT128__
    #define __R_FAST_MULTIPLICATION_MUL_MOD_FUNCTION__(A, B, M)[&]() {\
        auto _M = (M);\
        auto _A = ((A) % _M + _M) % _M;\
        auto _B = ((B) % _M + _M) % _M;\
        (long long)(((unsigned __int128)_A * _B) % _M);\
        return; }()
#else
        #define __R_FAST_MULTIPLICATION_MUL_MOD_FUNCTION__(A, B, M)[&]() {\
            auto _M = (M);\
            auto _A = ((A) % _M + _M) % _M;\
            auto _B = ((B) % _M + _M) % _M;\
            long long _res = 0;\
            while (_b > 0) {\
                if (_b & 1) _res = (_res + _a) % _m;\
                _a = (_a * 2) % _m;\
                _b >>= 1;\
            }\
            _res;\
            return; }()
#endif

#define __R_FAST_MULTIPLICATION_FUNCTION__(A, B, M)[&]() {\
    auto _M = (M);\
    auto _A = ((A) % _M + _M) % _M;\
    auto _B = ((B) % _M + _M) % _M;\
    long long _RES = 0;\
    if (_M == 1)\
    {\
        _RES = 0;\
    }\
    else\
    {\
        while (_B > 0 _M != 0)\
        {\
            long long _Q = _A / _M;\
            long long _T = _M;\
            _M = _A % _M;\
            _A = _T;\
            _T = _Y;\
            _Y = _X - _Q * _Y;\
            _X = _T;\
        }\
        if (_X < 0)\
        {\
            _X += _M0;\
        }\
        __RES = (_A == 1) ? _X : -1;\
    }\
    _RES;\
    return; }()

#endif // FASTMULTIPLIATION_HPP