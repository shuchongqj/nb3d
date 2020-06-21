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
#include "../IO/File.h"
#include "../IO/FileSystem.h"
#include "../Resource/ResourceCache.h"
#include "../UI2/RmlFile.h"

namespace Urho3D
{

namespace Detail
{

RmlFile::RmlFile(Urho3D::Context* context)
    : context_(context)
{

}

Rml::Core::FileHandle RmlFile::Open(const Rml::Core::String& path)
{
    SharedPtr<File> file(new File(context_));
    ResourceCache* cache = context_->GetSubsystem<ResourceCache>();
    FileSystem* fs = context_->GetSubsystem<FileSystem>();

    for (const ea::string& prefix : cache->GetResourceDirs())
    {
        ea::string fullPath = AddTrailingSlash(prefix) + path.c_str();
        if (fs->Exists(fullPath) && file->Open(fullPath.c_str()))
            return reinterpret_cast<Rml::Core::FileHandle>(file.Detach());
    }

    if (file->Open(path.c_str()))
        return reinterpret_cast<Rml::Core::FileHandle>(file.Detach());

    return 0;
}

void RmlFile::Close(Rml::Core::FileHandle file)
{
    delete reinterpret_cast<File*>(file);
}

size_t RmlFile::Read(void* buffer, size_t size, Rml::Core::FileHandle file)
{
    return reinterpret_cast<File*>(file)->Read(buffer, size);
}

bool RmlFile::Seek(Rml::Core::FileHandle file, long offset, int origin)
{
    File* fp = reinterpret_cast<File*>(file);
    if (origin == SEEK_CUR)
        offset = fp->Tell() + offset;
    else if (origin == SEEK_END)
        offset = fp->GetSize() - offset;
    return fp->Seek(offset) == offset;
}

size_t RmlFile::Tell(Rml::Core::FileHandle file)
{
    return reinterpret_cast<File*>(file)->Tell();
}

size_t RmlFile::Length(Rml::Core::FileHandle file)
{
    return reinterpret_cast<File*>(file)->GetSize();
}

}   // namespace Detail

}   // namespace Urho3D
