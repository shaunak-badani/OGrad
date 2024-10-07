#include "output_metrics.h"


void OutputMetrics::setTimeTaken(double t_taken)
{
    this->time_taken = t_taken;
}

double OutputMetrics::getTimeTaken()
{
    return this->time_taken;
}