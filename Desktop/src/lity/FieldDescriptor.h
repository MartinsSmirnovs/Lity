#pragma once

#include <QString>
#include <lity/RGB.h>
#include <vector>

struct FieldDescriptor
{
    QString text;
    int id;
    RGB color;
};

using FieldDescriptorList = std::vector< FieldDescriptor >;
