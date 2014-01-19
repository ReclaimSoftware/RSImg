BUILD=../build

RSTEST=../upstream/RSTest
RSTEST_ARGS="-isystem $RSTEST/ $RSTEST/RSTest.c"

RSIMG=../
RSIMG_ARGS="-isystem $RSIMG/ $RSIMG/RSImg.c"


mkdir -p $BUILD

echo 'Building...' && \
    $CC \
        -std=c99 \
        -Wall \
        -O3 \
        $RSTEST_ARGS \
        $RSIMG_ARGS \
        -o $BUILD/runtests \
        test-RSImgFreadPPMP6Header.c \
        runtests.c && \
    $BUILD/runtests
