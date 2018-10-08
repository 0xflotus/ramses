//  -------------------------------------------------------------------------
//  Copyright (C) 2012 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#ifndef RAMSES_SCENEAPI_SCENEID_H
#define RAMSES_SCENEAPI_SCENEID_H

#include "PlatformAbstraction/PlatformTypes.h"
#include "Common/StronglyTypedValue.h"
#include "Collections/Vector.h"
#include "Collections/String.h"

namespace ramses_internal
{
    struct SceneIdTag {};
    typedef StronglyTypedValue<UInt64, 0, SceneIdTag> SceneId;

    typedef Vector<SceneId> SceneIdVector;

    struct SceneInfo
    {
        SceneInfo() {}
        SceneInfo(const SceneId& sceneID_, const String& friendlyName_ = String())
            : sceneID(sceneID_)
            , friendlyName(friendlyName_)
        {}

        friend bool operator==(const SceneInfo& a, const SceneInfo& b)
        {
            return a.sceneID == b.sceneID && a.friendlyName == b.friendlyName;
        }

        friend bool operator!=(const SceneInfo& a, const SceneInfo& b)
        {
            return !(a == b);
        }

        SceneId sceneID;
        String friendlyName;
    };
    typedef Vector<SceneInfo> SceneInfoVector;
}

#endif