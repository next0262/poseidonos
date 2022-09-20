/*
 *   BSD LICENSE
 *   Copyright (c) 2022 Samsung Electronics Corporation
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

#include "src/trace/trace_instrumentation.h"

using namespace opentelemetry;

namespace pos
{

TraceSpan::TraceSpan()
: te(TraceExporterSingleton::Instance(nullptr))
{
    provider = trace::Provider::GetTracerProvider();
    tracer = provider->GetTracer(te->GetServiceName(), te->GetServiceVersion());
}

void
TraceSpan::Start(std::string name)
{
    span = tracer->StartSpan(name);
}

void
TraceSpan::StartWithParent(std::string name, struct ContextW3C ctx)
{
    HttpTextMapCarrier<std::map<std::string, std::string>> carrier;

    carrier.Set(trace::propagation::kTraceParent, ctx.traceParent);
    carrier.Set(trace::propagation::kTraceState, ctx.traceState);

    trace::propagation::HttpTraceContext httpTraceContext;

    auto currentContext = context::RuntimeContext::GetCurrent();
    auto newContext = httpTraceContext.Extract(carrier, currentContext);

    trace::StartSpanOptions opts;    
    opts.parent = trace::GetSpan(newContext)->GetContext();

    span = tracer->StartSpan(name, opts);
}

void
TraceSpan::End()
{
    span->End();
}

void
TraceSpan::AddAttribute(nostd::string_view key, const common::AttributeValue &value)
{
    span->SetAttribute(key,value);
}

nostd::shared_ptr<trace::Span>
TraceSpan::GetSpan(void)
{
    return span;
}

nostd::shared_ptr<trace_api::Tracer>
TraceSpan::GetTracer(void)
{
    return tracer;
}

TraceScope::TraceScope(nostd::shared_ptr<trace_api::Tracer> tracer, nostd::shared_ptr<trace::Span> span)
: scope(tracer->WithActiveSpan(span))
{
}

}