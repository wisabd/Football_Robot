
include_directories(${CMAKE_SOURCE_DIR}/include)


set(AR_SRC1 mAlloc.c mFree.c mAllocDup.c mDup.c mAllocTrans.c mTrans.c 
    mAllocMul.c mMul.c mAllocInv.c mInv.c mSelfInv.c mAllocUnit.c mUnit.c 
    mDisp.c mDet.c mPCA.c vAlloc.c vDisp.c vFree.c vHouse.c vInnerP.c vTridiag.c)
set(AR_SRC2 paramGet.c paramDecomp.c paramDistortion.c paramChangeSize.c paramFile.c paramDisp.c)
set(AR_SRC3 arDetectMarker.c arGetTransMat.c arGetTransMat2.c arGetTransMat3.c 
    arGetTransMatCont.c arLabeling.c arDetectMarker2.c arGetMarkerInfo.c arGetCode.c arUtil.c )

set(AR_SRC ${AR_SRC1} ${AR_SRC2} ${AR_SRC3})

add_library(AR STATIC ${AR_SRC})
