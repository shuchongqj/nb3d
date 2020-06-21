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
#pragma once


#include "../Container/Ptr.h"

#include <RmlUi/Core/FileInterface.h>

namespace Urho3D
{

class Context;

namespace Detail
{

class RmlFile : public RefCounted, public Rml::Core::FileInterface
{
public:
    /// Construct.
    explicit RmlFile(Context* context);

    /// Opens a file.
    Rml::Core::FileHandle Open(const Rml::Core::String& path) override;
    /// Closes a previously opened file.
    void Close(Rml::Core::FileHandle file) override;
    /// Reads data from a previously opened file.
    size_t Read(void* buffer, size_t size, Rml::Core::FileHandle file) override;
    /// Seeks to a point in a previously opened file.
    bool Seek(Rml::Core::FileHandle file, long offset, int origin) override;
    /// Returns the current position of the file pointer.
    size_t Tell(Rml::Core::FileHandle file) override;
    /// Returns the length of the file.
    size_t Length(Rml::Core::FileHandle file) override;

private:
    /// Context pointer.
    WeakPtr<Context> context_;
};

}   // namespace Detail

}   // namespace Urho3D
