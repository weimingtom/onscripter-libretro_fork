LOCAL_PATH := $(call my-dir)
CORE_DIR := $(LOCAL_PATH)/..

#include $(CORE_DIR)/Makefile.common
#include $(CORE_DIR)/Makefile-jh.common
include $(CORE_DIR)/Makefile-yuri.common

include $(CLEAR_VARS)
LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE := retro
LOCAL_SRC_FILES := $(SOURCES_C) $(SOURCES_CXX)

LOCAL_CFLAGS := $(CFLAGS) -std=c99 -DBUILD_RETROARCH=1
#-DSDL_JAVA_PACKAGE_PATH=com_example_SanAngeles 

LOCAL_LDFLAGS := -Wl,-version-script=$(CORE_DIR)/link.T
LOCAL_LDLIBS := -llog -landroid 
#-lEGL -lGLESv2

LOCAL_STATIC_LIBRARIES := cpufeatures
#LOCAL_STATIC_LIBRARIES := cpufeatures android_support android_native_app_glue ndk_helper

include $(BUILD_SHARED_LIBRARY)

#SDL_cpuinfo
$(call import-module,cpufeatures)

#SDL_icov, iconv
#$(call import-module, android/support)

#$(call import-module,android/ndk_helper)
#$(call import-module,android/native_app_glue)
#$(call import-module,android/cpufeatures)
