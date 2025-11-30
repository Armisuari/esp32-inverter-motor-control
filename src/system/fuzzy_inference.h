#pragma once

#include <Fuzzy.h>

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
    FuzzySet *NB = new FuzzySet(0, 0, 0, 25);       // Negatif Besar
    FuzzySet *NK = new FuzzySet(0, 25, 25, 50);     // Negatif Kecil
    FuzzySet *Z = new FuzzySet(25, 50, 50, 75);     // Zero / 0
    FuzzySet *PK = new FuzzySet(50, 75, 75, 100);   // Positif Kecil
    FuzzySet *PB = new FuzzySet(75, 100, 100, 100); // Positif Besar

    // FuzzyInput (deltaError)
    FuzzyInput *dError = new FuzzyInput(2);
    FuzzySet *TC = new FuzzySet(-100, -100, -80, -40); // Turun Cepat
    FuzzySet *TL = new FuzzySet(-80, -40, -40, 0);     // Turun Lambat
    FuzzySet *S = new FuzzySet(-40, 0, 0, 40);         // Stabil
    FuzzySet *NL = new FuzzySet(0, 40, 40, 80);        // Naik Lambat
    FuzzySet *NC = new FuzzySet(40, 80, 100, 100);     // Naik Cepat

    // FuzzyOutput (frequency)
    FuzzyOutput *frequency = new FuzzyOutput(1);
    FuzzySet *KB = new FuzzySet(0, 0, 0, 25);       // Kurangi Banyak
    FuzzySet *KS = new FuzzySet(0, 25, 25, 50);     // Kurangi Sedikit
    FuzzySet *T = new FuzzySet(25, 50, 50, 75);     // Tidak Berubah
    FuzzySet *TS = new FuzzySet(50, 75, 75, 100);   // Tambah Sedikit
    FuzzySet *TB = new FuzzySet(75, 100, 100, 100); // Tambah Banyak

private:
    Fuzzy *_fuzzy = new Fuzzy();
};