#ifndef OUTPUT_METRICS_H
#define OUTPUT_METRICS_H


class OutputMetrics
{
    private:
        double time_taken;
        
    public:
        void setTimeTaken(double t_taken);

        double getTimeTaken();
};


#endif