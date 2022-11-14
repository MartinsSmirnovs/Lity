#pragma once

#include "Animation.h"
#include "CrossCalculator.h"
#include "LityConfig.h"
#include <memory>

class LityLogic {
    using FieldPointList = CrossCalculator::FieldPointList;
    using PointList      = CrossCalculator::PointList;

    using IAnimation = std::shared_ptr<Animation>;

public:
    using AnimationList = std::vector<IAnimation>;

    AnimationList process(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight);
    void populateFields(const FieldsRaw& rawFields);

    const Fields& getFields() const;
    const PointList& getUpdatedPoints() const;

private:
    Fields fields;

    std::pair<int, Field> makeField(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight) const;

    void createAppearingAnimation(const Field& left, const Field& right, const Point& point, AnimationList& list) const;

    void createPaymentAnimations(const FieldPointList& left, const FieldPointList& right, AnimationList& list) const;

    void applyPayment(const FieldPointList& price);

    FieldPointList calculateFunds(const FieldPointList& price);

    PointList updatedPoints;
};
