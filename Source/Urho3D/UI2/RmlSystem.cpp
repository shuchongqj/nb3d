//
// Copyright (c) 2017-2020 the rbfx project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#include "../Core/Context.h"
#include "../Core/Timer.h"
#include "../IO/Log.h"
#include "../Input/Input.h"
#include "../Resource/Localization.h"
#include "../UI2/RmlSystem.h"

#include <SDL/SDL_clipboard.h>

namespace Urho3D
{

namespace Detail
{

RmlSystem::RmlSystem(Context* context)
    : context_(context)
{
}

double RmlSystem::GetElapsedTime()
{
    return context_->GetSubsystem<Time>()->GetElapsedTime();
}

int RmlSystem::TranslateString(Rml::Core::String& translated, const Rml::Core::String& input)
{
    Localization* l18n = context_->GetSubsystem<Localization>();
    if (l18n->GetLanguageIndex() > -1)
    {
        translated = l18n->Get(input.c_str()).c_str();
        return 1;
    }
    translated = input;
    return 0;
}

bool RmlSystem::LogMessage(Rml::Core::Log::Type type, const Rml::Core::String& message)
{
    switch (type)
    {
    case Rml::Core::Log::LT_ALWAYS:
    case Rml::Core::Log::LT_ERROR:
    case Rml::Core::Log::LT_ASSERT:
        URHO3D_LOGERROR(message.c_str());
        break;
    case Rml::Core::Log::LT_WARNING:
        URHO3D_LOGWARNING(message.c_str());
        break;
    case Rml::Core::Log::LT_INFO:
        URHO3D_LOGINFO(message.c_str());
        break;
    case Rml::Core::Log::LT_DEBUG:
        URHO3D_LOGDEBUG(message.c_str());
        break;
    default:
        return false;
    }
    return true;
}

void RmlSystem::SetMouseCursor(const Rml::Core::String& cursor_name)
{
    SystemInterface::SetMouseCursor(cursor_name);
}

void RmlSystem::SetClipboardText(const Rml::Core::String& text)
{
    SDL_SetClipboardText(text.c_str());
}

void RmlSystem::GetClipboardText(Rml::Core::String& text)
{
    text = SDL_GetClipboardText();
}

void RmlSystem::ActivateKeyboard()
{
    context_->GetSubsystem<Input>()->SetScreenKeyboardVisible(true);
}

void RmlSystem::DeactivateKeyboard()
{
    context_->GetSubsystem<Input>()->SetScreenKeyboardVisible(false);
}

}   // namespace Detail

}   // namespace Urho3D
