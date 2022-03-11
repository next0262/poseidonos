/*
 *   BSD LICENSE
 *   Copyright (c) 2021 Samsung Electronics Corporation
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Samsung Electronics Corporation nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#define EID(X) ((int)POS_EVENT_ID::X)

#include <unordered_map>
#include <string>

enum class POS_EVENT_ID
{
    // ------------------- PoseidonOS (0 - 999) -------------------
    SUCCESS = 0,
    POS_STARTED,
    POS_TERMINATED,
    POS_EVENT_ID_END = 999,

    // ------------------- CLI Server (1200 - 1599) -------------------
    CLI_EVENT_ID_START = 1200,
    CLI_SERVER_INITIALIZED,
    CLI_CLIENT_CREATED,
    CLI_CLIENT_CREATION_FAILURE,
    CLI_CLIENT_DETACHED,
    CLI_CLIENT_DETACHEMENT_FAILURE,
    CLI_CLIENT_ACCEPTED,
    CLI_CLIENT_DISCONNECTED,
    CLI_MSG_RECEIVED,
    CLI_MSG_SENT,
    CLI_MSG_SENDING_FAILURE,
    CLI_SERVER_FINISH,
    CLI_SERVER_THREAD_JOINED,
    CLI_REUSE_ADDR_ENABLED,
    CLI_REUSE_ADDR_FAILURE,
    CLI_SOCK_CREATE_FAILURE,
    CLI_SOCK_BIND_FAILURE,
    CLI_SOCK_LISTEN_FAILURE,
    CLI_EPOLL_CREATE_FAILURE,
    CLI_SOCK_ACCEPT_FAILURE,
    CLI_ADD_CLIENT_FAILURE_MAX_CLIENT,
    CLI_MSG_RECEIVE_FAILURE,
    CLI_SERVER_TIMED_OUT,
    CLI_SERVER_BUSY,
    CLI_LIST_ARRAY_NO_ARRAY_EXISTS,
    CLI_LIST_ARRAY_FAILURE,
    CLI_ADD_DEVICE_FAILURE,
    CLI_ADD_DEVICE_FAILURE_NO_SPARE,
    CLI_ADD_DEVICE_SUCCESS,
    CLI_ADD_LISTENER_FAILURE,
    CLI_ADD_LISTENER_SUCCESS,
    CLI_APPLY_FILTER_FAILURE,
    CLI_APPLY_FILTER_SUCCESS,
    CLI_ARRAY_INFO_NO_ARRAY_NAME,
    CLI_ARRAY_INFO_ARRAY_NOT_EXIST,
    CLI_AUTOCREATE_ARRAY_FAILURE,
    CLI_AUTOCREATE_ARRAY_SUCCESS,
    CLI_EVENT_ID_END = 1599,

    INVALID_PARAM,
    SYSTEM_RECOVERY,
    STATE_CONTEXT_UPDATED,
    STATE_CHANGED,
    STATE_CONTROL_ADDED,
    STATE_CONTROL_REMOVED,
    STATE_CONTROL_DEBUG,

    // ---------------Volume (2000)-----------------------
    VOL_CREATED = 2000,
    VOL_DELETED = 2001,
    VOL_MOUNTED = 2002,
    VOL_UNMOUNTED = 2003,
    VOL_ADDED = 2004,
    VOL_REMOVED = 2005,
    VOL_NOT_EXIST = 2010,
    VOL_CNT_EXCEEDED = 2011,
    VOL_SIZE_EXCEEDED = 2012,
    VOL_DELETE_FAILED = 2013,
    VOL_CREATE_FAILED = 2014,

    VOL_NAME_TOO_SHORT = 2020,
    VOL_NAME_TOO_LONG = 2021,
    VOL_NAME_DUPLICATED = 2022,
    VOL_NAME_NOT_ALLOWED = 2023,

    VOL_SIZE_TOO_BIG = 2030,
    VOL_SIZE_TOO_SMALL = 2031,
    VOL_SIZE_NOT_ALIGNED = 2032,

    VOL_ALD_MOUNTED = 2040,
    VOL_ALD_UNMOUNTED = 2041,

    DEL_MOUNTED_VOL = 2050,

    META_CREATE_FAIL = 2060,
    META_OPEN_FAIL = 2061,
    META_READ_FAIL = 2062,
    META_WRITE_FAIL = 2063,
    META_CONTENT_BROKEN = 2064,

    MEM_ALLOC_FAIL = 2070,
    INVALID_INDEX = 2071,
    VOLID_ALLOC_FAIL = 2072,
    VOL_SAMEID_EXIST = 2073,
    VOL_UNEXPECTED_PENDING_IO_COUNT = 2074,

    OUT_OF_QOS_RANGE = 2080,

    ARRAY_NOT_MOUNTED = 2090,
    SYSTEM_FAULT = 2091,
    DONE_WITH_ERROR = 2092,

    SUBSYSTEM_NOT_CREATED = 2100,
    VOL_ALD_SET_SUBNQN = 2101,
    CANNOT_EXTEND_NSID = 2102,
    VOL_UNMOUNT_FAIL = 2103,
    VOL_DETACH_FAIL = 2104,
    SUBSYSTEM_ALREADY_SET_ARRAY = 2105,
    SUBSYSTEM_ARRAY_DOES_NOT_MATCH_VOLUME_ARRAY = 2106,

    VOL_DATA_SIZE_TOO_BIG = 2110,
    VOL_DATA_SIZE_TOO_SMALL = 2111,
    INVALID_VOL_ID_ERROR = 2112,

    INVALID_VOL_MGR = 2120,

    VOL_EVENT_OK = 2130,
    VOL_EVENT_ABORTED,
    VOL_EVENT_DATA_LOSS,
    VOL_EVENT_DEAD_LINE_EXCEEDED,
    VOL_EVENT_RETRY,
    VOL_EVENT_UNIMPLEMENTED,
    VOL_EVENT_UNKNOWN,
    VOL_EVENT_FAIL,
    VOL_EVENT_ROLLBACK_FAIL,

    // --------------Mbr (2300)-----------------------
    MBR_START = 2300,
    MBR_ALLOCATE_MEMORY = MBR_START,
    MBR_CREATE_AND_WRITE,
    MBR_ADD_AND_WRITE,
    MBR_WRITE_DONE,
    MBR_READ_DONE,
    MBR_PARITY_CHECK,
    MBR_SYSTEM_UUID_CHECK,
    MBR_DEVICE_NOT_FOUND = 2310,
    MBR_PARITY_CHECK_FAILED,
    MBR_SYSTEM_UUID_CHECK_FAILED,
    MBR_DATA_NOT_FOUND,
    MBR_KEY_NOT_FOUND,
    MBR_ABR_NOT_FOUND,
    MBR_DELETE_ABR_FAILED,
    MBR_MAX_ARRAY_CNT_EXCEED,
    MBR_ABR_ALREADY_EXIST,
    MBR_WRONG_ARRAY_VALID_FLAG,
    MBR_WRONG_ARRAY_INDEX_MAP,
    MBR_DEVICE_ALREADY_IN_ARRAY,
    MBR_ABR_LIST_SUCCESS,
    MBR_ALLOCATE_MEMORY_FAILED = 2330,
    MBR_DATA_SIZE_ERROR,
    MBR_FORMAT_ERROR,
    MBR_GET_SYSTEM_UUID_FAILED,
    MBR_DEBUG_MSG = 2399,
    MBR_WRITE_ERROR,
    MBR_END,
    MBR_COUNT = MBR_END - MBR_START,

    // --------------Array (2500)-----------------------
    CREATE_ARRAY_DEBUG_MSG = 2500,
    CREATE_ARRAY_EXCEED_MAX_NUM_OF_ARRAYS = 2501,
    CREATE_ARRAY_SAME_ARRAY_NAME_EXISTS = 2502,
    CREATE_ARRAY_NAME_TOO_SHORT = 2503,
    CREATE_ARRAY_NAME_TOO_LONG = 2504,
    CREATE_ARRAY_NAME_INCLUDES_SPECIAL_CHAR = 2505,
    CREATE_ARRAY_NAME_START_OR_END_WITH_SPACE = 2506,
    CREATE_ARRAY_SSD_NAME_NOT_FOUND = 2507,
    CREATE_ARRAY_NVM_NAME_NOT_FOUND = 2508,
    CREATE_ARRAY_NOT_SUPPORTED_RAIDTYPE = 2509,
    CREATE_ARRAY_RAID_INVALID_SSD_CNT = 2510,
    CREATE_ARRAY_RAID_DOES_NOT_SUPPORT_SPARE_DEV = 2511,
    CREATE_ARRAY_NO_AVAILABLE_DEVICE = 2512,
    CREATE_ARRAY_SSD_CAPACITY_IS_LT_MIN = 2513,
    CREATE_ARRAY_NVM_CAPACITY_IS_LT_MIN = 2514,
    CREATE_ARRAY_UNABLE_TO_CREATE_NVM_PARTITION = 2515,
    CREATE_ARRAY_UNABLE_TO_CREATE_SSD_PARTITION = 2516,
    CREATE_ARRAY_INSUFFICIENT_MEMORY_UNABLE_TO_ALLOC_PARITY_POOL = 2517,
    CREATE_ARRAY_INSUFFICIENT_NUMA_DEVS = 2518,

    LOAD_ARRAY_DEBUG_MSG = 2530,
    LOAD_ARRAY_NVM_DOES_NOT_EXIST = 2531,
    LOAD_ARRAY_SSD_DOES_NOT_EXIST = 2532,
    LOAD_ARRAY_ALREADY_LOADED = 2533,
    LOAD_ARRAY_CAN_ONLY_BE_WHILE_OFFLINE = 2534,
    LOAD_ARRAY_BROKEN_ARRAY_CANNOT_BE_LOADED = 2535,

    DELETE_ARRAY_DEBUG_MSG = 2550,
    DELETE_ARRAY_CAN_ONLY_BE_WHILE_OFFLINE = 2551,
    DELETE_ARRAY_ARRAY_NAME_DOES_NOT_EXIST = 2552,
    DELETE_ARRAY_TIMED_OUT = 2553,

    MOUNT_ARRAY_DEBUG_MSG = 2570,
    MOUNT_ARRAY_UNABLE_TO_INVOKE_MOUNT_STATE = 2571,
    MOUNT_ARRAY_ALREADY_MOUNTED = 2572,
    MOUNT_ARRAY_ARRAY_NAME_DOES_NOT_EXIST = 2573,
    MOUNT_ARRAY_UNABLE_TO_REGISTER_ARRAY_SERVICE = 2574,
    MOUNT_ARRAY_BROKEN_ARRAY_CANNOT_BE_MOUNTED = 2575,

    UNMOUNT_ARRAY_DEBUG_MSG = 2590,
    UNMOUNT_ARRAY_ALREADY_UNMOUNTED = 2591,
    UNMOUNT_ARRAY_UNABLE_TO_INVOKE_UNMOUNT_STATE = 2592,
    UNMOUNT_ARRAY_ARRAY_NAME_DOES_NOT_EXIST = 2593,
    UNMOUNT_ARRAY_REJECTED_DUE_TO_REBUILD_INPROGRESS = 2594,
    UNMOUNT_BROKEN_ARRAY_DEBUG_MSG = 2595,

    ADD_SPARE_DEBUG_MSG = 2610,
    ADD_SPARE_CAN_ONLY_BE_WHILE_ONLINE = 2611,
    ADD_SPARE_SSD_NAME_NOT_FOUND = 2612,
    ADD_SPARE_CAPACITY_IS_TOO_SMALL = 2613,
    ADD_SPARE_RAID_DOES_NOT_SUPPORT_SPARE_DEV = 2614,
    REMOVE_SPARE_DEBUG_MSG = 2615,
    REMOVE_SPARE_CAN_ONLY_BE_WHILE_ONLINE = 2616,
    REMOVE_SPARE_DEV_NAME_NOT_FOUND = 2617,

    ARRAY_DEV_DEBUG_MSG = 2620,
    ABR_ARRAY_NOT_FOUND = 2621,
    ARRAY_SSD_NOT_FOUND = 2622,
    ARRAY_NVM_NOT_FOUND = 2623,
    UNABLE_TO_SET_NVM_MORE_THAN_ONE = 2624,
    UNABLE_TO_SET_NULL_NVM = 2625,
    UNABLE_TO_SET_NVM_ALREADY_OCCUPIED = 2626,
    UNABLE_TO_SET_NVM_CAPACITY_IS_LT_MIN = 2627,
    UNABLE_TO_ADD_SSD_ALREADY_OCCUPIED = 2631,

    UPDATE_ABR_DEBUG_MSG = 2641,
    ARRAY_INFO_DEBUG_MSG = 2642,
    ARRAY_COMPO_DEBUG_MSG = 2643,
    RAID_DEBUG_MSG = 2644,
    FORMAT_PARTITION_DEBUG_MSG = 2645,
    REBUILD_ARRAY_DEBUG_MSG = 2646,
    IO_RECOVER_DEBUG_MSG = 2647,
    LOCKER_DEBUG_MSG = 2648,
    IO_TRANSLATOR_NOT_FOUND = 2650,
    IO_RECOVER_NOT_FOUND = 2651,

    ARRAY_MGR_DEBUG_MSG = 2670,
    ARRAY_MGR_NO_ARRAY_MATCHING_REQ_NAME = 2671,
    ARRAY_MGR_NO_ARRAY_OWNING_REQ_DEV = 2672,

    RECOVER_INVALID_LBA = 2680,
    RECOVER_REQ_DEV_NOT_FOUND = 2681,
    ADDRESS_TRANSLATE_DEBUG_MSG = 2682,
    ADDRESS_TRANSLATION_INVALID_LBA = 2683,
    ADDRESS_TRANSLATION_INVALID_BLK_CNT = 2684,
    ADDRESS_BYTE_TRANSLATION_INVALID_LBA = 2685,
    ADDRESS_BYTE_TRANSLATION_IS_NOT_SUPPORTED = 2686,

    ARRAY_EVENT_STATE_CHANGED = 2700,
    ARRAY_EVENT_UNHANDLED_STATE_TRANSITION = 2701,
    ARRAY_EVENT_BROKEN = 2702,
    ARRAY_EVENT_DEV_STATE_CHANGED = 2703,
    ARRAY_EVENT_DEV_DETACHED = 2704,
    ARRAY_EVENT_DATA_SSD_DETACHED = 2705,
    ARRAY_EVENT_SPARE_SSD_DETACHED = 2706,
    ARRAY_EVENT_NVM_DETACHED = 2707,
    ARRAY_EVENT_SSD_REPLACED = 2708,
    NO_SPARE_SSD_TO_REPLACE = 2709,

    ARRAY_TELEMETRY_DEBUG_MSG = 2750,

    STOP_POS_REJECTED_DUE_TO_MOUNTED_ARRAY_EXISTS = 2790,
    WBT_CMD_NEED_ARRAY_MOUNT = 2791,

    // --------------Rebuilder (2800)----------------
    REBUILD_START = 2800,
    REBUILD_DEBUG_MSG = REBUILD_START,
    REBUILD_STOPPED = 2802,
    REBUILD_FAILED = 2803,
    REBUILD_PROGRESS = 2804,
    REBUILD_PROGRESS_DETAIL = 2805,
    REBUILD_STRIPE_LOCK = 2806,
    REBUILD_STRIPE_UNLOCK = 2807,
    REBUILD_RESULT_PASS = 2810,
    REBUILD_RESULT_FAILED = 2811,
    REBUILD_RESULT_CANCELLED = 2812,
    REBUILD_TRIGGER_FAIL = 2813,
    REBUILD_INVALIDATED = 2814,
    REBUILD_RECORD = 2850,
    REBUILD_END,
    REBUILD_COUNT = REBUILD_END - REBUILD_START,

    // --------------CONFIG (2900)----------------
    CONFIG_START = 2900,
    CONFIG_FILE_READ_DONE = CONFIG_START,

    CONFIG_REQUEST_CONFIG_TYPE_ERROR = 2910,
    CONFIG_REQUEST_KEY_ERROR,
    CONFIG_REQUEST_MODULE_ERROR,

    CONFIG_FILE_OPEN_FAIL = 2920,
    CONFIG_FILE_SIZE_ERROR,
    CONFIG_FILE_READ_ERROR,
    CONFIG_FILE_FORMAT_ERROR,
    CONFIG_JSON_DOC_IS_NOT_OBJECT,
    CONFIG_VALUE_TYPE_ERROR,

    CONFIG_END,
    CONFIG_COUNT = CONFIG_END - CONFIG_START,

    // --------------Journal manager (3000)----------------
    JOURNAL_START = 3000,
    JOURNAL_MANAGER_INITIALIZED = JOURNAL_START,
    JOURNAL_MANAGER_NOT_INITIALIZED = 3001,
    JOURNAL_CONFIGURATION = 3002,
    JOURNAL_NOT_READY = 3003,
    JOURNAL_ALREADY_EXIST = 3004,
    JOURNAL_INVALID = 3005,

    // Journal log buffer (3010)
    JOURNAL_LOG_BUFFER_CREATED = 3010,
    JOURNAL_LOG_BUFFER_CREATE_FAILED = 3011,
    JOURNAL_LOG_BUFFER_LOADED = 3012,
    JOURNAL_LOG_BUFFER_RESET = 3013,
    JOURNAL_LOG_BUFFER_RESET_FAILED = 3014,
    JOURNAL_LOG_BUFFER_OPEN_FAILED = 3015,
    JOURNAL_LOG_BUFFER_CLOSE_FAILED = 3016,
    JOURNAL_LOG_BUFFER_READ_FAILED = 3017,

    // Write logs (3020)
    JOURNAL_LOG_WRITE_FAILED = 3020,
    JOURNAL_INVALID_SIZE_LOG_REQUESTED = 3021,
    ADD_TO_JOURNAL_WAITING_LIST = 3022,
    JOURNAL_CALLBACK_FAILED = 3023,
    JOURNAL_NO_LOG_BUFFER_AVAILABLE = 3024,

    // Checkpoint (3030)
    JOURNAL_LOG_GROUP_FULL = 3030,
    JOURNAL_FLUSH_LOG_GROUP = 3031,
    JOURNAL_CHECKPOINT_STARTED = 3032,
    JOURNAL_CHECKPOINT_STATUS = 3033,
    JOURNAL_CHECKPOINT_COMPLETED = 3034,
    JOURNAL_CHECKPOINT_FAILED = 3035,
    JOUNRAL_WRITE_LOG_GROUP_FOOTER = 3036,
    JOURNAL_CHECKPOINT_IN_PROGRESS = 3037,

    // Journaling system events (3040)
    JOURNAL_HANDLE_VOLUME_DELETION = 3040,

    // Replay journal (3050)
    JOURNAL_REPLAY_STARTED = 3050,
    JOURNAL_REPLAY_STATUS = 3051,
    JOURNAL_REPLAY_STOPPED = 3052,
    JOURNAL_REPLAY_FAILED = 3053,
    JOURNAL_REPLAY_COMPLETED = 3054,
    JOURNAL_INVALID_LOG_FOUND = 3055,

    JOURNAL_REPLAY_STRIPE_FLUSH = 3060,
    JOURNAL_REPLAY_STRIPE_FLUSH_FAILED = 3061,
    JOURNAL_REPLAY_WB_TAIL = 3062,
    JOURNAL_REPLAY_USER_STRIPE_TAIL = 3063,
    JOURNAL_REPLAY_VOLUME_EVENT = 3064,

    JOURNAL_DEBUG = 3099,
    JOURNAL_END = JOURNAL_DEBUG,
    JOURNAL_COUNT = JOURNAL_END - JOURNAL_START,

    // --------------Mapper (3100)----------------
    MAPPER_START = 3100,

    MAPPER_SUCCESS = MAPPER_START,
    MAP_FLUSH_STARTED,
    MAP_FLUSH_IN_PROGRESS,
    MAP_FLUSH_ONGOING,
    MAP_FLUSH_COMPLETED,

    MAP_LOAD_STARTED,
    MAP_LOAD_ONGOING,
    MAP_LOAD_COMPLETED,
    MPAGE_NULLPTR,
    MPAGE_ALREADY_EXIST,

    MPAGE_MEMORY_ALLOC_FAILURE,
    VSAMAP_NULL_PTR,
    VSAMAP_SET_FAILURE,
    STRIPEMAP_SET_FAILURE,
    MAPCONTENT_HEADER_NOT_INITIALIZED,

    INVALID_VOLUME_ID,
    REVMAP_GET_MFS_ALIGNED_IOSIZE_FAILURE,
    REVMAP_PACK_ALREADY_LINKED,
    REVMAP_NOT_LINKED_PACK,
    REVMAP_FILE_SIZE,
    REVMAP_VOLUME_ID_FOUND,
    REVMAP_VOLUME_ID_NOT_FOUND,

    REVMAP_MFS_IO_ERROR,
    MAP_UPDATE_HANDLER_EVENT_ALLOCATE_FAIL,
    TRIED_TO_LOAD_WITHOUT_MFSFILE,
    NO_BLOCKMAP_MFS_FILE,
    VSAMAP_HEADER_LOAD_FAILURE,

    VSAMAP_LOAD_FAILURE,
    VSAMAP_NOT_LOADED,
    VSAMAP_UNMOUNT_FAILURE,
    VSAMAP_INVALIDATE_ALLBLKS_FAILURE,
    VSAMAP_UNLOAD_FAILURE,

    VSAMAP_STORE_FAILURE,
    STRIPEMAP_STORE_FAILURE,
    MFS_SYNCIO_ERROR,
    MFS_ASYNCIO_ERROR,
    VSAMAP_NOT_ACCESSIBLE,
    DELETE_VOLUME,
    FILE_NOT_EXIST,
    NEED_TO_INITIAL_STORE,

    WRONG_MAP_ID,
    MAPPER_ALREADY_EXIST,
    MAPPER_FAILED,
    MAPPER_END,
    MAPPER_COUNT = MAPPER_END - MAPPER_START,

    // --------------Allocator (3150)----------------
    ALLOCATOR_START = 3150,

    ALLOCATOR_META_ARCHIVE_STORE = ALLOCATOR_START,
    ALLOCATOR_META_ARCHIVE_LOAD,
    ALLOCATOR_META_ARCHIVE_STORE_REBUILD_SEGMENT,
    ALLOCATOR_META_ARCHIVE_LOAD_REBUILD_SEGMENT,
    ALLOCATOR_META_ARCHIVE_FLUSH_IN_PROGRESS,

    ALLOCATOR_MAKE_REBUILD_TARGET,
    ALLOCATOR_MAKE_REBUILD_TARGET_FAILURE,
    ALLOCATOR_TARGET_SEGMENT_FREED,
    ALLOCATOR_REBUILD_TARGET_SET_NOT_EMPTY,
    ALLOCATOR_REBUILD_TARGET_SET_EMPTY,

    ALLOCATOR_NO_FREE_WB_STRIPE,
    ALLOCATOR_REBUILD_CTX_LOADED,
    ALLOCATOR_REBUILD_SEGMENT_COMPLETED,
    ALLOCATOR_NO_FREE_SEGMENT,
    ALLOCATOR_WRONG_STRIPE_REFERENCE_COUNT,

    ALLOCATOR_CANNOT_ALLOCATE_USER_BLOCK,
    ALLOCATOR_CANNOT_ALLOCATE_STRIPE,
    ALLOCATOR_CANNOT_LINK_REVERSE_MAP,
    ALLOCATOR_STRIPE_WITHOUT_REVERSEMAP,
    ALLOCATOR_RECONSTRUCT_STRIPE,

    ALLOCATOR_REPLAYED_STRIPE_IS_FULL,
    ALLOCATOR_REPLAY_SEGMENT_STATUS,
    ALLOCATOR_TRIGGER_FLUSH,
    REVMAP_RECONSTRUCT_FOUND_RBA,
    REVMAP_RECONSTRUCT_NOT_FOUND_RBA,

    GET_VOLUMESIZE_FAILURE,
    WRONG_BLOCK_COUNT,
    PICKUP_ACTIVE_STRIPE,
    SEGMENT_WAS_VICTIM,
    ALLOCATOR_SEGMENT_FREED,
    VALID_COUNT_UNDERFLOWED,
    VALID_COUNT_OVERFLOWED,
    FAILED_TO_ISSUE_ASYNC_METAIO,
    ERROR_REINIT_WITHOUT_DISPOSE,
    ALLOCATOR_FILE_ERROR,
    GC_STRIPE_ALLOCATED,
    ALLOCATE_GC_VICTIM,
    ALLOCATOR_CURRENT_GC_MODE,
    ALLOCATOR_META_ASYNCLOAD,
    TELEMETRY_CLIENT_ERROR,
    UNKNOWN_ALLOCATOR_ERROR,

    ALLOCATOR_DEBUG,
    ALLOCATOR_END,
    ALLOCATOR_COUNT = ALLOCATOR_END - ALLOCATOR_START,

    // --------------Metadata (3200)----------------
    META_START = 3200,
    META_INITIALIZED = META_START,
    META_NOT_INITIALIZED = 3201,
    META_ALREADY_REGISTERED = 3202,

    META_END,
    META_COUNT = META_END - META_START,

    // --------------Garbage collector (3400)----------------
    GC_START = 3400,
    GC_TRIGGERED = GC_START,
    GC_STARTED = 3401,
    GC_DONE = 3402,
    GC_CANNOT_START = 3403,
    GC_VICTIM_STRIPE_CONSTRUCTOR = 3410,
    GC_LOAD_REVERSE_MAP = 3411,
    GC_LOAD_VALID_BLOCKS = 3412,
    GC_GET_UNMAP_VSA = 3413,
    GC_GET_UNMAP_LSA = 3414,
    GC_GET_VICTIM_SEGMENT = 3415,
    GC_GET_VALID_BLOCKS = 3416,
    GC_GET_VALID_BLOCK_INFO = 3417,
    GC_COPY_COMPLETE = 3418,
    GC_GET_BUFFER_FAILED = 3419,
    GC_STRIPE_COPIER_SUBMIT = 3420,
    GC_STRIPE_FLUSH_SUBMIT = 3421,
    GC_STRIPE_FLUSH_COMPLETION = 3422,
    GC_ACQUIRE_OWNERSHIP_RBA_LIST = 3423,
    GC_MAP_UPDATE_REQUEST = 3424,
    GC_MAP_UPDATE = 3425,
    GC_MAP_UPDATE_COMPLETION = 3426,
    GC_MAP_UPDATE_FAILED = 3427,
    GC_COPIER_NOT_EXIST = 3428,
    GC_CANNOT_CREATE_COPIER = 3429,
    GC_ERROR_MSG = 3430,

    // --------------Flow control (3500)----------------
    FC_START = 3500,
    FC_TOKEN_DISTRIBUTED,
    FC_TOKEN_OVERFLOW,
    FC_NEGATIVE_TOKEN,
    FC_WRONG_STRATEGY,
    FC_RESET_FORCERESET,
    FC_SET_FORCERESET,
    FC_FORCERESET_DONE,
    FC_CONFIGURATION,

    // --------------Meta filesystem (4000)----------------
    // Debug, Info, Warning, Error, Critical
    MFS_START = 4000,
    MFS_DEBUG_START = MFS_START,
    MFS_DEBUG_MESSAGE = MFS_DEBUG_START,
    MFS_INFO_START = 4100,
    MFS_INFO_MESSAGE = MFS_INFO_START,
    MFS_CREATE_META_FILE,
    MFS_WARNING_START = 4200,
    MFS_WARNING_INIT_AGAIN = MFS_WARNING_START,
    MFS_SYSTEM_MOUNT_AGAIN,
    MFS_SYSTEM_UNMOUNT_AGAIN,
    MFS_MSG_ENQUEUE_FAILED,
    MFS_COMPACTION_FAILED,

    MFS_ERROR_START = 4300,
    MFS_ERROR_MOUNTED = MFS_ERROR_START,
    MFS_ERROR_UNMOUNTED,
    MFS_ERROR_MESSAGE,
    MFS_INVALID_PARAMETER,
    MFS_MODULE_NOT_READY,
    MFS_MODULE_ALREADY_READY,
    MFS_MODULE_INIT_FAILED,
    MFS_MODULE_BRINGUP_FAILED,
    MFS_MODULE_NO_MEDIA,
    MFS_SYSTEM_OPEN_FAILED,
    MFS_INVALID_INFORMATION,

    MFS_FILE_CREATE_FAILED,
    MFS_FILE_NOT_FOUND,
    MFS_FILE_NOT_OPENED,
    MFS_FILE_OPEN_FAILED,
    MFS_FILE_OPEN_REPETITIONARY,
    MFS_FILE_CLOSE_FAILED,
    MFS_FILE_FORMAT_FAILED,
    MFS_FILE_DELETE_FAILED,
    MFS_FILE_ALREADY_LOCKED,
    MFS_FILE_READ_FAILED,
    MFS_FILE_WRITE_FAILED,
    MFS_MEDIA_WROTE_SIZE_NOT_MATCHED,
    MFS_MEDIA_SEEK_FAILED,
    MFS_MEDIA_READ_FAILED,
    MFS_MEDIA_WRITE_FAILED,
    MFS_FILE_TRIM_FAILED,

    MFS_MEDIA_MOUNT_FAILED,
    MFS_MEDIA_UNMOUNT_FAILED,
    MFS_MEDIA_NULL,
    MFS_META_STORAGE_CREATE_FAILED,
    MFS_META_STORAGE_CLOSE_FAILED,
    MFS_META_STORAGE_NOT_READY,

    MFS_META_VOLUME_CREATE_FAILED,
    MFS_META_VOLUME_OPEN_FAILED,
    MFS_META_VOLUME_CLOSE_FAILED,
    MFS_META_VOLUME_CLOSE_FAILED_DUE_TO_ACTIVE_FILE,
    MFS_META_VOLUME_NOT_ENOUGH_SPACE,
    MFS_META_VOLUME_ALMOST_FULL,
    MFS_META_VOLUME_ALREADY_CLOSED,
    MFS_META_VOLUME_CATALOG_INVALID,
    MFS_META_SAVE_FAILED,
    MFS_META_LOAD_FAILED,
    MFS_IO_FAILED_DUE_TO_ENQUEUE_FAILED,
    MFS_IO_FAILED_DUE_TO_STOP_STATE,
    MFS_IO_FAILED_DUE_TO_ERROR,
    MFS_QUEUE_POP_FAILED,
    MFS_QUEUE_PUSH_FAILED,
    MFS_MAX_FILE_SIZE_NOT_SET,
    MFS_ARRAY_CREATE_FAILED,
    MFS_ARRAY_ADD_FAILED,
    MFS_ARRAY_REMOVE_FAILED,
    MFS_ARRAY_DELETE_FAILED,
    MFS_INVALID_MBR,
    MFS_NEED_MORE_CONTEXT_SLOT,
    MFS_FILE_DESCRIPTOR_NOT_EXIST,
    MFS_FILE_INACTIVATED,
    MFS_DATA_CORRUPTED,
    MFS_INVALID_CONFIG,

    MFS_CRITICAL_START = 4400,
    MFS_RECOVERY_CATALOG_FAILED = MFS_CRITICAL_START,
    MFS_TEST_FAILED,
    MFS_END,
    MFS_COUNT = MFS_END - MFS_START,
    // Event
    VOLUME_EVENT = 4500,
    DEVICE_DETACH_EVENT = 4510,
    STATE_EVENT = 4520,

    LOGGER_FILTER_POLICY_DECODE_FAIL = 4580,
    LOGGER_FILTER_POLICY_FILE_NOT_FOUND = 4581,
    LOGGER_SET_LEVEL_FAILED,
    LOGGER_FILTER_APPLY_SUCCESS,

    // --------------QOS Related (4600)----------------
    QOS_START = 4600,
    // QOS CLI Commands Related
    QOS_CLI_WRONG_MISSING_PARAMETER = QOS_START,
    QOS_CLI_FE_QOS_DISABLED,
    // QOS Manager Related
    QOS_SET_EVENT_POLICY,
    QOS_NOT_SUPPORTED,
    QOS_FINALIZATION,
    QOS_POLLER_REGISTRATION,
    QOS_POLLER_REGISTRATION_FAILED,
    QOS_POLLER_UNREGISTRATION,
    QOS_POLLER_UNREGISTRATION_FAILED,
    QOS_MINIMUM_NOT_MET,
    QOS_MAX_ARRAYS_EXCEEDED,
    QOS_ARRAY_DOES_NOT_EXIST,
    QOS_END,
    QOS_COUNT = QOS_END - QOS_START,
    // --------------IO Path nvmf (5000)----------------
    IONVMF_START = 5000,

    IONVMF_1H = IONVMF_START,
    IONVMF_2H,
    IONVMF_3H,
    IONVMF_4H,
    IONVMF_5H,
    IONVMF_6H,
    IONVMF_7H,
    IONVMF_8H,
    IONVMF_NAMESPACE_ATTACH_FAILED,
    IONVMF_FAIL_TO_FIND_VOLID,
    IONVMF_FAIL_TO_FIND_ARRAYNAME,
    IONVMF_OVERRIDE_UNVMF_IO_HANDLER,
    IONVMF_VOL_CREATE_TIMEOUT,
    IONVMF_VOL_DELETE_TIMEOUT,
    IONVMF_VOL_MOUNT_TIMEOUT,
    IONVMF_VOLUME_DETACH_COUNT_OVERFLOW,
    IONVMF_FAIL_TO_CREATE_POS_BDEV,
    IONVMF_FAIL_TO_DELETE_POS_BDEV,
    IONVMF_FAIL_TO_DETACH_NAMESPACE,
    IONVMF_BDEV_DOES_NOT_EXIST,
    IONVMF_BDEV_UUID_DOES_NOT_EXIST,
    IONVMF_FAIL_TO_CONVERT_UUID_INTO_STRING,
    IONVMF_FAIL_TO_PARSE_UUID,
    IONVMF_FAIL_TO_FIND_SUBSYSTEM,
    IONVMF_BDEV_ALREADY_EXIST,
    IONVMF_FAIL_TO_READ_TRANSPORT_CONFIG,
    IONVMF_FAIL_TO_CREATE_TRANSPORT,
    IONVMF_TRANSPORT_NUM_SHARED_BUFFER_CHANGED,
    IONVMF_FAIL_TO_CREATE_SUBSYSTEM,
    IONVMF_SET_ARRAY_TO_SUBSYSTEM,
    IONVMF_NO_CONFIG_MGR,
    IONVMF_FAIL_TO_INIT_POS_BDEV,
    // IONVMF_9H_FFH,    // Reserved

    IONVMF_END,
    IONVMF_COUNT = IONVMF_END - IONVMF_START,

    // --------------IO Path Frontend (5100)----------------
    IOFRONTEND_START = 5100,

    AFTMGR_CPU_COUNT_NOT_ENOUGH = IOFRONTEND_START,
    AFTMGR_DISABLED_CORE,
    AFTMGR_FAIL_TO_FIND_MASTER_REACTOR,
    AFTMGR_FAIL_TO_ALLOCATE_ALL_CPU,
    AFTMGR_FAIL_TO_OVERLAP_MASK,
    AFTMGR_FAIL_TO_PARSING_ERROR,
    AFTMGR_CORE_NOT_SUFFICIENT,
    AFTMGR_NO_EVENT_WORKER_ALLOCATED,
    AFTMGR_NO_USE_CONFIG,
    AFTMGR_USE_CONFIG,

    AIO_CONTEXT_NOT_FOUND,
    AIO_FAIL_TO_ALLOCATE_EVENT,
    AIO_FAIL_TO_ALLOCATE_MEMORY,
    AIO_INVALID_AIO_CONTEXT,
    AIO_INVALID_AIO_PRIVATE,
    AIO_INVALID_BDEV_IO,
    AIO_INVALID_UBIO,
    AIO_IO_FROM_INVALID_THREAD,
    AIO_DEBUG_COMPLETION,
    AIO_DEBUG_SUBMISSION,
    AIO_FLUSH_START,
    AIO_FLUSH_END,

    BLKALGN_INVALID_UBIO,

    BLKHDLR_FAIL_TO_ALLOCATE_EVENT,
    BLKHDLR_WRONG_IO_DIRECTION,

    CALLBACK_INVALID_CALLEE,
    CALLBACK_INVALID_COUNT,
    CALLBACK_TIMEOUT,
    CALLBACK_DESTROY_WITHOUT_EXECUTED,
    CALLBACK_DESTROY_WITH_ERROR,

    EVENTFRAMEWORK_FAIL_TO_ALLOCATE_EVENT,
    EVENTFRAMEWORK_INVALID_EVENT,
    EVENTFRAMEWORK_INVALID_REACTOR,

    EVENTSCHEDULER_NOT_MATCH_WORKER_COUNT,

    EVTARG_WRONG_ARGUMENT_ACCESS,
    EVTARG_WRONG_ARGUMENT_ADD,

    EVTQ_INVALID_EVENT,

    EVTSCHDLR_INVALID_WORKER_ID,

    FLUSHREAD_DEBUG_SUBMIT,
    FLUSHREAD_FAIL_TO_ALLOCATE_MEMORY,
    FLUSH_DEBUG_SUBMIT,
    FLUSH_DEBUG_COMPLETION,

    FREEBUFPOOL_FAIL_TO_ALLOCATE_MEMORY,

    IOAT_CONFIG_INVALID,

    IOATAPI_FAIL_TO_FINALIZE,
    IOATAPI_FAIL_TO_INITIALIZE,
    IOATAPI_FAIL_TO_SUBMIT_COPY,
    IOATAPI_DISABLED,
    IOATAPI_ENABLED,

    IODISPATCHER_INVALID_CPU_INDEX,
    IODISPATCHER_INVALID_PARM,

    MERGER_INVALID_SPLIT_REQUESTED,

    RBAMGR_WRONG_VOLUME_ID,

    RDCMP_INVALID_ORIGIN_UBIO,
    RDCMP_INVALID_UBIO,
    RDCMP_READ_FAIL,

    RDHDLR_INVALID_UBIO,
    RDHDLR_READ_DURING_REBUILD,

    SCHEDAPI_COMPLETION_POLLING_FAIL,
    SCHEDAPI_NULL_COMMAND,
    SCHEDAPI_SUBMISSION_FAIL,
    SCHEDAPI_WRONG_BUFFER,

    STRIPE_INVALID_VOLUME_ID,

    REF_COUNT_RAISE_FAIL,
    TRANSLATE_CONVERT_FAIL,
    TRANSLATE_CONVERT_FAIL_IN_SYSTEM_STOP,

    TRSLTR_INVALID_BLOCK_INDEX,
    TRSLTR_WRONG_ACCESS,
    TRSLTR_WRONG_VOLUME_ID,

    VOLUMEIO_DEBUG_SUBMIT,

    UBIO_DEBUG_CHECK_VALID,
    UBIO_DEBUG_COMPLETE,
    UBIO_ALREADY_SYNC_DONE,
    UBIO_CALLBACK_EVENT_ALREADY_SET,
    UBIO_DUPLICATE_IO_ABSTRACTION,
    UBIO_FAIL_TO_ALLOCATE_MEMORY,
    UBIO_FREE_UNALLOWED_BUFFER,
    UBIO_INVALID_GC_PROGRESS,
    UBIO_INVALID_POS_IO,
    UBIO_INVALID_IO_STATE,
    UBIO_INVALID_LSID,
    UBIO_INVALID_ORIGIN_UBIO,
    UBIO_INVALID_ORIGINAL_CORE,
    UBIO_INVALID_PBA,
    UBIO_INVALID_RBA,
    UBIO_INVALID_UBIO_HANDLER,
    UBIO_INVALID_VOLUME_ID,
    UBIO_INVALID_VSA,
    UBIO_INVALID_ARRAY_NAME,
    UBIO_INVALID_DEVICE,
    UBIO_NO_COMPLETION_FOR_FRONT_END_EVENT,
    UBIO_REMAINING_COUNT_ERROR,
    UBIO_REQUEST_NULL_BUFFER,
    UBIO_REQUEST_OUT_RANGE,
    UBIO_SYNC_FLAG_NOT_SET,
    UBIO_WRONG_SPLIT_SIZE,

    URAM_BACKUP_FILE_NOT_EXISTS,
    URAM_BACKUP_FILE_OPEN_FAILED,
    URAM_BACKUP_FILE_READ_FAILED,
    URAM_BACKUP_FILE_STAT_FAILED,
    URAM_CONFIG_FILE_OPEN_FAILED,
    URAM_COMPLETION_TIMEOUT,
    URAM_COMPLETION_FAILED,

    URAM_FAIL_TO_CLOSE,
    URAM_FAIL_TO_OPEN,
    URAM_FAIL_TO_REQUEST_IO,
    URAM_FAIL_TO_RETRY_IO,
    URAM_PENDING_IO_NOT_FOUND,
    URAM_RESTORING_FAILED,
    URAM_RESTORING_PAGE_DONE,
    URAM_SUBMISSION_FAILED,
    URAM_SUBMISSION_TIMEOUT,

    WRCMP_FAIL_TO_ALLOCATE_MEMORY,
    WRCMP_INVALID_SPLIT_UBIO,
    WRCMP_INVALID_STRIPE,
    WRCMP_IO_ERROR,
    WRCMP_WRITE_WRAPUP_FAILED,
    WRCMP_MAP_UPDATE_FAILED,

    IOCONTROL_REBUILD_FAIL,
    WRHDLR_ALLOC_WRITE_BUFFER_FAILED,
    WRHDLR_FAIL_TO_ALLOCATE_MEMORY,
    WRHDLR_FAIL_BY_SYSTEM_STOP,
    WRHDLR_INVALID_UBIO,

    WRHDLR_NO_FREE_SPACE,
    WRHDLR_DEBUG_READ_OLD,
    WRHDLR_DEBUG_READ_OLD_COMPLETE,

    WRWRAPUP_EVENT_ALLOC_FAILED,
    WRWRAPUP_STRIPE_NOT_FOUND,
    WRWRAPUP_DEBUG_STRIPE,
    BLKMAP_DEBUG_UPDATE_REQUEST,
    BLKMAP_DEBUG_UPDATE,

    FLUSH_HANDLING_ENABLED,
    FLUSH_HANDLING_DISABLED,
    FLUSH_CMD_MAPPER_FLUSH_FAILED,
    FLUSH_CMD_ALLOCATOR_FLUSH_FAILED,
    FLUSH_CMD_ONGOING,

    IOFRONTEND_END,
    IOFRONTEND_COUNT = IOFRONTEND_END - IOFRONTEND_START,

    // --------------IO Path Backend (5300)----------------

    IOBACKEND_START = 5300,

    IOWORKER_OPERATION_NOT_SUPPORTED = IOBACKEND_START,
    IOWORKER_DEVICE_ADDED,
    IOWORKER_UNDERFLOW_HAPPENED,
    IOSMHDLR_BUFFER_NOT_ENOUGH,
    IOSMHDLR_BUFFER_NOT_ALIGNED,
    IOSMHDLR_OPERATION_NOT_SUPPORTED,
    IOSMHDLR_DEBUG_ASYNC_READ,
    IOSMHDLR_COUNT_DIFFERENT,
    IOSMHDLR_DEBUG_ASYNC_WRITE,
    IOSMHDLR_ARRAY_LOCK,
    IOSMHDLR_ARRAY_UNLOCK,
    IOSMHDLR_BYTEIO_BUFFER_NULLPTR,
    IOSMHDLR_BYTEIO_PARTITION_IS_NOT_BYTE_ACCESSIBLE,
    IOSMHDLR_BYTEIO_DIR_NOT_SUPORTTED,
    IOSMHDLR_BYTEIO_PARTITION_TRANSLATE_ERROR,
    I_IOSMHDLR_NULLPTR,

    DEVICE_OPEN_FAILED,
    DEVICE_CLOSE_FAILED,
    DEVICE_SCAN_FAILED,
    DEVICE_SCAN_IGNORED,
    DEVICE_SUBMISSION_FAILED,

    DEVICE_SUBMISSION_QUEUE_FULL,
    DEVICE_SUBMISSION_TIMEOUT,
    DEVICE_COMPLETION_FAILED,
    DEVICE_THREAD_REGISTERED_FAILED,
    DEVICE_THREAD_UNREGISTERED_FAILED,
    DEVICE_OPERATION_NOT_SUPPORTED,
    DEVICE_PENDING_IO_NOT_FOUND,
    DEVICE_UNEXPECTED_PENDING_ERROR_COUNT,
    DEVICE_OVERLAPPED_SET_IOWORKER,
    DEVICE_NULLPTR_IOWORKER,

    UNVME_SSD_DEBUG_CREATED,
    UNVME_SSD_SCAN_FAILED,
    UNVME_SSD_SCANNED,
    UNVME_SSD_ATTACH_NOTIFICATION_FAILED,
    UNVME_SSD_DETACH_NOTIFICATION_FAILED,
    UNVME_SSD_OPEN_FAILED,
    UNVME_SSD_CLOSE_FAILED,
    UNVME_SSD_UNDERFLOW_HAPPENED,
    UNVME_SUBMISSION_FAILED,
    UNVME_SUBMISSION_QUEUE_FULL,
    UNVME_SUBMISSION_RETRY_EXCEED,
    UNVME_COMPLETION_TIMEOUT,

    UNVME_COMPLETION_FAILED,
    UNVME_OPERATION_NOT_SUPPORTED,
    UNVME_CONTROLLER_FATAL_STATUS,
    UNVME_CONTROLLER_RESET_FAILED,
    UNVME_CONTROLLER_RESET,
    UNVME_SUBMITTING_CMD_ABORT,
    UNVME_ABORT_TIMEOUT,
    UNVME_ABORT_SUBMISSION_FAILED,
    UNVME_ABORT_COMPLETION_FAILED,
    UNVME_ABORT_COMPLETION,
    UNVME_DO_NOTHING_ON_TIMEOUT,
    UNVME_ABORT_TIMEOUT_FAILED,

    UNVME_NOT_SUPPORTED_DEVICE,

    UNVME_DEBUG_RETRY_IO,
    UNVME_DEBUG_REQUEST_IO,
    UNVME_DEBUG_COMPLETE_IO,

    DEVICE_CONTEXT_NOT_FOUND,

    DEVCTX_ALLOC_TIMEOUT_CHECKER_FAILED,
    IOCTX_ERROR_KEY_NOT_SET,
    IOCTX_IO_KEY_NOT_SET,

    IOQ_ENQUEUE_NULL_UBIO,

    BUFFER_ENTRY_OUT_OF_RANGE,

    NFLSH_ERROR_DETECT,
    NFLSH_EVENT_ALLOCATION_FAILED,
    NFLSH_EVENT_MAP_UPDATE_FAILED,
    NFLSH_STRIPE_NOT_IN_WRITE_BUFFER,
    NFLSH_STRIPE_DEBUG,
    NFLSH_STRIPE_DEBUG_UPDATE,

    FLUSH_WRAPUP_STRIPE_NOT_IN_USER_AREA,
    STRIPEPUTEVT_STRIPE_NOT_IN_NORMAL_POOL,

    IOBACKEND_END,
    IOBACKEND_COUNT = IOBACKEND_END - IOBACKEND_START,

    // --------------Device (5500)----------------
    DEVICE_START = 5500,

    UNVME_DAEMON_START = DEVICE_START,
    UNVME_DAEMON_FINISH,
    UNVME_REGISTER_CTRL,
    UNVME_REGISTER_NS,
    UNVME_PROBE_CALLBACK,
    UNVME_INIT_SCAN_CALLBACK,
    UNVME_ATTACH_CALLBACK,
    UNVME_DETACH_CALLBACK,
    UNVME_SPDK_DETACH,
    UNVME_CLEAN_UP,
    UNVME_INIT_CONTROLLER,
    UNVME_MAX_RETRY_EXCEED,
    UNVME_MAX_TIMEOUT_EXCEED,

    DEVICEMGR_ATTACH,
    DEVICEMGR_CLEAR_DEVICE,
    DEVICEMGR_START_MONITOR,
    DEVICEMGR_STOP_MONITOR,
    DEVICEMGR_CHK_DUPLICATE,
    DEVICEMGR_INIT_SCAN,
    DEVICEMGR_REMOVE_DEV,
    DEVICEMGR_RESCAN,
    DEVICEMGR_GETDEV,
    DEVICEMGR_LISTDEV,
    DEVICEMGR_DETACH,
    DEVICEMGR_SETUPMODEL,
    DEVICEMGR_DEVICE_NOT_FOUND,

    DEVICE_CREATION_FAIL,
    DEVICE_DETACH_TRIGGER_FAIL,

    URAM_INVALID_NUMA,

    DEVICE_INFO_MSG,
    DEVICE_DEBUG_MSG,
    DEVICE_WARN_MSG,

    RESOURCE_MANAGER_START = 5700,
    RESOURCE_MANAGER_DEBUG_MSG = RESOURCE_MANAGER_START,
    BUFFER_POOL_EMPTY,
    HUGEPAGE_ALLOCATION_FAIL,

    INVALID_BUFFER_IN_SMART_LOG = 8500,
    NO_DISK_IN_ARRAY,
    INVALID_LOG_PAGE_ID,
    SMART_LOG_ENABLED,
    SMART_LOG_DISABLED,

    SYSTEM_START = 9000,
    SYSTEM_SPACE_INFO = SYSTEM_START,
    SYSTEM_VERSION_LOAD_SUCCESS,
    SYSTEM_END,
    SYSTEM_COUNT = SYSTEM_END - SYSTEM_START,

    // --------------Telemetry (9500)----------------
    TELEMETRY_DEBUG_MSG = 9500,
    TELEMETRY_DISABLED = 9501,

    TELEMETRY_ERROR_MSG = 9600,
    TELEMETRY_CONFIG_BAD_FILE,
    TELEMETRY_CONFIG_INVALID_FIELD,

    TELEMETRY_AIR_DATA_PARSING_FAILED = 9700,

    // --------------Debug (10000)----------------
    DEBUG_START = 10000,
    DEBUG_MEMORY_CHECK_DOUBLE_FREE = DEBUG_START,
    DEBUG_MEMORY_CHECK_INVALID_ACCESS,
    DEBUG_CORE_DUMP_SETTING_FAILED,
    DEBUG_ATOMIC_UNDERFLOW,
    DEBUG_SIGNAL_HANDLING,

    // -----------------Exceptions-------------------
    EVENT_ID_MAPPING_WRONG = 0x7FFFFFFE,
    RESERVED = 0x7FFFFFFF,
};

// Event information
class PosEventInfoEntry
{
    public:
        PosEventInfoEntry(const char* eventName, const char* message,
            const char* cause, const char* solution)
        {
            this->eventName = eventName;
            this->message = message;
            this->cause = cause;
            this->solution = solution;
        }
        std::string GetEventName() { return eventName; }
        std::string GetMessage() { return message; }
        std::string GetCause() { return cause; }
        std::string GetSolution() { return solution; }

    private:
        std::string eventName = "";
        std::string message = "";
        // mj: Fill in cause and solution for erroneous events only.
        std::string cause = "";
        std::string solution = "";
};

static std::unordered_map<int, PosEventInfoEntry*> PosEventInfo =
    {
        // map<eventId, PosEventInfoEntry(eventName, message, cause)>
        {(int)POS_EVENT_ID::CLI_SERVER_INITIALIZED,
            new PosEventInfoEntry("CLI_SERVER_INITIALIZED",
                "The CLI server has been initialized successfully.", "", "")},
        {(int)POS_EVENT_ID::CLI_CLIENT_ACCEPTED,
            new PosEventInfoEntry("CLI_CLIENT_ACCEPTED",
                "A new client has been accepted (connected).", "", "")},
        {(int)POS_EVENT_ID::CLI_CLIENT_DISCONNECTED,
            new PosEventInfoEntry("CLI_CLIENT_DISCONNECTED",
                "A client has been disconnected.", "", "")},
        {(int)POS_EVENT_ID::CLI_MSG_RECEIVED,
            new PosEventInfoEntry("CLI_MSG_RECEIVED",
                "CLI server has recieved a message from a CLI client.", "", "")},
        {(int)POS_EVENT_ID::CLI_MSG_SENT,
            new PosEventInfoEntry("CLI_MSG_SENT",
                "CLI server has sent a message to a client.", "", "")},
        {(int)POS_EVENT_ID::CLI_MSG_SENDING_FAILURE,
            new PosEventInfoEntry("CLI_MSG_SENDING_FAILURE,",
                "CLI server has failed to send a message to a client.", "", "")},
        {(int)POS_EVENT_ID::CLI_SERVER_FINISH,
            new PosEventInfoEntry("CLI_SERVER_FINISH",
                "CLI server has finished successfully.", "", "")},
        {(int)POS_EVENT_ID::CLI_SERVER_THREAD_JOINED,
            new PosEventInfoEntry("CLI_SERVER_THREAD_JOINED",
                "A CLI server thread has joined. The main thread is blocked until the CLI processing finishes", "", "")},
        {(int)POS_EVENT_ID::CLI_REUSE_ADDR_ENABLED,
            new PosEventInfoEntry("CLI_REUSE_ADDR_ENABLED",
                "CLI server has enabled to reuse address.", "", "")},
        {(int)POS_EVENT_ID::CLI_REUSE_ADDR_FAILURE,
            new PosEventInfoEntry("CLI_REUSE_ADDR_FAILURE",
                "CLI server has failed to reuse address.", "", "")},
        {(int)POS_EVENT_ID::CLI_SOCK_CREATE_FAILURE,
            new PosEventInfoEntry("CLI_SOCK_CREATE_FAILURE",
                "CLI server has failed to create a socket.", "", "")},
        {(int)POS_EVENT_ID::CLI_SOCK_BIND_FAILURE,
            new PosEventInfoEntry("CLI_SOCK_BIND_FAILURE",
                "CLI server has failed to bind a socket.", "", "")},
        {(int)POS_EVENT_ID::CLI_SOCK_LISTEN_FAILURE,
            new PosEventInfoEntry("CLI_SOCK_LISTEN_FAILURE",
                "CLI server has failed to listen to a socket.", "", "")},
        {(int)POS_EVENT_ID::CLI_EPOLL_CREATE_FAILURE,
            new PosEventInfoEntry("CLI_EPOLL_CREATE_FAILURE",
                "CLI server has failed to create a epoll.", "", "")},
        {(int)POS_EVENT_ID::CLI_SOCK_ACCEPT_FAILURE,
            new PosEventInfoEntry("CLI_SOCK_ACCEPT_FAILURE",
                "CLI server has failed to accept the client socket.", "", "")},
        {(int)POS_EVENT_ID::CLI_ADD_CLIENT_FAILURE_MAX_CLIENT,
            new PosEventInfoEntry("CLI_ADD_CLIENT_FAILURE_MAX_CLIENT",
                "CLI server has failed to add a client.",
                    "The number of clients exceeds the maximum.", "")},
        {(int)POS_EVENT_ID::CLI_MSG_RECEIVE_FAILURE,
            new PosEventInfoEntry("CLI_MSG_RECEIVE_FAILURE",
                "CLI server has failed to receive a message from a client.", "", "")},
        {(int)POS_EVENT_ID::CLI_SERVER_TIMED_OUT,
            new PosEventInfoEntry("CLI_SERVER_TIMED_OUT",
                "CLI server has timed out.", "Command processing takes too long.", "")},
        {(int)POS_EVENT_ID::CLI_SERVER_BUSY,
            new PosEventInfoEntry("CLI_SERVER_BUSY",
                "CLI server could not receive the command.",
                "POS is processing a previously receieved command.", "Please try after a while.")},
        {(int)POS_EVENT_ID::CLI_CLIENT_CREATED,
            new PosEventInfoEntry("CLI_CLIENT_CREATED",
                "CLI server has created a thread for CLI.", "", "")},
        {(int)POS_EVENT_ID::CLI_CLIENT_CREATION_FAILURE,
            new PosEventInfoEntry("CLI_CLIENT_CREATION_FAILURE",
                "CLI server could not create a thread.", "", "")},
        {(int)POS_EVENT_ID::CLI_CLIENT_DETACHED,
            new PosEventInfoEntry("CLI_CLIENT_DETACHED",
                "CLI server has detached a thread for CLI.", "", "")},
        {(int)POS_EVENT_ID::CLI_CLIENT_DETACHEMENT_FAILURE,
            new PosEventInfoEntry("CLI_CLIENT_DETACHEMENT_FAILURE",
                "CLI server could not detach a thread for CLI.", "", "")},
        {(int)POS_EVENT_ID::CLI_LIST_ARRAY_FAILURE,
            new PosEventInfoEntry("CLI_LIST_ARRAY_FAILURE",
                "failed to retrieve array list", "unable to read the array configuration.", "try device scanning first")},
        {(int)POS_EVENT_ID::CLI_ADD_DEVICE_FAILURE,
            new PosEventInfoEntry("CLI_ADD_DEVICE_FAILURE",
                "failed to add spare device", "", "")},
        {(int)POS_EVENT_ID::CLI_ADD_DEVICE_FAILURE_NO_SPARE,
            new PosEventInfoEntry("CLI_ADD_DEVICE_FAILURE_NO_SPARE",
                "failed to add spare device", "spare device is not specified", "please specify the spare device")},
        {(int)POS_EVENT_ID::CLI_ADD_DEVICE_SUCCESS,
            new PosEventInfoEntry("CLI_ADD_DEVICE_SUCCESS",
                "spare device has been added to an array", "", "")},
        {(int)POS_EVENT_ID::CLI_ADD_LISTENER_FAILURE,
            new PosEventInfoEntry("CLI_ADD_LISTENER_FAILURE",
                "failed to add listener", "", "")},
        {(int)POS_EVENT_ID::CLI_ADD_LISTENER_SUCCESS,
            new PosEventInfoEntry("CLI_ADD_LISTENER_SUCCESS",
                "a lisenter has been added successfully", "", "")},
        {(int)POS_EVENT_ID::LOGGER_FILTER_POLICY_FILE_NOT_FOUND,
            new PosEventInfoEntry("LOGGER_FILTER_POLICY_FILE_NOT_FOUND",
                "failed to find a logger filter policy file", "", "")},
        {(int)POS_EVENT_ID::LOGGER_FILTER_APPLY_SUCCESS,
            new PosEventInfoEntry("LOGGER_FILTER_APPLY_SUCCESS",
                "log filter has been successfully applied", "", "")},
        {(int)POS_EVENT_ID::LOGGER_FILTER_POLICY_DECODE_FAIL,
            new PosEventInfoEntry("LOGGER_FILTER_POLICY_DECODE_FAIL",
                "failed to decode logger filter policy", "", "")},
        {(int)POS_EVENT_ID::CLI_ARRAY_INFO_NO_ARRAY_NAME,
            new PosEventInfoEntry("CLI_ARRAY_INFO_NO_ARRAY_NAME",
                "failed to retrieve array info", "array name is not typed", "type an arry name")},
        {(int)POS_EVENT_ID::CLI_ARRAY_INFO_ARRAY_NOT_EXIST,
            new PosEventInfoEntry("CLI_ARRAY_INFO_ARRAY_NOT_EXIST",
                "failed to retrieve array info", "array does not exist", "")},
        {(int)POS_EVENT_ID::CLI_AUTOCREATE_ARRAY_FAILURE,
            new PosEventInfoEntry("CLI_AUTOCREATE_ARRAY_FAILURE",
                "failed to create an array via autocreate", "", "")},
        {(int)POS_EVENT_ID::CLI_AUTOCREATE_ARRAY_SUCCESS,
            new PosEventInfoEntry("CLI_AUTOCREATE_ARRAY_SUCCESS",
                "an array has been created successfully via autocreate", "", "")},
    };
