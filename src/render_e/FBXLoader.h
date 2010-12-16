/* 
 * File:   FBXLoader.h
 * Author: morten
 *
 * Created on December 10, 2010, 4:02 PM
 */

#ifndef FBXLOADER_H
#define	FBXLOADER_H
#include "MeshComponent.h"
#include "SceneObject.h"
#define KFBX_NODLL
#include <fbxsdk.h>

/**
 * Since this class is optional since depends on third party proprietary library.
 * To skip compilation of this class, define the preprocessor symbol 
 * NO_FBX_LOADER
 */
#ifndef NO_FBX_LOADER

namespace render_e {
class FBXLoader {
public:
    FBXLoader();
    FBXLoader(const FBXLoader& orig);
    virtual ~FBXLoader();
    SceneObject *Load(const char *filename);
private:
    KFbxSdkManager *manager;
};
}

#endif /* NO_FBX_LOADER */
#endif	/* FBXLOADER_H */

