#pragma once

// Helper to declare fuzzy ranges.
#define FUZZY_RANGE(NAME, A, B, C, D)                 \
    struct NAME                                       \
    {                                                 \
        static constexpr int a = (A);                 \
        static constexpr int b = (B);                 \
        static constexpr int c = (C);                 \
        static constexpr int d = (D);                 \
        static_assert(a <= b && b <= c && c <= d,     \
                      "Invalid ordering for " #NAME); \
    }

// Encoder fuzzy sets
FUZZY_RANGE(encoder_negatif_besar, 0, 0, 0, 25);
FUZZY_RANGE(encoder_negatif_kecil, 0, 25, 25, 50);
FUZZY_RANGE(encoder_zero, 25, 50, 50, 75);
FUZZY_RANGE(encoder_positif_kecil, 50, 75, 75, 100);
FUZZY_RANGE(encoder_positif_besar, 75, 100, 100, 100);

// Delta error fuzzy sets
FUZZY_RANGE(deltaerror_turun_cepat, -100, -100, -80, -40);
FUZZY_RANGE(deltaerror_turun_lambat, -80, -40, -40, 0);
FUZZY_RANGE(deltaerror_stabil, -40, 0, 0, 40);
FUZZY_RANGE(deltaerror_naik_lambat, 0, 40, 40, 80);
FUZZY_RANGE(deltaerror_naik_cepat, 40, 80, 100, 100);

// Frequency (output) fuzzy sets
FUZZY_RANGE(frequency_kurangi_banyak, 0, 0, 0, 25);
FUZZY_RANGE(frequency_kurangi_sedikit, 0, 25, 25, 50);
FUZZY_RANGE(frequency_tidak_berubah, 25, 50, 50, 75);
FUZZY_RANGE(frequency_tambah_sedikit, 50, 75, 75, 100);
FUZZY_RANGE(frequency_tambah_banyak, 75, 100, 100, 100);

// Undefine helper to avoid leaking macro into other translation units.
#undef FUZZY_RANGE