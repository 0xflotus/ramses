//  -------------------------------------------------------------------------
//  Copyright (C) 2017 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#ifndef RAMSES_TEXTURE2DBUFFER_H
#define RAMSES_TEXTURE2DBUFFER_H

#include "ramses-client-api/SceneObject.h"
#include "TextureEnums.h"

namespace ramses
{
    /**
    * @brief The Texture2DBuffer is a mutable scene resource used to hold texture data with the possibility
    * to perform partial updates. This object _must_ be initialized with data, otherwise the contents of it
    * are not specified (garbage data or black, depending on driver behavior).
    * The number of mipmap levels is user given value and the size of the mipchain is computed
    * according to OpenGL specification (each further mipMap level has half the size of the previous
    * mipMap level). Refer to documentation of glTexStorage2D for more details.
    */
    class RAMSES_API Texture2DBuffer : public SceneObject
    {
    public:

        /**
        * @brief Update a subregion of the data of Texture2DBuffer. The caller is responsible to check that
        * the data has the correct size, i.e. the size of a texel times the number of texels specified in the
        * subregion of the texture face. Returns error if the specified subregion exceeds the size of the
        * target mipmap level.
        *
        * @param data               Pointer in memory to the data provided for update. The function makes
        *                           a copy of the data into Texture2DBuffer data structures. Texture2DBuffer
        *                           object does not take ownership of the memory data passed to it.
        * @param mipLevel           The level of the mipMap level which will receive the data. First mipMap is 0, second is 1 and so on
        * @param offsetX            The horizontal texel offset into the texture data
        * @param offsetY            The vertical texel offset into the texture data
        * @param width              The horizontal subregion size in texels
        * @param height             The vertical subregion size in texels
        * @return StatusOK for success, otherwise the returned status can be used
        *         to resolve error message using getStatusMessage().
        */
        status_t setData(const char* data, uint32_t mipLevel, uint32_t offsetX, uint32_t offsetY, uint32_t width, uint32_t height);

        /**
        * @brief Returns the number of mipmap levels created for the Texture2DBuffer (same as provided in
        * ramses::Scene::createTexture2DBuffer() )
        *
        * @return number of mipmap levels
        */
        uint32_t getMipLevelCount() const;

        /**
        * @brief Returns the size of a specific mipmap level in texels
        *
        * @param[in] mipLevel   The mipMap level of which the size will be returned
        * @param[out] widthOut  the width of the mipMap level which was specified
        * @param[out] heightOut the height of the mipMap level which was specified
        * @return StatusOK for success, otherwise the returned status can be used
        *         to resolve error message using getStatusMessage().
        */
        status_t getMipLevelSize(uint32_t mipLevel, uint32_t& widthOut, uint32_t& heightOut) const;

        /**
        * @brief Returns the size of a specific mipmap level in bytes
        *
        * @param[in] mipLevel   The mipMap level of which the size will be returned
        * @return Size of data in bytes for given mip level, 0 if mipLevel invalid
        */
        uint32_t getMipLevelDataSizeInBytes(uint32_t mipLevel) const;

        /**
        * @brief Returns the texel format provided at creation
        *
        * @return The texel format provided at creation
        */
        ETextureFormat getTexelFormat() const;

        /**
        * @brief Copies the data of a single mip-level into a user-provided buffer.
        *        The amount of data copied is \c bufferSize or \c getMipLevelDataSizeInBytes,
        *        whichever is smaller.
        *
        * @param[in] mipLevel   The mipMap level of which the data will be returned
        * @param[out] buffer The buffer where the mip data will be copied into
        * @param[in] bufferSize The size of given buffer in bytes
        * @return StatusOK for success, otherwise the returned status can be used
        *         to resolve error message using getStatusMessage().
        */
        status_t getMipLevelData(uint32_t mipLevel, char* buffer, uint32_t bufferSize) const;

        /**
        * Stores internal data for implementation specifics of Texture2DBuffer.
        */
        class Texture2DBufferImpl& impl;

    protected:
        /**
        * @brief Scene is the factory for creating Texture2DBuffer instances.
        */
        friend class SceneImpl;

        /**
        * @brief Constructor for Texture2DBuffer.
        *
        * @param[in] pimpl Internal data for implementation specifics of Texture2DBuffer (sink - instance becomes owner)
        */
        explicit Texture2DBuffer(Texture2DBufferImpl& pimpl);

        /**
        * @brief Destructor of the Texture2DBuffer
        */
        virtual ~Texture2DBuffer();
    };
}

#endif
