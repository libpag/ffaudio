/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Tencent is pleased to support the open source community by making libpag available.
//
//  Copyright (C) 2025 THL A29 Limited, a Tencent company. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
//  except in compliance with the License. You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  unless required by applicable law or agreed to in writing, software distributed under the
//  license is distributed on an "as is" basis, without warranties or conditions of any kind,
//  either express or implied. see the license for the specific language governing permissions
//  and limitations under the license.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "ffaudio.h"
#include "AudioMuxerImpl/AudioMuxerImpl.h"

AudioMuxer::AudioMuxer() : impl(std::make_unique<AudioMuxerImpl>()) {}

AudioMuxer::~AudioMuxer() {}

bool AudioMuxer::init(std::string& outputPath, int channel, int sampleRate) {
    return impl->init(outputPath, channel, sampleRate);
}

void AudioMuxer::close() {
    impl->close();
}

int AudioMuxer::putData(int16_t* data, int numSamples) {
    return impl->putData(data, numSamples);
}

std::string AudioMuxer::getFilename() {
    return impl->getFilename();
}