#include <stdio.h>
#include <stdlib.h>


struct _retire_info
{
    int months;
    double contribution;
    double expenditure;
    double rate_of_return;
};

typedef struct _retire_info retire_info;


double compute_savings(double savings, double expenditure, double contribution, double rate)
{
    // We first compute rate of return
    savings += savings * rate;

    // Then we add the monthly contribution and subtract the expenditure
    savings += contribution - expenditure;

    return savings;
}

void retirement(int startAge,        // in months
                double initial,      // initial savings in dollars
                retire_info working, // info about working
                retire_info retired) // info about being retired
{

    double savings = initial;
    int months = startAge;
    for (int i = 0; i < working.months; i++)
    {
        // print the status when the starting of a month
        printf("Age %3d month %2d you have $%.2f\n", (int) (months / 12), months % 12, savings);

        // caculate the changes
        savings = compute_savings(savings, working.expenditure, working.contribution, working.rate_of_return);
        months++;
    }


    for (int i = 0; i < retired.months; i++)
    {
        printf("Age %3d month %2d you have $%.2f\n", (int) (months / 12), months % 12, savings);
        savings = compute_savings(savings, retired.expenditure, retired.contribution, retired.rate_of_return);
        months++;
    }
}

int main(void)
{
    retire_info working;
    retire_info retired;

    working.months = 489;
    working.contribution = 1000;
    working.expenditure = 0;
    working.rate_of_return = 0.045 / 12;

    retired.months = 384;
    retired.contribution = 0;
    retired.expenditure = 4000;
    retired.rate_of_return = 0.01 / 12;

    retirement(327, 21345, working, retired);

    return 0;
}
