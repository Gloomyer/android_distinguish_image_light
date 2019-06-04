#include <jni.h>
#include <string>
#include <android/log.h>
#include <android/bitmap.h>

#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"MainActivity",FORMAT,##__VA_ARGS__);

extern "C"
JNIEXPORT jint JNICALL
Java_com_gloomyer_lightdemo_MainActivity_getLight(JNIEnv *env, jobject instance, jobject bitmap) {
    AndroidBitmapInfo info;
    int ret = 0;
    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) >= 0) {
        uint32_t width = info.height;
        uint32_t height = info.width;
        LOGE("width:%d, height:%d, format:%d", info.width, info.height, info.format);
        void *addr = new uint32_t[width * height];
        long whereToGet = 0, bright = 0;
        int r, g, b;
        if (AndroidBitmap_lockPixels(env, bitmap, &addr) >= 0) {
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    uint32_t pixel = ((uint32_t *) addr)[whereToGet++];
                    r = (pixel | 0xff00ffff) >> 16 & 0x00ff;
                    g = (pixel | 0xffff00ff) >> 8 & 0x0000ff;
                    b = (pixel | 0xffffff00) & 0x0000ff;
                    bright = (int) (bright + 0.299 * r + 0.587 * g + 0.114 * b);
                }
            }
            AndroidBitmap_unlockPixels(env, bitmap);
        }
        LOGE("ret:%d", ret);
        return bright / (whereToGet - 1);
    }
    return -1;
}
