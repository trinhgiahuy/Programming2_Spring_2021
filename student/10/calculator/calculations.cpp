// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}
double exponential_func(double left , double right){

    double result = 1;
    if(right==0){
        return 1;
    }
    else
    {
        int i = 0;
        while (i != right)
        {
            result = result * left;
            i++;
        }
        return result;
    }
}

