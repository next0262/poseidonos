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

#include "src/cli/rename_volume_command.h"

#include "src/cli/cli_event_code.h"
#include "src/volume/volume_service.h"
#include "src/array_mgmt/array_manager.h"

namespace pos_cli
{
RenameVolumeCommand::RenameVolumeCommand(void)
{
}

// Exclude destructor of abstract class from function coverage report to avoid known issues in gcc/gcov
// LCOV_EXCL_START
RenameVolumeCommand::~RenameVolumeCommand(void)
{
}
// LCOV_EXCL_STOP

string
RenameVolumeCommand::Execute(json& doc, string rid)
{
    string arrayName = DEFAULT_ARRAY_NAME;
    if (doc["param"].contains("array") == true)
    {
        arrayName = doc["param"]["array"].get<std::string>();
    }

    JsonFormat jFormat;
    if (doc["param"].contains("name") && doc["param"].contains("newname"))
    {
        string oldName = doc["param"]["name"].get<std::string>();
        string newName = doc["param"]["newname"].get<std::string>();

        IVolumeEventManager* volMgr =
            VolumeServiceSingleton::Instance()->GetVolumeManager(arrayName);

        int ret = FAIL;

        ComponentsInfo* info = ArrayMgr()->GetInfo(arrayName);
        if (info == nullptr)
        {
            return jFormat.MakeResponse("RENAMEVOLUME", rid, ret,
                 "failed to rename volume " + oldName + "to " + newName, GetPosInfo());
        }

        IArrayInfo* array = info->arrayInfo;
        ArrayStateType arrayState = array->GetState();
        if (arrayState == ArrayStateEnum::BROKEN)
        {
            int eventId = EID(CLI_COMMAND_FAILURE_ARRAY_BROKEN);
            POS_TRACE_WARN(eventId, "arrayName: {}, arrayState: {}",
                arrayName, arrayState.ToString());

            return jFormat.MakeResponse("RENAMEVOLUME", rid, ret,
                 "failed to rename volume " + oldName + "to " + newName, GetPosInfo());
        }
        if (volMgr != nullptr)
        {
            ret = volMgr->Rename(oldName, newName);
        }

        if (ret == SUCCESS)
        {
            return jFormat.MakeResponse("RENAMEVOLUME", rid, ret,
                oldName + " is renamed to " + newName,
                GetPosInfo());
        }
        else
        {
            return jFormat.MakeResponse(
                "RENAMEVOLUME", rid, ret,
                "failed to rename " + oldName + " to " + newName +
                    "(code:" + to_string(ret) + ")",
                GetPosInfo());
        }
    }
    else
    {
        return jFormat.MakeResponse(
            "RENAMEVOLUME", rid, (int)POS_EVENT_ID::INVALID_PARAM,
            "volume name or newname is not entered", GetPosInfo());
    }
}
}; // namespace pos_cli
