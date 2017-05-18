//
//  OptionPricing.h
//  Assignment9
//
//  Created by miao on 11/8/14.
//  Copyright (c) 2014 miao. All rights reserved.
//

#ifndef __Assignment9__OptionPricing__
#define __Assignment9__OptionPricing__

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

class OptionPricing
{
private:
    float up_factor, uptick_prob, notick_prob, downtick_prob, risk_free_rate, strike_price;
    float initial_stock_price, expiration_time, volatility, R;
    int no_of_divisions;
public:
    OptionPricing(float expiration_time, int no_of_divisions, float risk_free_rate, float volatility, float initial_stock_price, float strike_price);
    void display();
    float AmericanAsian_call_option(int k, int i, float ave_stock_price, float current_price);
    float AmericanAsian_put_option(int k, int i, float ave_stock_price, float current_price);
};



#endif /* defined(__Assignment9__OptionPricing__) */
