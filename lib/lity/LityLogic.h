#pragma once

#include "Figure.h"
#include "LityConfig.h"
#include <memory>

class LityLogic {
    using FieldPointList = std::vector<FieldPoint>;
    using PointList      = std::vector<Point>;

    using IFigure       = std::shared_ptr<Figure>;
    using AnimationList = Figure::AnimationList;

public:
    AnimationList process(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight);
    void populateFields(const FieldsRaw& rawFields);

    const Fields& getFields() const;
    const Field& getFieldAt(const Point& point) const;
    const PointList& getUpdatedPoints() const;

private:
    Fields fields;
    PointList updatedPoints;

    FieldPoint makeFieldPoint(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight) const;

    void createAppearingAnimation(const Field& left, const Field& right, const Point& point, AnimationList& list) const;
    void createPaymentAnimations(const FieldPointList& left, const FieldPointList& right, AnimationList& list) const;

    void applyPayment(const FieldPointList& price);
    FieldPointList calculateFunds(const FieldPointList& price);

    void appendTo(PointList& pointList, const FieldPointList& appendable) const;
    void appendTo(PointList& pointList, const PointList& appendable) const;
    void appendTo(PointList& pointList, const Point& appendable) const;

    void removeDuplicates(PointList& list) const;

    IFigure findFigure(const Fields& fields, const FieldPoint& fieldPoint) const;
};
