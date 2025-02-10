//Copyright (c) 2025 Joshua Shelton
//
//This software is provided 'as-is', without any express or implied
//        warranty. In no event will the authors be held liable for any damages
//arising from the use of this software.
//
//Permission is granted to anyone to use this software for any purpose,
//        including commercial applications, and to alter it and redistribute it
//freely, subject to the following restrictions:
//
//1. The origin of this software must not be misrepresented; you must not
//claim that you wrote the original software. If you use this software
//in a product, an acknowledgment in the product documentation would be
//appreciated but is not required.
//2. Altered source versions must be plainly marked as such, and must not be
//        misrepresented as being the original software.
//3. This notice may not be removed or altered from any source distribution.

#include <iostream>
#include "imgui_impl_slag.h"
//fragment shader

//#version 450 core
//layout(location = 0) in vec2 aPos;
//layout(location = 1) in vec2 aUV;
//layout(location = 2) in uint aColor;
//
//layout(push_constant) uniform uPushConstant {
//        vec2 uScale;
//        vec2 uTranslate;
//} pc;
//
//out gl_PerVertex {
//        vec4 gl_Position;
//};
//
//layout(location = 0) out struct {
//    vec4 Color;
//    vec2 UV;
//} Out;
//
//void main()
//{
//    Out.Color = unpackUnorm4x8(aColor);
//    Out.UV = aUV;
//    gl_Position = vec4(aPos.x * pc.uScale.x + pc.uTranslate.x,-(aPos.y * pc.uScale.y + pc.uTranslate.y) , 0, 1);
//}

const unsigned char DEAR_IMGUI_SLAG_IMPL_VERT_SHADER_DATA[] = {
        0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x0b, 0x00, 0x0d, 0x00, 0x3b, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x06, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x47, 0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, 0x35, 0x30,
        0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x0f, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e,
        0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00,
        0x1d, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00,
        0xc2, 0x01, 0x00, 0x00, 0x04, 0x00, 0x0a, 0x00, 0x47, 0x4c, 0x5f, 0x47, 0x4f, 0x4f, 0x47, 0x4c,
        0x45, 0x5f, 0x63, 0x70, 0x70, 0x5f, 0x73, 0x74, 0x79, 0x6c, 0x65, 0x5f, 0x6c, 0x69, 0x6e, 0x65,
        0x5f, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00,
        0x47, 0x4c, 0x5f, 0x47, 0x4f, 0x4f, 0x47, 0x4c, 0x45, 0x5f, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64,
        0x65, 0x5f, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x00, 0x05, 0x00, 0x04, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00,
        0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x05, 0x00, 0x09, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x00, 0x00, 0x06, 0x00, 0x04, 0x00,
        0x09, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x55, 0x56, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00,
        0x0b, 0x00, 0x00, 0x00, 0x4f, 0x75, 0x74, 0x00, 0x05, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x61, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, 0x17, 0x00, 0x00, 0x00,
        0x61, 0x55, 0x56, 0x00, 0x05, 0x00, 0x06, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x67, 0x6c, 0x5f, 0x50,
        0x65, 0x72, 0x56, 0x65, 0x72, 0x74, 0x65, 0x78, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00,
        0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74,
        0x69, 0x6f, 0x6e, 0x00, 0x05, 0x00, 0x03, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x05, 0x00, 0x04, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x61, 0x50, 0x6f, 0x73, 0x00, 0x00, 0x00, 0x00,
        0x05, 0x00, 0x06, 0x00, 0x23, 0x00, 0x00, 0x00, 0x75, 0x50, 0x75, 0x73, 0x68, 0x43, 0x6f, 0x6e,
        0x73, 0x74, 0x61, 0x6e, 0x74, 0x00, 0x00, 0x00, 0x06, 0x00, 0x05, 0x00, 0x23, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x75, 0x53, 0x63, 0x61, 0x6c, 0x65, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00,
        0x23, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x75, 0x54, 0x72, 0x61, 0x6e, 0x73, 0x6c, 0x61,
        0x74, 0x65, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, 0x25, 0x00, 0x00, 0x00, 0x70, 0x63, 0x00, 0x00,
        0x47, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x47, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
        0x47, 0x00, 0x04, 0x00, 0x17, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x48, 0x00, 0x05, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x03, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
        0x47, 0x00, 0x04, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x48, 0x00, 0x05, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0x23, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x23, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x47, 0x00, 0x03, 0x00, 0x23, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x21, 0x00, 0x03, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, 0x06, 0x00, 0x00, 0x00,
        0x20, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x04, 0x00, 0x09, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
        0x09, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x0e, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x13, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
        0x07, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x16, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x16, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x19, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x03, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
        0x20, 0x00, 0x04, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00,
        0x3b, 0x00, 0x04, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
        0x3b, 0x00, 0x04, 0x00, 0x16, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x2b, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x20, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
        0x1e, 0x00, 0x04, 0x00, 0x23, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
        0x20, 0x00, 0x04, 0x00, 0x24, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00,
        0x3b, 0x00, 0x04, 0x00, 0x24, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
        0x20, 0x00, 0x04, 0x00, 0x26, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
        0x2b, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f,
        0x36, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
        0x0e, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x06, 0x00,
        0x07, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
        0x11, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
        0x0b, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x14, 0x00, 0x00, 0x00,
        0x12, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
        0x17, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x19, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00,
        0x0b, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x1a, 0x00, 0x00, 0x00,
        0x18, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x20, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00,
        0x1e, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00,
        0x22, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x26, 0x00, 0x00, 0x00,
        0x27, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00,
        0x3d, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00,
        0x85, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00,
        0x28, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x26, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00,
        0x25, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
        0x06, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x81, 0x00, 0x05, 0x00,
        0x06, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00,
        0x41, 0x00, 0x05, 0x00, 0x20, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00,
        0x2d, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00,
        0x2e, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x26, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
        0x25, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
        0x06, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x85, 0x00, 0x05, 0x00,
        0x06, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00,
        0x41, 0x00, 0x06, 0x00, 0x26, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00,
        0x15, 0x00, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00,
        0x34, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x81, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00,
        0x35, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x04, 0x00,
        0x06, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x50, 0x00, 0x07, 0x00,
        0x07, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00,
        0x37, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x13, 0x00, 0x00, 0x00,
        0x3a, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00,
        0x3a, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00
};

//fragment shader

//#version 450 core
//layout(location = 0) out vec4 fColor;
//
//layout(set=0, binding=0) uniform sampler2D sTexture;
//
//layout(location = 0) in struct {
//    vec4 Color;
//    vec2 UV;
//} In;
//
//void main()
//{
//    fColor = In.Color * texture(sTexture, In.UV.st);
//}

const unsigned char DEAR_IMGUI_SLAG_IMPL_FRAG_SHADER_DATA[]  = {
        0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x0b, 0x00, 0x0d, 0x00, 0x1e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x06, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x47, 0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, 0x35, 0x30,
        0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x0f, 0x00, 0x07, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e,
        0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x10, 0x00, 0x03, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00,
        0xc2, 0x01, 0x00, 0x00, 0x04, 0x00, 0x0a, 0x00, 0x47, 0x4c, 0x5f, 0x47, 0x4f, 0x4f, 0x47, 0x4c,
        0x45, 0x5f, 0x63, 0x70, 0x70, 0x5f, 0x73, 0x74, 0x79, 0x6c, 0x65, 0x5f, 0x6c, 0x69, 0x6e, 0x65,
        0x5f, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00,
        0x47, 0x4c, 0x5f, 0x47, 0x4f, 0x4f, 0x47, 0x4c, 0x45, 0x5f, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64,
        0x65, 0x5f, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x00, 0x05, 0x00, 0x04, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x04, 0x00,
        0x09, 0x00, 0x00, 0x00, 0x66, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00,
        0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x00, 0x00, 0x06, 0x00, 0x04, 0x00,
        0x0b, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x55, 0x56, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00,
        0x0d, 0x00, 0x00, 0x00, 0x49, 0x6e, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x16, 0x00, 0x00, 0x00,
        0x73, 0x54, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
        0x09, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
        0x0d, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
        0x16, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
        0x16, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x21, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
        0x16, 0x00, 0x03, 0x00, 0x06, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00,
        0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
        0x08, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00,
        0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00,
        0x0a, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x04, 0x00,
        0x0b, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
        0x0c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00,
        0x0c, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00,
        0x0e, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00,
        0x0e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
        0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x19, 0x00, 0x09, 0x00,
        0x13, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x1b, 0x00, 0x03, 0x00, 0x14, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
        0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00,
        0x15, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00,
        0x0e, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
        0x19, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x36, 0x00, 0x05, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
        0xf8, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x11, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
        0x07, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
        0x14, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00,
        0x19, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
        0x3d, 0x00, 0x04, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00,
        0x57, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00,
        0x1b, 0x00, 0x00, 0x00, 0x85, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00,
        0x12, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x09, 0x00, 0x00, 0x00,
        0x1d, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00
};

void* (*IMGUI_IMPL_SLAG_GET_NATIVE_WINDOW_HANDLE)(ImGuiViewport* fromViewport)=nullptr;
class ImGuiFrameResources: public slag::FrameResources
{
public:
    slag::CommandBuffer* commandBuffer = nullptr;
    ImGuiFrameResources()
    {
        commandBuffer = slag::CommandBuffer::newCommandBuffer(slag::GpuQueue::GRAPHICS);
    }
    ~ImGuiFrameResources()override
    {
        if(commandBuffer)
        {
            delete commandBuffer;
        }
    }
    void waitForResourcesToFinish()override
    {
        commandBuffer->waitUntilFinished();
    }
    bool isFinished()override
    {
        return commandBuffer->isFinished();
    }
};

slag::FrameResources* ImGui_Slag_CreateFrameResources(size_t frameIndex, slag::Swapchain* swapchain)
{
    return new ImGuiFrameResources();
}

void ImGui_Slag_CreateWindow(ImGuiViewport* viewport)
{
    assert(IMGUI_IMPL_SLAG_GET_NATIVE_WINDOW_HANDLE!= nullptr && "Must assign function to extract native window handle from ImGuiViewport in ImGui_ImplSlag_Init!");
    ImGuiIO& io = ImGui::GetIO();
    auto slagData = static_cast<ImGui_ImplSlag_Data*>(io.BackendRendererUserData);

    auto pd = slagData->platformData;
    slag::PlatformData platformData{};

    platformData.platform = pd.platform;

    switch (pd.platform)
    {

        case slag::PlatformData::WIN_32:
            platformData.data.win32 = {.hwnd = IMGUI_IMPL_SLAG_GET_NATIVE_WINDOW_HANDLE(viewport), .hinstance = pd.data.win32.hinstance};
            break;
        case slag::PlatformData::X11:
            platformData.data.x11 = {.window = IMGUI_IMPL_SLAG_GET_NATIVE_WINDOW_HANDLE(viewport), .display = pd.data.x11.display};
            break;
            //TODO: test this
        case slag::PlatformData::WAYLAND:
            platformData.data.wayland = {.surface = IMGUI_IMPL_SLAG_GET_NATIVE_WINDOW_HANDLE(viewport), .display = pd.data.wayland.surface};
            break;
    }

    auto viewportData = new ImGui_ImplSlag_ViewportData(slag::Swapchain::newSwapchain(platformData,viewport->Size.x,viewport->Size.y,3,slag::Swapchain::MAILBOX,slagData->backBufferFormat,ImGui_Slag_CreateFrameResources),false);
    viewportData->swapchain->next();
    viewport->RendererUserData = viewportData;
}
void ImGui_Slag_DestroyWindow(ImGuiViewport* viewport)
{
    auto viewportData = static_cast<ImGui_ImplSlag_ViewportData*>(viewport->RendererUserData);
    delete viewportData;
    viewport->RendererUserData = nullptr;
}
void ImGui_Slag_SetWindowSize(ImGuiViewport* viewport, ImVec2 newSize)
{
    auto viewportData = static_cast<ImGui_ImplSlag_ViewportData*>(viewport->RendererUserData);
    viewportData->swapchain->resize(newSize.x,newSize.y);
}
void ImGui_Slag_RenderWindow(ImGuiViewport* viewport, void* unknown)
{
    ImGuiIO& io = ImGui::GetIO();

    auto viewportData = static_cast<ImGui_ImplSlag_ViewportData*>(viewport->RendererUserData);
    auto frame = viewportData->swapchain->currentFrame();
    if(frame)
    {
        auto rendererData = static_cast<ImGui_ImplSlag_Data*>(io.BackendRendererUserData);
        auto resources = static_cast<ImGuiFrameResources*>(frame->resources);
        auto commandBuffer = resources->commandBuffer;
        auto renderBuffer = frame->backBuffer();

        commandBuffer->begin();
        commandBuffer->bindDescriptorPool(rendererData->descriptorPool);
        commandBuffer->insertBarrier(
                {.texture=renderBuffer,
                        .oldLayout=slag::Texture::UNDEFINED,
                        .newLayout=slag::Texture::RENDER_TARGET,
                        .accessBefore=slag::BarrierAccessFlags::NONE,
                        .accessAfter=slag::BarrierAccessFlags::COLOR_ATTACHMENT_WRITE,
                        .syncBefore = slag::PipelineStageFlags::NONE,
                        .syncAfter = slag::PipelineStageFlags::COLOR_ATTACHMENT
                }
        );

        slag::Attachment attachment{.texture=renderBuffer,.layout=slag::Texture::RENDER_TARGET,.clearOnLoad=true,.clear={.color={0.0f,0.0f,0.0f,1.0f}}};
        commandBuffer->beginRendering(&attachment,1, nullptr,{.offset={0,0},.extent={renderBuffer->width(),renderBuffer->height()}});

        ImGui_ImplSlag_RenderDrawData(viewport->DrawData,commandBuffer);
        commandBuffer->endRendering();
        commandBuffer->insertBarrier(
                {.texture=frame->backBuffer(),
                        .oldLayout=slag::Texture::RENDER_TARGET,
                        .newLayout=slag::Texture::PRESENT,
                        .accessBefore=slag::BarrierAccessFlags::COLOR_ATTACHMENT_WRITE,
                        .accessAfter=slag::BarrierAccessFlags::NONE,
                        .syncBefore = slag::PipelineStageFlags::COLOR_ATTACHMENT,
                        .syncAfter = slag::PipelineStageFlags::NONE
                }
        );

        commandBuffer->end();

        slag::SlagLib::graphicsCard()->graphicsQueue()->submit(&commandBuffer, 1, nullptr, 0, nullptr, 0, frame);
    }
}
void ImGui_Slag_SwapBuffers(ImGuiViewport* viewport, void* unknown)
{
    auto viewportData = static_cast<ImGui_ImplSlag_ViewportData*>(viewport->RendererUserData);
    viewportData->swapchain->next();
}
bool ImGui_ImplSlag_Init(slag::Swapchain* mainSwapchain, slag::PlatformData platformData, void* (*extractNativeHandle)(ImGuiViewport* fromViewport), slag::Sampler* sampler, slag::Pixels::Format backBufferFormat)
{
    //set backend data
    ImGuiIO& io = ImGui::GetIO();
    io.BackendRendererName = "imgui_impl_slag";
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
    io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;
    auto backendData = new ImGui_ImplSlag_Data();
    io.BackendRendererUserData = backendData;

    slag::VertexDescription vertexDescription(1);
    vertexDescription.add(slag::GraphicsTypes::VECTOR2, offsetof(ImDrawVert,pos),0);
    vertexDescription.add(slag::GraphicsTypes::VECTOR2, offsetof(ImDrawVert,uv),0);
    vertexDescription.add(slag::GraphicsTypes::UNSIGNED_INTEGER, offsetof(ImDrawVert,col),0);

    slag::FrameBufferDescription frameBufferDescription;
    frameBufferDescription.addColorTarget(backBufferFormat);

    slag::ShaderModule modules[2]
            {
                    slag::ShaderModule (slag::ShaderStageFlags::VERTEX, (void*) DEAR_IMGUI_SLAG_IMPL_VERT_SHADER_DATA, sizeof(DEAR_IMGUI_SLAG_IMPL_VERT_SHADER_DATA)),
                    slag::ShaderModule (slag::ShaderStageFlags::FRAGMENT, (void*) DEAR_IMGUI_SLAG_IMPL_FRAG_SHADER_DATA, sizeof(DEAR_IMGUI_SLAG_IMPL_FRAG_SHADER_DATA))
            };
    slag::ShaderProperties shaderProperties;
    backendData->shaderPipeline = slag::ShaderPipeline::newShaderPipeline(modules,2, nullptr,0,shaderProperties,&vertexDescription,frameBufferDescription);
    backendData->sampler = sampler;
    backendData->platformData = platformData;
    backendData->backBufferFormat = backBufferFormat;

    //create dear imgui managed resources(just the texture, the descriptor bundle has to have a current descriptor pool, which requires an active frame)
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    size_t upload_size = width * height * 4 * sizeof(char);
    backendData->fontsTexture = slag::Texture::newTexture(pixels,slag::Pixels::R8G8B8A8_UNORM,width,height,1,slag::TextureUsageFlags::SAMPLED_IMAGE,slag::Texture::SHADER_RESOURCE);

    auto viewportData = new ImGui_ImplSlag_ViewportData(mainSwapchain, true);

    auto mainViewport = ImGui::GetMainViewport();
    mainViewport->RendererUserData = viewportData;

    ImGuiPlatformIO& platformIo = ImGui::GetPlatformIO();
    platformIo.Renderer_CreateWindow = ImGui_Slag_CreateWindow;
    platformIo.Renderer_DestroyWindow = ImGui_Slag_DestroyWindow;
    platformIo.Renderer_SetWindowSize = ImGui_Slag_SetWindowSize;
    platformIo.Renderer_RenderWindow = ImGui_Slag_RenderWindow;
    platformIo.Renderer_SwapBuffers = ImGui_Slag_SwapBuffers;

    IMGUI_IMPL_SLAG_GET_NATIVE_WINDOW_HANDLE = extractNativeHandle;

    return true;
}

void ImGui_ImplSlag_Shutdown()
{
    ImGuiIO& io = ImGui::GetIO();
    auto backend = static_cast<ImGui_ImplSlag_Data*>(io.BackendRendererUserData);
    //clean up IMGUI managed resources
    delete backend->fontsTexture;
    delete backend->fontsTextureBundle;
    delete backend->shaderPipeline;

    delete backend;
    io.BackendRendererUserData = nullptr;
}

void ImGui_ImplSlag_NewFrame(slag::DescriptorPool* framePool)
{
    ImGuiIO& io = ImGui::GetIO();
    auto rendererData = static_cast<ImGui_ImplSlag_Data*>(io.BackendRendererUserData);
    rendererData->descriptorPool = framePool;
    if(rendererData->fontsTextureBundle== nullptr)
    {
        rendererData->fontsTextureBundle = new slag::DescriptorBundle(framePool->makeBundle(rendererData->shaderPipeline->descriptorGroup(0)));
    }
    else
    {
        *(rendererData->fontsTextureBundle) = framePool->makeBundle(rendererData->shaderPipeline->descriptorGroup(0));

    }
    rendererData->fontsTextureBundle->setSamplerAndTexture(0,0,rendererData->fontsTexture, slag::Texture::SHADER_RESOURCE,rendererData->sampler);
    io.Fonts->SetTexID((ImTextureID)rendererData->fontsTextureBundle);
}
void ImGui_ImplSlag_SetupRenderState(ImDrawData* draw_data, slag::ShaderPipeline* pipeline, slag::CommandBuffer* commandBuffer, slag::Buffer* vertexBuffer, slag::Buffer* indexBuffer, uint32_t frameBufferWidth, uint32_t frameBufferHeight)
{
    ImGuiIO& io = ImGui::GetIO();
    auto slagData = static_cast<ImGui_ImplSlag_Data*>(io.BackendRendererUserData);

    commandBuffer->bindGraphicsShader(slagData->shaderPipeline);


    // Bind Vertex And Index Buffer:
    if (draw_data->TotalVtxCount > 0)
    {
        size_t offset = 0;
        size_t stride = sizeof(ImDrawVert);
        size_t size = vertexBuffer->size();
        commandBuffer->bindVertexBuffers(0,&vertexBuffer,&offset,&size,&stride,1);
        commandBuffer->bindIndexBuffer(indexBuffer,sizeof(ImDrawIdx) == 2 ? slag::Buffer::UINT16: slag::Buffer::UINT32,0);
    }

    commandBuffer->setViewPort(0,0,frameBufferWidth,frameBufferHeight,1,0);

    {
        float scale[2];
        scale[0] = 2.0f / draw_data->DisplaySize.x;
        scale[1] = 2.0f / draw_data->DisplaySize.y;
        float translate[2];
        translate[0] =  -1.0f - draw_data->DisplayPos.x * scale[0];
        translate[1] = -1.0f - draw_data->DisplayPos.y * scale[1];
        commandBuffer->pushConstants(pipeline,slag::ShaderStageFlags::VERTEX,0,sizeof(float)*2,scale);
        commandBuffer->pushConstants(pipeline,slag::ShaderStageFlags::VERTEX,sizeof(float)*2,sizeof(float)*2,translate);
        auto drawList = draw_data->CmdLists.Data[0];

    }
}
void ImGui_ImplSlag_RenderDrawData(ImDrawData* draw_data, slag::CommandBuffer* commandBuffer)
{
    ImGuiIO& io = ImGui::GetIO();
    auto rendererData = static_cast<ImGui_ImplSlag_Data*>(io.BackendRendererUserData);
    auto rendererViewportData = static_cast<ImGui_ImplSlag_ViewportData*>(draw_data->OwnerViewport->RendererUserData);
    auto currentIndex = rendererViewportData->swapchain->currentFrameIndex();
    auto shader = rendererData->shaderPipeline;
    auto sampler = rendererData->sampler;
    if(draw_data->TotalVtxCount > 0)
    {
        if(rendererViewportData->drawDataArrays[currentIndex] == nullptr)
        {
            //create new arrays that will fit the data
            rendererViewportData->drawDataArrays[currentIndex]= slag::Buffer::newBuffer(draw_data->TotalVtxCount*sizeof(ImDrawVert),slag::Buffer::CPU_AND_GPU,slag::Buffer::VERTEX_BUFFER);
            rendererViewportData->drawDataIndexArrays[currentIndex]= slag::Buffer::newBuffer(draw_data->TotalIdxCount*sizeof(ImDrawIdx),slag::Buffer::CPU_AND_GPU,slag::Buffer::INDEX_BUFFER);
        }

        if(rendererViewportData->drawDataArrays[currentIndex]->size()< draw_data->TotalVtxCount*sizeof(ImDrawVert) ||
           rendererViewportData->drawDataArrays[currentIndex]->size()>= draw_data->TotalVtxCount*sizeof(ImDrawVert)*1.75
                )
        {
            delete rendererViewportData->drawDataArrays[currentIndex];
            rendererViewportData->drawDataArrays[currentIndex]= slag::Buffer::newBuffer(draw_data->TotalVtxCount*sizeof(ImDrawVert),slag::Buffer::CPU_AND_GPU,slag::Buffer::VERTEX_BUFFER);
        }
        if(rendererViewportData->drawDataIndexArrays[currentIndex]->size()< draw_data->TotalIdxCount*sizeof(ImDrawIdx) ||
           rendererViewportData->drawDataIndexArrays[currentIndex]->size()>= draw_data->TotalIdxCount*sizeof(ImDrawIdx)*1.75)
        {
            delete rendererViewportData->drawDataIndexArrays[currentIndex];
            rendererViewportData->drawDataIndexArrays[currentIndex]= slag::Buffer::newBuffer(draw_data->TotalIdxCount*sizeof(ImDrawIdx),slag::Buffer::CPU_AND_GPU,slag::Buffer::INDEX_BUFFER);
        }
        //copy draw data into buffers
        auto vertexBuffer = rendererViewportData->drawDataArrays[currentIndex];
        auto indexBuffer = rendererViewportData->drawDataIndexArrays[currentIndex];
        size_t vertexOffset = 0;
        size_t indexOffset = 0;
        for(int i=0; i<draw_data->CmdListsCount; i++)
        {
            const ImDrawList* draw_list = draw_data->CmdLists[i];
            auto vsize = draw_list->VtxBuffer.Size*sizeof(ImDrawVert);
            auto isize = draw_list->IdxBuffer.Size*sizeof(ImDrawIdx);
            vertexBuffer->update(vertexOffset,draw_list->VtxBuffer.Data,vsize);
            indexBuffer->update(indexOffset,draw_list->IdxBuffer.Data,isize);
            vertexOffset+=vsize;
            indexOffset+=isize;
        }
        auto frameBufferWidth = rendererViewportData->swapchain->width();
        auto frameBufferHeight = rendererViewportData->swapchain->height();

        ImGui_ImplSlag_SetupRenderState(draw_data,shader,commandBuffer,vertexBuffer,indexBuffer,frameBufferWidth,frameBufferHeight);
        // Setup render state structure (for callbacks and custom texture bindings)
        ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
        ImGui_ImplSlag_RenderState render_state;
        render_state.commandBuffer = commandBuffer;
        render_state.shader = shader;
        platform_io.Renderer_RenderState = &render_state;

        // Will project scissor/clipping rectangles into framebuffer space
        ImVec2 clip_off = draw_data->DisplayPos;         // (0,0) unless using multi-viewports
        ImVec2 clip_scale = draw_data->FramebufferScale; // (1,1) unless using retina display which are often (2,2)

        size_t vertexDrawOffset = 0;
        size_t indexDrawOffset = 0;
        for(int i=0; i< draw_data->CmdListsCount; i++)
        {
            const ImDrawList* draw_list = draw_data->CmdLists[i];
            for (int cmd_i = 0; cmd_i < draw_list->CmdBuffer.Size; cmd_i++)
            {
                const ImDrawCmd* pcmd = &draw_list->CmdBuffer[cmd_i];
                if (pcmd->UserCallback != nullptr)
                {
                    // User callback, registered via ImDrawList::AddCallback()
                    // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                    if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                    {
                        ImGui_ImplSlag_SetupRenderState(draw_data,shader,commandBuffer,vertexBuffer,indexBuffer,frameBufferWidth,frameBufferHeight);
                    }
                    else
                    {
                        pcmd->UserCallback(draw_list,pcmd);
                    }
                }
                else
                {
                    // Project scissor/clipping rectangles into framebuffer space
                    ImVec2 clip_min((pcmd->ClipRect.x - clip_off.x) * clip_scale.x, (pcmd->ClipRect.y - clip_off.y) * clip_scale.y);
                    ImVec2 clip_max((pcmd->ClipRect.z - clip_off.x) * clip_scale.x, (pcmd->ClipRect.w - clip_off.y) * clip_scale.y);

                    // Clamp to viewport as vkCmdSetScissor() won't accept values that are off bounds
                    if (clip_min.x < 0.0f) { clip_min.x = 0.0f; }
                    if (clip_min.y < 0.0f) { clip_min.y = 0.0f; }
                    if (clip_max.x > frameBufferWidth) { clip_max.x = (float)frameBufferWidth; }
                    if (clip_max.y > frameBufferHeight) { clip_max.y = (float)frameBufferHeight; }
                    if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y)
                        continue;

                    // Apply scissor/clipping rectangle
                    slag::Rectangle scissor;
                    scissor.offset.x = (int32_t)(clip_min.x);
                    scissor.offset.y = (int32_t)(clip_min.y);
                    scissor.extent.width = (uint32_t)(clip_max.x - clip_min.x);
                    scissor.extent.height = (uint32_t)(clip_max.y - clip_min.y);
                    commandBuffer->setScissors(scissor);


                    // Bind DescriptorSet with font or user texture
                    auto descriptorBundle = (slag::DescriptorBundle*)pcmd->GetTexID();
                    commandBuffer->bindGraphicsDescriptorBundle(shader,0,*descriptorBundle);
                    // Draw
                    commandBuffer->drawIndexed(pcmd->ElemCount,1,pcmd->IdxOffset+indexDrawOffset,pcmd->VtxOffset+vertexDrawOffset,0);
                }
            }
            indexDrawOffset += draw_list->IdxBuffer.Size;
            vertexDrawOffset += draw_list->VtxBuffer.Size;
        }

        platform_io.Renderer_RenderState = nullptr;

        slag::Rectangle scissor = { { 0, 0 }, { frameBufferWidth, frameBufferHeight } };
        commandBuffer->setScissors(scissor);
    }

}