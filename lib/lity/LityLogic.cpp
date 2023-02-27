#include "LityLogic.h"
#include "AnimationFactory.h"
#include "Converter.h"
#include "CrossCalculator.h"
#include "Differ.h"
#include "FigureFactory.h"
#include <stdexcept>

void LityLogic::populateFields(const FieldsRaw& rawFields) {
    Converter::toFields(rawFields, fields);
}

auto LityLogic::process(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight) -> AnimationList {
    // Get field+point from difference between two raw fields lists
    const auto& fieldPoint = makeFieldPoint(fieldsLeft, fieldsRight);

    // This is reading from pulled up pin. Skip
    const auto& field = fieldPoint.first;
    if (field.isNone()) {
        return AnimationList();
    }

    const auto& figure = findFigure(fields, fieldPoint);
    if (!figure) {
        return AnimationList();
    }

    return figure->apply(fields, fieldPoint);


    //    // Store resulting field in fields list
    //    const auto fieldPrevious = fields[point.y][point.x];
    //    fields[point.y][point.x] = field;

    //    // Find middle point of crosses which appeared after fields list was updated
    //    auto crossMiddleList = CrossCalculator::find(fields, field, point);

    //    // Upgrade middle points of crosses
    //    CrossCalculator::upgrade(crossMiddleList, fields);

    //    // Get price to pay for upgrade
    //    const auto price = CrossCalculator::price(crossMiddleList, fields);
    //    // Pay for upgrades by darkening fields around middle point of cross
    //    applyPayment(price);

    //    // Funds are current fields before they become spent (black)
    //    const auto funds = calculateFunds(price);

    //    AnimationList animations;
    //    createPaymentAnimations(funds, price, animations);
    //    createAppearingAnimation(fieldPrevious, field, point, animations);

    //    // Generates list of points which got updated
    //    // Note that there could be duplicates
    //    updatedPoints.clear();
    //    appendTo(updatedPoints, price);
    //    appendTo(updatedPoints, crossMiddleList);
    //    appendTo(updatedPoints, point);

    //    return animations;
}

auto LityLogic::findFigure(const Fields& fields, const FieldPoint& fieldPoint) const -> IFigure {
    FigureFactory figureFactory;
    IFigure figure;

    figure = figureFactory.yield();
    while (figure) {
        if (figure->find(fields, fieldPoint)) {
            return figure;
        }
        figure = figureFactory.yield();
    }

    return figure;
}

//auto LityLogic::calculateFunds(const FieldPointList& price) -> FieldPointList {
//    FieldPointList funds;

//    for (const auto& fieldPoint : price) {
//        const auto& point = fieldPoint.second;
//        const auto& field = fields[point.y][point.x];

//        funds.push_back({ field, point });
//    }

//    return funds;
//}

//void LityLogic::applyPayment(const FieldPointList& price) {
//    for (const auto& fieldPoint : price) {
//        const auto& field        = fieldPoint.first;
//        const auto& point        = fieldPoint.second;
//        fields[point.y][point.x] = field;
//    }
//}

//void LityLogic::createPaymentAnimations(const FieldPointList& left, const FieldPointList& right, AnimationList& list) const {
//    // There should be equal amount of different fields. If it is not, something went wrong
//    if (left.size() != right.size()) {
//        return;
//    }

//    for (int i = 0; i < left.size(); i++) {
//        const auto& leftField  = left[i].first;
//        const auto& rightField = right[i].first;
//        const auto& point      = right[i].second;

//        list.push_back(AnimationFactory::Create(leftField, rightField, point, Animation::payment));
//    }
//}

//void LityLogic::createAppearingAnimation(const Field& left, const Field& right, const Point& point, AnimationList& list) const {
//    // Make sure that currently inputted field gets displayed if
//    // there were no crosses
//    if (list.empty()) {
//        list.push_back(AnimationFactory::Create(left, right, point, Animation::appearance));
//        return;
//    }

//    // If field has to appear in the middle of cross it should appear with appearance
//    // Note that fields that create cross by finishing it on side, are marked as payment
//    // fields
//    int counter = 0;
//    for (const auto& animation : list) {
//        if (animation->getPoint() != point) {
//            counter++;
//        }
//    }

//    if (counter == list.size()) {
//        list.push_back(AnimationFactory::Create(left, right, point, Animation::appearance));
//    }
//}

FieldPoint LityLogic::makeFieldPoint(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight) const {
   const auto idValuePair = Differ::diff(fieldsLeft, fieldsRight);

   const auto id    = idValuePair.first;
   const auto value = idValuePair.second;

   if (value == Differ::noDifference) {
       throw std::runtime_error("No difference between raw fields values!");
   }

   const auto& point = Converter::toFieldId(id);
   const auto& field = Field(value);

   return std::make_pair(field, point);
}

// const Fields& LityLogic::getFields() const {
//    return fields;
// }

// auto LityLogic::getUpdatedPoints() const -> const PointList& {
//    return updatedPoints;
// }

//void LityLogic::appendTo(PointList& pointList, const FieldPointList& appendable) const {
//    for (const auto& element : appendable) {
//        const auto& point = element.second;
//        appendTo(pointList, point);
//    }
//}

//void LityLogic::appendTo(PointList& pointList, const PointList& appendable) const {
//    pointList.insert(pointList.end(), appendable.begin(), appendable.end());
//}

//void LityLogic::appendTo(PointList& pointList, const Point& appendable) const {
//    pointList.push_back(appendable);
//}
