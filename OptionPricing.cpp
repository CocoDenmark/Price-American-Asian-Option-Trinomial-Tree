//
//  OptionPricing.cpp
//  Assignment9
//
//  Created by miao on 11/8/14.
//  Copyright (c) 2014 miao. All rights reserved.
//

#include "OptionPricing.h"
//this is the construction function
//all the attributes are initialized here using the input from the command line
OptionPricing::OptionPricing(float expiration_time, int no_of_divisions, float risk_free_rate, float volatility, float initial_stock_price, float strike_price)
{
    this->expiration_time = expiration_time;
    this->no_of_divisions = no_of_divisions;
    this->risk_free_rate = risk_free_rate;
    this->volatility = volatility;
    this->initial_stock_price = initial_stock_price;
    this->strike_price = strike_price;
    
    //the up factor and probability of the up-stay-down ways are calculated here
    up_factor = exp(volatility*sqrt(2*expiration_time/((float) no_of_divisions)));
    R = exp(risk_free_rate*expiration_time/((float) no_of_divisions));
    uptick_prob = pow((sqrt(R)-1/sqrt(up_factor))/(sqrt(up_factor)-1/sqrt(up_factor)), 2);
    downtick_prob = pow((sqrt(up_factor)-sqrt(R))/(sqrt(up_factor)-1/sqrt(up_factor)), 2);
    notick_prob = 1 - uptick_prob - downtick_prob;
}

//in display function, the pricing functions are called and all the information
//of the options is displayed here
void OptionPricing::display()
{
    cout << "Recursive Trinomial American-Asian Option Pricing" << endl;
    cout << "Expiration Time (Years) = " << expiration_time << endl;
    cout << "Number of Divisions = " << no_of_divisions << endl;
    cout << "Risk Free Interest Rate = " << risk_free_rate << endl;
    cout << "Volatility (%age of stock value) = " << volatility*100 << endl;
    cout << "Initial Stock Price = " << initial_stock_price << endl;
    cout << "Strike Price = " << strike_price << endl;
    cout << "--------------------------------------" << endl;
    cout << "Up Factor = " << up_factor << endl;
    cout << "Uptick Probability = " << uptick_prob << endl;
    cout << "Notick Probability = " << notick_prob << endl;
    cout << "Downtick Probability = " << downtick_prob << endl;
    cout << "--------------------------------------" << endl;
    float call_price = AmericanAsian_call_option(0, 0, initial_stock_price, initial_stock_price);
    cout << "Trinomail Price of an American-Asian Call Option = " << call_price << endl;
    float put_price = AmericanAsian_put_option(0, 0, initial_stock_price, initial_stock_price);
    cout << "Trinomail Price of an American-Asian Put Option = " << put_price << endl;
    cout << "--------------------------------------" << endl;

}

//the recursive function pricing the american-asian call option
//american-asian options uses the average price to compare with the strike price
float OptionPricing::AmericanAsian_call_option(int k, int i, float ave_stock_price, float current_price)
{
    if (k == no_of_divisions)
        return max((float)0.0, (ave_stock_price - strike_price));
    else
        return max(ave_stock_price-strike_price, (uptick_prob*AmericanAsian_call_option(k+1, i+1, (ave_stock_price*(k+1)+up_factor*current_price)/(k+2), up_factor*current_price) + notick_prob*AmericanAsian_call_option(k+1, i, (ave_stock_price*(k+1)+current_price)/(k+2), current_price) + downtick_prob*AmericanAsian_call_option(k+1, i-1, (ave_stock_price*(k+1)+current_price/up_factor)/(k+2), current_price/up_factor))/R);
}

//the recursive function pricing the american-asian put option
float OptionPricing::AmericanAsian_put_option(int k, int i, float ave_stock_price, float current_price)
{
    if (k == no_of_divisions)
        return max((float)0.0, (strike_price - ave_stock_price));
    else
        return max((strike_price - ave_stock_price), (uptick_prob*AmericanAsian_put_option(k+1, i+1, (ave_stock_price*(k+1)+up_factor*current_price)/(k+2), up_factor*current_price) + notick_prob*AmericanAsian_put_option(k+1, i, (ave_stock_price*(k+1)+current_price)/(k+2), current_price) + downtick_prob*AmericanAsian_put_option(k+1, i-1, (ave_stock_price*(k+1)+current_price/up_factor)/(k+2), current_price/up_factor))/R);

}



















