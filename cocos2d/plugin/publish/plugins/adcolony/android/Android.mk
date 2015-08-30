LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := PluginAdColonyStatic
LOCAL_MODULE_FILENAME := libPluginAdColonyStatic

LOCAL_SRC_FILES := ./lib/$(TARGET_ARCH_ABI)/libPluginAdColonyStatic.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include $(LOCAL_PATH)
LOCAL_EXPORT_LDLIBS := -llog

include $(PREBUILT_STATIC_LIBRARY)
