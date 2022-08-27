package systemcmds

import (
	"cli/cmd/displaymgr"
	"cli/cmd/globals"
	"cli/cmd/grpcmgr"
	"cli/cmd/otelmgr"
	"fmt"

	pb "cli/api"

	"github.com/spf13/cobra"
	"google.golang.org/protobuf/encoding/protojson"
)

var SystemInfoCmd = &cobra.Command{
	Use:   "info",
	Short: "Display information of PoseidonOS.",
	Long: `
Display the information of PoseidonOS.

Syntax:
	poseidonos-cli system info
          `,
	RunE: func(cmd *cobra.Command, args []string) error {
		ctx := cmd.Context()
		defer tracemgr.Shutdown(ctx)
		ctx, span := tracemgr.SetTrace(ctx, "systemcmds", "SystemInfoCmd")
		defer span.End()

		var mytrace = Tracer{ctx, "systemcmds", "systeminfocmd"}
		defer mytrace.release() 

		var command = "SYSTEMINFO"

		req, buildErr := buildSystemInfoReq(command)
		if buildErr != nil {
			fmt.Printf("failed to build request: %v", buildErr)
			span.RecordError(buildErr)
			mytrace.error(buildErr)
			return buildErr
		}

		reqJson, err := protojson.Marshal(req)
		if err != nil {
			fmt.Printf("failed to marshal the protobuf request: %v", err)
			span.RecordError(err)
			return err
		}
		displaymgr.PrintRequest(string(reqJson))

		res, gRpcErr := grpcmgr.SendSystemInfo(ctx, req)
		if gRpcErr != nil {
			globals.PrintErrMsg(gRpcErr)
			span.RecordError(gRpcErr)
			return gRpcErr
		}

		printErr := displaymgr.PrintProtoResponse(command, res)
		if printErr != nil {
			fmt.Printf("failed to print the response: %v", printErr)
			span.RecordError(printErr)
			return printErr
		}

		return nil
	},
}

func buildSystemInfoReq(command string) (*pb.SystemInfoRequest, error) {
	uuid := globals.GenerateUUID()
	req := &pb.SystemInfoRequest{Command: command, Rid: uuid, Requestor: "cli"}

	return req, nil
}

func init() {
}

func SendSystemInfoCmdSocket() {

}
