#include <gmock/gmock.h>

#include <list>
#include <string>
#include <vector>

#include "src/volume/i_volume_event_manager.h"

namespace pos
{
class MockIVolumeEventManager : public IVolumeEventManager
{
public:
    using IVolumeEventManager::IVolumeEventManager;
    MOCK_METHOD(int, Create, (std::string name, uint64_t size, uint64_t maxiops, uint64_t maxbw), (override));
    MOCK_METHOD(int, Delete, (std::string name), (override));
    MOCK_METHOD(int, Mount, (std::string name, std::string subnqn), (override));
    MOCK_METHOD(int, Unmount, (std::string name), (override));
    MOCK_METHOD(int, UpdateQoS, (std::string name, uint64_t maxiops, uint64_t maxbw, uint64_t miniops, uint64_t minbw), (override));
    MOCK_METHOD(int, Rename, (std::string oldname, std::string newname), (override));
    MOCK_METHOD(void, DetachVolumes, (), (override));   
};

} // namespace pos
