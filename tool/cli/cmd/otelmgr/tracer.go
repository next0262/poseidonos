package otelmgr

import (
	"context"
	"go.opentelemetry.io/otel"
	tracesdk "go.opentelemetry.io/otel/sdk/trace"
	"go.opentelemetry.io/otel/trace"
)

type TracerManager struct {
	tp   *tracesdk.TracerProvider
	ctx  context.Context
	span trace.Span
}

func (mgr *TracerManager) SetTrace(ctx context.Context, appName string, funcName string) {

	mgr.ctx, mgr.span = otel.Tracer(appName).Start(ctx, funcName)

}

func (mgr *TracerManager) RecordError(err error) {

	mgr.span.RecordError(err)

}

func (mgr *TracerManager) ReleaseTrace() {

	mgr.span.End()

}
