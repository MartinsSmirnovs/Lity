#pragma once

#include "LityConfig.h"
#include "LityLogic.h"

class LityManager
{
public:
    void setup();
    void run();

private:
    LityLogic logic;

    FieldsRaw rawFields;
    FieldsRaw rawFieldsPrevious;

    Fields fields;

    void updatePreviousFields();

    void doAnimations( const Fields& fieldsTarget, const Figure::AnimationList& animationList );
};
