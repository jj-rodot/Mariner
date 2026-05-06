#include "services/m_Directory.h"
#include <CoreFoundation/CoreFoundation.h>

namespace Mariner {

    namespace Services {

        m_Directory* m_Directory::New() {

            static m_Directory* Instance = new m_Directory();
            Instance->Name = "DirectoryService";
            Instance->ClassName = "m_Directory";
            return Instance;

        }

        Mariner::Libraries::m_String m_Directory::GetContentDirectory() {

            CFBundleRef AppBundleReference = CFBundleGetMainBundle();
            CFURLRef AppBundlePath = CFBundleCopyResourcesDirectoryURL(AppBundleReference);

            UInt8 Buff[496];
            CFURLGetFileSystemRepresentation(AppBundlePath, true, Buff, sizeof(Buff));

            CFRelease(AppBundlePath);
            return Mariner::Libraries::m_String(reinterpret_cast<const char*>(Buff)) + "/content";

        };

        Mariner::Libraries::m_String m_Directory::GetVendoredDirectory() {

            CFBundleRef AppBundleReference = CFBundleGetMainBundle();
            CFURLRef AppBundlePath = CFBundleCopyResourcesDirectoryURL(AppBundleReference);

            UInt8 Buff[496];
            CFURLGetFileSystemRepresentation(AppBundlePath, true, Buff, sizeof(Buff));

            CFRelease(AppBundlePath);
            return Mariner::Libraries::m_String(reinterpret_cast<const char*>(Buff)) + "/libraries";

        };

    }

}