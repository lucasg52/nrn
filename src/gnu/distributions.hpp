#pragma once

#include <random>
class NrnRandom123;

class Distribution {
    public:
        virtual ~Distribution() = default;
        virtual double operator()(NrnRandom123* rng) = 0;
};

class Uniform: public Distribution {
    public:
        Uniform(double a, double b)
            : d(a, b)
        {}

        double operator()(NrnRandom123* rng) override {
            return d(*rng);
        }

    private:
        std::uniform_real_distribution<double> d;
};

class DiscreteUniform: public Distribution {
    public:
        DiscreteUniform(long a, long b)
            : d(a, b)
        {}

        double operator()(NrnRandom123* rng) override {
            return d(rng);
        }

    private:
        std::uniform_int_distribution<long> d;
};

class Normal: public Distribution {
    public:
        Normal(double mean, double stddev)
            : d(mean, stddev)
        {}

        double operator()(NrnRandom123* rng) override {
            return d(rng);
        }

    private:
        std::normal_distribution<double> d;
};

class LogNormal: public Distribution {
    public:
        LogNormal(double mean, double stddev)
            : d(mean, stddev)
        {}

        double operator()(NrnRandom123* rng) override {
            return d(rng);
        }

    private:
        std::lognormal_distribution<double> d;
};

class Poisson: public Distribution {
    public:
        Poisson(double mean)
            : d(mean)
        {}

        double operator()(NrnRandom123* rng) override {
            return d(rng);
        }

    private:
        std::poisson_distribution<int> d;
};

class Binomial: public Distribution {
    public:
        Binomial(int t, double p)
            : d(t, p)
        {}

        double operator()(NrnRandom123* rng) override {
            return d(rng);
        }

    private:
        std::binomial_distribution<int> d;
};

class Geometric: public Distribution {
    public:
        Geometric(double mean)
            : d(mean)
        {}

        double operator()(NrnRandom123* rng) override {
            return d(rng);
        }

    private:
        std::geometric_distribution<int> d;
};

class NegExp: public Distribution {
    public:
        NegExp(double xmean)
            : d(1 / xmean)
        {}

        double operator()(NrnRandom123* rng) override {
            return d(rng);
        }

    private:
        std::exponential_distribution<> d;
};

class Weibull: public Distribution {
    public:
        Weibull(double alpha, double beta)
            : d(alpha, beta)
        {}

        double operator()(NrnRandom123* rng) override {
            return d(rng);
        }

    private:
        std::weibull_distribution<> d;
};
