module cli

go 1.18

replace pnconnector => ./lib/pnconnector

require (
	code.cloudfoundry.org/bytefmt v0.0.0-20210608160410-67692ebc98de
	github.com/c2h5oh/datasize v0.0.0-20200825124411-48ed595a09d2
	github.com/google/uuid v1.3.0
	github.com/labstack/gommon v0.3.0
	github.com/lib/pq v1.0.0
	github.com/spf13/cast v1.4.1
	github.com/spf13/cobra v1.5.0
	github.com/zpatrick/go-bytesize v0.0.0-20170214182126-40b68ac70b6a
	go.opentelemetry.io/otel v1.9.0
	go.opentelemetry.io/otel/exporters/otlp/otlptrace v1.9.0
	go.opentelemetry.io/otel/exporters/otlp/otlptrace/otlptracehttp v1.9.0
	go.opentelemetry.io/otel/sdk v1.9.0
	go.opentelemetry.io/otel/trace v1.9.0
	google.golang.org/genproto v0.0.0-20211118181313-81c1377c94b1
	google.golang.org/grpc v1.46.2
	google.golang.org/protobuf v1.28.0
	pnconnector v0.0.0-00010101000000-000000000000
)

require (
	github.com/cenkalti/backoff/v4 v4.1.3 // indirect
	github.com/cpuguy83/go-md2man/v2 v2.0.2 // indirect
	github.com/go-logr/logr v1.2.3 // indirect
	github.com/go-logr/stdr v1.2.2 // indirect
	github.com/golang/protobuf v1.5.2 // indirect
	github.com/grpc-ecosystem/grpc-gateway/v2 v2.7.0 // indirect
	github.com/inconshreveable/mousetrap v1.0.0 // indirect
	github.com/influxdata/influxdb v1.8.0 // indirect
	github.com/juju/errors v0.0.0-20200330140219-3fe23663418f // indirect
	github.com/konsorten/go-windows-terminal-sequences v1.0.1 // indirect
	github.com/mattn/go-colorable v0.1.6 // indirect
	github.com/mattn/go-isatty v0.0.12 // indirect
	github.com/russross/blackfriday/v2 v2.1.0 // indirect
	github.com/sirupsen/logrus v1.5.0 // indirect
	github.com/spf13/pflag v1.0.5 // indirect
	github.com/valyala/bytebufferpool v1.0.0 // indirect
	github.com/valyala/fasttemplate v1.1.0 // indirect
	go.opentelemetry.io/otel/exporters/otlp/internal/retry v1.9.0 // indirect
	go.opentelemetry.io/proto/otlp v0.18.0 // indirect
	golang.org/x/net v0.0.0-20210428140749-89ef3d95e781 // indirect
	golang.org/x/sys v0.0.0-20210510120138-977fb7262007 // indirect
	golang.org/x/text v0.3.6 // indirect
	gopkg.in/yaml.v2 v2.4.0 // indirect
)
