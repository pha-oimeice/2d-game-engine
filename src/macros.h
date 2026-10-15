#ifndef __MACRO_H__
#define __MACRO_H__

#ifdef _MSC_VER
    #define CPP_VERSION _MSVC_LANG
#else
    #define CPP_VERSION __cplusplus
#endif

#if CPP_VERSION >= 202002L
#define CPP_20
#else
#define std::jthread std::thread
#endif // CPP_VERSION >= 202002L



#endif // !__MACRO_H__