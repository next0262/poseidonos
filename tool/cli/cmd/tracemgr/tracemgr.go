package tracemgr

import (
	"cli/cmd/globals"
	"context"
	"fmt"
	"time"
	"go.opentelemetry.io/otel"
	"go.opentelemetry.io/otel/attribute"
	"go.opentelemetry.io/otel/exporters/otlp/otlptrace"
	"go.opentelemetry.io/otel/exporters/otlp/otlptrace/otlptracehttp"
	"go.opentelemetry.io/otel/sdk/resource"
	tracesdk "go.opentelemetry.io/otel/sdk/trace"
	semconv "go.opentelemetry.io/otel/semconv/v1.12.0"
	"go.opentelemetry.io/otel/trace"
)

var tp *tracesdk.TracerProvider

func InitTracerProvider(ctx context.Context, servName string, version string) error {

	client := otlptracehttp.NewClient(
		otlptracehttp.WithEndpoint(globals.OtlpServerAddress),
		otlptracehttp.WithInsecure(),
	)
	exp, err := otlptrace.New(ctx, client)
	if err != nil {
		return fmt.Errorf("creating OTLP trace exporter: %w", err)
	}

	tp = tracesdk.NewTracerProvider(
		// Always be sure to batch in production.
		tracesdk.WithBatcher(exp),
		// Record information about this application in a Resource.
		tracesdk.WithResource(resource.NewWithAttributes(
			semconv.SchemaURL,
			semconv.ServiceNameKey.String(servName),
			attribute.String("version", version),
		)),
	)

	otel.SetTracerProvider(tp)

	return nil

}

func SetTrace(ctx context.Context, appName string, funcName string) (context.Context, trace.Span) {

	ctx, span := otel.Tracer(appName).Start(ctx, funcName)

	return ctx, span

}

func Shutdown(ctx context.Context) error {
	ctx, cancel := context.WithTimeout(ctx, time.Second*5)
	defer cancel()
	if err := tp.Shutdown(ctx); err != nil {
		return fmt.Errorf("fail to shutdown OTel: %w", err)
	}

	return nil
}

// tracer := otel.Tracer("test-tracer")

// // Attributes represent additional key-value descriptors that can be bound
// // to a metric observer or recorder.
// commonAttrs := []attribute.KeyValue{
// 	attribute.String("attrA", "chocolate"),
// 	attribute.String("attrB", "raspberry"),
// 	attribute.String("attrC", "vanilla"),
// }

// // work begins
// ctx, span := tracer.Start(
// 	ctx,
// 	"CollectorExporter-Example",
// 	trace.WithAttributes(commonAttrs...))
