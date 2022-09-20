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

#pragma once

#include "src/trace/trace_exporter.h"
#include "opentelemetry/trace/provider.h"
#include "opentelemetry/trace/propagation/http_trace_context.h"

using namespace opentelemetry;

namespace pos
{

template <typename T>
class HttpTextMapCarrier : public opentelemetry::context::propagation::TextMapCarrier
{
public:
    HttpTextMapCarrier<T>(T &headers) : headers_(headers) {}
    HttpTextMapCarrier() = default;
    virtual nostd::string_view Get(nostd::string_view key) const noexcept override
    { 
        auto it = headers_.find(key.data());
        if (it != headers_.end())
        {
            return it->second;
        }
        return "";
    }
    virtual void Set(nostd::string_view key, nostd::string_view value) noexcept override
    {
        headers_.insert(std::pair<std::string, std::string>(std::string(key), std::string(value)));
    }

    T headers_;
};

struct ContextW3C{
    std::string traceParent;
    std::string traceState;
};

class TraceSpan
{
public:
    TraceSpan();
    void Start(std::string name);
    void StartWithParent(std::string name, struct ContextW3C ctx);
    void End();
    void AddAttribute(nostd::string_view key, const common::AttributeValue &value);
    nostd::shared_ptr<trace::Span> GetSpan(void);
    nostd::shared_ptr<trace_api::Tracer> GetTracer(void);
private:
    TraceExporter *te{nullptr};
    nostd::shared_ptr<trace::TracerProvider> provider{nullptr};
    nostd::shared_ptr<trace::Span> span{nullptr};
    nostd::shared_ptr<trace_api::Tracer> tracer{nullptr};
};

class TraceScope
{
public:
    TraceScope(nostd::shared_ptr<trace_api::Tracer> tracer, nostd::shared_ptr<trace::Span> span);
private:
    trace::Scope scope;
};

#define POS_START_SPAN() \
    TraceSpan *tspan {nullptr};   \
    TraceScope *tscope {nullptr}; \
    if(TraceExporterSingleton::Instance(nullptr)->IsEnabled())  \
    {   \
        tspan = new TraceSpan;  \
        tspan->Start(std::string(__func__) + "()" + "@" + std::string(__FILE__) + ":" + std::to_string(__LINE__));  \
        tscope = new TraceScope(tspan->GetTracer(), tspan->GetSpan());  \
    }

#define POS_START_SPAN_WITH_PARENT(CTX) \
    TraceSpan *tspan {nullptr};   \
    TraceScope *tscope {nullptr}; \
    if(TraceExporterSingleton::Instance(nullptr)->IsEnabled())  \
    {   \
        tspan = new TraceSpan;  \
        tspan->StartWithParent(std::string(__func__) + "()" + "@" + std::string(__FILE__) + ":" + std::to_string(__LINE__), CTX);  \
        tscope = new TraceScope(tspan->GetTracer(), tspan->GetSpan());  \
    }

#define POS_ADD_SPAN_ATTR(KEY, VALUE)   \
    if(TraceExporterSingleton::Instance(nullptr)->IsEnabled())  \
    {   \
        if (nullptr != tspan){  \
            tspan->AddAttribute(KEY, VALUE);    \
        }   \
    }

#define POS_END_SPAN()  \
    if(TraceExporterSingleton::Instance(nullptr)->IsEnabled())  \
    {   \
        if (nullptr != tspan)   \
        {   \
            tspan->End();   \
            delete tspan;   \
            if (nullptr != tscope)  \
            {   \
                delete tscope;  \
            }   \
        }   \
    }
} // namespace pos