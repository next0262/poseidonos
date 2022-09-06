package globals

const PosBusy = "PoseidonOS may be processing a command. Please try after a while."

const OTEL_SERVICE_NAME = "poseidonos-cli"

const (
	SYSTEM_CMD_APP_NAME   = "systemcmds"
	SYSTEM_INFO_FUNC_NAME = "systeminfocmd"
)

const (
	ARRAY_CMD_APP_NAME      = "arraycmds"
	ARRAY_MOUNT_FUNC_NAME   = "MountArrayCmd"
	ARRAY_UNMOUNT_FUNC_NAME = "UnmountArrayCmd"
)

const (
	VOLUME_CMD_APP_NAME      = "volumecmds"
	VOLUME_MOUNT_FUNC_NAME   = "MountVolumeCmd"
	VOLUME_UNMOUNT_FUNC_NAME = "UnmountVolumeCmd"
)

const (
	GRPC_MGR_APP_NAME            = "grpcmgr"
	GRPC_SYSTEM_INFO_FUNC_NAME   = "SendSystemInfo"
	GRPC_ARRAY_MOUNT_FUNC_NAME   = "SendMountArray"
	GRPC_ARRAY_UNMOUNT_FUNC_NAME = "SendUnmountArray"
)

const (
	SOCKET_MGR_APP_NAME           = "socketmgr"
	SOCKET_SEND_RECEIVE_FUNC_NAME = "SendReqAndReceiveRes"
)
