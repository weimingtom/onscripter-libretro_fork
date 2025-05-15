#ndk-build -j8
#ndk-build NDK_DEBUG=1 -j8

#APP_STL := gnustl_static
#APP_STL := c++_static
#APP_STL := stlport_static

#android-24 tested, android-20 failed
#APP_PLATFORM := android-24
#APP_PLATFORM := android-20
# for #include <EGL/eglplatform.h>, FIXME:TODO: need to be removed
APP_PLATFORM := android-21

#APP_CPPFLAGS := -frtti -std=c++11 -fsigned-char
#APP_LDFLAGS := -latomic
#APP_CONLYFLAGS := -std=c99

#ifeq ($(NDK_DEBUG),1)
#  APP_CPPFLAGS += -D_DEBUG
#  APP_OPTIM := debug
#else
#  APP_CPPFLAGS += -DNDEBUG
#  APP_OPTIM := release
#endif

APP_STL := c++_static
APP_ABI := armeabi-v7a arm64-v8a
#APP_ABI := armeabi-v7a
APP_CFLAGS += -D__LIBRETRO__ -DBUILD_ALL_LOG
