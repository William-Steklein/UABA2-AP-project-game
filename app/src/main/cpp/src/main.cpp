#include <android/log.h>

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include <string>

static int pfd[2];
static pthread_t loggingThread;
static const char *LOG_TAG = "EXAMPLE_DEBUG";

static void *loggingFunction(void *) {
    ssize_t readSize;
    char buf[128];
    while ((readSize = read(pfd[0], buf, sizeof buf - 1)) > 0) {
        if (buf[readSize - 1] == '\n')
            --readSize;
        buf[readSize] = 0;  // add null-terminator
        __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, buf); // Set any log level you want
    }
    return nullptr;
}

static int runLoggingThread() {
    setvbuf(stdout, nullptr, _IOLBF, 0); // make stdout line-buffered
    setvbuf(stderr, nullptr, _IONBF, 0); // make stderr unbuffered

    pipe(pfd);
    dup2(pfd[1], 1);
    dup2(pfd[1], 2);

    pthread_create(&loggingThread, nullptr, loggingFunction, nullptr);
    pthread_detach(loggingThread);
    return 0;
}

#include <renderer/Renderer.h>

int main() {
    std::cout << "hello" << std::endl;

    runLoggingThread();

    renderer::Renderer app;
    app.run();

    return 0;
}