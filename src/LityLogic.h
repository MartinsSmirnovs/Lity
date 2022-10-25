#pragma once

#include "CrossCalculator.h"
#include "LityConfig.h"

class LityLogic {
    using FieldPointList = CrossCalculator::FieldPointList;
    using PointList      = CrossCalculator::PointList;

public:
    const FieldPointList& process(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight);
    void populateFields(const FieldsRaw& rawFields);

private:
    Fields fields;

    FieldPointList resultList;

    std::pair<int, Field> makeField(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight) const;
};
