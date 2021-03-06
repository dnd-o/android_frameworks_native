/*
 * Copyright 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_DVR_HARDWARE_COMPOSER_IMPL_VR_COMPOSER_CLIENT_H
#define ANDROID_DVR_HARDWARE_COMPOSER_IMPL_VR_COMPOSER_CLIENT_H

#include <android/frameworks/vr/composer/1.0/IVrComposerClient.h>
#include <ComposerClient.h>
#include <IComposerCommandBuffer.h>

namespace android {
namespace dvr {

class VrHwc;

using hardware::graphics::common::V1_0::PixelFormat;
using hardware::graphics::composer::V2_1::implementation::ComposerClient;

class VrComposerClient : public ComposerClient {
 public:
  VrComposerClient(android::dvr::VrHwc& hal);
  virtual ~VrComposerClient();

 private:
  class VrCommandReader : public ComposerClient::CommandReader {
   public:
    VrCommandReader(VrComposerClient& client);
    ~VrCommandReader() override;

    bool parseCommand(IComposerClient::Command command,
                      uint16_t length) override;

   private:
    bool parseSetLayerInfo(uint16_t length);
    bool parseSetClientTargetMetadata(uint16_t length);
    bool parseSetLayerBufferMetadata(uint16_t length);

    IVrComposerClient::BufferMetadata readBufferMetadata();

    VrComposerClient& mVrClient;
    android::dvr::VrHwc& mVrHal;

    VrCommandReader(const VrCommandReader&) = delete;
    void operator=(const VrCommandReader&) = delete;
  };

  std::unique_ptr<CommandReader> createCommandReader() override;

  dvr::VrHwc& mVrHal;

  VrComposerClient(const VrComposerClient&) = delete;
  void operator=(const VrComposerClient&) = delete;
};

} // namespace dvr
} // namespace android

#endif  // ANDROID_DVR_HARDWARE_COMPOSER_IMPL_VR_COMPOSER_CLIENT_H
