LOCAL_PATH := $(call my-dir)
CORE_DIR := $(LOCAL_PATH)/..

include $(CORE_DIR)/Makefile.common

include $(CLEAR_VARS)
LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := retro
LOCAL_SRC_FILES := $(SOURCES_C) $(SOURCES_CXX)
LOCAL_CFLAGS    := $(CFLAGS)
LOCAL_LDFLAGS   := -Wl,-version-script=$(CORE_DIR)/link.T
include $(BUILD_SHARED_LIBRARY)
