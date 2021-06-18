#include <iostream>
#include <string>
using namespace std;

class TimeWindow
{
public:
    double *r0;    // R0 value at the end of time window
    float dist_param; // Movement range
    float m;          // Movement frequency
    double imm_frac;  // Immigration fraction at end of time window
    double hosp_rate;
    double icu_rate;
    double death_rate;
    double recov_hosp;
    int window_length; // Number of days in the time window

    TimeWindow *prev;
    TimeWindow *next;

    ///// Class functions

    // R0 functions
    float getMinR0(int index)
    {
        if (prev != NULL)
        {
            if (prev->r0[index] < r0[index])
            {
                return prev->r0[index];
            }
        }
        return r0[index];
    }

    float getMaxR0(int index)
    {
        if (prev != NULL)
        {
            if (prev->r0[index] < r0[index])
            {
                return r0[index];
            }
        }
        return prev->r0[index];
    }

    double getR0Slope(int index)
    {
        if ((window_length > 1) && (prev != NULL))
        {
            return (r0[index] - prev->r0[index]) / window_length;
        }
        return 0;
    }

    double getR0Intercept(int index, int t=0)
    {
        if (prev != NULL)
        {
            return prev->r0[index] - getR0Slope(index) * t;
        }
        return 0;
    }

    // dist_param functions
    float getMinDistParam()
    {
        if (prev != NULL)
        {
            if (prev->dist_param < dist_param)
            {
                return prev->dist_param;
            }
        }
        return dist_param;
    }

    float getMaxDistParam()
    {
        if (prev != NULL)
        {
            if (prev->dist_param < dist_param)
            {
                return dist_param;
            }
        }
        return prev->dist_param;
    }

    double getDistParamSlope()
    {
        if ((window_length > 1) && (prev != NULL))
        {
            return (dist_param - prev->dist_param) / window_length;
        }
        return 0;
    }

    double getDistParamIntercept(int t = 0)
    {
        if (prev != NULL)
        {
            return prev->dist_param - getDistParamSlope() * t;
        }
        return 0;
    }

    // m functions (movement frequency)
    float getMinM()
    {
        if (prev != NULL)
        {
            if (prev->m < m)
            {
                return prev->m;
            }
        }
        return m;
    }

    float getMaxM()
    {
        if (prev != NULL)
        {
            if (prev->m < m)
            {
                return m;
            }
        }
        return prev->m;
    }

    double getMSlope()
    {
        if ((window_length > 1) && (prev != NULL))
        {
            return (m - prev->m) / window_length;
        }
        return 0;
    }

    double getMIntercept(int t = 0)
    {
        if (prev != NULL)
        {
            return prev->m - getMSlope() * t;
        }
        return 0;
    }

    // imm_frac functions
    float getMinImmFrac()
    {
        if (prev != NULL)
        {
            if (prev->imm_frac < imm_frac)
            {
                return prev->imm_frac;
            }
        }
        return imm_frac;
    }

    float getMaxImmFrac()
    {
        if (prev != NULL)
        {
            if (prev->imm_frac < imm_frac)
            {
                return imm_frac;
            }
        }
        return prev->imm_frac;
    }

    double getImmFracSlope()
    {
        if ((window_length > 1) && (prev != NULL))
        {
            return (imm_frac - prev->imm_frac) / window_length;
        }
        return 0;
    }

    double getImmFracIntercept(int t = 0)
    {
        if (prev != NULL)
        {
            return prev->imm_frac - getImmFracSlope() * t;
        }
        return 0;
    }
    //
    // // hosp_rate functions
    // float getMinHospRate()
    // {
    //     if (prev != NULL)
    //     {
    //         if (prev->hosp_rate < hosp_rate)
    //         {
    //             return prev->hosp_rate;
    //         }
    //     }
    //     return hosp_rate;
    // }
    //
    // float getMaxHospRate()
    // {
    //     if (prev != NULL)
    //     {
    //         if (prev->hosp_rate < hosp_rate)
    //         {
    //             return hosp_rate;
    //         }
    //     }
    //     return prev->hosp_rate;
    // }
    //
    // double getHospRateSlope()
    // {
    //     if ((window_length > 1) && (prev != NULL))
    //     {
    //         return (hosp_rate - prev->hosp_rate) / window_length;
    //     }
    //     return 0;
    // }
    //
    // double getHospRateIntercept(int t=0)
    // {
    //     if (prev != NULL)
    //     {
    //         return prev->hosp_rate - getHospRateSlope() * t;
    //     }
    //     return 0;
    // }
    //
    // // icu_rate functions
    // float getMinIcuRate()
    // {
    //     if (prev != NULL)
    //     {
    //         if (prev->icu_rate < icu_rate)
    //         {
    //             return prev->icu_rate;
    //         }
    //     }
    //     return icu_rate;
    // }
    //
    // float getMaxIcuRate()
    // {
    //     if (prev != NULL)
    //     {
    //         if (prev->icu_rate < icu_rate)
    //         {
    //             return icu_rate;
    //         }
    //     }
    //     return prev->icu_rate;
    // }
    //
    // double getIcuRateSlope()
    // {
    //     if ((window_length > 1) && (prev != NULL))
    //     {
    //         return (icu_rate - prev->icu_rate) / window_length;
    //     }
    //     return 0;
    // }
    //
    // double getIcuRateIntercept(int t=0)
    // {
    //     if (prev != NULL)
    //     {
    //         return prev->icu_rate - getIcuRateSlope() * t;
    //     }
    //     return 0;
    // }
    //
    // // death_rate functions
    // float getMinDeathRate()
    // {
    //     if (prev != NULL)
    //     {
    //         if (prev->death_rate < death_rate)
    //         {
    //             return prev->death_rate;
    //         }
    //     }
    //     return death_rate;
    // }
    //
    // float getMaxDeathRate()
    // {
    //     if (prev != NULL)
    //     {
    //         if (prev->death_rate < death_rate)
    //         {
    //             return death_rate;
    //         }
    //     }
    //     return prev->death_rate;
    // }
    //
    // double getDeathRateSlope()
    // {
    //     if ((window_length > 1) && (prev != NULL))
    //     {
    //         return (death_rate - prev->death_rate) / window_length;
    //     }
    //     return 0;
    // }
    //
    // double getDeathRateIntercept(int t=0)
    // {
    //     if (prev != NULL)
    //     {
    //         return prev->death_rate - getDeathRateSlope() * t;
    //     }
    //     return 0;
    // }
    //
    // // recov_hosp functions
    // float getMinRecovHosp()
    // {
    //     if (prev != NULL)
    //     {
    //         if (prev->recov_hosp < recov_hosp)
    //         {
    //             return prev->recov_hosp;
    //         }
    //     }
    //     return recov_hosp;
    // }
    //
    // float getMaxRecovHosp()
    // {
    //     if (prev != NULL)
    //     {
    //         if (prev->recov_hosp < recov_hosp)
    //         {
    //             return recov_hosp;
    //         }
    //     }
    //     return prev->recov_hosp;
    // }
    //
    // double getRecovHospSlope()
    // {
    //     if ((window_length > 1) && (prev != NULL))
    //     {
    //         return (recov_hosp - prev->recov_hosp) / window_length;
    //     }
    //     return 0;
    // }
    //
    // double getRecovHospIntercept(int t=0)
    // {
    //     if (prev != NULL)
    //     {
    //         return prev->recov_hosp - getRecovHospSlope() * t;
    //     }
    //     return 0;
    // }
};

///// Globals
// NONE

///// Function Declarations
TimeWindow *addTimeWindow(TimeWindow *node, TimeWindow *new_node);
void clearTimeWindows(TimeWindow *node);
TimeWindow *importTimeWindowData(int n_pop,
                                 int total,
                                 double *r0,
                                 double *dist_param,
                                 double *m,
                                 double *imm_frac,
                                 double *hosp_rate,
                                 double *icu_rate,
                                 double *death_rate,
                                 double *recov_hosp,
                                 int *window_length);
