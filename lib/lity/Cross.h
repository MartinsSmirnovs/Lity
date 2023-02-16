#pragma once

#include "Figure.h"

class Cross : public Figure {
public:
    Cross();
    bool find(const Fields& fields, const FieldPoint& fieldPoint) const override;
    AnimationList apply(Fields& fields, const FieldPoint& fieldPoint) const override;

private:
    Description2 description;

    bool checkColorMask(const Fields& fields, const FieldPoint& fieldPoint) const;
    bool checkBuildingMask(const Fields& fields, const FieldPoint& fieldPoint) const;
    void applyPaymentMask(Fields& fields, const FieldPoint& fieldPoint) const;
    void applyUpgradeMask(Fields& fields, const FieldPoint& fieldPoint) const;
    AnimationList createAnimationList(const FieldPoint& fieldPoint) const;
};
