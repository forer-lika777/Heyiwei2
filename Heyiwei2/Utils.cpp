#include "pch.h"
#include "Utils.h"
double Utils::calculateTotalWaterFee(double waterUsage, double unitPrice)
{
	return waterUsage * unitPrice;
}
