/*
* Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/

#include <aws/polly-to-output/windows/WaveOutPCMOutputDriver.h>
#include <aws/core/utils/StringUtils.h>

#include <windows.h>

using namespace Aws::Utils;

static void CALLBACK waveOutProc(HWAVEOUT waveOut, UINT uMsg, DWORD_PTR, DWORD_PTR dwParam1, DWORD_PTR)
{
    switch (uMsg)
    {
    case WOM_CLOSE:
        return;
    case WOM_DONE:
        waveOutUnprepareHeader(waveOut, (WAVEHDR*)dwParam1, sizeof(WAVEHDR));
        Aws::DeleteArray(((WAVEHDR*)dwParam1)->lpData);
        Aws::Delete((WAVEHDR*)dwParam1);
        return;
    case WOM_OPEN:
        return;
    default:
        return;

    }
}

namespace Aws
{
    namespace PollyToOutput
    {
        static const char* CLASS_TAG = "WaveOutPCMOutputDriver";

        WaveOutPCMOutputDriver::WaveOutPCMOutputDriver() : m_waveOut(nullptr) {}

        void WaveOutPCMOutputDriver::WriteBufferToDevice(const unsigned char* buffer, size_t size)
        {
            InitDevice();

            WAVEHDR* waveHdr = Aws::New<WAVEHDR>(CLASS_TAG);
            char* buf = Aws::NewArray<char>(size, CLASS_TAG);
            memcpy(buf, buffer, size);
            waveHdr->lpData = buf;
            waveHdr->dwBufferLength = static_cast<DWORD>(size);
            waveHdr->dwFlags = 0;
            waveHdr->dwLoops = 0;
            waveHdr->dwUser = NULL;

            auto res = waveOutPrepareHeader(m_waveOut, waveHdr, sizeof(WAVEHDR));

            res = waveOutWrite(m_waveOut, waveHdr, sizeof(WAVEHDR));
        }

        const char* WaveOutPCMOutputDriver::GetName() const
        {
            return "Win32 WaveOut";
        }

        void WaveOutPCMOutputDriver::InitDevice()
        {
            if (!m_isInit)
            {
                if (m_waveOut)
                {
                    waveOutClose(m_waveOut);
                    m_waveOut = nullptr;
                }

                WAVEFORMATEX format;
                format.nChannels = static_cast<WORD>(m_selectedCaps.channels);
                format.nSamplesPerSec = static_cast<DWORD>(m_selectedCaps.sampleRate);
                format.wBitsPerSample = static_cast<WORD>(m_selectedCaps.sampleWidthBits);
                format.wFormatTag = WAVE_FORMAT_PCM;
                format.nBlockAlign = (format.nChannels * format.wBitsPerSample) / 8;
                format.cbSize = 0;
                format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;

                if (m_activeDevice.deviceId.empty())
                {
                    auto res = waveOutOpen(&m_waveOut, WAVE_MAPPER, &format, (DWORD_PTR)&waveOutProc, NULL, 
                        CALLBACK_FUNCTION | WAVE_ALLOWSYNC | WAVE_MAPPED_DEFAULT_COMMUNICATION_DEVICE | WAVE_ALLOWSYNC);
                    m_isInit = !res;
                }
                else
                {
                    unsigned id = static_cast<unsigned>(StringUtils::ConvertToInt32(m_activeDevice.deviceId.c_str()));
                    auto res = waveOutOpen(&m_waveOut, id, &format, (DWORD_PTR)&waveOutProc, NULL,
                        CALLBACK_FUNCTION | WAVE_ALLOWSYNC | WAVE_ALLOWSYNC);
                    m_isInit = !res;
                }
            }
        }

        void WaveOutPCMOutputDriver::SetActiveDevice(const DeviceInfo& device, const CapabilityInfo& caps)
        { 
            m_activeDevice = device; 
            m_selectedCaps = caps; 
            m_isInit = false; 
            InitDevice(); 
        }

        Aws::Vector<DeviceInfo> WaveOutPCMOutputDriver::EnumerateDevices() const
        {
            Aws::Vector<DeviceInfo> devices;

            auto deviceCount = waveOutGetNumDevs();

            for (UINT i = 0; i < deviceCount; ++i)
            {
                WAVEOUTCAPSA waveoutCaps;
                auto res = waveOutGetDevCapsA(i, &waveoutCaps, sizeof(WAVEOUTCAPSA));

                if (!res)
                {
                    DeviceInfo devInfo;
                    devInfo.deviceId = StringUtils::to_string(i);
                    devInfo.deviceName = waveoutCaps.szPname;                

                    if ((waveoutCaps.dwFormats & WAVE_FORMAT_1M16) == WAVE_FORMAT_1M16)
                    {
                        CapabilityInfo capsInfo;                        
                        capsInfo.channels = 1;
                        capsInfo.sampleRate = 8000;
                        capsInfo.sampleWidthBits = 16;

                        devInfo.capabilities.push_back(capsInfo);

                        capsInfo.channels = 1;
                        capsInfo.sampleRate = 16000;
                        capsInfo.sampleWidthBits = 16;

                        devInfo.capabilities.push_back(capsInfo);
                    }

                    if ((waveoutCaps.dwFormats & WAVE_FORMAT_2M16) == WAVE_FORMAT_2M16)
                    {
                        CapabilityInfo capsInfo;
                        capsInfo.channels = 1;
                        capsInfo.sampleRate = 22050;
                        capsInfo.sampleWidthBits = 16;

                        devInfo.capabilities.push_back(capsInfo);
                    }

                    devices.push_back(devInfo);
                }
            }

            return devices;
        }
    }
}