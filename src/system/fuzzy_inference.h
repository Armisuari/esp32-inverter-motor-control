#pragma once

#include <Fuzzy.h>
#include "fuzzy_rule_config.h"

class FuzzyInference
{
public:
    void setup();
    bool setInput(int fuzzyInputIndex, float crispValue);
    bool fuzzify();
    float defuzzify(int fuzzyOutputIndex);
    float getPertinence();

    // FuzzyInput (encoder)
    FuzzyInput *encoder = new FuzzyInput(1);
    FuzzySet *NB = new FuzzySet(encoder_negatif_besar::a, encoder_negatif_besar::b, encoder_negatif_besar::c, encoder_negatif_besar::d); // Negatif Besar
    FuzzySet *NK = new FuzzySet(encoder_negatif_kecil::a, encoder_negatif_kecil::b, encoder_negatif_kecil::c, encoder_negatif_kecil::d); // Negatif Kecil
    FuzzySet *Z = new FuzzySet(encoder_zero::a, encoder_zero::b, encoder_zero::c, encoder_zero::d);                                      // Zero / 0
    FuzzySet *PK = new FuzzySet(encoder_positif_kecil::a, encoder_positif_kecil::b, encoder_positif_kecil::c, encoder_positif_kecil::d); // Positif Kecil
    FuzzySet *PB = new FuzzySet(encoder_positif_besar::a, encoder_positif_besar::b, encoder_positif_besar::c, encoder_positif_besar::d); // Positif Besar

    // FuzzyInput (deltaerror)
    FuzzyInput *deltaerror = new FuzzyInput(2);
    FuzzySet *TC = new FuzzySet(deltaerror_turun_cepat::a, deltaerror_turun_cepat::b, deltaerror_turun_cepat::c, deltaerror_turun_cepat::d);     // Turun Cepat
    FuzzySet *TL = new FuzzySet(deltaerror_turun_lambat::a, deltaerror_turun_lambat::b, deltaerror_turun_lambat::c, deltaerror_turun_lambat::d); // Turun Lambat
    FuzzySet *S = new FuzzySet(deltaerror_stabil::a, deltaerror_stabil::b, deltaerror_stabil::c, deltaerror_stabil::d);                          // Stabil
    FuzzySet *NL = new FuzzySet(deltaerror_naik_lambat::a, deltaerror_naik_lambat::b, deltaerror_naik_lambat::c, deltaerror_naik_lambat::d);     // Naik Lambat
    FuzzySet *NC = new FuzzySet(deltaerror_naik_cepat::a, deltaerror_naik_cepat::b, deltaerror_naik_cepat::c, deltaerror_naik_cepat::d);         // Naik Cepat

    // FuzzyOutput (frequency)
    FuzzyOutput *frequency = new FuzzyOutput(1);
    FuzzySet *KB = new FuzzySet(frequency_kurangi_banyak::a, frequency_kurangi_banyak::b, frequency_kurangi_banyak::c, frequency_kurangi_banyak::d);     // Kurangi Banyak
    FuzzySet *KS = new FuzzySet(frequency_kurangi_sedikit::a, frequency_kurangi_sedikit::b, frequency_kurangi_sedikit::c, frequency_kurangi_sedikit::d); // Kurangi Sedikit
    FuzzySet *T = new FuzzySet(frequency_tidak_berubah::a, frequency_tidak_berubah::b, frequency_tidak_berubah::c, frequency_tidak_berubah::d);          // Tidak Berubah
    FuzzySet *TS = new FuzzySet(frequency_tambah_sedikit::a, frequency_tambah_sedikit::b, frequency_tambah_sedikit::c, frequency_tambah_sedikit::d);     // Tambah Sedikit
    FuzzySet *TB = new FuzzySet(frequency_tambah_banyak::a, frequency_tambah_banyak::b, frequency_tambah_banyak::c, frequency_tambah_banyak::d);         // Tambah Banyak

private:
    Fuzzy *_fuzzy = new Fuzzy();
};