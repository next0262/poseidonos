#include "src/journal_manager/log_write/log_group_buffer_status.h"

#include <gtest/gtest.h>

namespace pos
{
static const uint64_t META_PAGE_SIZE = 4032;

TEST(LogGroupBufferStatus, Reset_testIfAllReset)
{
    LogGroupBufferStatus status(0, 0);
    status.Reset();

    EXPECT_EQ(status.GetSeqNum(), 0);
    EXPECT_EQ(status.GetNumLogsAdded(), 0);
    EXPECT_EQ(status.GetNumLogsFilled(), 0);
    EXPECT_EQ(status.GetNextOffset(), 0);
    EXPECT_EQ(status.GetStatus(), LogGroupStatus::INIT);
}

TEST(LogGroupBufferStatus, SetActive_testIfStatusChangedToActive)
{
    LogGroupBufferStatus status(0, 0);

    uint64_t seqNum = 1000;
    status.SetActive(1000);

    EXPECT_EQ(status.GetStatus(), LogGroupStatus::ACTIVE);
    EXPECT_EQ(status.GetSeqNum(), seqNum);
}

TEST(LogGroupBufferStatus, TryToAllocate_testIfAllocatedOffsetIsNotCrossingMetaPage)
{
    // Given: Initialized buffer status
    uint64_t maxOffset = 1024 * 1024;
    LogGroupBufferStatus status(maxOffset, META_PAGE_SIZE);

    // When: Try to allocate log
    uint64_t logSize = 52;

    // Then: Allocation should not cross the meta page
    for (int testCount = 0; testCount < 10; testCount++)
    {
        uint64_t allocatedOffset = 0;
        EXPECT_TRUE(status.TryToAllocate(logSize, allocatedOffset) == true);

        uint64_t startMpage = allocatedOffset / META_PAGE_SIZE;
        uint64_t endMpage = (allocatedOffset + logSize - 1) / META_PAGE_SIZE;

        EXPECT_TRUE(startMpage == endMpage);
    }
}

TEST(LogGroupBufferStatus, TryToAllocate_testIfAllocFailWithSizeLargerThanMetaPage)
{
    // Given: Initialized buffer status
    uint64_t maxOffset = 1024 * 1024;
    LogGroupBufferStatus status(maxOffset, META_PAGE_SIZE);

    // When: Try to allocate log size larger than meta page
    uint64_t logSize = META_PAGE_SIZE * 2;

    // Then: Allocation should be failed
    uint64_t allocatedOffset = 0;
    EXPECT_TRUE(status.TryToAllocate(logSize, allocatedOffset) == false);
}

TEST(LogGroupBufferStatus, TryToAllocate_testIfAllocFailsWhenFull)
{
    // Given: Initialized buffer status with small maxOffset
    uint64_t maxOffset = META_PAGE_SIZE;
    LogGroupBufferStatus status(maxOffset, META_PAGE_SIZE);

    uint64_t logSize = 52;

    // When: Log buffer offset is allocated
    int numTestsToMakeBufferFull = META_PAGE_SIZE / logSize;
    for (int testCount = 0; testCount < numTestsToMakeBufferFull; testCount++)
    {
        uint64_t offset = 0;
        EXPECT_TRUE(status.TryToAllocate(logSize, offset) == true);
    }

    // When: Try to allocate one more log
    // Then: Allocation should be failed
    uint64_t offset = 0;
    EXPECT_TRUE(status.TryToAllocate(logSize, offset) == false);
}

TEST(LogGroupBufferStatus, LogFilled_testIfLogFilled)
{
    // Given: Initialized buffer status
    uint64_t maxOffset = 1024 * 1024;
    LogGroupBufferStatus status(maxOffset, META_PAGE_SIZE);

    // When: Allocate logs 10 times, and notify log filled
    uint32_t logSize = 52;
    int numLogsToTest = 10;
    for (int testCount = 0; testCount < numLogsToTest; testCount++)
    {
        uint64_t offset = 0;
        EXPECT_EQ(status.TryToAllocate(logSize, offset), true);
    }
    for (int testCount = 0; testCount < numLogsToTest; testCount++)
    {
        status.LogFilled();
    }

    // Then: 10 logs should be filled
    EXPECT_EQ(status.GetNumLogsAdded(), numLogsToTest);
    EXPECT_EQ(status.GetNumLogsFilled(), numLogsToTest);
}

TEST(LogGroupBufferStatus, TryToSetFull_testIfSetFullSuccess)
{
    // Given: Initialized buffer status with small maxOffset
    uint64_t maxOffset = META_PAGE_SIZE;
    LogGroupBufferStatus status(maxOffset, META_PAGE_SIZE);

    uint64_t logSize = 52;

    // When: Try to allocate log buffer until it's full, and notify all logs are filled
    int numTestsToMakeBufferFull = META_PAGE_SIZE / logSize;
    uint64_t offset = 0;

    for (int testCount = 0; testCount < numTestsToMakeBufferFull; testCount++)
    {
        EXPECT_EQ(status.TryToAllocate(logSize, offset), true);
    }
    for (int testCount = 0; testCount < numTestsToMakeBufferFull; testCount++)
    {
        status.LogFilled();
    }

    // When: One more log try to allocate buffer, but fails
    EXPECT_EQ(status.TryToAllocate(logSize, offset), false);

    // Then: TryToSetFull should be succeed
    EXPECT_EQ(status.TryToSetFull(), true);
}

TEST(LogGroupBufferStatus, TryToSetFull_testIfSetFullFailWhenNotFullyFilled)
{
    // Given: Initialized buffer status with small maxOffset
    uint64_t maxOffset = META_PAGE_SIZE;
    LogGroupBufferStatus status(maxOffset, META_PAGE_SIZE);

    uint64_t logSize = 52;

    // When: Try to allocate log buffer until it's full, and notify all logs except the last one are filled
    int numTestsToMakeBufferFull = META_PAGE_SIZE / logSize;
    uint64_t offset = 0;

    for (int testCount = 0; testCount < numTestsToMakeBufferFull; testCount++)
    {
        EXPECT_EQ(status.TryToAllocate(logSize, offset), true);
    }
    for (int testCount = 0; testCount < numTestsToMakeBufferFull - 1; testCount++)
    {
        status.LogFilled();
    }

    // When: One more buffer allocation requested, and found there's no more space
    EXPECT_EQ(status.TryToAllocate(logSize, offset), false);

    // Then: TryToSetFull should not be succeed
    EXPECT_EQ(status.TryToSetFull(), false);

    // When: The last log is filled
    status.LogFilled();

    // Then: TryToSetFull should be succeed
    EXPECT_EQ(status.TryToSetFull(), true);
}

TEST(LogGroupBufferStatus, TryToSetFull_testIfSetFullFailWhenNotWaitingToBeFilled)
{
    // Given: Initialized buffer status with small maxOffset
    uint64_t maxOffset = META_PAGE_SIZE;
    LogGroupBufferStatus status(maxOffset, META_PAGE_SIZE);

    uint64_t logSize = 52;

    // When: Try to allocate log buffer until it's full, and notify all logs
    int numTestsToMakeBufferFull = META_PAGE_SIZE / logSize;
    uint64_t offset = 0;
    for (int testCount = 0; testCount < numTestsToMakeBufferFull; testCount++)
    {
        EXPECT_EQ(status.TryToAllocate(logSize, offset), true);
    }
    for (int testCount = 0; testCount < numTestsToMakeBufferFull; testCount++)
    {
        status.LogFilled();
    }

    // Then: TryToSetFull should not be succeed
    EXPECT_EQ(status.TryToSetFull(), false);

    // When: One more buffer allocation requested, and found there's no more space
    EXPECT_EQ(status.TryToAllocate(logSize, offset), false);

    // Then: TryToSetFull should be succeed
    EXPECT_EQ(status.TryToSetFull(), true);
}
} // namespace pos
