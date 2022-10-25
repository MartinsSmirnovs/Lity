#include "LityLogic.h"
#include "Converter.h"
#include "CrossCalculator.h"
#include "Differ.h"

void LityLogic::populateFields(const FieldsRaw& rawFields) {
    Converter::toFields(rawFields, fields);
}

auto LityLogic::process(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight) -> const FieldPointList& {
    // Get field from difference between two raw fields lists
    const auto valueFieldPair = makeField(fieldsLeft, fieldsRight);

    const auto point = Converter::toFieldId(valueFieldPair.first);
    const auto field = valueFieldPair.second;

    // Store resulting field in fields list
    fields[point.y][point.x] = field;

    // Find middle point of crosses which appeared after fields list was updated
    auto crossMiddleList = CrossCalculator::find(fields, field, point);

    // Upgrade middle points of crosses
    CrossCalculator::upgrade(crossMiddleList, fields);

    // Pay for upgrades by darkening fields around middle point of cross
    CrossCalculator::pay(crossMiddleList, fields, resultList);

    // Make sure that at least currently inputted field gets displayed
    resultList.push_back({ field, point });

    return resultList;
}

std::pair<int, Field> LityLogic::makeField(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight) const {
    const auto idValuePair = Differ::diff(fieldsLeft, fieldsRight);

    const auto id    = idValuePair.first;
    const auto value = idValuePair.second;

    if (value == Differ::noDifference) {
        throw std::runtime_error("No difference between raw fields values!");
    }

    return std::pair<int, Field>(id, Field(value));
}
