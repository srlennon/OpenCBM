#ifndef CBM4WIN_VERSION_H
#define CBM4WIN_VERSION_H

#define CBM4WIN_VERSION_MAJOR       0
#define CBM4WIN_VERSION_MINOR       4
#define CBM4WIN_VERSION_SUBMINOR    0
#define CBM4WIN_VERSION_PATCHLEVEL  0
#define CBM4WIN_VERSION_DEVEL       29

#define CBM4WIN_BUILD_VERSION_HELP(          _a        ) #_a
#define CBM4WIN_BUILD_VERSION_STRING_PART(   _a        ) CBM4WIN_BUILD_VERSION_HELP(_a)
#define CBM4WIN_BUILD_VERSION_STRING_RELEASE(_a, _b, _c) CBM4WIN_BUILD_VERSION_HELP(_a) "." CBM4WIN_BUILD_VERSION_HELP(_b) "." CBM4WIN_BUILD_VERSION_HELP(_c) 

#define CBM4WIN_BUILD_VERSION_STRING_CVS "$Id: version.h,v 1.127 2006-07-21 11:58:01 strik Exp $"


#if CBM4WIN_VERSION_DEVEL == 0
#define CBM4WIN_VERSION_STRING   CBM4WIN_BUILD_VERSION_STRING_RELEASE(CBM4WIN_VERSION_MAJOR, CBM4WIN_VERSION_MINOR, CBM4WIN_VERSION_SUBMINOR)
#elif CBM4WIN_VERSION_PATCHLEVEL == 0
#define CBM4WIN_VERSION_STRING   CBM4WIN_BUILD_VERSION_STRING_RELEASE(CBM4WIN_VERSION_MAJOR, CBM4WIN_VERSION_MINOR, CBM4WIN_VERSION_SUBMINOR) "." CBM4WIN_BUILD_VERSION_STRING_PART( CBM4WIN_VERSION_DEVEL)
#else
#define CBM4WIN_VERSION_STRING   CBM4WIN_BUILD_VERSION_STRING_RELEASE(CBM4WIN_VERSION_MAJOR, CBM4WIN_VERSION_MINOR, CBM4WIN_VERSION_SUBMINOR) "." CBM4WIN_BUILD_VERSION_STRING_PART( CBM4WIN_VERSION_DEVEL) "pl" CBM4WIN_BUILD_VERSION_STRING_PART(CBM4WIN_VERSION_PATCHLEVEL)
#endif

#endif /* #ifndef CBM4WIN_VERSION_H */
