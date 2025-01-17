/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <LibWeb/DOM/Element.h>
#include <LibWeb/HTML/EventNames.h>
#include <LibWeb/HTML/GlobalEventHandlers.h>

namespace Web::HTML {

class HTMLElement
    : public DOM::Element
    , public HTML::GlobalEventHandlers {
public:
    using WrapperType = Bindings::HTMLElementWrapper;

    HTMLElement(DOM::Document&, const QualifiedName& qualified_name);
    virtual ~HTMLElement() override;

    String title() const { return attribute(HTML::AttributeNames::title); }

    virtual bool is_editable() const final;
    String content_editable() const;
    void set_content_editable(const String&);

    String inner_text();
    void set_inner_text(StringView);

    bool cannot_navigate() const;

protected:
    virtual void parse_attribute(const FlyString& name, const String& value) override;

private:
    // ^HTML::GlobalEventHandlers
    virtual EventTarget& global_event_handlers_to_event_target() override { return *this; }

    enum class ContentEditableState {
        True,
        False,
        Inherit,
    };
    ContentEditableState content_editable_state() const;
};

}
