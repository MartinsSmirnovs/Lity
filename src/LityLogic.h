#pragma once

#include "Animation.h"
#include "CrossCalculator.h"
#include "LityConfig.h"
#include <memory>

class LityLogic {
    using FieldPointList = CrossCalculator::FieldPointList;
    using PointList      = CrossCalculator::PointList;

    using OldNewFieldPoint     = std::pair<CrossCalculator::FieldPoint, CrossCalculator::FieldPoint>;
    using OldNewFieldPointList = std::vector<OldNewFieldPoint>;

    using IAnimation = std::shared_ptr<Animation>;

public:
    using AnimationList = std::vector<IAnimation>;

    AnimationList process(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight);
    void populateFields(const FieldsRaw& rawFields);

private:
    Fields fields;

    FieldPointList resultList;

    std::pair<int, Field> makeField(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight) const;

    void contemplateAnimations(const Field& left, const Field& right, const Point& point, AnimationList& list);

    AnimationList createPaymentAnimations(const FieldPointList& left, const FieldPointList& right) const;

    void applyPayment(const FieldPointList& price);

    FieldPointList calculateFunds(const FieldPointList& price);
};
