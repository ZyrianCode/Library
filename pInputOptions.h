#pragma once

template<class T>
class InputOptions
{
    virtual T Input(T value) = 0;
    //virtual T Input(T value...) = 0;
};

