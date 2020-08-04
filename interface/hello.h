#ifndef _HELLO_H_
#define _HELLO_H_

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <TFile.h>
#include <TH2D.h>
#include <TRandom3.h>
#include <TString.h>

void test_run();

class retrieve_scale_factor{
    public:
        retrieve_scale_factor();
        ~retrieve_scale_factor();

        void set_type_sys_uncertainty(TString);
        void set_cvsl_cvsb(double, double);
        void convert_disciminants_into_bin_numbers();
        double get_scale_factor(TString, double, double);
        void debug_mode();

        void init_raw_histogram(TString);
        void print_th2d_content(TString);
        void print_th2d_difference(TString);
        void accumulate_th2d_uncertainty(TString);
        void print_overall_uncertainty();

    private:
        TFile *file;
        TH2D *h;
        TH2D *h_raw; //to keep the SFs w/o any systmatic source
        TH2D *h_rec; //to record the uncertainties in quadratic sum
        int bin_cvsl;
        int bin_cvsb;
        double scale_factor;

        TString type_sys_uncertainty;
        double cvsl;
        double cvsb;

        bool debug_;
};

#endif
