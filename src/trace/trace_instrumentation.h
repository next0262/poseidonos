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

using namespace opentelemetry;

namespace pos
{

class TraceSpan
{
public:
    TraceSpan();
    void Start(std::string str);
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
        tspan->Start(std::string(__func__) + "@" + std::string(__FILE__));  \
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